#ifndef MODEL_H_
#define MODEL_H_

#include "uniform.h"
#include "buffer.h"
#include "texture.h"

#include <string>
#include <vector>

constexpr auto DEFAULT_MODEL_PATH = "../assets/model/";

class Model {
protected:
    std::string name_;

    VertexBuffer vertex_buffer_;
    std::vector<Triangle> faces_;
    Texture texture_;

    // todo: model mat, material, multi-texture, multi-shape

public:
    Model(std::string name);

    std::vector<Triangle> Faces();

    //void Load();
    void LoadVertices();
    //void LoadMaterial();
    void LoadTexture(std::string texture_name);

    //void AlterUniform(Uniform &uniform);
    void AlterUniformTexture(Uniform &uniform);
    //void AlterUniformModelMat(Uniform &uniform);
    //void AlterUniformMaterial(Uniform &uniform);
};

#endif // MODEL_H_