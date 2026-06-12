#pragma once

#include <QtTest>
#include "model/listModel.h"
#include "database/database.h"

class ListModelCppTest : public QObject {

    Q_OBJECT

private slots:

    void init();
    void cleanup();
    void addTaskTest();
    void deleteTaskTest();
    void clearAllTest();
    void loadTaskTest();
    void updateModelTest();
    void updateTitleTest();
    void rowCountTest();
    void roleNamesTest();
    void dataTest();


private:
    Database *db = nullptr;
    ListModelCpp *model = nullptr;
};