# Key Logger

A simple Linux keylogger that captures and displays keystrokes
in real-time using SDL2. It logs keys from the moment it's started
and displays them in a small on-screen window.

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
    - [Running](#running-the-keylogger)
    - [Exiting](#exiting)
    - [Building](#making)
- [Symbols](#symbols-against-keys)

# Installation
Run the install script and select your platform when prompted. It will
install required dependencies and compile the binary.

```bash
sudo ./install.sh
````

# Usage

## Run the keylogger
```bash
keylogger
```

## Exiting
When the program is running use
```
Alt + Esc
```
this will exit the keylogger

## Making
You can also build and install manually using **make**
```bash
make                # Compile
sudo make run       # Compile and run
make clean          # Remove compiled binary
```

# Symbols against Keys

|     Key     | Symbol |
| ----------- | ------ |
| SPACE       |    ␣   |
| ENTER       |    ↲   |
| BACKSPACE   |    ⌫   |
| TAB         |    ⇥   |
| SHIFT       |    ⇧   |
| ALT         |    ⎇   |
| CTRL        |    ^   |
| INSERT      |    ↙   |
| DELETE      |    ⌦   |
| HOME        |    ↖   |
| END         |    ↘   |
| UP          |    ↑   |
| DOWN        |    ↓   |
| LEFT        |    ←   |
| RIGHT       |    →   |
| PAGEUP      |    ⇞   |
| PAGEDOWN    |    ⇟   |
| CAPSLOCK    |    ⇪   |
| NUM-LOCK    |    ⇭   |
| SCROLL-LOCK |    ⤓   |
| ESC         |    ⎋   |
| SUPER-KEY   |    ⌘   |

