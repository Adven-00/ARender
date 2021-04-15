#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <iostream>

int main() {
    glm::vec4 a(1, 2, 3, 4);

    glm::mat4 proj = glm::perspective(glm::radians(60.f), 1.f, 1.f, 100.f);
    glm::vec4 v(0.1f, 0.1f, 2.0f, 1.0f);

    glm::vec4 r = proj * v;

    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            std::cout << proj[x][y] << "\t";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < 4; i++) {
        std::cout << r[i] << "\t";
    }

    return 0;
}