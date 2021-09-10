#ifndef BUFFER_H_
#define BUFFER_H_  

#include "config.h"

#include <vector>

template<typename T>
class Buffer {

private:
    int width_;
    int height_;

    std::vector<T> data_;

    // the origin is in the lower left corner of screen
    int xy_to_n(int x, int y) { return y * width_ + x; }

public:
    Buffer(int width, int height, const T &element);
    Buffer(int width, int height, const T *data, size_t data_len);
    Buffer() = default;
    ~Buffer() = default;

    void Reset(const T &element);
    void Set(int x, int y, const T &element);
    T Get(int x, int y);
};

using ColorBuffer = Buffer<glm::vec4>;
using DepthBuffer = Buffer<float>;

template<typename T>
Buffer<T>::Buffer(int width, int height, const T &element) 
    : width_(width), height_(height) {
    data_.resize(width * height, element);
}

template<typename T>
Buffer<T>::Buffer(int width, int height, const T *data, size_t data_len)
    : width_(width), height_(height) {
    data.assign(data, data + data_len);
}

template<typename T>
void Buffer<T>::Set(int x, int y, const T &element) {
    data_[xy_to_n(x, y)] = element;
}

template<typename T>
T Buffer<T>::Get(int x, int y) {
    return data_[xy_to_n(x, y)];
}

template<typename T>
void Buffer<T>::Reset(const T &element) {
    std::fill(data_.begin(), data_.end(), element);
}

#endif //BUFFER_H_h