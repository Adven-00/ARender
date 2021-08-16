#include "camera.h"

Camera::Camera(CameraPos pos, CameraField field) 
    : pos_(pos), field_(field) {}

void Camera::ChangeUniformViewMat(Uniform &uniform) {
    auto view_mat = glm::lookAt(pos_.eye_pos, pos_.gaze_dir, pos_.up_dir);
    uniform.view_mat = view_mat;
    uniform.RefreshMvp();
}

void Camera::ChangeUniformProjMat(Uniform &uniform) {
    auto proj_mat = glm::perspective(field_.fovy, field_.aspect, field_.z_near, field_.z_far);
    uniform.proj_mat = proj_mat;
    uniform.RefreshMvp();
}

void Camera::ChangeUniform(Uniform &uniform) {
    ChangeUniformProjMat(uniform);
    ChangeUniformViewMat(uniform);
}