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
