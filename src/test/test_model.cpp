#include "tool.h"

inline void VS_2(Vertex *v, Uniform &uniform) {
    v->coord.csc = uniform.mvp_mat * v->coord.world;
}

inline glm::vec4 FS_2(Attr &attr, Uniform &uniform) {
    float u = attr.vec2_attr["uv"].x;
    float v = attr.vec2_attr["uv"].y;

    return uniform.texture.Color(u, v);
}

int main() {
    const int w = 500;
    const int h = 500;

    Uniform u;

    Model m("cube");
    m.LoadVertices();
    m.LoadTexture("rock.png");
    m.AlterUniformTexture(u);
    

    Camera c;
    c.AlterUniform(u);

    Render r(w, h);
    r.SetUniform(u);

    r.SetFragmentShader(FS_2);
    r.SetVertexShader(VS_2);

    r.DrawModel(m);
    SaveImage(w, h, r.Output());

    return 0;
}