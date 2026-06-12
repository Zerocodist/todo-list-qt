#include "../proxyModel/proxyModelTest.h"

void ProxyModelTest::setSearchTextTest()
{
    Database db(true);
    ListModelCpp model(db);
    ProxyModel proxy;

    proxy.setSourceModel(&model);

    model.addTask("Buy milk");
    model.addTask("Buy coffee");
    model.addTask("Buy tea");

    proxy.setSearchText("milk");

    QCOMPARE(proxy.rowCount(), 1);

    QCOMPARE(
        proxy.data(proxy.index(0, 0), ListModelCpp::TitleRole).toString(),
        QString("Buy milk")
    );
}
