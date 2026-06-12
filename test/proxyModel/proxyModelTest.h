#pragma once

#include <QtTest>
#include "proxyModel/proxyModel.h"
#include "database/database.h"
#include "model/listModel.h"

class ProxyModelTest : public QObject {

    Q_OBJECT

private slots:

    void setSearchTextTest();

};