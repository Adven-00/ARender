#pragma once

#ifndef BUFFER_H_
#define BUFFER_H_  

#include <glm/vec4.hpp>

template<typename T>
using Buffer = T **;

using FrameBuffer = Buffer<glm::vec4>;
using DepthBuffer = Buffer<float>;

namespace buffer {
    template<typename T>
    void InitBuffer(int width, int height, T &content, Buffer<T> &buffer);

    template<typename T>
    void DestoryBuffer(int width, int height, Buffer<T> &buffer);
}

template<typename T>
void buffer::InitBuffer(int width, int height, T &content, Buffer<T> &buffer) {
    buffer = new T*[width];
    for (int i = 0; i < width; i++) {
        buffer[i] = new T[height];
    }

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            buffer[x][y] = content;
        }
    }
}

template<typename T>
void buffer::DestoryBuffer(int width, int height, Buffer<T> &buffer) {
    for (int x = 0; x < width; x++) {
        delete[] buffer[x];
    }
    delete[] buffer;
}

#endif // BUFFER_H_
