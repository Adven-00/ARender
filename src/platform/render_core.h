#ifndef RENDER_CORE_H_
#define RENDER_CORE_H_

#include "core/render.h"

#include <QObject>

class RenderCore : public QObject
{
    Q_OBJECT

private:
    Render *render_;
    uchar *frame_data_;

    bool stop_flag_;
    
public:
    RenderCore(QObject *parent = nullptr);

public slots:
    void MainLoop();
    void StopLoop();
signals:
    void FrameData(uchar *frame_data, int width, int height);
};

#endif // RENDER_CORE_H_