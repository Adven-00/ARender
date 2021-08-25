#ifndef CAMERA_H_
#define CAMERA_H_

#include "uniform.h"
#include "config.h"

class Camera {
protected:

    glm::vec3 eye_pos_;
    glm::vec3 gaze_dir_;
    glm::vec3 up_dir_;

    float fovy_;
    float aspect_;
    float z_near_;
    float z_far_;

public:
    Camera();
    ~Camera() = default;

    void AlterUniformViewMat(Uniform &uniform);
    void AlterUniformProjMat(Uniform &uniform);
    void AlterUniform(Uniform &uniform);
};

#endif // CAMERA_H_