#include <svpng/svpng.h>

#include "output_interface.h"

OutputInterface::OutputInterface(const FrameBuffer &frame_buffer) : frame_buffer_(frame_buffer) {}

void OutputInterface::SavePNG(std::string filename) {

    int width = frame_buffer_.GetWidth();
    int height = frame_buffer_.GetHeight();

    unsigned char *data  = new unsigned char[width * height * 4]; 
    unsigned char *p = data;

    FILE *fp;
    if (fopen_s(&fp, (filename + ".png").c_str(), "wb")) {
        return;
    }

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            *p++ = (unsigned char)frame_buffer_[x][y].r;
            *p++ = (unsigned char)frame_buffer_[x][y].g;
            *p++ = (unsigned char)frame_buffer_[x][y].b;
            *p++ = (unsigned char)frame_buffer_[x][y].a;
        }
    }

    svpng(fp, width, height, data, 1);

    delete[] data;
    fclose(fp);
}