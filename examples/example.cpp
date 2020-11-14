#include <despair-au.hpp>
#include <AL/al.h>
#include <AL/alc.h>
#include <iostream>

#define OGG_FILE "../examples/LoL_LoginScreenIntro_6.10.ogg"
#define ERR_AL_DEVICE     1
#define ERR_AL_CONTEXT    2

int main()
{
    despair_au::i8array buffer;
    despair_au::buf_info bufferInfo;
    despair_au::load_ogg(OGG_FILE, buffer, bufferInfo);
    std::cout << "Buffer data size: " << buffer.size() << '\n';

    ALCdevice* device = alcOpenDevice(nullptr);
    if(device == nullptr)
    {
        std::cerr << "No device found!\n";
        return ERR_AL_DEVICE;
    }

    ALCcontext* ctx = alcCreateContext(device, nullptr);
    if(ctx == nullptr)
    {
        std::cerr << "Failed creating context!\n";
        alcCloseDevice(device);
        return ERR_AL_CONTEXT;
    }
    alcMakeContextCurrent(ctx);

    ALuint alBuffer;
    alGenBuffers(1, &alBuffer);
    alBufferData(alBuffer, bufferInfo.format, buffer.data(), buffer.size(), bufferInfo.frequency);

    ALuint source;
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, alBuffer);
    alSourcePlay(source);

    while(std::cin.get() != 'q')
    {

    }

    alcCloseDevice(device);
    return 0;
}
