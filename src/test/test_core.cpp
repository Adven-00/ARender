#include "tool.h"

int main() {
    glm::vec4 red(255.f, 0.f, 0.f, 255.f);
    glm::vec4 blue(0.f, 0.f, 255.f, 255.f);
    glm::vec4 green(0.f, 255.f, 0.f, 255.f);
    glm::vec4 yellow(255.f, 255.f, 0.f, 255.f);

    glm::vec4 p_a(5.f, 5.f, -10.f, 1.f);
    glm::vec4 p_b(-5.f, 5.f, -5.1f, 1.f);
    glm::vec4 p_c(-5.f, -5.f, -10.f, 1.f);
    glm::vec4 p_d(5.f, -5.f, -10.f, 1.f);

    Triangle tri_1 = MakeTriangle({p_a, p_b, p_c}, red);
    Triangle tri_2 = MakeTriangle({p_d, p_c, p_a}, blue);
    Triangle tri_3 = MakeTriangle({p_d, p_c, p_b}, green);

    const int w = 600;
    const int h = 600;

    Render r(w, h);

    Camera c;
    Uniform u;
    c.ChangeUniform(u);
    r.SetUniform(u);

    r.DrawTriangle(tri_1);
    r.DrawTriangle(tri_2);
    r.DrawTriangle(tri_3);

    SaveImage(w, h, 3, r.GetColorBuffer());
    return 0;
};