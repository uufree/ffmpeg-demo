#include <cstdio>
//#include "simple_player.h"
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"

int main(int argc, char** argv) {
    //simple_player();
    av_register_all();
    avformat_network_init();
    return 0;
}