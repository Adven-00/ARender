#include "render_widget.h"

RenderWidget::RenderWidget(QObject *parent) : frame_(nullptr) {
    render_core_ = new RenderCore;
    render_thread_ = new QThread(this);

    render_core_->moveToThread(render_thread_);
	connect(render_thread_, &QThread::finished, render_core_, &RenderCore::deleteLater);
	connect(render_thread_, &QThread::started, render_core_, &RenderCore::MainLoop);
	connect(render_core_, &RenderCore::FrameData, this, &RenderWidget::DrawFrame);

    this->setWindowTitle(QString("ARender"));

    render_thread_->start();
}

RenderWidget::~RenderWidget() {
    render_core_->StopLoop();

    // quit thread safely
    render_thread_->quit();
    render_thread_->wait();
}

void RenderWidget::DrawFrame(uchar *frame_data, int width, int height) {
    if (frame_)
        delete frame_;
    frame_ = new QImage(frame_data, width, height, QImage::Format_RGBA8888);
    update();
}

void RenderWidget::paintEvent(QPaintEvent *event)
{
	if (frame_) {
        QPainter painter(this);
		painter.drawImage(frame_->rect(), frame_->mirrored());
    }
}