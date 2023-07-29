#include "main.h"

/**
 * get_signature - Handles crtl + c call.
 * @signal: Signal handler
 */
void get_signature(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n($) ", 5);
}
