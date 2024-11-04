#ifndef LINE_BREAK_H
#define LINE_BREAK_H

#include <stdio.h>

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
char **read_file_to_array(const char *filename, int *num_strings);

/**
 * @brief Calcualtes cost for break points start and end
 *
 * @param strings The arrays of strings representing the text to break
 * @param start The first break point
 * @param end The last break point
 * @param line_length Max number of chars in one line
 * @returns int Cost for breaks points start and end
 */
int cost(char **strings, int start, int end, int line_length);

/**
 * @brief Create a table with cost for family of break pairs
 *
 * @param strings Arrays of strings in text to break
 * @param line_length Max number of chars in single line
 * @param end Index of ending break point
 * @param n Number of words in text
 * @returns int* array of costs
 */
int *create_cost_table(char **strings, int line_length, int end, int n);

/**
 * @brief Find the optimal line break points for a array of strings and a max
 * line length
 *
 * @param strings Array of strings to break
 * @param line_length Max number of chars in single line
 * @param n Number of words in array
 * @returns int* array of line breaks
 */
int *find_line_breaks(char **strings, int line_length, int n);

#endif /* LINE_BREAK_H */
