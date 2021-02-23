#include <stdio.h>
#include "include/st_audio_extract.h"

int main(int argc, char **argv) {
  if (argc != 3) {
    printf("USAGE: main video_path audio_path \n");
    return -1;
  }

  char err_msg[256];
  st_audio_extract_init();

  while (1) {
    int ret = st_audio_convert(argv[1], argv[2], err_msg);
    if (ret != 0) {
      printf("call st_audio_extract failed, ret: %d, err: %s\n", ret, err_msg);
      return -2;
    }
  }


  return 0;
}