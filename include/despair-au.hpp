#ifndef DESPAIR_AU_HPP
#define DESPAIR_AU_HPP

#include <string>
#include <vector>


class despair_au
{
    typedef despair_au _THIS;
public:
    typedef std::string string;
    typedef std::vector<int8_t> i8array;
    typedef std::vector<uint8_t> ui8array;
    enum class err {
        none=0, file_api_convert, file_not_found, ogg_hole
    };
    struct buf_info {
        uint32_t format, frequency;
    };

    static err load_ogg(const string& wFilePath, i8array& wData, buf_info& wInfo);
    static err load_wav(const string& wFilePath);

private:
    typedef bool endian_t;
    static constexpr endian_t big_endian = true;
    static constexpr endian_t little_endian = false;
    static endian_t getEndian();
};

#endif // DESPAIR_AU_HPP
