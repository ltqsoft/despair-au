/****************************************************************************************
MIT License

Copyright (c) 2022 流陳光

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
****************************************************************************************/
#include "despair-au-pch.hh"
#include "despair-au.hh"

#define OGG_BUFFER_BLOCK_SIZE 1024


static struct {
    ALCdevice*  dev = nullptr;
    ALCcontext* ctx = nullptr;
} __alContext;


float despair_au::listenerPos_[] = { 0.0f, 0.0f, 0.0f };


despair_au::err despair_au::init()
{
    __alContext.dev = alcOpenDevice(nullptr);
    if(__alContext.dev == nullptr) { return err::audio_device; }

    __alContext.ctx = alcCreateContext(__alContext.dev, nullptr);
    if(__alContext.ctx == nullptr)
    {
        alcCloseDevice(__alContext.dev);
        return err::context;
    }
    alcMakeContextCurrent(__alContext.ctx);

    return err::none;
}


void despair_au::terminate()
{
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(__alContext.ctx);
    alcCloseDevice(__alContext.dev);
}


despair_au::err despair_au::load_ogg(const string& wFilePath, i8array& wData, buf_info& wInfo)
{
    endian_t endian = _THIS::getEndian();
    if(endian == little_endian) {
        std::cout << "endian=little\n";
    } else {
        std::cout << "endian=big\n";
    }


    long bytes = 0;
    char array[OGG_BUFFER_BLOCK_SIZE];
    int channels = 0;
    //std::vector<char> alBuf;

    FILE* fp = fopen(wFilePath.c_str(), "rb");
    if(fp == nullptr)
    {
        std::cerr << "OGG file opening failed!\n";
        return err::file_not_found;
    }

    OggVorbis_File oggFile;
    if(ov_open(fp, &oggFile, nullptr, 0))
    {
        std::cerr << "Error reading file with Vorbis API!\n";
        return err::file_api_convert;
    }

    const vorbis_info* pInfo = ov_info(&oggFile, -1);
    channels = pInfo->channels;
    constexpr int bitsPerSample = 16;

    if(pInfo->channels == 1) { wInfo.format = AL_FORMAT_MONO16; }
    else { wInfo.format = AL_FORMAT_STEREO16; }
    wInfo.frequency = pInfo->rate;

    do
    {
        int bitStream ;//= -1;
        bytes = ov_read(&oggFile, array, OGG_BUFFER_BLOCK_SIZE, endian, 2, 1, &bitStream);
        if(bytes < 0)
        {
            ov_clear(&oggFile);
            std::cerr << "ov_read error!\n";
            return err::ogg_hole;
        }
        wData.insert(wData.end(), array, array+bytes);

    } while(bytes > 0);

    ov_clear(&oggFile);

    return _THIS::err::none;
}


despair_au::err despair_au::load_wav(const string& wFilePath)
{
    return _THIS::err::none;
}


despair_au::endian_t despair_au::getEndian()
{
    uint16_t i = 1;
	return (*(char*)&i == '\0');
}


despair_au::float3 despair_au::listener_pos()
{
    alGetListenerfv(AL_POSITION, listenerPos_);
    return listenerPos_;
}


void despair_au::listener_pos(float3 wPos)
{
    alListenerfv(AL_POSITION, wPos);
}


despair_au::norm32 despair_au::master_volume()
{
    norm32 ret;
    alGetListenerf(AL_GAIN, &ret);
    return ret;
}


void despair_au::master_volume(norm32 wValue)
{
    if(wValue > 1.0f) wValue = 1.0f;
    else if(wValue < 0.0f) wValue = 0.0f;
    alListenerf(AL_GAIN, wValue);
}
