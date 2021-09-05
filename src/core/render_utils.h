#ifndef UTILS_H_
#define UTILS_H_

#include "vertex.h"

namespace utils {

    struct BoundingBox2D {
        int x_min;
        int y_min;
        int x_max;
        int y_max;
    };
    
    // square of screen triangle
    float ScreenTriangleSquare(const Triangle &tri);

    bool InTriangle(const std::array<float, 3> &bc);

    // return 2D boundingbox of triangle
    BoundingBox2D BoundingBox(const Triangle &tri);

    // judge whether vertex.coord.csc is in clip space
    bool InClipSpace(Vertex *v);

    // interpolate vertex.attr for fragment shader
    Attr Interpolate(const std::array<float, 3> &coeff, const Triangle &tri);

    std::array<float, 3> PespectiveCorrection(const std::array<float, 3> &bc, const Triangle &tri);

    // calculate vertex.coord.ndc
    void HomogeneousDivision(Vertex *v);

    // calculate vertex.coord.screen and vertex.coord.screen_int
    void ViewPortTransform(int width, int height, Vertex *v);

    // interpolate depth for depth test
    float InterpolateDepth(const std::array<float, 3> &coeff, const Triangle &tri);

    // calculate barycentric coordinate of (x, y) in tri
    std::array<float, 3> BarycentricCoordinate(int x, int y, float s, const Triangle &tri);
};

#endif // UTILS_H_