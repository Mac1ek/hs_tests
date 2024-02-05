#ifndef _MAIN_WINDOW_HPP__
#define _MAIN_WINDOW_HPP__

#include <QCheckBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QJsonDocument>
#include <QLabel>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QRadioButton>
#include <QSplashScreen>
#include <QStackedWidget>
#include <QStatusBar>
#include <QTimer>
#include <QWidget>
#include <random>
#include "QuestionWidget.hpp"
#include "TestWidget.hpp"

class MainWindow : public QMainWindow
{

  Q_OBJECT

private:
  QSplashScreen *splash_screen;
  QPushButton *select_test_btn;
  QGridLayout *main_layout;
  std::vector<QPushButton *> test_btn;
  QGroupBox *group_question;
  QMenuBar *menu_bar;
  QMenu *menu_file;
  QMenu *menu_help;
  QMenu *menu_options;
  QWidget *main_widget;
  QLabel *label_logo;
  QMenu *btn_menu;
  QPushButton *main_btn;
  QWidget *main_test_widget;
  QJsonDocument *test_doc;
  QLabel *test_title;
  QGridLayout *test_grid_layout;
  QRadioButton *radio_test_button;
  QCheckBox *checkbox_test_button;
  TestWidget *test_widget;
  QStackedWidget *stacketTestWidget;
  QStatusBar *statusBar;
  std::vector<std::pair<QString, QString>> answers;

  QTimer *timer;
  unsigned int countdown;

public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();
  auto showMainWindow() -> void;

private:
  auto createMainWidgets() -> void;
  auto createMainLayout() -> void;
  auto connectActions() -> void;
  auto connectMenuFile() -> void;
  auto connectMenuOptions() -> void;
  auto connectMenuHelp() -> void;
  auto connectTestButton() -> void;
  auto createOneAnswerBox() -> void;
  auto createMultipleAnswerBox() -> void;
  auto prepareTestJson(const QString &) -> void;
  auto prepareTestWindow() -> void;
  auto parseJSON(const QJsonDocument &) -> bool;
  auto mainApp() -> void;
  auto formatTime(int) -> QString;
  auto addMultipleQuestionWidget(const QJsonObject &, std::default_random_engine &) -> void;
  auto addMultipleQuestionImageWidget(const QJsonObject &, std::default_random_engine &) -> void;
  auto addSingleQuestionImageWidget(const QJsonObject &, std::default_random_engine &) -> void;
  auto showSplashScreen() -> void;

public slots:

  auto showAbout() -> void;
  auto showAboutQt() -> void;
  auto createMenuActions() -> void;
  auto createMenuItems() -> void;
  auto createMenuBar() -> void;
  auto openTest() -> void;
  auto returnToMain() -> void;
  auto updateTimer() -> void;
  auto quitApp() -> void;
};

#endif