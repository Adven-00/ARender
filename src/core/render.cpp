#include "render.h"

Render::Render(int width, int height) 
    : width_(width),
      height_(height),
      depth_buffer_(width, height, config::render::MaxDepth),
      color_buffer_(width, height, config::render::Background) {
          frame_data_ = new unsigned char[width_ * height_ * 4];
      }

// Meyers' Singleton
Render *Render::Instance(int width, int height) {
    static Render instance(width, height);
    return &instance;
}

Render::~Render() {
    delete[] frame_data_;
}

void Render::DrawModel() {
    RefreshUniform();
    RefreshBuffer();

    for (auto &t : model_.Faces()) {
        DrawTriangle(t);
    }
}

void Render::RefreshUniform() {
    uniform_.proj_mat = camera_.GetProjMat();
    uniform_.view_mat = camera_.GetViewMat();
    uniform_.mvp_mat = uniform_.proj_mat * uniform_.view_mat * uniform_.model_mat;
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

void Render::SetVertexShader(const VertexShader &vs) {
    vertex_shader_ = vs;
}

void Render::SetFragmentShader(const FragmentShader &fs) {
    fragement_shader_ = fs;
}

void Render::SetShader(const VertexShader &vs, const FragmentShader &fs) {
    vertex_shader_ = vs;
    fragement_shader_ = fs;
}

void Render::RefreshBuffer() {
    color_buffer_.Reset(config::render::Background);
    depth_buffer_.Reset(config::render::MaxDepth);
}

unsigned char *Render::GetFrameData() {
    int index = 0;
    int size = width_ * height_;

    for (int i = 0; i < size; i++) {
        auto pixel = color_buffer_.Get(i % width_, i / width_);
        frame_data_[index++] = (unsigned char)pixel.r;
        frame_data_[index++] = (unsigned char)pixel.g;
        frame_data_[index++] = (unsigned char)pixel.b;
        frame_data_[index++] = (unsigned char)pixel.a;
    }

    return frame_data_;
}

std::array<int, 2> Render::GetFrameSize() {
    return {width_, height_};
}