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
#include <QTimer>
#include <QWidget>
#include <memory>
#include "QuestionWidget.hpp"

class MainWindow : public QMainWindow {
  Q_OBJECT

private:
  std::shared_ptr<QPushButton> select_test_btn;
  std::shared_ptr<QGridLayout> main_layout;
  std::vector<std::shared_ptr<QPushButton>> test_btn;
  std::shared_ptr<QGroupBox> group_question;
  std::shared_ptr<QMenuBar> menu_bar;
  std::shared_ptr<QMenu> menu_file;
  std::shared_ptr<QMenu> menu_help;
  std::shared_ptr<QMenu> menu_options;
  std::shared_ptr<QWidget> main_widget;
  std::shared_ptr<QLabel> label_logo;
  std::shared_ptr<QMenu> btn_menu;
  std::shared_ptr<QPushButton> main_btn;
  std::shared_ptr<QWidget> main_test_widget;
  std::shared_ptr<QJsonDocument> test_doc;
  std::shared_ptr<QLabel> test_title;
  std::shared_ptr<QGridLayout> test_grid_layout;
  std::shared_ptr<QRadioButton> radio_test_button;
  std::shared_ptr<QCheckBox> checkbox_test_button;
  std::shared_ptr<QPushButton> btn_return;
  std::shared_ptr<QHBoxLayout> box_layout;

  std::vector<std::shared_ptr<QuestionWidget> > test_questions;

  QTimer timer;

public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();
  auto showMainWindow() -> void;
  auto createMainWidgets() -> void;
  auto createMainLayout() -> void;

private:
  auto connectActions() -> void;
  auto connectMenuFile() -> void;
  auto connectMenuOptions() -> void;
  auto connectMenuHelp() -> void;
  auto createOneAnswerBox() -> void;
  auto createMultipleAnswerBox() -> void;
  auto prepareJsonTest(const QString &file) -> void;
  auto parseJSON(const QJsonDocument &doc) -> void;
  auto main() -> void;
private slots:
  auto showAbout() -> void;
  auto setMenuActions() -> void;
  auto createMenuItems() -> void;
  auto createMenuBar() -> void;
  auto openTest() -> void;
  auto returnToMain() -> void;
};

#endif