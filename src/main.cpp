#include "MainWindow.hpp"
#include <QApplication>
#include <windows.h>

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
  QApplication app(__argc, __argv);
  MainWindow w(nullptr);
  w.showMainWindow();
  return app.exec();
}
