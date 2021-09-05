#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
    : eye_pos_(config::camera::EyePos),
      gaze_dir_(config::camera::GazeDir),
      up_dir_(config::camera::UpDir),
  
      fovy_(config::camera::Fovy),
      aspect_(config::camera::Aspect),
      z_near_(config::camera::ZNear),
      z_far_(config::camera::ZFar) {}

glm::mat4 Camera::GetViewMat() {
    return glm::lookAt(eye_pos_, gaze_dir_, up_dir_);
}

glm::mat4 Camera::GetProjMat() {
    return glm::perspective(fovy_, aspect_, z_near_, z_far_);
}