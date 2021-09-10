#include "uniform.h"

Uniform::Uniform()
    : model_mat(glm::mat4(1.0f)),
      view_mat(glm::mat4(1.0f)),
      proj_mat(glm::mat4(1.0f)), 
      mvp_mat(glm::mat4(1.0f)) {}