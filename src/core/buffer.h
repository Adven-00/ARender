#pragma once

#ifndef BUFFER_H_
#define BUFFER_H_  

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <array>

template<int w, int h>
using FrameBuffer = std::array<std::array<glm::vec4, h>, w>;

template<int w, int h>
using DepthBuffer = std::array<std::array<float, h>, w>;


#endif // BUFFER_H_