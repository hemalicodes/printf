#include "main.h"
/************************* PRINT CHAR *************************/
/**
 * print_char - Takes a char argument and writes it to the buffer array
 * @args: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_char(va_list args, char buffer[],
int flags, int width, int precision, int size)
{
char c = va_arg(args, int);
int num_chars = handle_write_char(c, buffer, flags, width, precision, size);
return num_chars;
}
/************************* PRINT A STRING *************************/
/**
 * print_percent - Takes a string arg from a var argument list, formats it
 * according to the specified flags, width, and precision, and writes the
 * resulting string to the buffer or std output
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_string(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
char *str = va_arg(types, char *);
int str_length = 0;
if (str == NULL)
str = "(null)";
while (str[str_length] != '\0')
str_length++;
if (precision >= 0 && precision < str_length)
str_length = precision;
int total_length = str_length;
if (width > str_length)
{
total_length = width;
char padding_char = (flags & F_ZERO) ? '0' : ' ';
if (flags & F_MINUS)
{
write_buffer(buffer, str, str_length);
write_padding(buffer, padding_char, width - str_length);
}
else
{
write_padding(buffer, padding_char, width - str_length);
write_buffer(buffer, str, str_length);
}
}
else
{
write_buffer(buffer, str, str_length);
}
return total_length;
}
/************************* PRINT PERCENT SIGN *************************/
/**
 * print_percent - Prints a percent sign to the output stream
 * @args: Unused variable argument list
 * @buffer: Unused buffer array to handle print
 * @flags: Unused formatting flags
 * @width: Unused width specifier
 * @precision: Unused precision specifier
 * @size: Unused size specifier
 * Return: Number of characters printed (always 1)
 */
int print_percent(va_list args, char buffer[],
int flags, int width, int precision, int size)
{
UNUSED(args);
UNUSED(buffer);
UNUSED(flags);
UNUSED(width);
UNUSED(precision);
UNUSED(size);
write(1, "%", 1);
return (1);
}
/************************* PRINT INT *************************/
/**
 * print_int - Takes a variable no. of arguments, formats and prints
 * an int to the std output
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_int(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
int i = BUFF_SIZE - 2;
int is_negative = 0;
long int n = va_arg(types, long int);
unsigned long int num;
n = convert_size_number(n, size);
if (n == 0)
buffer[i--] = '0';
buffer[BUFF_SIZE - 1] = '\0';
num = (unsigned long int)n;
if (n < 0)
{
num = (unsigned long int)((-1) * n);
is_negative = 1;
}
while (num > 0)
{
buffer[i--] = (num % 10) + '0';
num /= 10;
}
i++;
return (write_number(is_negative, i, buffer, flags, width, precision, size));
}
/************************* PRINT BINARY *************************/
/**
 * print_binary - Prints an unsigned number in binary format
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed.
 */
int print_binary(va_list types, char buffer[], int flags, int width, int precision, int size)
{
unsigned int n = va_arg(types, unsigned int);
int count = 0;
for (int i = 31; i >= 0; i--)
{
unsigned int mask = 1 << i;
if (n & mask)
{
write(1, "1", 1);
count++;
}
else if (count > 0 || i == 0)
{
write(1, "0", 1);
count++;
}
}
return count;
}
