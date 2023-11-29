#include "MainWindow.hpp"

#include <QApplication>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {}

MainWindow::~MainWindow() {}

auto MainWindow::showMainWindow() -> void {
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

auto MainWindow::createMainWidgets() -> void {
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
  this->main_btn.reset(new QPushButton("What we do ?", this));
  this->btn_menu.reset(new QMenu("What You want ?"));
  this->btn_menu->addAction("Open test");
  this->btn_menu->addAction("Show log");
  this->btn_menu->addAction("Exit");
  this->main_btn->setMenu(this->btn_menu.get());
  this->main_widget.reset(new QWidget(this));
  this->setMenuBar(this->menu_bar.get());
  this->test_title.reset(new QLabel(""));
  this->main_test_widget.reset(new QWidget(this));
  this->test_grid_layout.reset(new QGridLayout());
  this->test_grid_layout->addWidget(this->test_title.get(), 0, 0,
                                    Qt::AlignHCenter);
  this->btn_return.reset(new QPushButton("RETURN"));
  this->test_grid_layout->addWidget(this->btn_return.get(), 1, 0,
                                    Qt::AlignHCenter);
  this->connect(this->btn_return.get(), SIGNAL(clicked()),
                SLOT(returnToMain()));
  this->main_test_widget->setLayout(this->test_grid_layout.get());
}

auto MainWindow::createMainLayout() -> void {
  this->main_layout.reset(new QGridLayout(this));
  this->main_layout->addWidget(this->label_logo.get(), 0, 0, Qt::AlignHCenter);
  this->main_layout->addWidget(this->main_btn.get(), 1, 0,
                               Qt::AlignTop | Qt::AlignHCenter);
  this->main_widget->setLayout(this->main_layout.get());
}

auto MainWindow::connectActions() -> void {
  this->connectMenuFile();
  this->connectMenuOptions();
  this->connectMenuHelp();
}
auto MainWindow::connectMenuFile() -> void {}

auto MainWindow::connectMenuOptions() -> void {}

auto MainWindow::connectMenuHelp() -> void {
  this->connect(this->menu_file->actions()[2], SIGNAL(triggered()), this,
                SLOT(close()));
  this->connect(this->menu_help->actions()[1], SIGNAL(triggered()), this,
                SLOT(showAbout()));
  this->connect(this->btn_menu->actions()[0], SIGNAL(triggered()), this,
                SLOT(openTest()));
}

auto MainWindow::showAbout() -> void { qApp->aboutQt(); }

auto MainWindow::openTest() -> void {
  QFileDialog dlg(this, "Open test", "./", "json test file (*.json)");
  this->prepareJsonTest(dlg.getOpenFileName());
}

auto MainWindow::createOneAnswerBox() -> void {}

auto MainWindow::createMultipleAnswerBox() -> void {}

auto MainWindow::prepareJsonTest(const QString &file) -> void {
  QFile test(file);
  if (test.open(QFile::ReadOnly)) {
    this->test_doc.reset(new QJsonDocument());
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(test.readAll(), &error);
    if (error.error != QJsonParseError::NoError) {
      this->test_title->setText(error.errorString());
      this->takeCentralWidget();
      this->setCentralWidget(this->main_test_widget.get());
    } else {
      QJsonObject jsonObj = doc.object();
      this->parseJSON(doc);
      this->test_title->setText("PARSER OK!");
      this->takeCentralWidget();
      this->setCentralWidget(this->main_test_widget.get());
    }
  }
}

auto MainWindow::parseJSON(const QJsonDocument &doc) -> void {
  if (doc.isObject()) {
    QJsonObject obj = doc.object();
    QJsonObject test = obj["TEST"].toObject();
    qDebug() << test["TEST_TITLE"].toString();
    qDebug() << test["TEST_TIME"].toString();
    QJsonArray jsonArray = obj["questions"].toArray();
    foreach (const QJsonValue &value, jsonArray) {
      QJsonObject tmp_obj = value.toObject();
      qDebug() << tmp_obj["type"].toString();
    }
  }
}

auto MainWindow::main() -> void {
  this->takeCentralWidget();
  this->setCentralWidget(this->main_widget.get());
}
auto MainWindow::returnToMain() -> void { this->main(); }