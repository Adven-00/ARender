#ifndef RENDER_WIDGET_H_
#define RENDER_WIDGET_H_

#include "render_core.h"

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QThread>

class RenderWidget : public QWidget {

private :
    RenderCore *render_core_;
    QThread *render_thread_;
    QImage *frame_;

public:
    RenderWidget(QObject *parent = nullptr);
    ~RenderWidget();

public slots:
    void DrawFrame(uchar *frame_data, int width, int height);

protected:
	void paintEvent(QPaintEvent *event) override;
};

#endif // RENDER_WIDGET_H_