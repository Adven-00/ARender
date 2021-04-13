#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <iostream>

int main() {
    glm::vec4 a(1, 2, 3, 4);
    glm::vec2 b(3, 4);
    glm::vec2 c(1, 2);

    std::cout << glm::dot(b, c) << std::endl;

    int x = int(glm::max(b.x, c.x));

    std::cout << x;

    return 0;
}