#!/bin/bash

set -e

BIN_NAME="keylogger"
BIN_DIR="/usr/local/bin"
SRC_FILE="logger.c"

echo "[*] Select your platform:"
echo "1) Arch"
echo "2) Debian/Ubuntu"
echo "3) CentOS/Fedora/RHEL"
echo "4) Other"
read -rp "Enter number: " platform

case $platform in
  1)
    echo "[*] Installing dependencies with pacman..."
    sudo pacman -Sy --needed sdl2 sdl2_ttf ttf-fira-code base-devel
    ;;
  2)
    echo "[*] Installing dependencies with apt..."
    sudo apt update
    sudo apt install -y libsdl2-dev libsdl2-ttf-dev fonts-firacode build-essential
    ;;
  3)
    echo "[*] Installing dependencies with dnf..."
    sudo dnf install -y SDL2-devel SDL2_ttf-devel fira-code-fonts gcc make
    ;;
  4)
    echo "[-] Manual install required. Install SDL2, SDL2_ttf, FiraCode font, and build tools."
    exit 1
    ;;
  *)
    echo "Invalid option."
    exit 1
    ;;
esac

echo "Checking FiraCodeNerdFont-Medium Availability"
FIRA_PATH="/usr/share/fonts/TTF/FiraCodeNerdFont-Medium.ttf"
if [[ ! -f "$FIRA_PATH" ]]; then
  echo "[*] FiraCode Nerd Font not found, downloading..."
  mkdir -p ~/.local/share/fonts
  curl -LO https://github.com/ryanoasis/nerd-fonts/releases/download/v3.1.1/FiraCode.zip
  unzip -o FiraCode.zip -d ~/.local/share/fonts
  fc-cache -f
  rm FiraCode.zip
fi

echo "[*] Compiling source..."
mkdir -p "$BIN_DIR"
sudo gcc "$SRC_FILE" -o "$BIN_DIR/$BIN_NAME" -lSDL2 -lSDL2_ttf

if ! echo "$PATH" | grep -q "$BIN_DIR"; then
  echo "export PATH=\"$BIN_DIR:\$PATH\"" >> ~/.bashrc
  echo "export PATH=\"$BIN_DIR:\$PATH\"" >> ~/.zshrc
  echo "[*] Added $BIN_DIR to PATH (bashrc/zshrc)."
fi

echo "[*] Granting input read capability..."
sudo setcap cap_dac_read_search+ep "$BIN_DIR/$BIN_NAME"

echo "[✓] Installed: $BIN_DIR/$BIN_NAME"
