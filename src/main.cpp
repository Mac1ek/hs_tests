#include "MainWindow.hpp"
#include <QApplication>

auto main(int argc, char **argv) -> int
{
    QApplication app(argc, argv);
    MainWindow w(nullptr);
    w.showMainWindow();
    return app.exec();
}
