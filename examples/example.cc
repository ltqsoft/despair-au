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
#include <despair-au.hh>
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

    std::cout << "Type command 'q' to quit.\n\n" "user@despair-au>$ ";

    float Delta = 0.1f;
    std::string command;
    do{
        std::getline(std::cin, command);
        if(command == "lower-volume") {
            source.volume(source.volume() - Delta);
            std::cout << "new volume: " << source.volume() << '\n';
            continue;
        } // no_else
        if(command == "raise-volume") {
            source.volume(source.volume() + Delta);
            std::cout << "new volume: " << source.volume() << '\n';
            continue;
        } // no_else
        if(command == "help") {
            std::cout << "lower-volume\n" "raise-volume\n"  "q (or quit)\n";
            continue;
        } // no_else
        if(command == "q" || command == "quit") break;
        std::cout << "ERROR: unknown command " << command << '\n';
    }while(true);

    source.cleanup();
    despair_au::terminate();
    std::cout << "Bye.\n";
    return 0;
}
