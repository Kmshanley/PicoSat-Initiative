#ifndef LOG_H
#define LOG_H

#include "usart.h"
#include <stdio.h>
#include <stdarg.h>

#ifdef __GNUC__
	#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else

	#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

void log_error(const char* message, ...);
void log_info(const char* message, ...);
void log_debug(const char* message, ...);

#endif /* LOG_H */
