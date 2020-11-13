#ifndef DESPAIR_AU_HPP
#define DESPAIR_AU_HPP

#include <string>


class despair_au
{
    typedef despair_au _THIS;
public:
    typedef std::string string;
    enum class err {
        none=0, ogg_hole
    };
    static err load_ogg(const string& wFilePath);
};

#endif // DESPAIR_AU_HPP
