#include "main.h"
/**
 * get_width - Calculates the width for printing
 * @format: Formatted string in which to print the arguments.
 * @i: Pointer to index of current character in format string.
 * @list: List of arguments.
 *
 * Return: Width for printing.
 */
int get_width(const char *format, int *i, va_list list)
{
int curr_i = *i + 1; // Get the index of the next character in the format string.
int width = 0;
// Loop through the characters in the format string starting at curr_i.
for (; format[curr_i] != '\0'; curr_i++) {
// If the current character is a digit, add it to the width.
if (is_digit(format[curr_i])) {
width *= 10;
width += format[curr_i] - '0';
} 
// If the current character is an asterisk, get the width from the argument list.
else if (format[curr_i] == '*') {
curr_i++;
width = va_arg(list, int); // Get the width argument from the list.
break; // Stop looping because we found the width specifier.
} 
// If the current character is not a digit or asterisk, stop looping because we reached the end of the width specifier.
else {
break;
}
}
*i = curr_i - 1; // Update the index of the current character in the format string.
return width; // Return the calculated width.
}
