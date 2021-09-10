#include "render_utils.h"

void utils::HomogeneousDivision(Vertex *v) {
    v->coord.ndc = v->coord.csc / v->coord.csc.w;
}

void utils::ViewPortTransform(int width, int height, Vertex *v) {

    v->coord.screen.x = (v->coord.ndc.x + 1.0f) * width * 0.5f;
    v->coord.screen.y = (v->coord.ndc.y + 1.0f) * height * 0.5f;

    v->coord.screen_int.x = int(v->coord.screen.x + 0.5f);
    v->coord.screen_int.y = int(v->coord.screen.y + 0.5f);
}

float utils::ScreenTriangleSquare(const Triangle &tri) {
    auto [a, b, c] = tri;

    glm::vec2 ab = b->coord.screen - a->coord.screen;
    glm::vec2 ac = c->coord.screen - a->coord.screen;

    float s = glm::abs(ab.x * ac.y - ab.y * ac.x);
    return s;
}

bool utils::InClipSpace(Vertex *v) {
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

utils::BoundingBox2D utils::BoundingBox(const Triangle &tri) {
    BoundingBox2D bb;
    auto [a, b, c] = tri;

    bb.x_max = glm::max(a->coord.screen_int.x, b->coord.screen_int.x, c->coord.screen_int.x);
    bb.x_min = glm::min(a->coord.screen_int.x, b->coord.screen_int.x, c->coord.screen_int.x);
    bb.y_max = glm::max(a->coord.screen_int.y, b->coord.screen_int.y, c->coord.screen_int.y);
    bb.y_min = glm::min(a->coord.screen_int.y, b->coord.screen_int.y, c->coord.screen_int.y);

    return bb;
}

bool utils::InTriangle(const std::array<float, 3> &bc) {
    auto [bc_a, bc_b, bc_c] = bc;
    if ((bc_a > -FLT_EPSILON && bc_b > -FLT_EPSILON && bc_c > -FLT_EPSILON) ||
        (bc_a < FLT_EPSILON && bc_b < FLT_EPSILON && bc_c < FLT_EPSILON)) {
            return true;
        } else {
            return false;
        }
}

std::array<float, 3> utils::PespectiveCorrection(const std::array<float, 3> &bc, const Triangle &tri) {
    auto [a, b, c] = tri;
    auto [bc_a, bc_b, bc_c] = bc;
    
    bc_a = glm::abs(bc_a);
    bc_b = glm::abs(bc_b);
    bc_c = glm::abs(bc_c);

    float z = 1 / (bc_c / c->coord.csc.w + bc_a / a->coord.csc.w + bc_b / b->coord.csc.w);
    auto i_a = bc_a * z / a->coord.csc.w;
    auto i_b = bc_b * z / b->coord.csc.w;
    auto i_c = bc_c * z / c->coord.csc.w;

    return {i_a, i_b, i_c};
}

Attr utils::Interpolate(const std::array<float, 3> &coeff, const Triangle &tri) {
    Attr attr;
    auto [i_a, i_b, i_c] = coeff;
    auto [a, b, c] = tri;

    for (auto &it : a->attr.float_attr) {
        auto key = it.first;
        float f_a = a->attr.float_attr[key];
        float f_b = b->attr.float_attr[key];
        float f_c = c->attr.float_attr[key];
        attr.float_attr[key] = f_a * i_a + f_b * i_b + f_c * i_c;
    }

    for (auto &it : a->attr.vec2_attr) {
        auto key = it.first;
        glm::vec2 v2_a = a->attr.vec2_attr[key];
        glm::vec2 v2_b = b->attr.vec2_attr[key];
        glm::vec2 v2_c = c->attr.vec2_attr[key];
        attr.vec2_attr[key] = v2_a * i_a + v2_b * i_b + v2_c * i_c;
    }

    for (auto &it : a->attr.vec3_attr) {
        auto key = it.first;
        glm::vec3 v3_a = a->attr.vec3_attr[key];
        glm::vec3 v3_b = b->attr.vec3_attr[key];
        glm::vec3 v3_c = c->attr.vec3_attr[key];
        attr.vec3_attr[key] = v3_a * i_a + v3_b * i_b + v3_c * i_c;
    }

    for (auto &it : a->attr.vec4_attr) {
        auto key = it.first;
        glm::vec4 v4_a = a->attr.vec4_attr[key];
        glm::vec4 v4_b = b->attr.vec4_attr[key];
        glm::vec4 v4_c = c->attr.vec4_attr[key];
        attr.vec4_attr[key] = v4_a * i_a + v4_b * i_b + v4_c * i_c;
    }

    return attr;
}

float utils::InterpolateDepth(const std::array<float, 3> &coeff, const Triangle &tri) {
    auto [i_a, i_b, i_c] = coeff;
    auto [a, b, c] = tri;

    return -i_a * a->coord.csc.w - i_b * b->coord.csc.w - i_c * c->coord.csc.w;
}

std::array<float, 3> utils::BarycentricCoordinate(int x, int y, float s, const Triangle &tri) {
    auto [a, b, c] = tri;

    glm::vec2 p((float)x + 0.5f, (float)y + 0.5f);

    glm::vec2 pa = a->coord.screen - p;
    glm::vec2 pb = b->coord.screen - p;
    glm::vec2 pc = c->coord.screen - p;

    float bc_c = (pb.x * pa.y - pb.y * pa.x) / s;
    float bc_b = (pa.x * pc.y - pa.y * pc.x) / s;
    float bc_a = (pc.x * pb.y - pc.y * pb.x) / s;

    return {bc_a, bc_b, bc_c};
}