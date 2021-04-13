#pragma once

#ifndef UTILS_H_
#define UTILS_H_

#include "vertex.h"

#include <array>
#include <map>
#include <memory>

struct BoundingBox2D {
    int x_min;
    int y_min;
    int x_max;
    int y_max;
};

using VertexIndex = int;
using VertexPtr = std::shared_ptr<Vertex>;
using VertexIndexList = std::map<VertexIndex, VertexPtr>;
using Triangle = std::array<VertexIndex, 3>;

namespace utils {

    float TriangleSquare(Triangle tri, VertexIndexList &list);

    bool IsInTriangle(int x, int y, Triangle tri, VertexIndexList &list);

    // return 2D boundingbox of triangle
    BoundingBox2D GetBoundingBox(Triangle tri, VertexIndexList &list);

    // judge whether vertex.coord.csc is in clip space
    bool InClipSpace(VertexIndex v, VertexIndexList &list);

    // interpolate vertex.shader_input_ for fragment shader
    ShaderInput Interpolate(int x, int y, Triangle tri, VertexIndexList &list);

    // calculate vertex.coord.ndc
    void HomogeneousDivision(VertexIndex v, VertexIndexList &list);

    // calculate vertex.coord.screen and vertex.coord.screen_int
    void ViewPortTransformation(int width, int height, VertexIndex v, VertexIndexList &list);
};

#endif // UTILS_H_