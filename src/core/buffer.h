#ifndef BUFFER_H_
#define BUFFER_H_  

#include "vertex.h"
#include "config.h"

#include <vector>

template<typename T>
class Buffer {

private:
    int width_;
    int height_;

    std::vector<T> buffer_;

    int xy_to_n(int x, int y);

public:
    Buffer(int width, int height, T content);
    Buffer() = default;
    ~Buffer() = default;

    void Set(int x, int y, T content);
    T Get(int x, int y);
};

using ColorBuffer = Buffer<glm::vec4>;
using DepthBuffer = Buffer<float>;

// the origin is in the lower left corner of screen
template<typename T>
int Buffer<T>::xy_to_n(int x, int y) {
    return y * width_ + x;
}

template<typename T>
Buffer<T>::Buffer(int width, int height, T content) 
    : width_(width), height_(height) {
    buffer_.resize(width * height, content);
}

template<typename T>
void Buffer<T>::Set(int x, int y, T content) {
    buffer_[xy_to_n(x, y)] = content;
}

template<typename T>
T Buffer<T>::Get(int x, int y) {
    return buffer_[xy_to_n(x, y)];
}

#endif //BUFFER_H_h