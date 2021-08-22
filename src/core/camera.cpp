#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(CameraPos pos, CameraField field) 
    : pos_(pos), field_(field) {}

void Camera::AlterUniformViewMat(Uniform &uniform) {
    auto view_mat = glm::lookAt(pos_.eye_pos, pos_.gaze_dir, pos_.up_dir);
    uniform.view_mat = view_mat;
    uniform.RefreshMvp();
}

void Camera::AlterUniformProjMat(Uniform &uniform) {
    auto proj_mat = glm::perspective(field_.fovy, field_.aspect, field_.z_near, field_.z_far);
    uniform.proj_mat = proj_mat;
    uniform.RefreshMvp();
}

void Camera::AlterUniform(Uniform &uniform) {
    AlterUniformProjMat(uniform);
    AlterUniformViewMat(uniform);
}