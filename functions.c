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
/************************* PRINT UNSIGNED NUMBER *************************/
/**
 * print_unsigned - Handles an unsigned number
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width specifier
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_unsigned(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
unsigned int num = va_arg(types, unsigned int);
int i = BUFF_SIZE - 2;
num = convert_size_unsgnd(num, size);
if (num == 0)
buffer[i--] = '0';
buffer[BUFF_SIZE - 1] = '\0';
while (num > 0)
{
buffer[i--] = (num % 10) + '0';
num /= 10;
}
i++;
return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}
/************* PRINT UNSIGNED NUMBER IN OCTAL  ****************/
/**
 * print_octal - Prints an unsigned number in octal notation
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Active flags
 * @width: Width specifier
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_octal(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
unsigned long num = va_arg(types, unsigned long);
unsigned long init_num = num;
int count = 0;
char *digits = "01234567";
char result[BUFF_SIZE] = {0};
num = convert_size_unsgnd(num, size);
if (num == 0)
result[count++] = '0';
while (num > 0)
{
result[count++] = digits[num % 8];
num /= 8;
}
if (flags & F_HASH && init_num != 0)
result[count++] = '0';
if (flags & F_MINUS)
count += print_padding(buffer, count, width, count, ' ');
if (flags & F_ZERO)
count += print_padding(buffer, count, width, count, '0');
for (int i = count - 1; i >= 0; i--)
buffer[i] = result[count - 1 - i];
if (!(flags & F_MINUS))
count += print_padding(buffer, count, width, count, ' ');
return count;
}
/************** PRINT UNSIGNED NUMBER IN HEXADECIMAL **************/
/**
 * print_hexadecimal - Prints an unsigned number in hexadecimal notation
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_hexadecimal(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
return (print_base(types, "0123456789abcdef", buffer,
flags, 'x', width, precision, size));
}
/************* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL **************/
/**
 * print_hexa_upper - Prints an unsigned number in upper hexadecimal notation
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_hexa_upper(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
return print_hexa(types, "0123456789ABCDEF", buffer,
flags, 'X', width, precision, size);
}
/************** PRINT HEXX NUM IN LOWER OR UPPER **************/
/**
 * print_hexa - Prints a hexadecimal number in lower or upper case
 * @types: List of arguments
 * @map_to: Array of values to map the number to
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @flag_ch: Calculates active flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_hexa(va_list types, char map_to[], char buffer[],
int flags, char flag_ch, int width, int precision, int size)
{
int i = BUFF_SIZE - 2;
unsigned long int num = va_arg(types, unsigned long int);
unsigned long int init_num = num;
UNUSED(width);
num = convert_size_unsgnd(num, size);
if (num == 0)
buffer[i--] = '0';
buffer[BUFF_SIZE - 1] = '\0';
while (num > 0)
{
buffer[i--] = map_to[num % 16];
num /= 16;
}
if (flags & F_HASH && init_num != 0)
{
buffer[i--] = flag_ch;
buffer[i--] = '0';
}
i++;
return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}
/****************** PRINT POINTER ******************/
/**
 * print_pointer - Prints the value of a pointer variable
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int print_pointer(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
unsigned long int num_addrs;
char map_to[] = "0123456789abcdef";
void *addrs = va_arg(types, void *);
if (addrs == NULL)
return (write(1, "(nil)", 5));
num_addrs = (unsigned long int)addrs;
int length = 2, padd_start = 1;
while (num_addrs > 0)
{
buffer[length++] = map_to[num_addrs % 16];
num_addrs /= 16;
}
if (flags & F_PLUS || flags & F_SPACE)
length++;
int padding = width - length;
if (padding > 0 && !(flags & F_MINUS))
{
char padding_char = ' ';
if (flags & F_ZERO)
padding_char = '0';
while (padding--)
buffer[padd_start++] = padding_char;
}
if (flags & F_PLUS)
buffer[padd_start++] = '+';
else if (flags & F_SPACE)
buffer[padd_start++] = ' ';
buffer[padd_start++] = '0';
buffer[padd_start++] = 'x';
int i;
for (i = length; i > 2; i--)
buffer[padd_start++] = buffer[i];
if (padding > 0 && flags & F_MINUS)
{
while (padding--)
buffer[padd_start++] = ' ';
}
return write(1, buffer, padd_start);
}
/************************* PRINT NON PRINTABLE *************************/
/**
 * print_non_printable - Prints non-printable characters in hexadecimal
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_non_printable(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
char *str = va_arg(types, char *);
int count = 0;
UNUSED(flags);
UNUSED(width);
UNUSED(precision);
UNUSED(size);
if (str == NULL)
return (write(1, "(null)", 6));
for (int i = 0; str[i] != '\0'; i++)
{
if (isprint(str[i]))
{
if (append_buffer(str[i], buffer, &count) == -1)
return (-1);
}
else
{
if (append_hexadecimal((unsigned char)str[i], buffer, &count) == -1)
return (-1);
}
}
return (write(1, buffer, count));
}
/**
 * append_buffer - Appends a character to the buffer and increments the count
 * @c: The character to append
 * @buffer: The buffer array to append to
 * @count: Pointer to the count of characters in the buffer
 * Return: 0 on success, -1 on failure
 */
int append_buffer(char c, char buffer[], int *count)
{
if (*count >= BUFF_SIZE - 1)
return (-1);
buffer[(*count)++] = c;
return (0);
}
/**
 * append_hexadecimal - Appends a hexadecimal representation of a character
 * @c: The character to append
 * @buffer: The buffer array to append to
 * @count: Pointer to the count of characters in the buffer
 * Return: 0 on success, -1 on failure
 */
int append_hexadecimal(unsigned char c, char buffer[], int *count)
{
int n;
if (*count >= BUFF_SIZE - 4)
return (-1);
buffer[(*count)++] = '\\';
buffer[(*count)++] = 'x';
n = c / 16;
buffer[(*count)++] = n < 10 ? n + '0' : n - 10 + 'a';
n = c % 16;
buffer[(*count)++] = n < 10 ? n + '0' : n - 10 + 'a';
return (0);
}
/************************* PRINT REVERSE *************************/
/**
 * print_reverse - Prints reverse string.
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */

int print_reverse(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
char *str;
int i, count = 0;
UNUSED(buffer);
UNUSED(flags);
UNUSED(width);
UNUSED(size);
str = va_arg(types, char *);
if (str == NULL)
{
UNUSED(precision);
str = ")Null(";
}
for (i = 0; str[i]; i++)
;
for (i = i - 1; i >= 0; i--)
{
char z = str[i];
write(1, &z, 1);
count++;
}
return (count);
}
/************************* PRINT A STRING IN ROT13 *************************/
/**
 * print_rot13string - Takes a string as an arg and 
 * prints the rot13 encoding of the string
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_rot13string(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
char *str = va_arg(types, char *);
int count = 0;
UNUSED(buffer);
UNUSED(flags);
UNUSED(width);
UNUSED(precision);
UNUSED(size);
if (str == NULL)
str = "(AHYY)";
for (int i = 0; str[i] != '\0'; i++)
{
if (str[i] >= 'A' && str[i] <= 'Z')
buffer[i] = ((str[i] - 'A' + 13) % 26) + 'A';
else if (str[i] >= 'a' && str[i] <= 'z')
buffer[i] = ((str[i] - 'a' + 13) % 26) + 'a';
else
buffer[i] = str[i];
count++;
}
return (write(1, buffer, count));
}
