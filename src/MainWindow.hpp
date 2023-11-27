#ifndef _MAIN_WINDOW_HPP__
#define _MAIN_WINDOW_HPP__

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QRadioButton>
#include <QMenu>
#include <QMenuBar>
#include <QSplashScreen>
#include <QTimer>
#include <QGridLayout>
#include <QMenuBar>
#include <QWidget>
#include <QGroupBox>
#include <memory>

class MainWindow : public QMainWindow
{
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
private slots:
    auto showAbout() -> void;
};

#endif