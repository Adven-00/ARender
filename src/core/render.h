#ifndef RENDER_H_
#define RENDER_H_  

#include "render_utils.h"
#include "shader/shader.h"
#include "camera.h"
#include "model.h"
#include "buffer.h"

class Render {

private:
    int width_;
    int height_;
    
    ColorBuffer color_buffer_;
    DepthBuffer depth_buffer_;

    VertexShader vertex_shader_;
    FragmentShader fragement_shader_;

    Uniform uniform_;
    Camera camera_;
    Model model_;

    unsigned char *frame_data_;

    Render(int width, int height);
    ~Render();
    Render(Render &other) = delete;
    void operator=(const Render &) = delete;

public:
    static Render *Instance(int width = config::render::Width, int height = config::render::Height);

    void RefreshUniform();
    void RefreshBuffer();

    void SetVertexShader(const VertexShader &vs);
    void SetFragmentShader(const FragmentShader &fs);
    void SetShader(const VertexShader &vs, const FragmentShader &fs);

    // handel mouse movemonet

    void DrawTriangle(const Triangle &tri);
    void DrawModel();

    unsigned char *GetFrameData();
    std::array<int, 2> GetFrameSize();
};

#endif // RENDER_H_