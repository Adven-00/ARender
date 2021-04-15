#pragma once

#ifndef RASTERRIZER_H_
#define RASTERRIZER_H_  

#include "utils.h"
#include "buffer.h"

#include <array>
#include <iostream>
#include <limits>

template<int w, int h>
class Rasterizer {

protected:
    FrameBuffer<w, h> frame_buffer_;
    DepthBuffer<w, h> depth_buffer_;

    VertexIndexList list_;
    // ModelIndex

protected:
    virtual void VertexShader(VertexPtr v); // = 0
    virtual void FragmentShader(int x, int y, ShaderInput &shader_input); // = 0

public: // protected
    void DrawPrimitive(Triangle tri);
    void DrawModel();

    Rasterizer();

    void SetVertexIndexList(VertexIndexList &list_);
    FrameBuffer<w, h> GetFrameBuffer();
};

template<int w, int h>
Rasterizer<w, h>::Rasterizer() {

    for (int x = 0; x < w; x++) {
        for (int y = 0; y < h; y++) {
            frame_buffer_[x][y] = glm::vec4(0.f, 0.f, 0.f, 255.f);
            depth_buffer_[x][y] = std::numeric_limits<float>::lowest();
        }
    }
}

// todo: use MeshIndexList
template<int w, int h>
void Rasterizer<w, h>::DrawModel() {
    if (list_.size() < 3)
        return; 

    for (int i = 0; i < list_.size() - 2; i++) {

        // every primitive
        Triangle tri = {list_[i], list_[i + 1], list_[i + 2]};
        DrawPrimitive(tri);
    }
}

template<int w, int h>
void Rasterizer<w, h>::DrawPrimitive(Triangle tri) {

    // every vertex of primitive
    for (auto &v : tri) {

        // calculate list[v]->coord.csc
        VertexShader(v);

        // clip in homogeneous space
        if (!utils::InClipSpace(v)) {
            // todo: homogeneous clip
            return;
        }

        utils::HomogeneousDivision(v);
        utils::ViewPortTransformation(w, h, v);
    }
        
    if (utils::TriangleSquare(tri) == 0)
        return;

    BoundingBox2D bb = utils::GetBoundingBox(tri);

    // every pixel of primitive
    for (int x = bb.x_min; x < bb.x_max; x++) {
        for (int y = bb.y_min; y < bb.y_max; y++) {

            if (!utils::IsInTriangle(x, y, tri))
                continue;

            std::array<float, 3> coeff = utils::GetInterpolateCoeff(x, y, tri);
            ShaderInput fs_input = utils::Interpolate(coeff, tri);

            // depth test
            if (fs_input.float_input["depth"] < depth_buffer_[x][y])
                continue;

            depth_buffer_[x][y] = fs_input.float_input["depth"];
            FragmentShader(x, y, fs_input);
        }
    }
}
// for test
template<int w, int h>
void Rasterizer<w, h>::VertexShader(VertexPtr v) {
    v->coord.csc = v->coord.world;
}

// for test
template<int w, int h>
void Rasterizer<w, h>::FragmentShader(int x, int y, ShaderInput &shader_input) {
    frame_buffer_[x][y] = shader_input.vec4_input["color"];

    /*
    std::cout << frame_buffer_[x][y].r << " "
              << frame_buffer_[x][y].g << " "
              << frame_buffer_[x][y].b << " "
              << frame_buffer_[x][y].a << " " << std::endl;
    */
}

template<int w, int h>
FrameBuffer<w, h> Rasterizer<w, h>::GetFrameBuffer() {
    return frame_buffer_;
}

template<int w, int h>
void Rasterizer<w, h>::SetVertexIndexList(VertexIndexList &list) {
    list_ = list;
}

#endif // RASTERIZER_H_