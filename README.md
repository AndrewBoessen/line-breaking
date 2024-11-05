# Dynamic Line Breaking in C

This repository contains a C implementation of dynamic line breaking using dynamic programming. The algorithm optimally breaks a given text into lines of a specified maximum length, minimizing the total cost of line breaks.

## Features

- Read text from a file and convert it into an array of words
- Calculate the optimal line breaks for a given text and line length
- Implement dynamic programming to efficiently find the best line break points
- Handle various edge cases and memory management

## Files

- `main.c`: Contains the main implementation of the line breaking algorithm
- `input.txt`: Sample input file containing the text to be formatted

## Functions

`char **read_file_to_array(const char *filename, int *num_strings)`

Reads the contents of a text file and returns an array of strings, where each string represents a word from the file.

`int cost(char **strings, int start, int end, int line_length)`

Calculates the cost for break points between `start` and `end` indices.

`int *create_cost_table(char **strings, int line_length, int bound, int n, int end)`

Creates a table with costs for a family of break pairs.

`int *find_line_breaks(char **strings, int line_length, int n)`

Finds the optimal line break points for an array of strings and a maximum line length.

## Usage

1. Compile the program:
   ```
   gcc main.c line_break.c -o line_break
   ```

2. Run the program with an input file and desired line length:
   ```
   ./line_break input.txt 30
   ```

3. The program will output the formatted text with optimal line breaks.

## Algorithm

The line breaking algorithm uses dynamic programming to find the optimal break points. It minimizes the total cost of line breaks, where the cost is defined as the square of the number of spaces at the end of each line.

The algorithm works in the following steps:
1. Read the input text and convert it into an array of words.
2. Calculate the cost for all possible line break combinations.
3. Use dynamic programming to find the optimal break points that minimize the total cost.
4. Return the array of optimal break points.

## Contributing

Contributions to improve the algorithm or add new features are welcome. Please submit a pull request or open an issue to discuss proposed changes.

## License

This project is open source and available under the [MIT License](LICENSE).
```

This README provides an overview of the project, explains the main features and functions, gives usage instructions, and briefly describes the algorithm and memory management approach. You can adjust or expand this README as needed to better fit your project's specific details or requirements.
