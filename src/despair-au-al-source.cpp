//#include "pch.h"
#include "despair-au.hpp"
#include <AL/al.h>


despair_au::al_source::al_source() : id_(0), buffer_(0) {}


despair_au::al_source::~al_source() {}


void despair_au::al_source::init(const i8array& wBufferData, const buf_info& wInfo, bool repeating)
{
    alGenBuffers(1, &buffer_);
    alBufferData(buffer_, wInfo.format, wBufferData.data(), wBufferData.size(), wInfo.frequency);

    alGenSources(1, &id_);
    alSourcei(id_, AL_BUFFER, buffer_);

    if(repeating) alSourcei(id_, AL_LOOPING, AL_TRUE);
}


void despair_au::al_source::cleanup()
{
    alSourceStop(id_);
    alDeleteSources(1, &id_);
    alDeleteBuffers(1, &buffer_);
}


void despair_au::al_source::enable_repeating()
{
    alSourcei(id_, AL_LOOPING, AL_TRUE);
}


void despair_au::al_source::disable_repeating()
{
    alSourcei(id_, AL_LOOPING, AL_FALSE);
}


void despair_au::al_source::follow_listener()
{
    alSourcei(id_, AL_SOURCE_RELATIVE, AL_TRUE);
}


void despair_au::al_source::unfollow_listener()
{
    alSourcei(id_, AL_SOURCE_RELATIVE, AL_FALSE);
}


void despair_au::al_source::play()
{
    ALint state;
    alGetSourcei(id_, AL_SOURCE_STATE, &state);
    if(state != AL_PLAYING) alSourcePlay(id_);
}


void despair_au::al_source::pause()
{
    alSourcePause(id_);
}


void despair_au::al_source::replay()
{
    alSourcePlay(id_);
}


void despair_au::al_source::stop()
{
    alSourceStop(id_);
}


despair_au::norm32 despair_au::al_source::volume() const
{
    norm32 ret;
    alGetSourcef(id_, AL_GAIN, &ret);
    return ret;
}


void despair_au::al_source::volume(norm32 wValue)
{
    if(wValue > 1.0f) wValue = 1.0f;
    else if(wValue < 0.0f) wValue = 0.0f;
    alSourcef(id_, AL_GAIN, wValue);
}
