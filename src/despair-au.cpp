//#include "pch.h"
#include "despair-au.hpp"
#include <vorbis/vorbisfile.h>
#include <AL/al.h>
#include <iostream>

#define OGG_BUFFER_BLOCK_SIZE 1024


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
