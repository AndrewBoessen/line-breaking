#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Reads the contents of a text file and returns an array of strings,
 * where each string represents a word from the file.
 *
 * @param filename The path to the text file to be read.
 * @param num_strings A pointer to an integer that will store the number of
 * strings in the returned array.
 * @return char** An array of dynamically allocated strings, or NULL if the
 * file could not be opened.
 *
 * The caller is responsible for freeing the memory allocated for the
 * string array and the individual strings.
 */
char **read_file_to_array(const char *filename, int *num_strings) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    *num_strings = 0;
    return NULL;
  }

  // First pass: count words
  char line[1024];
  *num_strings = 0;
  while (fgets(line, sizeof(line), file)) {
    char *word = strtok(line, " \n\t\r");
    while (word != NULL) {
      (*num_strings)++;
      word = strtok(NULL, " \n\t\r");
    }
  }

  // Allocate array of string pointers
  char **arr = (char **)malloc(*num_strings * sizeof(char *));
  if (arr == NULL) {
    fclose(file);
    *num_strings = 0;
    return NULL;
  }

  // Initialize all pointers to NULL
  for (int i = 0; i < *num_strings; i++) {
    arr[i] = NULL;
  }

  // Reset file pointer to beginning
  rewind(file);

  // Second pass: store words
  int word_index = 0;
  while (fgets(line, sizeof(line), file)) {
    char *word = strtok(line, " \n\t\r");
    while (word != NULL && word_index < *num_strings) {
      // Allocate space for the word plus null terminator
      size_t word_len = strlen(word);
      arr[word_index] = (char *)malloc((word_len + 1) * sizeof(char));

      if (arr[word_index] == NULL) {
        // Cleanup on allocation failure
        for (int i = 0; i < word_index; i++) {
          free(arr[i]);
        }
        free(arr);
        fclose(file);
        *num_strings = 0;
        return NULL;
      }

      // Copy the word
      strcpy(arr[word_index], word);
      word_index++;
      word = strtok(NULL, " \n\t\r");
    }
  }

  fclose(file);
  return arr;
}

/**
 * @brief Calcualtes cost for break points start and end
 *
 * @param strings The arrays of strings representing the text to break
 * @param start The first break point
 * @param end The last break point
 * @param line_length Max number of chars in one line
 * @returns int Cost for breaks points start and end
 */
int cost(char **strings, int start, int end, int line_length) {
  // no words between breaks
  if (start == end) {
    return 0;
  }
  // start after end
  if (start > end) {
    return 100000; // infinite cost
  }
  // calculate num character between breaks
  int num_chars = 0;
  for (int i = start; i < end; i++) {
    char *curr_word = strings[i];
    // count chars in current word
    while (*curr_word != '\0') {
      num_chars++;
      curr_word++;
    }
  }
  int white_space = line_length - num_chars;
  // infinite cost if num chars longer than line length
  return white_space >= 0 ? white_space * white_space : 100000;
}

/**
 * @brief Create a table with cost for family of break pairs
 *
 * @param strings Arrays of strings in text to break
 * @param line_length Max number of chars in single line
 * @param end Index of ending break point
 * @n Number of words in text
 * @returns int* array of costs
 */
int *create_cost_table(char **strings, int line_length, int end, int n) {
  int *table = (int *)malloc(n * sizeof(int));

  // populate table with costs
  for (int i = 1; i <= n; i++) {
    table[i - 1] = cost(strings, i, end, line_length);
  }

  return table;
}
void printArray(int arr[], int size) {
  printf("Array elements: ");
  for (int i = 0; i < size; i++) {
    printf("%d", arr[i]);
    if (i < size - 1) {
      printf(", ");
    }
  }
  printf("\n");
}

/**
 * @brief Find the optimal line break points for a array of strings and a max
 * line length
 *
 * @param strings Array of strings to break
 * @param line_length Max number of chars in single line
 * @parm n Number of words in array
 * @returns int* array of line breaks
 */
int *find_line_breaks(char **strings, int line_length, int n) {
  // matrix to store optimal breaks for each break point
  int **optimal_breaks = malloc((n - 1) * sizeof(int *));
  // psi values for b_j
  int *psi_vals = NULL;
  // walk back from last line break to first
  for (int i = n; i >= 1; i--) {
    // find break for b_i
    if (psi_vals == NULL) {
      // psi b_n-1 is just costs
      psi_vals = create_cost_table(strings, line_length, i, n);
    } else {
      // optimal break values
      int *breaks = (int *)malloc(n * sizeof(int));
      // populate new psi_vals for b_j-1
      int *new_psi_vals = (int *)malloc(n * sizeof(int));
      memset(new_psi_vals, 0xF, n * sizeof(int));
      // optimize for b_j
      for (int j = 1; j <= n; j++) {
        // loop over b
        int *costs = create_cost_table(strings, line_length, j, n);
        for (int k = 1; k <= n; k++) {
          int cost = costs[k - 1];               // cost(b, b_j)
          int curr_val = psi_vals[j - 1] + cost; // psi_j(b_j) + cost(b, b_j)
          if (curr_val < new_psi_vals[k - 1]) {
            new_psi_vals[k - 1] = curr_val;
            breaks[k - 1] = j;
          }
        }
      }
      optimal_breaks[i] = breaks;
      free(breaks);
      psi_vals = new_psi_vals;
      free(new_psi_vals);
    }
    printArray(psi_vals, n);
  }

  // build breaks by walking through optimal_breaks
  int *final_breaks = (int *)malloc((n - 1) * sizeof(int));
  final_breaks[0] = optimal_breaks[0][0];
  for (int i = 1; i < n - 1; i++) {
    final_breaks[i] = optimal_breaks[i][final_breaks[i - 1]];
    free(optimal_breaks[i]);
  }

  free(optimal_breaks);
  free(psi_vals);

  return final_breaks;
}