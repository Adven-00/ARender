#include "rasterizer.h"

Rasterizer::Rasterizer(int width, int height) : width_(width), height_(height),
    depth_buffer_(width, height), frame_buffer_(width, height) {

    for (int x = 0; x < width_; x++) {
        for (int y = 0; y < height_; y++) {
            frame_buffer_[x][y] = glm::vec4(0.f, 0.f, 0.f, 255.f);
            depth_buffer_[x][y] = 0.f;
        }
    }
}

void Rasterizer::DrawModel() {
    if (list_.size() < 3)
        return; 

    for (int i = 0; i < list_.size() - 3; i++) {

        // every primitive
        Triangle tri = {i, i + 1, i + 2};
        DrawPrimitive(tri);
    }
}

void Rasterizer::DrawPrimitive(Triangle tri) {

    // every vertex of primitive
    for (auto &v : tri) {

        // calculate list[v]->coord.csc
        VertexShader(v);

        // clip in homogeneous space
        if (!utils::InClipSpace(v, list_)) {
            // todo: homogeneous clip
            return;
        }

        utils::HomogeneousDivision(v, list_);
        utils::ViewPortTransformation(width_, height_, v, list_);
    }
        
    if (utils::TriangleSquare(tri, list_) == 0)
        return;

    BoundingBox2D bb = utils::GetBoundingBox(tri, list_);

    // every pixel of primitive
    for (int x = bb.x_min; x < bb.x_max; x++) {
        for (int y = bb.y_min; y < bb.y_max; y++) {

            if (!utils::IsInTriangle(x, y, tri, list_))
                continue;

            ShaderInput fs_input = utils::Interpolate(x, y, tri, list_);

            // Z-buffer test
            if (fs_input.float_input["depth"] < depth_buffer_[x][y]) {
                depth_buffer_[x][y] = fs_input.float_input["depth"];

                FragmentShader(fs_input);

            }
        }
    }
}

void Rasterizer::VertexShader(VertexIndex v) {
    VertexPtr vertex = list_[v];
    vertex->coord.csc = vertex->coord.world;
}