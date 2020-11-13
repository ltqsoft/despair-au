//#include "pch.h"
#include "despair-au.hpp"


despair_au::err despair_au::load_ogg(const string& wFilePath)
{
    endian_t endian = get_endian();
    if(endian == little_endian) {
        std::cout << "endian=little\n";
    } else {
        std::cout << "endian=big\n";
    }

    ALbuffer_T alBuffer;

    int bitStream = -1;
    long bytes = 0;
    char array[OGG_BUFFER_BLOCK_SIZE];
    int channels = 0;
    std::vector<char> alBuf;

    FILE* fp = fopen(OGG_FILE, "rb");
    if(fp == nullptr)
    {
        std::cerr << "OGG file opening failed!\n";
        return 1;
    }

    vorbis_info* pInfo;
    OggVorbis_File oggFile;
    if(ov_open(fp, &oggFile, nullptr, 0))
    {
        std::cerr << "Error reading file with Vorbis API!\n";
        return 2;
    }

    pInfo = ov_info(&oggFile, -1);
    channels = pInfo->channels;
    int bitsPerSample = 16;

    if(pInfo->channels == 1) { alBuffer.format = AL_FORMAT_MONO16; }
    else { alBuffer.format = AL_FORMAT_STEREO16; }
    alBuffer.frequency = pInfo->rate;

    do
    {
        bytes = ov_read(&oggFile, array, OGG_BUFFER_BLOCK_SIZE, endian, 2, 1, &bitStream);
        if(bytes < 0)
        {
            ov_clear(&oggFile);
            std::cerr << "ov_read error!\n";
            return 3;
        }
        alBuf.insert(alBuf.end(), array, array+bytes);

    } while(bytes > 0);

    ov_clear(&oggFile);


    return _THIS::err::none;
}
