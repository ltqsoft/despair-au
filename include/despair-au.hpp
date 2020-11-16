#ifndef DESPAIR_AU_HPP
#define DESPAIR_AU_HPP

#include <string>
#include <vector>


class despair_au
{
    typedef despair_au _THIS;
public:
    typedef std::string             string;     //$ API-used string.
    typedef std::vector<int8_t>     i8array;    //$ array of signed bytes.
    typedef std::vector<uint8_t>    ui8array;   //$ array of unsigned bytes.
    typedef const float*            float3;     //$ array of 3 float values.
    typedef float                   norm32;     //$ float value between 0 and 1.

    enum class err {
        none=0, audio_device, context, file_api_convert, file_not_found, ogg_hole
    };

    struct buf_info { uint32_t format, frequency; };

    class al_source
    {
    public:
        al_source();
        al_source(const al_source&) = default;
        ~al_source();

        al_source& operator=(const al_source&) = default;

        void init(const i8array& wBufferData, const buf_info& wInfo, bool repeating = false);
        void cleanup();
        void enable_repeating();
        void disable_repeating();
        void follow_listener();
        void unfollow_listener();

        void play();
        void pause();
        void replay();
        void stop();

        inline uint32_t id() const { return id_; }
        inline uint32_t buf() const { return buffer_; }

        norm32 volume() const;      //$ getter
        void volume(norm32 wValue); //$ setter

    private:
        uint32_t id_, buffer_;
    };

    static err init();
    static void terminate();
    static err load_ogg(const string& wFilePath, i8array& wData, buf_info& wInfo);
    static err load_wav(const string& wFilePath);

    static void play(const al_source& wSource);
    static void play(const al_source& wSource, const al_source& wSourceToShutUp);

    static float3 listener_pos();               //$ getter
    static void listener_pos(float3 wPos);      //$ setter
    static norm32 master_volume();              //$ getter
    static void master_volume(norm32 wValue);   //$ setter

private:
    typedef bool endian_t;
    static constexpr endian_t big_endian = true;
    static constexpr endian_t little_endian = false;

    static float listenerPos_[3];

    static endian_t getEndian();
};

#endif // DESPAIR_AU_HPP
