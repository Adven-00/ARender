#pragma once

#ifndef RASTERRIZER_H_
#define RASTERRIZER_H_  

#include "utils.h"
#include "buffer.h"

#include <array>

class Rasterizer {

protected:
    int width_;
    int height_;

    FrameBuffer frame_buffer_;
    DepthBuffer depth_buffer_;

    VertexIndexList list_;

protected:
    virtual void VertexShader(VertexIndex v);
    virtual void FragmentShader(ShaderInput shader_input);

protected:
    Rasterizer(int width, int height);

    void SetVertexIndex(VertexIndexList vertex_index);

    void DrawPrimitive(Triangle tri);
    void DrawModel();
};

#endif // RASTERIZER_H_