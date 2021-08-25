//线框模式
//深度测试
//render输出方式

#ifndef CONFIG_H_
#define CONFIG_H_

#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>

#include <string>

namespace config {
    namespace buffer {
        constexpr auto Color = glm::vec4(0.f, 0.f, 0.f, 255.f);
        constexpr auto Depth = -9999.f;
    };

    namespace camera {
        constexpr auto EyePos = glm::vec3(0.f, 0.f, 5.f);
        constexpr auto GazeDir = glm::vec3(0.f, 0.f, -1.f);
        constexpr auto UpDir = glm::vec3(0.f, 1.f, 0.f);  

        constexpr auto Fovy = 0.33f * 3.1415926f;
        constexpr auto Aspect =  1.f;
        constexpr auto ZNear =  0.01f;
        constexpr auto ZFar  = 100.f;
    };

    namespace model {
        constexpr auto Path = "../assets/model/";
        
        constexpr bool Triangulate = true;
    };
};

#endif