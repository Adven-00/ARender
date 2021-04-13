#pragma once

#ifndef BUFFER_H_
#define BUFFER_H_  

#include <glm/glm.hpp>
#include <glm/ext.hpp>

template<typename T>
class Buffer {

private:
    int width_;
    int height_;

    T **buffer_;

public:
    Buffer(int width, int height);
    ~Buffer();

    T* operator[](int x);

    int GetWidth();
    int GetHeight();
};

using FrameBuffer = Buffer<glm::vec4>;
using DepthBuffer = Buffer<float>;

template<typename T>
Buffer<T>::Buffer(int width, int height) : width_(width), height_(height) {
    buffer_ = new T*[width_];
    for (int i = 0; i < width_; i++) {
        buffer_[i] = new T[height_];
    }
}

template<typename T>
Buffer<T>::~Buffer() {
    for (int i = 0; i < width_; i++) {
        delete[] buffer_[i];
    }
    delete[] buffer_;
}

template<typename T>
T* Buffer<T>::operator[](int x) {
    return buffer_[x];
}

template<typename T>
int Buffer<T>::GetWidth() {
    return width_;
}

template<typename T>
int Buffer<T>::GetHeight() {
    return height_;
}


#endif // BUFFER_H_