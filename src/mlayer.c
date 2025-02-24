#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

const char *options[] = {"recite", "spell", "change words list"};
int num_options = sizeof(options) / sizeof(options[0]);
int mlayer_index = 0;

extern int get_terminal_width();

// print function selection
void print_centered(const char *text) {
  int terminal_width = get_terminal_width();
  int text_length = strlen(text);
  int left_padding = (terminal_width - text_length) / 2;
  for (int i = 0; i < left_padding; i++) {
    printf(" ");
  }
  printf("%s\n", text);
}

void print_selected(const char *text) {
  int terminal_width = get_terminal_width();
  int text_length = strlen(text);
  int left_padding = (terminal_width - text_length) / 2;
  for (int i = 1; i < left_padding; i++) {
    printf(" ");
  }
  printf(">%s\n", text);
}
