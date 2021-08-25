#ifndef MODEL_H_
#define MODEL_H_

#include "uniform.h"
#include "texture.h"
#include "vertex.h"
#include "config.h"

#include <vector>

class Model {
protected:
    std::string name_;
    std::vector<Vertex> vertices_;
    std::vector<Triangle> faces_;
    Texture texture_;

    // todo: model mat, material, multi-texture, multi-shape

public:
    // load model from folder config::model::path/[name]
    // [name].obj will be loaded, but name of texture needs specified
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