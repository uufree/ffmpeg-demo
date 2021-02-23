package main

// #cgo LDFLAGS: -L../libs -laudio_extract -lavformat -lavdevice -lavcodec -lavutil -lswresample -lavfilter -lpostproc -lswscale
// #cgo CXXFLAGS: -Wall -std=c++11
/*
/// @brief 全局初始化函数，初始化ffmpeg相关的资源
void st_audio_extract_init();

/// @brief 音频提取.输出16bit 16kHz采样,单通道wav音频
/// @param [in] 输入视频路径;需要填写输入视频的全局路径
/// @param [in] 输出音频路径;需要填写期望输出音频的全局路径
/// @param [in/out] 输入分配好内存的块，输出函数调用失败的详细信息
/// @return 成功返回0，失败返回负数
/// @note 调用此函数之前，一定要调用st_audio_extract_init函数，否则会报错。
int st_audio_extract(const char* video_path, const char* audio_path, char* errmsg);

/// @brief 音频格式转换.输出16bit 16kHz采样,单通道wav音频
/// @param [in] 输入音频路径;需要填写输入视频的全局路径
/// @param [in] 输出音频路径;需要填写期望输出音频的全局路径
/// @param [in/out] 输入分配好内存的块，输出函数调用失败的详细信息
/// @return 成功返回0，失败返回负数
/// @note 调用此函数之前，一定要调用st_audio_extract_init函数，否则会报错。
int st_audio_convert(const char* raw_audio_path, const char* audio_path, char* errmsg);
*/
import "C"

import (
	"fmt"
	"sync"
	"unsafe"
)

func main() {
	C.st_audio_extract_init()

	errMsg := make([]byte, 256)
	cerrMsg := (*C.char)(unsafe.Pointer(&errMsg[0]))
	ch := make(chan struct{}, 4)
	wg := sync.WaitGroup{}
	wg.Add(1)
	for i := 0; i < 1; i++ {
		ch <- struct{}{}
		go func() {
			defer func() {
				<-ch
				wg.Done()
			}()

			if ret := C.st_audio_extract(C.CString("/data/radar/SenseradarTool/audio_extract/golang/20200904-a.mp4"), C.CString("/data/radar/SenseradarTool/audio_extract/golang/20200904-a.wav"), cerrMsg); ret != 0 {
				fmt.Errorf("call st_audio_extract failed, ret code: %v, errmsg: %v", ret, string(errMsg))
				return
			}
		}()
	}

	wg.Wait()
}
