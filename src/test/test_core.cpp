#include "../core/rasterizer.h"

#include <memory>

int main() {
    glm::vec4 red(255.f, 0.f, 0.f, 255.f);
    glm::vec4 blue(0.f, 0.f, 255.f, 255.f);
    glm::vec4 yellow(0.f, 255.f, 0.f, 255.f);

    glm::vec4 pos_a(-0.5f, -0.5f, 0.1f, 1.f);
    glm::vec4 pos_b(0.5f, -0.5f, 0.1f, 1.f);
    glm::vec4 pos_c(0.f, 0.5f, 0.1f, 1.f);

    Vertex a;
    ShaderInput shader_input_a;
    shader_input_a.vec4_input["color"] = red;
    a.coord.world = pos_a;
    a.shader_input = shader_input_a;

    Vertex b;
    ShaderInput shader_input_b;
    shader_input_b.vec4_input["color"] = yellow;
    b.coord.world = pos_b;
    b.shader_input = shader_input_b;

    Vertex c;
    ShaderInput shader_input_c;
    shader_input_c.vec4_input["color"] = blue;
    c.coord.world = pos_c;
    c.shader_input = shader_input_c;

    VertexIndexList list = {{0, std::make_shared<Vertex>(a)},
                            {1, std::make_shared<Vertex>(b)},
                            {2, std::make_shared<Vertex>(c)}};

    const int w = 300;
    const int h = 300;

    Rasterizer r(w, h);
    r.SetVertexIndexList(list);
    r.DrawModel();

    auto frame_buffer_ = r.GetFrameBuffer();



    return 0;
};