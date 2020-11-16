#include <despair-au.hpp>
#include <iostream>

#define OGG_FILE "../examples/LoL_LoginScreenIntro_6.10.ogg"
#define ERR_INIT           1
#define ERR_OGG_LOAD       2


int main()
{
    if(despair_au::init() != despair_au::err::none)
    {
        std::cerr << "despair-au: init failed!\n";
        return ERR_INIT;
    }

    despair_au::i8array     buffer;
    despair_au::buf_info    bufferInfo;

    despair_au::err err = despair_au::load_ogg(OGG_FILE, buffer, bufferInfo);
    if(err != despair_au::err::none)
    {
        std::cerr << "Failed loading OGG file!\n";
        return ERR_OGG_LOAD;
    } else
    {
        std::cout <<
            "Buffer data size: " << buffer.size() <<
            " bytes (" << static_cast<double>(buffer.size()) / 1024.0 <<
            ").\n";
    }

    despair_au::al_source source;
    source.init(buffer, bufferInfo);
    source.replay();

    std::cout <<
        "Type command 'q' to quit.\n\n"
        "user@despair-au>$ ";

    while(std::tolower(std::cin.get()) != 'q')
    {
        // Do nothing, just keep the console window open.
    }

    source.cleanup();
    despair_au::terminate();
    std::cout << "Bye.\n";
    return 0;
}
