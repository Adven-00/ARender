#include "tool.h"

inline void VS_1(Vertex *v, Uniform &uniform) {
    v->coord.csc = uniform.mvp_mat * v->coord.world;
}

inline glm::vec4 FS_1(Attr &attr, Uniform &uniform) {
    return attr.vec4_attr["color"];
}

int main() {
    glm::vec4 red(255.f, 0.f, 0.f, 255.f);
    glm::vec4 blue(0.f, 0.f, 255.f, 255.f);
    glm::vec4 green(0.f, 255.f, 0.f, 255.f);
    glm::vec4 yellow(255.f, 255.f, 0.f, 255.f);
    glm::vec4 cyan(0.f, 255.f, 255.f, 255.f);
    glm::vec4 purple(255.f ,0.f, 255.f, 255.f);

    glm::vec4 _1(1.f, -1.f, -1.f, 1.f);
    glm::vec4 _2(1.f, -1.f, 1.f, 1.f);
    glm::vec4 _3(-1.f, -1.f, 1.f, 1.f);
    glm::vec4 _4(-1.f, -1.f, -1.f, 1.f);
    glm::vec4 _5(1.f, 1.f, -1.f, 1.f);
    glm::vec4 _6(1.f, 1.f, 1.f, 1.f);
    glm::vec4 _7(-1.f, 1.f, 1.f, 1.f);
    glm::vec4 _8(-1.f, 1.f, -1.f, 1.f);

    Triangle t_1 = MakeTriangle({_5, _1, _4}, red);
    Triangle t_2 = MakeTriangle({_5, _8, _4}, red);
    Triangle t_3 = MakeTriangle({_3, _8, _7}, yellow);
    Triangle t_4 = MakeTriangle({_3, _8, _4}, yellow);
    Triangle t_5 = MakeTriangle({_3, _2, _6}, blue);
    Triangle t_6 = MakeTriangle({_3, _6, _7}, blue);
    Triangle t_7 = MakeTriangle({_1, _5, _2}, green);
    Triangle t_8 = MakeTriangle({_5, _6, _2}, green);
    Triangle t_9 = MakeTriangle({_5, _6, _8}, purple);
    Triangle t_10 = MakeTriangle({_8, _7, _6}, purple);
    Triangle t_11 = MakeTriangle({_1, _2, _3}, cyan);
    Triangle t_12 = MakeTriangle({_3, _4, _1}, cyan);

    const int w = 500;
    const int h = 500;

    Uniform u;

    Camera ca;
    ca.AlterUniform(u);

    Render r(w, h);
    r.SetUniform(u);
    r.SetFragmentShader(FS_1);
    r.SetVertexShader(VS_1);

    r.DrawTriangle(t_1);
    r.DrawTriangle(t_2);
    r.DrawTriangle(t_3);
    r.DrawTriangle(t_4);
    //r.DrawTriangle(t_5);
    //r.DrawTriangle(t_6);
    r.DrawTriangle(t_7);
    r.DrawTriangle(t_8);
    r.DrawTriangle(t_9);
    r.DrawTriangle(t_10);
    r.DrawTriangle(t_11);
    r.DrawTriangle(t_12);

    SaveImage(w, h, r.Output());

    return 0;
};