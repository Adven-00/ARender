#ifndef MODEL_H_
#define MODEL_H_

#include "vertex.h"
#include "config.h"

#include <vector>

class Model {
protected:
    std::string obj_path_; 
    std::string mtl_path_; 

    Vertex* vertices_;
    std::vector<Triangle> faces_;
    // todo: material

public:
    Model(std::string obj_path = config::model::ObjPath, std::string mtl_path = config::model::MtlPath);
    ~Model();

    std::vector<Triangle> Faces();

    //void Load();
    void LoadVertices();
    //void LoadMaterial();
};

#endif // MODEL_H_