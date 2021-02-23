#include <string>
#include <cstdio>
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"

int simple_player() {

    int errmsg_length = 256;
    char errmsg[errmsg_length];
    memset(errmsg, '\0', errmsg_length);
    // global init
    av_register_all();
    avformat_network_init();
/*
    AVFormatContext *format_context = avformat_alloc_context();
    if (format_context == NULL) {
        printf("call ffmpeg alloc format context failed!\n");
        return -1;
    }

    int ret = avformat_open_input(&format_context, file_path.c_str(), NULL, NULL);
    if (ret < 0) {
        av_strerror(ret, errmsg, errmsg_length);
        printf("open path: %s failed, ffmpeg errcode: %d, ffmpeg errmsg: %s\n", file_path.c_str(), ret, errmsg);
        return -2;
    }
*/
    return 0;
}

