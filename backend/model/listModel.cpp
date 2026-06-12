#include "listModel.h"

ListModelCpp::ListModelCpp(Database &db,QObject *parent)
    : QAbstractListModel(parent),
    database(db),
    task(db)
{
}


bool ListModelCpp::addTask(const QString &title)
{
    int id = task.addTask(title);

    if(id == -1) {
        emit status("Add task error! ❌ Check log ⬇");
        return false;
    }

    beginInsertRows(QModelIndex(),
                    tasks.size(),
                    tasks.size());

    if(id == -1)
    {
        emit status("Add task error! ❌");
        return false;
    }

    tasks.append({
         id,
         title,
         false
        });

    endInsertRows();

    emit status("Add task success! ✅");

    return true;
}

bool ListModelCpp::deleteTask(int id)
{
    qDebug() << "Delete id: " << id;
    qDebug() << "Tasks size: " << tasks.size();

    int row = -1;
    for(int i = 0; i < tasks.size(); ++i) {
        if(tasks[i].id == id) {
            row = i;
            break;
        }
    }

    if(row == -1) {
        emit status("Delete task error! ❌ Check log ⬇");
        return false;
    }

    beginRemoveRows(QModelIndex(), row, row);

    tasks.removeAt(row);

    endRemoveRows();

    task.deleteTask(id);

    emit status("Delete task success! ✅");

    return true;
}

bool ListModelCpp::loadTask()
{
    QSqlQuery query(database.connection());

    query.prepare(
        "SELECT id, title, completed "
        "FROM tasks ");

    if(!query.exec()) {
        qWarning() << "Load failed: " << query.lastError().text();

        return false;

        emit status("Load task error! ❌ Check log ⬇");
    }

    beginResetModel();

    tasks.clear();

    while(query.next()) {
        int id = query.value(0).toInt();

        QString title = query.value(1).toString();

        bool completed = query.value(2).toBool();

        tasks.append({
            id,
            title,
            completed
        });
    }

    endResetModel();

    emit status("Load task success! ✅");

    return true;
}

int ListModelCpp::rowCount(const QModelIndex &parent) const
{
    return tasks.size();
}

QVariant ListModelCpp::data(const QModelIndex &index, int role) const
{
    const Task &task =
        tasks.at(index.row());

    switch(role)
    {
    case IdRole:
        return task.id;
    case TitleRole:
        return task.title;
    case CompletedRole:
        return task.completed;
    }

    return QVariant();
}

QHash<int, QByteArray> ListModelCpp::roleNames() const
{
    return {
        {IdRole, "id"},
        {TitleRole, "title"},
        {CompletedRole, "completed"}
    };
}

bool ListModelCpp::updateTitle(int id, const QString &title)
{


    if(!task.updateTitle(id, title)) {
        emit status("Task title change failed! ❌");

        return false;
    }

    for(int i = 0; i < tasks.size(); ++i) {
        if(tasks[i].id == id) {
            tasks[i].title = title;

            QModelIndex idx = index(i);

            emit dataChanged(
                idx,
                idx,
                {TitleRole}
                );

            emit status("Task text change success! ✅");

            return true;
        }
    }
    emit status("Task not found! ❌");

    return false;
}

bool ListModelCpp::updateModel(int id, bool completed)
{
    if(!task.updateModel(id, completed)) {
        emit status("Task update status failed! ❌");

        return false;
    }

    for(int i = 0; i < tasks.size(); ++i) {
        if(tasks[i].id == id) {
            tasks[i].completed = completed;


            QModelIndex  idx = index(i);

            emit dataChanged(
                idx,
                idx,
                {CompletedRole}
                );

            emit status("Task status update succes! ✅");

            return true;
        }
    }
    emit status("Task id not found! ❌");

    return false;
}

bool ListModelCpp::clearAll()
{
    if(!task.clearAll()) {
        emit status("Clear all tasks error! ❌");

        return false;
    }

    beginResetModel();

    tasks.clear();

    endResetModel();

    emit status("Clear all tasks success! ✅");

    return true;
}

