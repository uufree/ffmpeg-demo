#include <stdio.h>
#include <string>
#include <fstream>

#include "video_encode.h"
#include "defer.h"
#include "utils.h"

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavutil/opt.h>
}

int video_encode(int width, int height, const char *input_path, const char *output_path) {
  if (input_path == nullptr || output_path == nullptr) {
    printf("input path or output path is nullptr\n");
    return -1;
  }

  char ffmpeg_errmsg[512];

  avcodec_register_all();

  AVCodec *codec = avcodec_find_encoder(AV_CODEC_ID_H264);
  if (codec == nullptr) {
    printf("find avcodec failed\n");
    return -2;
  }

  AVCodecContext *context = avcodec_alloc_context3(codec);
  if (context == nullptr) {
    printf("find avcodec context failed\n");
    return -3;
  }

  // set context
  context->bit_rate = 400000;
  context->width = width;
  context->height = height;
  context->time_base = AVRational{1, 25};
  context->framerate = AVRational{25, 1};
  context->gop_size = 10;
  context->max_b_frames = 1;
  context->pix_fmt = AV_PIX_FMT_YUV420P;

  // x264 setting
  AVDictionary *dict = nullptr;
  av_dict_set(&dict, "preset", "slow", AV_DICT_MATCH_CASE);
  defer(av_dict_free(&dict));

  int ret = avcodec_open2(context, codec, &dict);
  if (ret < 0) {
    av_strerror(ret, ffmpeg_errmsg, sizeof(ffmpeg_errmsg));
    printf("cannot open codec h264, err: %s", ffmpeg_errmsg);
    return -4;
  }
  defer(avcodec_close(context); avcodec_free_context(&context));

  AVPacket *packet = av_packet_alloc();
  if (packet == nullptr) {
    printf("alloc packet failed\n");
    return -5;
  }
  defer(av_packet_unref(packet); av_packet_free(&packet));

  AVFrame *frame = av_frame_alloc();
  if (frame == nullptr) {
    printf("alloc frame failed\n");
    return -6;
  }
  defer(av_frame_unref(frame); av_frame_free(&frame));

  // init frame
  frame->format = context->pix_fmt;
  frame->height = context->height;
  frame->width = context->width;
  ret = av_frame_get_buffer(frame, 0);
  if (ret < 0) {
    av_strerror(ret, ffmpeg_errmsg, sizeof(ffmpeg_errmsg));
    printf("get frame buffer failed, err: %s", ffmpeg_errmsg);
    return -7;
  }

  const std::string yuv_path("./yuv/");
  int yuv_count = split_yuv(input_path, yuv_path.c_str(), YUV420P, width, height);
  if (yuv_count < 0) {
    printf("split yuv failed, ret: %d\n", yuv_count);
    return -8;
  }

  int yuv_size = calculate_yuv_size(YUV420P, width, height);
  char yuv_file[yuv_size];
  // construct yuv
  for (int i = 1; i <= yuv_count; i++) {
    std::fstream ifs(yuv_path + std::to_string(i) + ".yuv");
    ifs.read(yuv_file, yuv_size);

    ret = av_frame_make_writable(frame);
    if (ret != 0) {
      av_strerror(ret, ffmpeg_errmsg, sizeof(ffmpeg_errmsg));
      printf("maker frame failed, ret: %d, errmsg: %s\n", ret, ffmpeg_errmsg);
      return -9;
    }
  }

  return 0;
}