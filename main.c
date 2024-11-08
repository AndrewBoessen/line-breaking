#include "line_break.h"
#include <stdio.h>
#include <stdlib.h>

// Helper function to check if a value is in an array
int is_in_array(int value, int *array, int array_size) {
  for (int i = 0; i < array_size; i++) {
    if (array[i] == value) {
      return 1; // Value found in the array
    }
  }
  return 0; // Value not found in the array
}
void print_formatted_text(char **strings, int *breaks, int num_strings,
                          int line_length) {
  printf("\nFormatted text with line length %d:\n", line_length);
  printf("----------------------------------------\n");

  for (int i = 0; i < num_strings; i++) {
    printf("%s", strings[i]);

    // If this position is a break point, print newline
    // Print new line if i+1 in breaks
    if (is_in_array(i + 1, breaks, num_strings)) {
      printf("\n");
    } else {
      printf(" "); // Print space between words
    }
  }
  printf("\n----------------------------------------\n");
}

void free_string_array(char **strings, int num_strings) {
  for (int i = 0; i < num_strings; i++) {
    free(strings[i]);
  }
  free(strings);
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: %s <input_file> <line_length>\n", argv[0]);
    return 1;
  }

  const char *filename = argv[1];
  int line_length = atoi(argv[2]);

  if (line_length <= 0) {
    printf("Error: Line length must be a positive integer\n");
    return 1;
  }

  // Read the input file
  int num_strings;
  char **strings = read_file_to_array(filename, &num_strings);

  if (strings == NULL) {
    printf("Error: Could not open file '%s'\n", filename);
    return 1;
  }

  // Print original text
  printf("\nOriginal text:\n");
  printf("----------------------------------------\n");
  for (int i = 0; i < num_strings; i++) {
    printf("%s ", strings[i]);
  }
  printf("\n----------------------------------------\n");

  // Find optimal line breaks
  int *breaks = find_line_breaks(strings, line_length, num_strings);

  // Print formatted text
  print_formatted_text(strings, breaks, num_strings, line_length);

  // Clean up
  free_string_array(strings, num_strings);
  free(breaks);

  return 0;
}
