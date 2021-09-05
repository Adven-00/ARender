#ifndef RENDER_H_
#define RENDER_H_  

#include "render_utils.h"
#include "shader.h"
#include "camera.h"
#include "model.h"
#include "buffer.h"

class Render {

private:
    ColorBuffer color_buffer_;
    DepthBuffer depth_buffer_;

    int width_;
    int height_;

    VertexShader vertex_shader_;
    FragmentShader fragement_shader_;

    Uniform uniform_;
    Camera camera_;

    Render(int width, int height);
    ~Render() = default;
    Render(Render &other) = delete;
    void operator=(const Render &) = delete;

public:
    static Render &Instance(int width = config::render::Width, int height = config::render::Height);

    void RefreshUniform();

    void SetVertexShader(const VertexShader &vertex_shader);
    void SetFragmentShader(const FragmentShader &fragement_shader);

    void DrawTriangle(const Triangle &tri);
    void DrawModel(Model &model);

    ColorBuffer Output();
};

#endif // RENDER_H_