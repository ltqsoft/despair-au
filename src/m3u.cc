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
#include "m3u.hh"


DESPAIR_AU_NAMESPACE_BEGIN


m3u::m3u() {}
m3u::~m3u() {}


despair_au_result m3u::load_form_file(const std::string& wPath)
{
    std::ifstream file(wPath);
    if(!file.good()) return despair_au_result::err_file_load;

    std::string line;
    std::getline(file, line);
    if(line != "#EXTM3U") return despair_au_result::err_not_a_m3u;
    while(std::getline(file, line)) 
    {
        if(line.substr(0,8) == "#EXTINF:") {
            std::getline(file, line);
            std::cout << "Found sound track " << line << '\n';
        } // no_else
    }
    return despair_au_result::success;
}


DESPAIR_AU_NAMESPACE_END
