#ifndef _HEADER_STRINGFORMAT
#define _HEADER_STRINGFORMAT

#define _formatstring(variable_name, format, ...) \
  int __fmt_strlen = snprintf(NULL, 0, format, __VA_ARGS__); \
  char *__fmt_str = new char[__fmt_strlen+1]; \
  sprintf(__fmt_str, format, __VA_ARGS__);\
  variable_name = string(__fmt_str);\
  delete __fmt_str

#endif