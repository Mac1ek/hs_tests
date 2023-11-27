#include <QApplication>
#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
}

MainWindow::~MainWindow()
{
}

auto MainWindow::showMainWindow() -> void
{
    QPixmap pixmap(tr(":/images/logo.png"));
    std::shared_ptr<QSplashScreen> screen(new QSplashScreen(pixmap));
    screen->show();
    this->createMainWidgets();
    this->createMainLayout();
    this->setCentralWidget(this->main_widget.get());
    this->resize(800, 600);
    this->connectActions();
    this->show();
}

auto MainWindow::createMainWidgets() -> void
{
    this->menu_bar.reset(new QMenuBar(this));
    this->menu_file.reset(new QMenu("FILE", this));
    this->menu_file->addAction("OPEN TEST");
    this->menu_file->addAction("SAVE RESULT");
    this->menu_file->addAction("QUIT");
    this->menu_options.reset(new QMenu("OPTIONS", this));
    this->menu_options->addAction("OPEN OPTIONS");
    this->menu_help.reset(new QMenu("HELP", this));
    this->menu_help->addAction("ABOUT");
    this->menu_help->addAction("ABOUT QT");
    this->menu_bar->addMenu(this->menu_file.get());
    this->menu_bar->addMenu(this->menu_options.get());
    this->menu_bar->addMenu(this->menu_help.get());
    QPixmap pixmap(tr(":/images/logo.png"));
    this->label_logo.reset(new QLabel(this));
    this->label_logo->setPixmap(pixmap);
    this->main_widget.reset(new QWidget(this));
    this->setMenuBar(this->menu_bar.get());
}

auto MainWindow::createMainLayout() -> void
{
    this->main_layout.reset(new QGridLayout(this));
    this->main_layout->addWidget(label_logo.get(), 0, 0, Qt::AlignHCenter);
    this->main_widget->setLayout(this->main_layout.get());
}

auto MainWindow::connectActions() -> void
{
    this->connectMenuFile();
    this->connectMenuOptions();
    this->connectMenuHelp();
}
auto MainWindow::connectMenuFile() -> void
{
}

auto MainWindow::connectMenuOptions() -> void
{
}

auto MainWindow::connectMenuHelp() -> void
{
    this->connect(this->menu_file->actions()[2], SIGNAL(triggered()), this, SLOT(close()));
    this->connect(this->menu_help->actions()[1], SIGNAL(triggered()), this, SLOT(showAbout()));
}

auto MainWindow::showAbout() -> void
{
    qApp->aboutQt();
}
