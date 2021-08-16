#ifndef UNIFORM_H_
#define UNIFORM_H_

#include <glm/vec3.hpp>
#include <glm/matrix.hpp>

class Uniform {
public:
    glm::mat4 model_mat;
    glm::mat4 view_mat;
    glm::mat4 proj_mat;
    glm::mat4 mvp_mat;

public:
    Uniform();
    void RefreshMvp();
};

#endif // UNIFORM_H_