#include <SDL2/SDL.h>

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include <fcntl.h>
#include <linux/input-event-codes.h>
#include <linux/input.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_KEYS 9

const char *keycodeMap[256] = {
    [KEY_A] = "a",          [KEY_B] = "b",          [KEY_C] = "c",
    [KEY_D] = "d",          [KEY_E] = "e",          [KEY_F] = "f",
    [KEY_G] = "g",          [KEY_H] = "h",          [KEY_I] = "i",
    [KEY_J] = "j",          [KEY_K] = "k",          [KEY_L] = "l",
    [KEY_M] = "m",          [KEY_N] = "n",          [KEY_O] = "o",
    [KEY_P] = "p",          [KEY_Q] = "q",          [KEY_R] = "r",
    [KEY_S] = "s",          [KEY_T] = "t",          [KEY_U] = "u",
    [KEY_V] = "v",          [KEY_W] = "w",          [KEY_X] = "x",
    [KEY_Y] = "y",          [KEY_Z] = "z",          [KEY_1] = "1",
    [KEY_2] = "2",          [KEY_3] = "3",          [KEY_4] = "4",
    [KEY_5] = "5",          [KEY_6] = "6",          [KEY_7] = "7",
    [KEY_8] = "8",          [KEY_9] = "9",          [KEY_0] = "0",
    [KEY_SPACE] = "␣",      [KEY_ENTER] = "↲",      [KEY_DOT] = ".",
    [KEY_COMMA] = ",",      [KEY_BACKSPACE] = "⌫",  [KEY_TAB] = "⇥",
    [KEY_MINUS] = "-",      [KEY_EQUAL] = "=",      [KEY_SLASH] = "/",
    [KEY_SEMICOLON] = ";",  [KEY_APOSTROPHE] = "'", [KEY_LEFTBRACE] = "[",
    [KEY_RIGHTBRACE] = "]", [KEY_GRAVE] = "`",      [KEY_LEFTSHIFT] = "⇧",
    [KEY_RIGHTSHIFT] = "⇧", [KEY_LEFTALT] = "⎇",    [KEY_RIGHTALT] = "⎇",
    [KEY_NUMLOCK] = "⇭",    [KEY_SCROLLLOCK] = "⤓", [KEY_INSERT] = "↙",
    [KEY_DELETE] = "⌦",     [KEY_RIGHTCTRL] = "^",  [KEY_LEFTCTRL] = "^",
    [KEY_HOME] = "↖",       [KEY_END] = "↘",        [KEY_UP] = "↑",
    [KEY_DOWN] = "↓",       [KEY_LEFT] = "←",       [KEY_RIGHT] = "→",
    [KEY_PAGEUP] = "⇞",     [KEY_PAGEDOWN] = "⇟",   [KEY_CAPSLOCK] = "⇪",
    [KEY_BACKSLASH] = "\\", [KEY_102ND] = "<",      [KEY_ESC] = "⎋ ",
    [KEY_LEFTMETA] = "⌘",
};

int main(void) {
  int fd = open("/dev/input/event3", O_RDONLY);

  char keyBuffer[MAX_KEYS][32];
  int keyCount = 0;

  if (fd < 0) {
    perror("open");
    return EXIT_FAILURE;
  }

  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();

  SDL_DisplayMode mode;
  SDL_GetCurrentDisplayMode(0, &mode);

  int win_w = 300;
  int win_h = 200;

  int x = mode.w - win_w;
  int y = mode.h - win_h;

  SDL_Window *win =
      SDL_CreateWindow("keylogger", x, y, 200, 50, SDL_WINDOW_SHOWN);

  int r = 48;
  int g = 48;
  int b = 48;
  int a = 255;

  SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
  SDL_SetRenderDrawColor(ren, r, g, b, a);
  SDL_RenderClear(ren);
  SDL_RenderPresent(ren);

  TTF_Font *font =
      TTF_OpenFont("/usr/share/fonts/TTF/FiraCodeNerdFont-Medium.ttf", 24);

  if (!font) {
    fprintf(stderr, "TTF font load failed\n");
    return EXIT_FAILURE;
  }

  struct input_event event;
  SDL_Event sdl_event;
  char currentKey[64] = "";

  while (1) {
    SDL_SetWindowPosition(win, x, y);

    while (SDL_PollEvent(&sdl_event)) {

      /* Exit */
      if (sdl_event.type == SDL_KEYDOWN) {
        const SDL_Keycode key = sdl_event.key.keysym.sym;
        const SDL_Keymod mod = SDL_GetModState();

        if (key == SDLK_ESCAPE && (mod & KMOD_ALT))
          goto cleanup;
      }
    }

    /* read the input */
    if (read(fd, &event, sizeof(event)) == sizeof(event)) {
      if (event.type == EV_KEY && event.value == 1) {
        const char *k = keycodeMap[event.code];
        if (k) {
          if (keyCount == MAX_KEYS) {
            for (int i = 1; i < MAX_KEYS; i++) {
              strcpy(keyBuffer[i - 1], keyBuffer[i]);
            }
            keyCount = MAX_KEYS - 1;
          }
          snprintf(keyBuffer[keyCount], sizeof(keyBuffer[0]), "%s", k);
          keyCount++;

          SDL_Color white = {255, 255, 255};

          SDL_SetRenderDrawColor(ren, r, g, b, a);
          SDL_RenderClear(ren);

          int x_offset = 4;

          for (int i = 0; i < keyCount; i++) {
            SDL_Surface *surf =
                TTF_RenderUTF8_Blended(font, keyBuffer[i], white);
            SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, surf);

            SDL_Rect dst = {x_offset, 5, surf->w, surf->h};
            SDL_RenderCopy(ren, tex, NULL, &dst);
            x_offset += surf->w + 5;

            SDL_FreeSurface(surf);
            SDL_DestroyTexture(tex);
          }

          SDL_RenderPresent(ren);
        }
      }
    }
  }

cleanup:
  TTF_CloseFont(font);
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  TTF_Quit();
  SDL_Quit();
  close(fd);
  return 0;

  return EXIT_SUCCESS;
}
