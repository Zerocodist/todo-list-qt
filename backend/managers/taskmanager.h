#pragma once

#include <QObject>
#include "../database/database.h"
#include <QtQml/qqml.h>
#include "../task/task.h"

class TaskManager : public QObject {
    Q_OBJECT
public:
    explicit TaskManager(Database &db, QObject *parent = nullptr);
    int addTask(const QString &title);
    bool deleteTask(int id);
    bool updateModel(int id, bool completed);
    bool updateTitle(int id, const QString &title);
    bool clearAll();
    QVector<Task> search(const QString &text);
private:
    Database &database;
};
