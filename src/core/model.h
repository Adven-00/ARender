#ifndef MODEL_H_
#define MODEL_H_

#include "uniform.h"
#include "buffer.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tinyobjloader/tiny_obj_loader.h>
#include <string>
#include <vector>

constexpr auto DEFAULT_MODEL_PATH = "../assets/model/";

class Model {
protected:
    std::string name_;
    std::string path_;

    VertexBuffer vertex_buffer_;
    std::vector<Triangle> faces_;
public:
    Model(std::string name);

    void Load();
    std::vector<Triangle> Faces();
};

#endif // MODEL_H_