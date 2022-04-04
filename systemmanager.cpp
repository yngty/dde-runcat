#include "systemmanager.h"

#include <QFile>
#include <QTimer>
#include <QDebug>

#include <memory>
#include <algorithm>

static constexpr char kCpu[] = "/proc/stat";

SystemManager *SystemManager::manager()
{
    static SystemManager manager;
    return &manager;
}

double SystemManager::cpuUtilization() const
{
    return cpuUtilizationValue;
}

SystemManager::SystemManager():
    timer(new QTimer(this)),
    lastActive(0),
    lastTotal(0),
    cpuUtilizationValue {0.0}
{
   refreshCpu();

   connect(timer, &QTimer::timeout, this, &SystemManager::refreshCpu);

   timer->setInterval(1000);
   timer->start();
}

void SystemManager::refreshCpu()
{
   QVector<CpuInfo> cpus = readCpuInfo();
   handleCpu(cpus);
}

QVector<CpuInfo> SystemManager::readCpuInfo()
{
    QFile file(kCpu);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "don't open " << kCpu;
        return {};
    }

    QTextStream stream(&file);

    QStringList list {};

    bool ok = false;
    CpuInfo cpu {-1, 0, 0};

    QVector<CpuInfo> cpus;

    int i = 0;

    do {
        cpu.index = i++;

        QString line = stream.readLine().simplified();
        list = line.split(QRegExp("\\s+"));
        cpu.total = std::accumulate(list.begin(), list.end(), 0, [&ok](int total, const QString &elem) { return total + elem.toLong(&ok); });
        cpu.active = std::accumulate(list.begin(), list.begin() + 4, 0, [&ok](int total, const QString &elem) { return total + elem.toLong(&ok); });

        cpus.push_back(std::move(cpu));

    } while(list.first() != QStringLiteral("intr"));

    file.close();

    return cpus;
}

void SystemManager::handleCpu(const QVector<CpuInfo> &cpus)
{
    cpuUtilizationValue = (cpus.begin()->active - lastActive) * 100.0 / (cpus.begin()->total - lastTotal);
    lastActive = cpus.begin()->active;
    lastTotal = cpus.begin()->total;

    Q_EMIT cpuUtilizationUpdated(cpuUtilizationValue);
}
