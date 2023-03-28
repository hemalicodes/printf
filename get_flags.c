#include "main.h"
/**
 * get_flags - Calculates active flags
 * @format: Formatted string in which to print the arguments
 * @i: take a parameter.
 * Return: Flags:
 */
int get_flags(const char *format, int *i)
{
// Characters that represent each flag
const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
// Bit value for each flag, in the same order as FLAGS_CH
const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};
// Current index in the format string
int curr_i = *i + 1;
// Active flags, initialized to zero
int flags = 0;
// Index for looping through FLAGS_CH and FLAGS_ARR
int j;
// Loop through the format string, starting at curr_i
for (; format[curr_i] != '\0'; curr_i++)
{
// Check if the current character is a flag character
for (j = 0; FLAGS_CH[j] != '\0'; j++)
{
if (format[curr_i] == FLAGS_CH[j])
{
// If it is, set the corresponding bit in flags
flags |= FLAGS_ARR[j];
break;
}
}
// If the current character is not a flag character, exit the loop
if (FLAGS_CH[j] == 0)
break;
}
// Update i to the current index in the format string
*i = curr_i - 1;
// Return the calculated flags value
return flags;
}
