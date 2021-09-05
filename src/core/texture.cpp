#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <glm/gtx/compatibility.hpp>

Texture::Texture(std::string path) : path_(path) {
    LoadMap();
}

void Texture::LoadMap() {
    int temp;
    stbi_set_flip_vertically_on_load(1);
    unsigned char *map_data_ptr = stbi_load(path_.c_str(), &width_, &height_, &temp, 4);
    map_.assign(map_data_ptr, map_data_ptr + width_ * height_ * 4);
    stbi_image_free(map_data_ptr);
}

glm::vec4 Texture::Color(float u, float v) {
    float x = u * width_;
    float y = v * height_;
    int xl = int(x);
    int yb = int(y);
    int xr = (xl == width_ - 1) ? xl : xl + 1;
    int yt = (yb == height_ - 1) ? yb : yb + 1;

    auto xy_to_n = [=](int x, int y) {
        return y * width_ + x;
    };
    
    auto get_color = [=](int x, int y) {
        glm::vec4 c;
        c.r = map_[xy_to_n(x, y) * 4];
        c.g = map_[xy_to_n(x, y) * 4 + 1];
        c.b = map_[xy_to_n(x, y) * 4 + 2];
        c.a = map_[xy_to_n(x, y) * 4 + 3];
        return c;
    };

    auto xl_yb = get_color(xl, yb);
    auto xl_yt = get_color(xl, yt);
    auto xr_yb = get_color(xr, yb);
    auto xr_yt = get_color(xr, yt);

    auto xl_y = glm::lerp(xl_yb, xl_yt, yt - y);
    auto xr_y = glm::lerp(xr_yb, xr_yt, yt - y);

    auto x_y = glm::lerp(xl_y, xr_y, xr - x);

    return x_y;
}