#pragma once

#ifndef OUTPUT_INTERFACE_H_
#define OUTPUT_INTERFACE_H_ 

#include <svpng/svpng.h>

#include <string>

#include "../core/buffer.h"

template<int w, int h>
void SavePNG(std::string filename, FrameBuffer<w, h> frame_buffer) {
    unsigned char *data  = new unsigned char[w * h * 4]; 
    unsigned char *p = data;

    FILE *fp;
    if (fopen_s(&fp, (filename + ".png").c_str(), "wb")) {
        return;
    }

    for (int x = 0; x < w; x++) {
        for (int y = 0; y < h; y++) {
            *p++ = (unsigned char)frame_buffer[x][y].r;
            *p++ = (unsigned char)frame_buffer[x][y].g;
            *p++ = (unsigned char)frame_buffer[x][y].b;
            *p++ = (unsigned char)frame_buffer[x][y].a;
        }
    }

    svpng(fp, w, h, data, 1);

    delete[] data;
    fclose(fp);
};

#endif // OUTPUT_INTERFACE_H_