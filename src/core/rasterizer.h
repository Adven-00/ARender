#pragma once

#ifndef RASTERRIZER_H_
#define RASTERRIZER_H_  

#include "utils.h"
#include "buffer.h"

#include <array>
#include <memory>
#include <iostream>
#include <fstream>
#include <limits>

class Rasterizer {

protected:
    FrameBuffer frame_buffer_;
    DepthBuffer depth_buffer_;

    VertexIndexList list_;
    // ModelIndex

    int width_;
    int height_;

protected:
    virtual void VertexShader(VertexPtr v); // = 0
    virtual void FragmentShader(int x, int y, ShaderInput &shader_input); // = 0

public: // protected
    void DrawPrimitive(Triangle tri);
    void DrawModel();

    Rasterizer(int width, int height);
    ~Rasterizer();

    void SetVertexIndexList(VertexIndexList &list_);
    FrameBuffer GetFrameBuffer();
};

#endif // RASTERIZER_H_