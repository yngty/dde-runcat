#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget() override;

protected:
    virtual void paintEvent(QPaintEvent *event) override;

private slots:
    void onTimeout();

private:
    QTimer *timer { nullptr };

    int currentIndex = { 0 };
    QList<QPixmap> runningPixmaps;
};

#endif   // WIDGET_H
