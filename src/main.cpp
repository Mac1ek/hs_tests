#include "MainWindow.hpp"
#include <QApplication>
#ifdef _WIN32
#include <Windows.h>
#endif

#ifdef _WIN32
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int main(int argc, char *argv[])
#endif
{
#ifdef _WIN32
    QApplication app(__argc, __argv);
#else
  QApplication app(argc, argv);
#endif
    MainWindow w(nullptr);
    w.showMainWindow();
    return app.exec();
  }
