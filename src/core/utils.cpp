#include "utils.h"

void utils::HomogeneousDivision(VertexPtr v) {
    v->coord.ndc = v->coord.csc / v->coord.csc.w;
}

void utils::ViewPortTransformation(int width, int height, VertexPtr v) {

    v->coord.screen.x = (v->coord.ndc.x + 1.0f) * width * 0.5f;
    v->coord.screen.y = (v->coord.ndc.y + 1.0f) * height * 0.5f;
    v->coord.screen.z = 0.f;

    v->coord.screen_int.x = int(v->coord.screen.x + 0.5f);
    v->coord.screen_int.y = int(v->coord.screen.y + 0.5f);
    v->coord.screen_int.z = 0;
}

float utils::TriangleSquare(Triangle tri) {
    auto [a, b, c] = tri;

    glm::vec3 ab = b->coord.screen - a->coord.screen;
    glm::vec3 ac = c->coord.screen - a->coord.screen;

    float s = glm::length(glm::cross(ab, ac));
    return s;
}

bool utils::InClipSpace(VertexPtr v) {
    float w = v->coord.csc.w;

    if (w == 0)
        return false;
    if (v->coord.csc.x < -w || v->coord.csc.x > w)
        return false;
    if (v->coord.csc.y < -w || v->coord.csc.y > w)
        return false;
    if (v->coord.csc.z < -w || v->coord.csc.z > w)
        return false;

    return true;
}

BoundingBox2D utils::GetBoundingBox(Triangle tri) {
    BoundingBox2D bb;
    auto [a, b, c] = tri;

    bb.x_max = glm::max(a->coord.screen_int.x, b->coord.screen_int.x, c->coord.screen_int.x);
    bb.x_min = glm::min(a->coord.screen_int.x, b->coord.screen_int.x, c->coord.screen_int.x);
    bb.y_max = glm::max(a->coord.screen_int.y, b->coord.screen_int.y, c->coord.screen_int.y);
    bb.y_min = glm::min(a->coord.screen_int.y, b->coord.screen_int.y, c->coord.screen_int.y);

    return bb;
}

bool utils::IsInTriangle(int x, int y, Triangle tri) {
    auto [a, b, c] = tri;

    glm::vec3 p((float)x + 0.5f, (float)y + 0.5f, 0.f);

    glm::vec3 pa = a->coord.screen - p;
    glm::vec3 pb = b->coord.screen - p;
    glm::vec3 pc = c->coord.screen - p;

    glm::vec3 pa_pb = glm::cross(pa, pb);
    glm::vec3 pb_pc = glm::cross(pb, pc);
    glm::vec3 pc_pa = glm::cross(pc, pa);

    if (pa_pb.z >= 0 && pb_pc.z >= 0 && pc_pa.z >=0)
        return true;

    if (pa_pb.z <= 0 && pb_pc.z <= 0 && pc_pa.z <=0)
        return true;

    return false;
}

std::array<float, 3> utils::GetInterpolateCoeff(int x, int y, Triangle tri) {
    auto [a, b, c] = tri;

    glm::vec3 p((float)x + 0.5f, (float)y + 0.5f, 0.f);

    glm::vec3 pa = a->coord.screen - p;
    glm::vec3 pb = b->coord.screen - p;
    glm::vec3 pc = c->coord.screen - p;

    float s = TriangleSquare(tri);

    // barycentric coordonates
    float bc_c = glm::length(glm::cross(pa, pb)) / s;
    float bc_b = glm::length(glm::cross(pa, pc)) / s;
    float bc_a = glm::length(glm::cross(pc, pb)) / s;

    // perspective correction
    float z = bc_c * c->coord.world.z + bc_a * a->coord.world.z + bc_b * b->coord.world.z;
    bc_a *= (z / a->coord.world.z);
    bc_b *= (z / b->coord.world.z);
    bc_c *= (z / c->coord.world.z);

    a->shader_input.float_input["depth"] = a->coord.world.z;
    b->shader_input.float_input["depth"] = b->coord.world.z;
    c->shader_input.float_input["depth"] = c->coord.world.z;

    return {bc_a, bc_b, bc_c};
}

ShaderInput utils::Interpolate(std::array<float, 3> coeff, Triangle tri) {
    ShaderInput fs_input;
    auto [i_a, i_b, i_c] = coeff;
    auto [a, b, c] = tri; 

    for (auto &it : a->shader_input.float_input) {
        std::string key = it.first;
        float f_a = a->shader_input.float_input[key];
        float f_b = b->shader_input.float_input[key];
        float f_c = c->shader_input.float_input[key];
        fs_input.float_input[key] = f_a * i_a + f_b * i_b + f_c * i_c;
    }

    for (auto &it : a->shader_input.vec2_input) {
        std::string key = it.first;
        glm::vec2 v2_a = a->shader_input.vec2_input[key];
        glm::vec2 v2_b = b->shader_input.vec2_input[key];
        glm::vec2 v2_c = c->shader_input.vec2_input[key];
        fs_input.vec2_input[key] = v2_a * i_a + v2_b * i_b + v2_c * i_c;
    }

    for (auto &it : a->shader_input.vec3_input) {
        std::string key = it.first;
        glm::vec3 v3_a = a->shader_input.vec3_input[key];
        glm::vec3 v3_b = b->shader_input.vec3_input[key];
        glm::vec3 v3_c = c->shader_input.vec3_input[key];
        fs_input.vec3_input[key] = v3_a * i_a + v3_b * i_b + v3_c * i_c;
    }

    for (auto &it : a->shader_input.vec4_input) {
        std::string key = it.first;
        glm::vec4 v4_a = a->shader_input.vec4_input[key];
        glm::vec4 v4_b = b->shader_input.vec4_input[key];
        glm::vec4 v4_c = c->shader_input.vec4_input[key];
        fs_input.vec4_input[key] = v4_a * i_a + v4_b * i_b + v4_c * i_c;
    }

    return fs_input;
}