#ifndef IO_H
#define IO_H

#include <stdlib.h>

#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>
#include "../utils.h"

typedef struct file {
  char *data;
  size_t len;
  bool is_valid;
} file;

char *io_file_read(const char *path);
i32 io_file_write(void *buffer, size_t size, const char *path);

#endif

