#include "render.h"

Render::Render(int width, int height) 
    : width_(width),
      height_(height),
      depth_buffer_(width, height, config::render::MaxDepth),
      color_buffer_(width, height, config::render::Background) {
          RefreshUniform();
      }

// Meyers' Singleton
Render &Render::Instance(int width, int height) {
    static Render instance(width, height);
    return instance;
}

void Render::DrawModel(Model &model) {
    for (auto &t : model.Faces()) {
        DrawTriangle(t);
    }
}

void Render::RefreshUniform() {
    uniform_.proj_mat = camera_.GetProjMat();
    uniform_.view_mat = camera_.GetViewMat();
    // uniform_.view_mat = camera_.GetModelMat();
    uniform_.RefreshMvp();
}

void Render::DrawTriangle(const Triangle &tri) {

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
    if (s == 0)
        return;

    utils::BoundingBox2D bb = utils::BoundingBox(tri);

    // every pixel of primitive
    for (int x = bb.x_min; x < bb.x_max; x++) {
        for (int y = bb.y_min; y < bb.y_max; y++) {

            std::array<float, 3> bc = utils::BarycentricCoordinate(x, y, s, tri);
            if (!utils::InTriangle(bc)) continue;

            std::array<float, 3> coeff = utils::PespectiveCorrection(bc, tri);
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

void Render::SetVertexShader(const VertexShader &vertex_shader) {
    vertex_shader_ = vertex_shader;
}

void Render::SetFragmentShader(const FragmentShader &fragment_shader) {
    fragement_shader_ = fragment_shader;
}

ColorBuffer Render::Output() {
    return color_buffer_;
}