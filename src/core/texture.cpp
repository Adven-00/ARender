#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <glm/gtx/compatibility.hpp>

Texture::Texture() 
    : width_(0), height_(0), data_(nullptr) {}

Texture::~Texture() {
    stbi_image_free(data_);
}

Texture::Texture(std::string texture_path) {
    int n;
    stbi_set_flip_vertically_on_load(1);
    data_ = stbi_load(texture_path.c_str(), &width_, &height_, &n, 4);
}

void Texture::Load(std::string texture_path) {
    int n;
    stbi_set_flip_vertically_on_load(1);
    data_ = stbi_load(texture_path.c_str(), &width_, &height_, &n, 4);
}

glm::vec4 Texture::Color(float u, float v) {
    float x = u * width_;
    float y = v * height_;
    int xl = int(x);
    int xr = int(x) + 1;
    int yb = int(y);
    int yt = int(y) + 1;

    auto xy_to_n = [=](int x, int y){return y * width_ + x;};
    auto get_color = [=](int x, int y) {
        glm::vec4 c;
        c.r = data_[xy_to_n(x, y) * 4];
        c.g = data_[xy_to_n(x, y) * 4 + 1];
        c.b = data_[xy_to_n(x, y) * 4 + 2];
        c.a = data_[xy_to_n(x, y) * 4 + 3];
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