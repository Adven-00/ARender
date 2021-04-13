#include "utils.h"

void utils::HomogeneousDivision(VertexIndex v, VertexIndexList &list) {
    VertexPtr vertex = list[v];
    vertex->coord.ndc = vertex->coord.csc / vertex->coord.csc.w;
}

void utils::ViewPortTransformation(int width, int height, VertexIndex v, VertexIndexList &list) {
    VertexPtr vertex = list[v];

    vertex->coord.screen.x = (vertex->coord.ndc.x + 1.0f) * width * 0.5f;
    vertex->coord.screen.y = (vertex->coord.ndc.y + 1.0f) * height * 0.5f;
    vertex->coord.screen.z = 0.f;

    vertex->coord.screen_int.x = int(vertex->coord.screen.x + 0.5f);
    vertex->coord.screen_int.y = int(vertex->coord.screen.y + 0.5f);
    vertex->coord.screen_int.z = 0.f;
}

float utils::TriangleSquare(Triangle tri, VertexIndexList &list) {
    VertexPtr a  = list[tri[0]];
    VertexPtr b  = list[tri[1]];
    VertexPtr c  = list[tri[2]];

    glm::vec3 ab = b->coord.screen - a->coord.screen;
    glm::vec3 ac = c->coord.screen - a->coord.screen;

    float s = glm::length(glm::cross(ab, ac));
    return s;
}

bool utils::InClipSpace(VertexIndex v, VertexIndexList &list) {
    VertexPtr vertex = list[v];
    float w = vertex->coord.csc.w;

    if (w == 0)
        return false;
    if (vertex->coord.csc.x < -w || vertex->coord.csc.x > w)
        return false;
    if (vertex->coord.csc.y < -w || vertex->coord.csc.y > w)
        return false;
    if (vertex->coord.csc.z < -w || vertex->coord.csc.z > w)
        return false;

    return true;
}

BoundingBox2D utils::GetBoundingBox(Triangle tri, VertexIndexList &list) {
    BoundingBox2D bb;

    VertexPtr a  = list[tri[0]];
    VertexPtr b  = list[tri[1]];
    VertexPtr c  = list[tri[2]];

    bb.x_max = int(glm::max(a->coord.screen_int.x, b->coord.screen_int.x, c->coord.screen_int.x));
    bb.x_min = int(glm::min(a->coord.screen_int.x, b->coord.screen_int.x, c->coord.screen_int.x));
    bb.y_max = int(glm::max(a->coord.screen_int.y, b->coord.screen_int.y, c->coord.screen_int.y));
    bb.y_min = int(glm::max(a->coord.screen_int.y, b->coord.screen_int.y, c->coord.screen_int.y));

    return bb;
}

bool utils::IsInTriangle(int x, int y, Triangle tri, VertexIndexList &list) {
    VertexPtr a  = list[tri[0]];
    VertexPtr b  = list[tri[1]];
    VertexPtr c  = list[tri[2]];

    glm::vec3 p((float)x + 0.5f, (float)y + 0.5f, 0.f);

}