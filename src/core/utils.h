#ifndef UTILS_H_
#define UTILS_H_

#include "vertex.h"

struct BoundingBox2D {
    int x_min;
    int y_min;
    int x_max;
    int y_max;
};

namespace utils {
    // square of screen triangle
    float ScreenTriangleSquare(Triangle tri);

    // return 2D boundingbox of triangle
    BoundingBox2D BoundingBox(Triangle tri);

    // judge whether vertex.coord.csc is in clip space
    bool InClipSpace(Vertex *v);

    bool InTriangle(int x, int y, Triangle tri);

    // interpolate vertex.attr for fragment shader
    Attr Interpolate(std::array<float, 3> coeff, Triangle tri);

    // get interpolate coefficent
    std::array<float, 3> InterpolateCoeff(int x, int y, float s, Triangle tri);

    // calculate vertex.coord.ndc
    void HomogeneousDivision(Vertex *v);

    // calculate vertex.coord.screen and vertex.coord.screen_int
    void ViewPortTransform(int width, int height, Vertex *v);

    // interpolate depth for depth test
    float InterpolateDepth(std::array<float, 3> coeff, Triangle tri);

};

#endif // UTILS_H_