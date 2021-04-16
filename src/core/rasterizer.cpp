#include "rasterizer.h"

Rasterizer::Rasterizer(int width, int height) : width_(width), height_(height) {
    glm::vec4 bg_color(0.f, 0.f, 0.f, 255.f);
    float float_min = std::numeric_limits<float>::lowest();

    buffer::InitBuffer(width_, height_, bg_color, frame_buffer_);
    buffer::InitBuffer(width_, height_, float_min, depth_buffer_);
}
Rasterizer::~Rasterizer() {
    buffer::DestoryBuffer(width_, height_, depth_buffer_);
    buffer::DestoryBuffer(width_, height_, frame_buffer_);
}

// todo: use MeshIndexList
void Rasterizer::DrawModel() {
    if (list_.size() < 3)
        return; 

    for (int i = 0; i < list_.size() - 2; i++) {

        // every primitive
        Triangle tri = {list_[i], list_[i + 1], list_[i + 2]};
        DrawPrimitive(tri);
    }
}

void Rasterizer::DrawPrimitive(Triangle tri) {

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
        utils::ViewPortTransformation(width_, height_, v);
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

// for test only
void Rasterizer::VertexShader(VertexPtr v) {
    v->coord.csc = v->coord.world;
}

// for test only
void Rasterizer::FragmentShader(int x, int y, ShaderInput &shader_input) {
    frame_buffer_[x][y] = shader_input.vec4_input["color"];

    std::ofstream outfile;
    outfile.open("log.txt", std::ios::out | std::ios::app);
    
    outfile << "(" << x << "," << y << ")" << ":"
            << "(" << frame_buffer_[x][y].r << ","
            << frame_buffer_[x][y].g << ","
            << frame_buffer_[x][y].b << "," << ")" << std::endl;
}

FrameBuffer Rasterizer::GetFrameBuffer() {
    return frame_buffer_;
}

void Rasterizer::SetVertexIndexList(VertexIndexList &list) {
    list_ = list;
}