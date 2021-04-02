#ifndef _UTILS_H_
#define _UTILS_H_

enum YuvType {
  YUV444P, YUV422P, YUV420P
};

int split_yuv(const char *input_path, const char *output_path, YuvType yuv_type, int width, int height);

int calculate_yuv_size(YuvType yuv_type, int width, int height);

#endif