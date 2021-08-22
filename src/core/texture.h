#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "glm/vec4.hpp"

#include <string>

class Texture {
private:
    int width_;
    int height_;
    unsigned char *data_;

public:
    Texture();
    Texture(std::string texture_path);
    ~Texture();

    glm::vec4 Color(float u, float v);
    void Load(std::string texture_path);
};

#endif // TEXTURE_H_