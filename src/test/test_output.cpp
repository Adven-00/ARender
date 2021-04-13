#include "../interface/output_interface.h"

#include <iostream>

int main() {
    FrameBuffer fb(100, 100);
    std::cout << fb.GetHeight() << " * " << fb.GetHeight() << std::endl;
    
    glm::vec4 red(255.f, 0.f, 0.f, 255.f);
    for (int x = 0; x < 100; x++)
        fb[x][x] = red;

    OutputInterface oi(fb);
    oi.SavePNG("test_output");
    
    return 0;
}