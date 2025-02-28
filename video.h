#ifndef VIDEO_H
#define VIDEO_H

#include <string_view>

class Video {
public:
    Video();

private:
    std::string_view fileName;
};

#endif // VIDEO_H
