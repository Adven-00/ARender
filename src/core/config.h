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

    namespace camera {
        inline auto EyePos = glm::vec3(0.f, 0.f, 5.f);
        inline auto GazeDir = glm::vec3(0.f, 0.f, -1.f);
        inline auto UpDir = glm::vec3(0.f, 1.f, 0.f);  

        inline auto Fovy = 0.33f * 3.1415926f;
        inline auto Aspect =  1.f;
        inline auto ZNear =  0.01f;
        inline auto ZFar  = 100.f;
    };

    namespace model {
        inline auto MtlPath = "../assets/model/cow";
        inline auto ObjPath = "../assets/model/cow/cow.obj";
    };

    namespace texture {
        inline auto Path = "../assets/model/cow/cow.png";
    };

    namespace render {
        inline auto Background = glm::vec4(0.f, 0.f, 0.f, 255.f);
        inline auto MaxDepth = -1000.f;
        inline auto Width = 500;
        inline auto Height = 500;
    };
};

#endif // CONFIG_H_