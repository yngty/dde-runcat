#ifndef RUNCATPLUGIN_H
#define RUNCATPLUGIN_H

# include <dde-dock/pluginsiteminterface.h>

#include <QObject>

class RuncatPlugin : public QObject, PluginsItemInterface
{
    Q_OBJECT
    // 声明实现了的接口
    Q_INTERFACES(PluginsItemInterface)
    // 插件元数据
    Q_PLUGIN_METADATA(IID "com.deepin.dock.PluginsItemInterface" FILE "runcat.json")

public:
    explicit RuncatPlugin(QObject *parent = nullptr);

public:
    virtual const QString pluginName() const override;
    virtual void init(PluginProxyInterface *proxyInter) override;
    virtual QWidget *itemWidget(const QString &itemKey) override;

//    virtual const QString pluginDisplayName() const override;

private:

    PluginProxyInterface *proxyInter { nullptr };
    QWidget *pluginWidget { nullptr };
};

#endif // RUNCATPLUGIN_H
