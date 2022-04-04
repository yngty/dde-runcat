#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H

#include <QObject>
#include <QVector>

QT_BEGIN_NAMESPACE
class QTimer;
QT_END_NAMESPACE


struct CpuInfo {
    int index;
    long active;
    long total;
};

class SystemManager : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(SystemManager)

public:
    static SystemManager* manager();

    double cpuUtilization() const;

signals:
    double cpuUtilizationUpdated(double value) const;

private:
    SystemManager();


private slots:
    void refreshCpu();

private:
    QVector<CpuInfo> readCpuInfo();
    void handleCpu(const QVector<CpuInfo> &cpus);

private:
    QTimer *timer {nullptr};
    long lastActive;
    long lastTotal;
    double cpuUtilizationValue;
};

#endif // SYSTEMINFO_H
