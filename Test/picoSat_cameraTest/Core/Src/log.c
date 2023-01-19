#include "log.h"

PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
  return ch;
}

void log_format(const char* tag, const char* message, va_list args)
{
	uint32_t time = HAL_GetTick();
	printf("%u [%s] ", (unsigned int)time, tag);
	vprintf(message, args);
	printf("\n");
}

void log_error(const char* message, ...)
{
	va_list args;
	va_start(args, message);
	log_format("error", message, args);
	va_end(args);
}

void log_info(const char* message, ...)
{
	va_list args;
	va_start(args, message);
	log_format("info", message, args);
	va_end(args);
}

void log_debug(const char* message, ...)
{
	va_list args;
	va_start(args, message);
	log_format("debug", message, args);
	va_end(args);
}
