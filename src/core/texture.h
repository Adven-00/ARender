#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "config.h"

#include <string>
#include <vector>

class Texture {
private:
    std::string path_;

    int width_;
    int height_;
    std::vector<unsigned char> map_;
    //norm data
public:
    Texture(std::string path = config::texture::Path);

    //2d sampler
    glm::vec4 Color(float u, float v);
    void LoadMap();
};

#endif // TEXTURE_H_