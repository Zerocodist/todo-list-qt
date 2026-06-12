#include "../listModel/listModelTest.h"

void ListModelCppTest::init()
{
    db = new Database(true);
    model = new ListModelCpp(*db);
}

void ListModelCppTest::cleanup()
{
    delete model;
    model = nullptr;

    delete db;
    db = nullptr;
}

void ListModelCppTest::addTaskTest()
{
    QCOMPARE(model->rowCount(), 0);

    QVERIFY(model->addTask("Buy milk"));

    QCOMPARE(model->rowCount(), 1);

    QModelIndex index = model->index(0, 0);

    QCOMPARE(
        model->data(
        index,
        ListModelCpp::TitleRole).toString(),
        QString("Buy milk")
        );
}

void ListModelCppTest::deleteTaskTest()
{
    model->addTask("Buy coffee");

    int id = model->data(
        model->index(0, 0),
        ListModelCpp::IdRole).toInt();

    QVERIFY(model->deleteTask(id));

    QCOMPARE(model->rowCount(), 0);
}

void ListModelCppTest::clearAllTest()
{
    model->addTask("Buy coffee");
    model->addTask("Buy milk");
    model->addTask("Buy tea");

    QVERIFY(model->clearAll());

    QCOMPARE(model->rowCount(), 0);
}

void ListModelCppTest::loadTaskTest()
{
    model->addTask("Buy drink");
    model->addTask("Buy chicken");
    model->addTask("Buy protein");

    ListModelCpp newModel(*db);

    QVERIFY(newModel.loadTask());

    QCOMPARE(newModel.rowCount(), 3);

    QCOMPARE(
        newModel.data(
        newModel.index(0, 0),ListModelCpp::TitleRole).toString(),
        QString("Buy drink")
    );

    QCOMPARE(
        newModel.data(
        newModel.index(1, 0),ListModelCpp::TitleRole).toString(),
        QString("Buy chicken")
    );

    QCOMPARE(
        newModel.data(
        newModel.index(2, 0),ListModelCpp::TitleRole).toString(),
        QString("Buy protein")
    );
}

void ListModelCppTest::updateModelTest()
{
    model->addTask("Just do it");

    int id = model->data(
             model->index(0, 0),ListModelCpp::IdRole).toInt();

    QVERIFY(model->updateModel(id, true));

    QCOMPARE(
        model->data(
        model->index(0, 0), ListModelCpp::CompletedRole).toBool(),
        bool(true)
    );
}

void ListModelCppTest::updateTitleTest()
{
    model->addTask("Golden brown");

    int id = model->data(
             model->index(0, 0), ListModelCpp::IdRole).toInt();

    QVERIFY(model->updateTitle(id, "Golden green"));

    QCOMPARE(
        model->data(
        model->index(0, 0), ListModelCpp::TitleRole).toString(),
        QString("Golden green")
    );
}

void ListModelCppTest::rowCountTest()
{
    model->addTask("Buy book");

    QCOMPARE(model->rowCount(), 1);
}

void ListModelCppTest::dataTest()
{
    model->addTask("Buy car");

    QModelIndex index  = model->index(0, 0);

    int id = model->data(index, ListModelCpp::IdRole).toInt();

    QCOMPARE(
        model->data(index, ListModelCpp::TitleRole).toString(),
        QString("Buy car")
    );

    QCOMPARE(
        model->data(index, ListModelCpp::CompletedRole).toBool(),
        bool(false)
    );

    QCOMPARE(
        model->data(index, ListModelCpp::IdRole).toInt(),
        int(id)
    );
}

void ListModelCppTest::roleNamesTest()
{
    auto roles = model->roleNames();

    QVERIFY(roles.contains(ListModelCpp::TitleRole));
    QVERIFY(roles.contains(ListModelCpp::IdRole));
    QVERIFY(roles.contains(ListModelCpp::CompletedRole));
}
