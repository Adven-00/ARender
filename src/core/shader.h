#ifndef SHADER_H_
#define SHADER_H_

#include "vertex.h"
#include "uniform.h"

#include <functional>

#include <glm/vec4.hpp>
#include <glm/vec3.hpp>

using VertexShader = std::function<void(Vertex *v, Uniform &uniform)>;
using FragmentShader = std::function<glm::vec4(Attr &attr, Uniform &uniform)>;

inline void DefaultVertexShader(Vertex *v, Uniform &uniform) {
    v->coord.csc = uniform.mvp_mat * v->coord.world;
}

inline glm::vec4 DefaultFragmentShader(Attr &attr, Uniform &uniform) {
    return attr.vec4_attr["color"];
}

#endif // SHADER_H_