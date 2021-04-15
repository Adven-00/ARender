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
using Triangle = std::array<VertexPtr, 3>;

namespace utils {
    
    float TriangleSquare(Triangle tri);

    bool IsInTriangle(int x, int y, Triangle tri);

    // return 2D boundingbox of triangle
    BoundingBox2D GetBoundingBox(Triangle tri);

    // judge whether vertex.coord.csc is in clip space
    bool InClipSpace(VertexPtr v);

    // interpolate vertex.shader_input_ for fragment shader
    // tnterpolated depth will be written into output for depth test
    ShaderInput Interpolate(std::array<float, 3> coeff, Triangle tri);

    // get interpolate coefficent
    std::array<float, 3> GetInterpolateCoeff(int x, int y, Triangle tri);

    // calculate vertex.coord.ndc
    void HomogeneousDivision(VertexPtr v);

    // calculate vertex.coord.screen and vertex.coord.screen_int
    void ViewPortTransformation(int width, int height, VertexPtr v);
};

#endif // UTILS_H_