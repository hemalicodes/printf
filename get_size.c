#include "main.h"
/**
 * get_size - Calculates the size to cast the argument
 * @format: Formatted string in which to print the arguments
 * @i: List of arguments to be printed.
 *
 * Return: The size of the argument based on the format specifier.
 */
int get_size(const char *format, int *i)
{
int curr_i = *i + 1; // Get the index of the next character in the format string.
int size = 0;
// Check if the next character in the format string is 'l'.
if (format[curr_i] == 'l') {
size = S_LONG; // Set the size to S_LONG (a constant defined elsewhere).
} 
// Check if the next character in the format string is 'h'.
else if (format[curr_i] == 'h') {
size = S_SHORT; // Set the size to S_SHORT (a constant defined elsewhere).
}
// If neither 'l' nor 'h' is found, we don't need to adjust the index.
if (size == 0) {
*i = curr_i - 1; // Set the index back to the original character in the format string.
} else {
*i = curr_i; // Set the index to the next character after the size specifier.
}
return size; // Return the size of the argument based on the format specifier.
}
