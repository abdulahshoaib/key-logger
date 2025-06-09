#include <fcntl.h>
#include <linux/input-event-codes.h>
#include <linux/input.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const char *keycode_map[256] = {
    [KEY_A] = "a",           [KEY_B] = "b",           [KEY_C] = "c",
    [KEY_D] = "d",           [KEY_E] = "e",           [KEY_F] = "f",
    [KEY_G] = "g",           [KEY_H] = "h",           [KEY_I] = "i",
    [KEY_J] = "j",           [KEY_K] = "k",           [KEY_L] = "l",
    [KEY_M] = "m",           [KEY_N] = "n",           [KEY_O] = "o",
    [KEY_P] = "p",           [KEY_Q] = "q",           [KEY_R] = "r",
    [KEY_S] = "s",           [KEY_T] = "t",           [KEY_U] = "u",
    [KEY_V] = "v",           [KEY_W] = "w",           [KEY_X] = "x",
    [KEY_Y] = "y",           [KEY_Z] = "z",           [KEY_1] = "1",
    [KEY_2] = "2",           [KEY_3] = "3",           [KEY_4] = "4",
    [KEY_5] = "5",           [KEY_6] = "6",           [KEY_7] = "7",
    [KEY_8] = "8",           [KEY_9] = "9",           [KEY_0] = "0",
    [KEY_SPACE] = " ",       [KEY_ENTER] = "⏎",       [KEY_DOT] = ".",
    [KEY_COMMA] = ",",       [KEY_BACKSPACE] = "⌫",   [KEY_TAB] = "⇥",
    [KEY_MINUS] = "-",       [KEY_EQUAL] = "=",       [KEY_SLASH] = "/",
    [KEY_SEMICOLON] = ";",   [KEY_APOSTROPHE] = "'",  [KEY_LEFTBRACE] = "[",
    [KEY_RIGHTBRACE] = "]",  [KEY_GRAVE] = "`",       [KEY_LEFTSHIFT] = "⇧",
    [KEY_RIGHTSHIFT] = "⇧",  [KEY_LEFTALT] = "[ALT]", [KEY_RIGHTALT] = "[ALT]",
    [KEY_NUMLOCK] = "⇭",     [KEY_SCROLLLOCK] = "⤓",  [KEY_INSERT] = "Ins",
    [KEY_DELETE] = "⌦",      [KEY_MUTE] = "🔇",       [KEY_VOLUMEDOWN] = "Vol-",
    [KEY_VOLUMEUP] = "Vol+", [KEY_RIGHTCTRL] = "^",   [KEY_LEFTCTRL] = "^",
    [KEY_HOME] = "Home",     [KEY_END] = "End",       [KEY_UP] = "↑",
    [KEY_DOWN] = "↓",        [KEY_LEFT] = "←",        [KEY_RIGHT] = "→",
    [KEY_PAGEUP] = "⇞",      [KEY_PAGEDOWN] = "⇟",    [KEY_CAPSLOCK] = "⇪",
    [KEY_BACKSLASH] = "\\",  [KEY_102ND] = "<",       [KEY_ESC] = "Esc",
    [KEY_LEFTMETA] = "⊞",
};

int main(void) {
  int fd = open("/dev/input/event3", O_RDONLY);

  if (fd < 0) {
    perror("open");
    return EXIT_FAILURE;
  }

  struct input_event event;

  while (1) {
    read(fd, &event, sizeof(struct input_event));
    if (event.type == EV_KEY && event.value == 1) {
      const char *key = keycode_map[event.code];
      printf("%s ", key);
      fflush(stdout);
    }
  }

  return EXIT_SUCCESS;
}
