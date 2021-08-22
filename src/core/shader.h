#ifndef SHADER_H_
#define SHADER_H_

#include "vertex.h"
#include "uniform.h"

#include <functional>

#include <glm/vec4.hpp>
#include <glm/vec3.hpp>

using VertexShader = std::function<void(Vertex *v, Uniform &uniform)>;
using FragmentShader = std::function<glm::vec4(Attr &attr, Uniform &uniform)>;

#endif // SHADER_H_