#include "render_core.h"

RenderCore::RenderCore(QObject *parent) {
    render_ = Render::Instance();
    frame_data_ = nullptr;
    stop_flag_ = false;

    // for test only
    render_->SetShader(VS_1, FS_2);
}

void RenderCore::MainLoop() {

    while(!stop_flag_) {
        render_->DrawModel();
        frame_data_ = render_->GetFrameData();
        auto [w, h] = render_->GetFrameSize();

        emit FrameData(frame_data_, w, h);
    }
}

void RenderCore::StopLoop() {
    stop_flag_ = true;
}