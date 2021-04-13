#pragma once

#ifndef OUTPUT_INTERFACE_H_
#define OUTPUT_INTERFACE_H_ 

#include <string>

#include "../core/buffer.h"
#include "../core/rasterizer.h"

class OutputInterface {

private:
    FrameBuffer frame_buffer_;

public:
    // shallow copy
    OutputInterface(const FrameBuffer &frame_buffer);
    OutputInterface(const Rasterizer &rasterizer);

    void SetFrameBuffer(const FrameBuffer &frame_buffer_);
    void SavePNG(std::string filename);
};

#endif // OUTPUT_INTERFACE_H_