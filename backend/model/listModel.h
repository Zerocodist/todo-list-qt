#pragma once

#include <QAbstractListModel>
#include <QVector>
#include <QString>
#include "../managers/taskmanager.h"
#include "../database/database.h"
#include "../task/task.h"

class ListModelCpp : public QAbstractListModel {
    Q_OBJECT
public:
    explicit ListModelCpp(Database &db, QObject *parent = nullptr);

    enum TaskRoles  {
        IdRole = Qt::UserRole + 1,
        TitleRole,
        CompletedRole
    };
    Q_ENUM(TaskRoles);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    Q_INVOKABLE bool addTask(const QString &title);
    Q_INVOKABLE bool deleteTask(int id);
    Q_INVOKABLE bool loadTask();
    Q_INVOKABLE bool updateTitle(int id, const QString &title);
    Q_INVOKABLE bool updateModel(int id, bool completed);
    Q_INVOKABLE bool clearAll();
private:
    QVector<Task> tasks;
    QVector<Task> visibleTask;
    Database &database;
    TaskManager task;
signals:
    void status(const QString &text);
};
