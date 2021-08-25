#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() {
    eye_pos_ = config::camera::EyePos;
    gaze_dir_ = config::camera::GazeDir;
    up_dir_ = config::camera::UpDir;

    fovy_ = config::camera::Fovy;
    aspect_ = config::camera::Aspect;
    z_near_ = config::camera::ZNear;
    z_far_ = config::camera::ZFar;
}

void Camera::AlterUniformViewMat(Uniform &uniform) {
    auto view_mat = glm::lookAt(eye_pos_, gaze_dir_, up_dir_);
    uniform.view_mat = view_mat;
    uniform.RefreshMvp();
}

void Camera::AlterUniformProjMat(Uniform &uniform) {
    auto proj_mat = glm::perspective(fovy_, aspect_, z_near_, z_far_);
    uniform.proj_mat = proj_mat;
    uniform.RefreshMvp();
}

void Camera::AlterUniform(Uniform &uniform) {
    AlterUniformProjMat(uniform);
    AlterUniformViewMat(uniform);
}