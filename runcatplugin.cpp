#include "runcatplugin.h"
#include "runcatwidget.h"

RuncatPlugin::RuncatPlugin(QObject *parent) : QObject(parent)
{

}


const QString RuncatPlugin::pluginName() const
{
    return QStringLiteral("runcat");
}

void RuncatPlugin::init(PluginProxyInterface *proxyInter)
{
    this->proxyInter = proxyInter;
    pluginWidget = new RuncatWidget;

    proxyInter->itemAdded(this, pluginName());

}

QWidget *RuncatPlugin::itemWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);
    return pluginWidget;
}

//const QString RuncatPlugin::pluginDisplayName() const
//{
//}
