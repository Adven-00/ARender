#ifndef BUFFER_H_
#define BUFFER_H_  

#include "config.h"

#include <vector>

template<typename T>
class Buffer {

private:
    int width_;
    int height_;

    std::vector<T> buffer_;

    // the origin is in the lower left corner of screen
    int xy_to_n(int x, int y) { return y * width_ + x; }

public:
    Buffer(int width, int height, const T &element);
    Buffer(int width, int height, const T *data, size_t data_len);
    Buffer() = default;
    ~Buffer() = default;

    void Set(int x, int y, const T &element);
    T Get(int x, int y);
    T Get(float u, float v);
};

using ColorBuffer = Buffer<glm::vec4>;
using DepthBuffer = Buffer<float>;

template<typename T>
Buffer<T>::Buffer(int width, int height, const T &element) 
    : width_(width), height_(height) {
    buffer_.resize(width * height, element);
}

template<typename T>
Buffer<T>::Buffer(int width, int height, const T *data, size_t data_len)
    : width_(width), height_(height) {
    buffer_.assign(data, data + data_len);
}

template<typename T>
void Buffer<T>::Set(int x, int y, const T &element) {
    buffer_[xy_to_n(x, y)] = element;
}

template<typename T>
T Buffer<T>::Get(int x, int y) {
    return buffer_[xy_to_n(x, y)];
}

#endif //BUFFER_H_h