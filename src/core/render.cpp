#include "render.h"

Render::Render(int width, int height) 
    : width_(width),
      height_(height),
      depth_buffer_(width, height, config::buffer::Depth),
      color_buffer_(width, height, config::buffer::Color) {}

void Render::DrawModel(Model &model) {
    for (auto &t : model.Faces()) {
        DrawTriangle(t);
    }
}

void Render::DrawTriangle(Triangle tri) {

    // every vertex of primitive
    for (auto &v : tri) {

        // calculate v->coord.csc
        vertex_shader_(v, uniform_);

        // clip in homogeneous space
        if (!utils::InClipSpace(v)) {
            // todo: homogeneous clip
            return;
        }

        utils::HomogeneousDivision(v);
        utils::ViewPortTransform(width_, height_, v);
    }
        
    float s = utils::ScreenTriangleSquare(tri);    
    if (s == 0) return;

    utils::BoundingBox2D bb = utils::BoundingBox(tri);

    // every pixel of primitive
    for (int x = bb.x_min; x < bb.x_max; x++) {
        for (int y = bb.y_min; y < bb.y_max; y++) {

            if (!utils::InTriangle(x, y, tri)) 
                continue;
            std::array<float, 3> coeff = utils::InterpolateCoeff(x, y, s, tri);

            float depth = utils::InterpolateDepth(coeff, tri);

            // depth test
            if (depth < depth_buffer_.Get(x, y)) {
                continue;
            } else {
                depth_buffer_.Set(x, y, depth);    
            }

            Attr attr = utils::Interpolate(coeff, tri);
            color_buffer_.Set(x, y, fragement_shader_(attr, uniform_));
        }
    }
}

void Render::SetVertexShader(VertexShader vertex_shader) {
    vertex_shader_ = vertex_shader;
}

void Render::SetFragmentShader(FragmentShader fragment_shader) {
    fragement_shader_ = fragment_shader;
}

void Render::SetUniform(Uniform &uniform) {
    uniform_ = uniform;
}

ColorBuffer Render::Output() {
    return color_buffer_;
}