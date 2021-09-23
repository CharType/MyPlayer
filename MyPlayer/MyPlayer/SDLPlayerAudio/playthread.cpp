//
//  playthread.cpp
//  MyPlayer
//
//  Created by 程倩的MacBook on 2021/9/22.
//

#include "playthread.hpp"
#include "SDL.h"
#include "MyPlayer-Bridging-Header.h"

using namespace std;
#define FILENAME "/Users/chartype/Desktop/ypsc/in.pcm"
#define SAMPLE_RATE 48000
#define SAMPLE_SIZE 16
#define CHANNELS 2
// 音频缓冲区的样本数量
#define SAMPLES 1024
// 每个样本占用多少个字节
#define BYTES_PER_SAMPLE ((SAMPLE_SIZE * CHANNELS) / 8)
// 文件缓冲区的大小
#define BUFFER_SIZE (SAMPLES * BYTES_PER_SAMPLE)
// 采样格式
#define SAMPLE_FORMAT AUDIO_S16LSB

typedef struct AudioBuffer {
	int len = 0;
	int pullLen = 0;
	Uint8 *data = nullptr;
} AudioBuffer;

void pull_audio_data(void *userdata,Uint8 *stream,int len) {
	// 情况stream中的数据(防止脏数据)
	SDL_memset(stream, 0, len);
	AudioBuffer *buffer = (AudioBuffer *)userdata;
	// 如果没有读取带数据，直接return
	if(buffer->len <= 0) return;
	buffer->pullLen = (len > buffer->len) ? buffer->len:len;
	SDL_MixAudio(stream, buffer->data, buffer->pullLen, SDL_MIX_MAXVOLUME);
	buffer->data += buffer->pullLen;
	buffer->len -= buffer->pullLen;
}

void PlayerThread::run(){
	// 初始化子系统
	if(SDL_Init(SDL_INIT_AUDIO)) {
		cout << "SDL_Init error" << SDL_GetError();
		return;
	}
	// 2. 设置音频参数
	SDL_AudioSpec spec;
	// 设置声道数
	spec.channels = CHANNELS;
	// 设置采样率
	spec.freq = SAMPLE_RATE;
	// 设置缓冲区样本数量，这个值必须是2的幂次方
	spec.samples = SAMPLES;
	// 设置采样格式（s16le）
	spec.format = AUDIO_F32LSB;
	spec.callback = pull_audio_data;
	// 传递给回调的参数
	AudioBuffer buffer;
	spec.userdata = &buffer;
	// 3.打开设备
	if(SDL_OpenAudio(&spec, nullptr)) {
		cout << "SDL_OpenAudio error" << SDL_GetError();
		// 出错之后清除所有的子系统
		SDL_Quit();
	}
	// 4.打开文件
	ifstream stream;
	stream.open(FILENAME,ios::in);
	if(!stream.is_open()) {
        cout << "file.open error" << FILENAME << endl;
		// 关闭设备
		SDL_CloseAudio();
		// 关闭所有子系统
		SDL_Quit();
		return;
	}
	// 5.开始播放(0 是取消暂停)
	SDL_PauseAudio(0);
	// 6.从文件中读取数据
	Uint8 data[BUFFER_SIZE];
	while (!stream.eof()) {
		if (buffer.len > 0) {
			continue;
		}
        stream.read((char *)&data, sizeof(data));
        buffer.len = (int)stream.gcount();
		if (buffer.len <= 0) {
			break;
		}
		// 将读取到的数据给bufferData;
		// 读取到了文件数据
		buffer.data = data;
	}
	// 7关闭文件
	stream.close();
	// 8.关闭设备
	SDL_CloseAudio();
	// 9.清除所有的子系统
	SDL_Quit();
}

PlayerThread::~PlayerThread(){
    cout << "对象被释放" << endl;
}

void player() {
    PlayerThread *thread = new PlayerThread();
    thread->run();
}
