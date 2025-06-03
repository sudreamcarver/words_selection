#include "mlayer.h"
#include <asm-generic/ioctls.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#define clearscreen printf("\033[2J\033[H");

extern int num_options;
extern int mlayer_index;

// for store original terminal information
struct termios original_termios;

// set terminal as buffering mode (the original mode)
void DisableRawMode() { tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios); }

// set terminal as raw mode (the work mode)
void EnableRawMode() {
  // get the original setting of terminal
  tcgetattr(STDIN_FILENO, &original_termios);
  atexit(DisableRawMode);

  struct termios raw =
      original_termios; // Create a new termios structure, raw, and initialize
                        // it to the original Settings.
  raw.c_lflag &= ~(ICANON | ECHO);

  // set terminal to raw mode
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

// print title
void print_figlet(void) {
  FILE *fp;
  char path[1035];

  fp = popen("figlet -t -c -f slant words_selection", "r");
  if (fp == NULL) {
    perror("Failed to run figlet.\ninstall figlet?");
    exit(EXIT_FAILURE);
  }

  while (fgets(path, sizeof(path), fp) != NULL) {
    printf("%s", path);
  }
  pclose(fp);
}

int get_terminal_width() {
  struct winsize w; // winsize form ioctl.h
                    // STDOUT_FILENO form unistd.h
                    // Usually -1 indicates error of get winsize
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
    perror("ioctl");
    exit(EXIT_FAILURE);
  }
  return w.ws_col;
}

void screen_flash() {
  clearscreen print_figlet();
  if (mlayer_index == 0) {
    print_selected("recite");
    print_centered("spell");
    print_centered("change words list");
  } else if (mlayer_index == 1) {
    print_centered("recite");
    print_selected("spell");
    print_centered("change words list");
  } else if (mlayer_index == 2) {
    print_centered("recite");
    print_centered("spell");
    print_selected("change words list");
  }
}

int main() {

  screen_flash();

  // clear screen
  EnableRawMode();

  while (1) {

    char K = getchar();

    switch (K) {
    case 'j':
      if (mlayer_index < num_options - 1)
        mlayer_index++;
      screen_flash();
      break;
    case 'k':
      if (mlayer_index > 0)
        mlayer_index--;
      screen_flash();
      break;
    case 'q':
      goto exit_loop;
    case '\n':
      while (1) {
        switch (mlayer_index) {
        case 0:
          clearscreen print_centered("recite");
        case 1:
          clearscreen print_centered("spell");
        case 2:
          clearscreen print_centered("change words list");
        }
      default:
        break;
      }
    }
  }

exit_loop:
  DisableRawMode();
  return 0;
}
