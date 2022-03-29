#include "widget.h"

#include <QTimer>
#include <QPainter>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      timer(new QTimer(this))
{

    for (int i = 0; i < 5; i++) {
        QPixmap pixMap(QString(":/icons/cat/my-running-%1-symbolic").arg(i));
        runningPixmaps.push_back(std::move(pixMap));
    }
    timer->start(1);
    connect(timer, &QTimer::timeout, this, &Widget::onTimeout);
}

Widget::~Widget()
{
}

void Widget::onTimeout()
{
    currentIndex += 1;
    currentIndex %= 5;
    qInfo() << "currentIndex: " << currentIndex;
    update();
}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.drawPixmap(rect(), runningPixmaps[currentIndex]);
}
