#include "database.h"
#include <QDebug>
#include <QDebug>

Database::Database(bool TestMode, QObject *parent)
    : QObject(parent)
{

    connectionName = TestMode ? QUuid::createUuid().toString() : "main_connection";
    dbName = TestMode ? ":memory:" : "tasks.db";

    initDatabase();
}

void Database::createTable()
{
    QSqlQuery query(db);

    if(!query.exec(
            "CREATE TABLE IF NOT EXISTS tasks ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "title TEXT NOT NULL, "
            "completed INTEGER DEFAULT 0)"
            )) {
        qWarning() << "Create table failed!: " << query.lastError().text();
        qWarning() << QSqlDatabase::drivers();
    }

}

void Database::initDatabase() {
    if(!openDatabase()) return;

    createTable();
}

bool Database::openDatabase()
{
    if(dbName == ":memory:") {
        db = QSqlDatabase::addDatabase("QSQLITE",   connectionName);
    } else {
        if(QSqlDatabase::contains(connectionName))
        db = QSqlDatabase::database(connectionName);

        else
        {
            db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
        }

        db.setDatabaseName(dbName);

        return db.open();
    }

    db.setDatabaseName(dbName);

    if(!db.open()) {
        qWarning() << "Database error: " << db.lastError().text();
        return false;
    }

    return true;
}

QSqlDatabase Database::connection() const {
    return db;
}

Database::~Database()
{
    QString name = connectionName;

    if(db.isOpen()) db.close();

    db = QSqlDatabase();

    QSqlDatabase::removeDatabase(name);
}