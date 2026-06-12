#include <QtTest>
#include <QCoreApplication>
#include "database/databaseTest.h"
#include "manager/managerTest.h"
#include "listModel/listModelTest.h"
#include "proxyModel/proxyModelTest.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    int status = 0;

    {
        DatabaseTest tc;
        status |= QTest::qExec(&tc, argc, argv);
    }

    {
        TaskManagerTest tc;
        status |= QTest::qExec(&tc, argc, argv);
    }

    {
        ListModelCppTest tc;
        status |= QTest::qExec(&tc, argc, argv);
    }

    {
        ProxyModelTest tc;
        status |= QTest::qExec(&tc, argc, argv);
    }

    return status;
}

