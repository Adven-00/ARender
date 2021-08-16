#ifndef CAMERA_H_
#define CAMERA_H_

#include "uniform.h"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct CameraPos {
    glm::vec3 eye_pos;
    glm::vec3 gaze_dir;
    glm::vec3 up_dir;
};

struct CameraField {
    float fovy;
    float aspect;
    float z_near;
    float z_far;
};

constexpr float PI = 3.1415926f;

constexpr CameraPos CAMERA_POS_DEFAULT = {
    glm::vec3(0.f, 0.f, 0.f),
    glm::vec3(0.f, 0.f, -1.f),
    glm::vec3(0.f, 1.f, 0.f)
};

constexpr CameraField DEFAULT_CAMERA_FIELD = {0.5 * PI, 1.f, 0.01f, 500.f};

class Camera {
protected:
    CameraPos pos_;
    CameraField field_;

public:
    Camera(CameraPos pos = CAMERA_POS_DEFAULT, CameraField field = DEFAULT_CAMERA_FIELD);
    ~Camera() = default;

    void ChangeUniformViewMat(Uniform &uniform);
    void ChangeUniformProjMat(Uniform &uniform);
    void ChangeUniform(Uniform &uniform);
};

#endif // CAMERA_H_