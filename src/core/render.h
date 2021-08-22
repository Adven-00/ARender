#ifndef RENDER_H_
#define RENDER_H_  

#include "utils.h"
#include "shader.h"
#include "model.h"

class Render {

protected:
    ColorBuffer color_buffer_;
    DepthBuffer depth_buffer_;

    int width_;
    int height_;

    VertexShader vertex_shader_;
    FragmentShader fragement_shader_;

    Uniform uniform_;

public:
    Render(int width, int height);
    ~Render() = default;

    ColorBuffer Output();

    void SetVertexShader(VertexShader vertex_shader);
    void SetFragmentShader(FragmentShader fragement_shader);
    void SetUniform(Uniform &uniform);

    void DrawTriangle(Triangle tri);
    void DrawModel(Model &model);
};

#endif // RENDER_H_