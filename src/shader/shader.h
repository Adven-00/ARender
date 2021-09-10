#ifndef SHADER_H_
#define SHADER_H_

#include "vertex.h"
#include "uniform.h"

#include <functional>

#include <glm/vec4.hpp>
#include <glm/vec3.hpp>

using VertexShader = std::function<void(Vertex *v, Uniform &uniform)>;
using FragmentShader = std::function<glm::vec4(Attr &attr, Uniform &uniform)>;

// for test only
inline void VS_1(Vertex *v, Uniform &uniform_) {
    v->coord.csc = uniform_.mvp_mat * v->coord.world;
}

inline glm::vec4 FS_1(Attr &attr, Uniform &uniform_) {
    return attr.vec4_attr["color"];
}

inline glm::vec4 FS_2(Attr &attr, Uniform &uniform) {
    float u = attr.vec2_attr["uv"].x;
    float v = attr.vec2_attr["uv"].y;

    return uniform.texture.Color(u, v);
}


#endif // SHADER_H_