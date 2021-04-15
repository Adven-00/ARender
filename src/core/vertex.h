#pragma once

#ifndef VERTEX_H_
#define VERTEX_H_ 

#include <map>
#include <string>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

// reserved key : "color", "uv", "norm", "depth"
struct ShaderInput {
    std::map<std::string, glm::vec4> vec4_input;
    std::map<std::string, glm::vec3> vec3_input;
    std::map<std::string, glm::vec2> vec2_input;
    std::map<std::string, float> float_input;
};

struct Coord {
    glm::vec4 world;        // homogeneous world coordinates
    glm::vec4 csc;          // homogeneous clip space coordinates
    glm::vec3 ndc;          // normalized device coordinates
    glm::vec3 screen;       // screen coordinates (z == 0)
    glm::ivec3 screen_int;  // interger screen coordinates (z == 0)
};

struct Vertex {
    ShaderInput shader_input;
    Coord coord;
};

#endif // VERTEX_H_
