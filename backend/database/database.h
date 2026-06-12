#pragma once

#include <QObject>
#include <QtSql/QtSql>

class Database : public QObject {
    Q_OBJECT
public:
    explicit Database(bool TestMode = false, QObject *parent = nullptr);
    void initDatabase();
    bool openDatabase();
    void createTable();
    QSqlDatabase connection() const;
    ~Database();
private:
    QSqlDatabase db;
    QString dbName;
    QString connectionName;

};
