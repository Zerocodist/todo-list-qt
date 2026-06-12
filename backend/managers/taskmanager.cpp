#include "taskmanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

TaskManager::TaskManager(Database &db, QObject *parent)
    : QObject(parent),
    database(db)
{
}

int TaskManager::addTask(const QString &title)
{
    QSqlQuery query(database.connection());

    query.prepare(
        "INSERT INTO tasks (title, completed) "
        "VALUES (:title, :completed)"
        );

    query.bindValue(":title", title);
    query.bindValue(":completed", 0);

    if(!query.exec()) {
        qWarning() << "Add task failed: "
                   << query.lastError().text();
        return -1;
    }

    int newId = query.lastInsertId().toInt();

    return newId;
}

bool TaskManager::deleteTask(int id)
{
    QSqlQuery query(database.connection());

    query.prepare("DELETE FROM tasks WHERE id = :id");

    query.bindValue(":id", id);

    if(!query.exec()) {
        qWarning() << "Delete task failed: "
                   << query.lastError().text();

        return false;
    }

    return true;
}

QVector<Task> TaskManager::search(const QString &text)
{
    QVector<Task> foundTasks;

    QSqlQuery query(database.connection());

    qDebug() << "Search: " << text;

    query.prepare(
        "SELECT id, title, completed "
        "FROM tasks "
        "WHERE title LIKE :text"
        );

    query.bindValue(":text", "%" + text  + "%");

    if(!query.exec()) {
        qWarning() << "Search failed: " << query.lastError().text();

        return foundTasks;
    }

    while(query.next()) {

        Task task;

        task.id = query.value(0).toInt();
        task.title = query.value(1).toString();
        task.completed = query.value(2).toBool();

        foundTasks.append(task);
    }
    qDebug() << "Found: " << foundTasks.size();

    return foundTasks;
}

bool TaskManager::updateModel(int id, bool completed)
{
    QSqlQuery query(database.connection());

    query.prepare(
        "UPDATE tasks "
        "SET completed = :completed "
        "WHERE id = :id"
        );

    query.bindValue(":completed", completed);
    query.bindValue(":id", id);

    if(!query.exec()) {
        qWarning() << query.lastError().text();
        return false;
    }

    return true;
}

bool TaskManager::updateTitle(int id, const QString &title)
{
    QSqlQuery query(database.connection());

    query.prepare(
        "UPDATE tasks "
        "SET title = :title "
        "WHERE id = :id"
        );

    query.bindValue(":title", title);
    query.bindValue(":id", id);

    if(!query.exec()) {
        qWarning() << "Title update failed: " << query.lastError().text();

        return false;
    }

    return true;
}

bool TaskManager::clearAll()
{
    QSqlQuery query(database.connection());

    query.prepare("DELETE FROM tasks");

    return query.exec();
}