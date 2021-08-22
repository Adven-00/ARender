#ifndef BUFFER_H_
#define BUFFER_H_  

#include "vertex.h"

#include <glm/vec4.hpp>
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

    // for color/depth buffer
    void Set(int x, int y, T content);
    T Get(int x, int y);

    // for vertex buffer
    void Add(T content);
    T Get(int n);
    T *GetPointer(int n);
    int Size();
};

using ColorBuffer = Buffer<glm::vec4>;
using VertexBuffer = Buffer<Vertex>;
using DepthBuffer = Buffer<float>;

constexpr auto COLOR_BUFFER_DEFAULT = glm::vec4(0.f, 0.f, 0.f, 255.f);
constexpr auto DEPTH_BUFFER_DEFAULT = -9999.f;

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
T Buffer<T>::Get(int n) {
    return buffer_.at(n);
}

template<typename T>
T *Buffer<T>::GetPointer(int n) {
    return buffer_.data() + n;
}

template<typename T>
T Buffer<T>::Get(int x, int y) {
    return buffer_[xy_to_n(x, y)];
}

template<typename T>
void Buffer<T>::Add(T content) {
    buffer_.push_back(content);
}

template<typename T>
int Buffer<T>::Size() {
    return int(buffer_.size());
}

#endif //BUFFER_H_h