#include "core/render.h"
#include "core/camera.h" 

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

void SaveImage(int w, int h, ColorBuffer color_bufer)
{
    unsigned char *data = new unsigned char[w * h * 4];

    int index = 0;
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            auto pixel = color_bufer.Get(x, y);
            data[index++] = (unsigned char)pixel.r;
            data[index++] = (unsigned char)pixel.g;
            data[index++] = (unsigned char)pixel.b;
            data[index++] = (unsigned char)pixel.a;
        }
    }

    stbi_flip_vertically_on_write(1);
    stbi_write_bmp("test.bmp", w, h ,4, data);
    delete[] data;
}

Vertex *MakeVertex(glm::vec4 pos, glm::vec4 color) {
    Vertex *v = new Vertex;
    v->attr.vec4_attr["color"] = color;
    v->coord.world = pos;
    return v;
}
Vertex *MakeVertex(glm::vec4 pos, glm::vec2 uv) {
    Vertex *v = new Vertex;
    v->attr.vec2_attr["uv"] = uv;
    v->coord.world = pos;
    return v;
}

Triangle MakeTriangle(std::array<glm::vec4, 3> vertices, glm::vec4 color) {
    Vertex *a = MakeVertex(vertices[0], color);
    Vertex *b = MakeVertex(vertices[1], color);
    Vertex *c = MakeVertex(vertices[2], color);

    return {a, b, c};
}