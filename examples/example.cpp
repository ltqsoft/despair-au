#include <despair-au.hpp>

#define OGG_FILE "../examples/LoL_LoginScreenIntro_6.10.ogg"

int main()
{
    despair_au::i8array buffer;
    despair_au::buf_info bufferInfo;
    despair_au::load_ogg(OGG_FILE, buffer, bufferInfo);
    return 0;
}
