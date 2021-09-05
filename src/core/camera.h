#ifndef CAMERA_H_
#define CAMERA_H_

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

    glm::mat4 GetViewMat();
    glm::mat4 GetProjMat();
    //glm::mat4 GetModelMat();
};

#endif // CAMERA_H_