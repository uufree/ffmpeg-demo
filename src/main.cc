#include "video_encode.h"
#include "utils.h"

int main(int argc, char** argv) {
//  video_encode("1", "2");

  split_yuv("/data/ffmpeg-demo/akiyo_qcif.yuv", "/data/ffmpeg-demo/yuv/", YUV420P, 176, 144);
  return 0;
}