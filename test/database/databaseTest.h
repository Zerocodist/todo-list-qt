#pragma once

#include <QTest>
#include "database/database.h"

class DatabaseTest : public QObject {

    Q_OBJECT

private slots:

    void init();
    void cleanup();
    void dbConnectTest();
    void tableExistTest();

private:
    Database *db = nullptr;

};