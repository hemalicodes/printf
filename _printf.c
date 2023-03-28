#include "main.h"
/* Declare function to print the contents of the buffer */
void print_buffer(char buffer[], int *buff_ind);
/**
 * _printf - Printf function
 * @format: format string to be printed
 * Return: the number of printed characters
 */
int _printf(const char *format, ...)
{
/* Declare variables */
int i, printed_chars = 0, printed = 0;
int flags, width, precision, size, buff_ind = 0;
va_list list;
char buffer[BUFF_SIZE];
/* Check for null format */
if (format == NULL)
return (-1);
/* Start the variable argument list */
va_start(list, format);
/* Loop through the format string */
for (i = 0; format && format[i] != '\0'; i++)
{
/* Check if the current character is not a format specifier */
if (format[i] != '%')
{
/* Add the character to the buffer */
buffer[buff_ind++] = format[i];
/* Check if the buffer is full */
if (buff_ind == BUFF_SIZE)
print_buffer(buffer, &buff_ind);
/* Increment the number of printed characters */
printed_chars++;
}
/* If the current character is a format specifier */
else
{
/* Print the contents of the buffer */
print_buffer(buffer, &buff_ind);
/* Parse the format specifier */
flags = get_flags(format, &i);
width = get_width(format, &i, list);
precision = get_precision(format, &i, list);
size = get_size(format, &i);
++i;
/* Print the argument based on the format specifier */
printed = handle_print(format, &i, list, buffer,
flags, width, precision, size);
/* Check for errors */
if (printed == -1)
return (-1);
/* Increment the number of printed characters */
printed_chars += printed;
}
}
/* Print the remaining contents of the buffer */
print_buffer(buffer, &buff_ind);
/* End the variable argument list */
va_end(list);
/* Return the number of printed characters */
return (printed_chars);
}
/**
 * print_buffer - Prints the contents of the buffer if it exists
 * @buffer: array of characters to be printed
 * @buff_ind: index of the next character to be added to the buffer
 */
void print_buffer(char buffer[], int *buff_ind)
{
/* Check if the buffer is not empty */
if (*buff_ind > 0)
write(1, &buffer[0], *buff_ind);
/* Reset the buffer index */
*buff_ind = 0;
}
