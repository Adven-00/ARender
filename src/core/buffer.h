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
    int size_;

    T *buffer_;

    int xy2n(int x, int y);

public:
    Buffer(int width, int height, T content);
    Buffer();
    ~Buffer();

    void Set(int x, int y, T content);
    void Set(int n, T content);

    T Get(int x, int y);
    T Get(int n);
};

using ColorBuffer = Buffer<glm::vec4>;
using VertexBuffer = Buffer<Vertex>;
using DepthBuffer = Buffer<float>;

constexpr auto BUFFER_SIZE_DEFAULT = 1000;
constexpr auto COLOR_BUFFER_DEFAULT = glm::vec4(0.f, 0.f, 0.f, 255.f);
constexpr auto DEPTH_BUFFER_DEFAULT = -9999.f;

// the origin is in the lower left corner of screen
template<typename T>
int Buffer<T>::xy2n(int x, int y) {
    return y * width_ + x;
}

template<typename T>
Buffer<T>::Buffer(int width, int height, T content) 
    : width_(width), height_(height), size_(height * width) {

    buffer_ = new T[size_];
    for (int i = 0; i < size_; i++) {
        buffer_[i] = content;
    }
}

template<typename T>
Buffer<T>::Buffer() 
    : width_(BUFFER_SIZE_DEFAULT), height_(1), size_(BUFFER_SIZE_DEFAULT) {
        
    buffer_ = new T[BUFFER_SIZE_DEFAULT];
}

template<typename T>
Buffer<T>::~Buffer() {
    delete[] buffer_;
}

template<typename T>
void Buffer<T>::Set(int n, T content) {
    if (n >= size_) {
        T *new_buffer_ = new T[n * 2];
        for (int i = 0; i < size_; i++) {
            new_buffer_[i] = buffer_[i];
        }
        delete[] buffer_;
        buffer_ = new_buffer_;
        size_ = n * 2;
    }
    buffer_[n] = content;
}

template<typename T>
void Buffer<T>::Set(int x, int y, T content) {
    buffer_[xy2n(x, y)] = content;
}

template<typename T>
T Buffer<T>::Get(int n) {
    return buffer_[n];
}

template<typename T>
T Buffer<T>::Get(int x, int y) {
    return buffer_[xy2n(x, y)];
}

#endif //BUFFER_H_h