#include "runcatwidget.h"
#include "systemmanager.h"

#include <QTimer>
#include <QPainter>
#include <QtMath>
#include <QDebug>

RuncatWidget::RuncatWidget(QWidget *parent)
    : QWidget(parent),
      timer(new QTimer(this))
{

    for (int i = 0; i < 5; i++) {
        QPixmap pixMap(QString(":/icons/cat/my-running-%1-symbolic").arg(i));
        runningPixmaps.push_back(std::move(pixMap));
    }
    timer->start(1);
    connect(timer, &QTimer::timeout, this, &RuncatWidget::onTimeout);

}

RuncatWidget::~RuncatWidget()
{
}

void RuncatWidget::onTimeout()
{
    double utilizationCoefficient = SystemManager::manager()->cpuUtilization() > 100 ? 100 :  SystemManager::manager()->cpuUtilization();

    // y = 5000/sqrt(x+30) - 400
    int animationInterval = qCeil(5000 / qSqrt(utilizationCoefficient + 30) - 400);

    timer->setInterval(animationInterval);

    currentIndex += 1;
    currentIndex %= 5;

    update();
}

void RuncatWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.drawPixmap(rect(), runningPixmaps[currentIndex]);
}
