#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <fstream>

int split_yuv444p(const char *input_path, const char *output_path, int width, int height) {
  return 0;
}

int split_yuv422p(const char *input_path, const char *output_path, int width, int height) {
  return 0;
}

int split_yuv420p(const char *input_path, const char *output_path, int width, int height) {
  int yuv_size = width * height * 3 / 2;
  std::ifstream ff(input_path);
  if (!ff.is_open()) {
    printf("file path: %s open failed.", input_path);
    return -1;
  }

  int i = 0;
  char buf[yuv_size];
  while (ff.good()) {
    memset(buf, 0, yuv_size);
    ff.read(buf, yuv_size);
    if (ff.eof()) {
      break;
    }
    printf("%d\n", yuv_size);
    std::ofstream ofs(std::string(output_path) + std::to_string(++i) + ".yuv",
                      std::ios_base::app | std::ios_base::out | std::ios_base::trunc);
    ofs.write(buf, yuv_size);
  }

  return i;
}

int split_yuv(const char *input_path, const char *output_path, YuvType yuv_type, int width, int height) {
  if (input_path == nullptr || output_path == nullptr) {
    printf("invalid input path or output path.\n");
    return -1;
  }

  if (width < 0 || height < 0) {
    printf("invalid input width or height\n");
    return -2;
  }

  int ret = 0;
  switch (yuv_type) {
    case YUV444P:ret = split_yuv444p(input_path, output_path, width, height);
      break;
    case YUV422P:ret = split_yuv422p(input_path, output_path, width, height);
      break;
    case YUV420P:ret = split_yuv420p(input_path, output_path, width, height);
      break;
    default: {
      printf("invalid yuv type: %d\n", yuv_type);
      return -1;
    }
  }

  return ret;
}

int calculate_yuv_size(YuvType yuv_type, int width, int height) {
  switch (yuv_type) {
    case YUV444P:return width * height * 3;
    case YUV422P:return width * height * 2;
    case YUV420P:return width * height * 3 / 2;
    default:printf("invalid yuv type: %d\n", yuv_type);
      return -1;
  }

  return 0;
}