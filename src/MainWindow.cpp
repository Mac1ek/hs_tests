#include "MainWindow.hpp"

#include <QApplication>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <windows.h>
#include "MultipleQuestionWidget.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {}

MainWindow::~MainWindow() {}

auto MainWindow::showMainWindow() -> void
{
  QPixmap pixmap(tr(":/images/logo.png"));
  std::shared_ptr<QSplashScreen> screen(new QSplashScreen(pixmap));
  screen->show();
  Sleep(1000);
  this->createMainWidgets();
  this->createMainLayout();
  this->setCentralWidget(this->main_widget.get());
  this->resize(800, 600);
  this->connectActions();
  this->show();
}

auto MainWindow::createMainWidgets() -> void
{
  this->createMenuItems();
  this->setMenuActions();
  this->createMenuBar();

  QPixmap pixmap(tr(":/images/logo.png"));
  this->label_logo.reset(new QLabel(this));
  this->label_logo->setPixmap(pixmap);
  this->main_btn.reset(new QPushButton("What we do ?", this));
  this->btn_menu.reset(new QMenu());
  this->btn_menu->addAction("Open test");
  this->btn_menu->addAction("Show log");
  this->btn_menu->addAction("Exit");
  this->main_btn->setMenu(this->btn_menu.get());
  this->main_widget.reset(new QWidget);
  this->setMenuBar(this->menu_bar.get());
  this->test_title.reset(new QLabel(""));
  this->main_test_widget.reset(new QWidget);
  this->btn_return.reset(new QPushButton(tr("Return")));
  // this->test_grid_layout.reset(new QGridLayout());
  // this->test_grid_layout->addWidget(this->test_title.get(), 0, 0,
  //                                   Qt::AlignHCenter);
  this->connect(this->btn_return.get(), SIGNAL(clicked()), this, SLOT(returnToMain()));
  // this->main_test_widget->setLayout(this->test_grid_layout.get());
}

auto MainWindow::createMainLayout() -> void
{
  this->main_layout.reset(new QGridLayout);
  this->main_layout->addWidget(this->label_logo.get(), 0, 0, Qt::AlignHCenter);
  this->main_layout->addWidget(this->main_btn.get(), 1, 0, Qt::AlignTop | Qt::AlignHCenter);
  this->main_widget->setLayout(this->main_layout.get());
}

auto MainWindow::connectActions() -> void
{
  this->connectMenuFile();
  this->connectMenuOptions();
  this->connectMenuHelp();
}
auto MainWindow::connectMenuFile() -> void {}

auto MainWindow::connectMenuOptions() -> void {}

auto MainWindow::connectMenuHelp() -> void
{
  this->connect(this->menu_file->actions()[2], SIGNAL(triggered()), this,
                SLOT(close()));
  this->connect(this->menu_help->actions()[1], SIGNAL(triggered()), this,
                SLOT(showAbout()));
  this->connect(this->btn_menu->actions()[0], SIGNAL(triggered()), this,
                SLOT(openTest()));
}

auto MainWindow::showAbout() -> void { qApp->aboutQt(); }

auto MainWindow::openTest() -> void
{
  QFileDialog dlg(this, "Open test", "./", "json test file (*.json)");
  this->prepareJsonTest(dlg.getOpenFileName());
}

auto MainWindow::createOneAnswerBox() -> void {}

auto MainWindow::createMultipleAnswerBox() -> void {}

auto MainWindow::prepareJsonTest(const QString &file) -> void
{
  QFile test(file);
  if (test.open(QFile::ReadOnly))
  {
    this->test_doc.reset(new QJsonDocument());
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(test.readAll(), &error);
    if (error.error != QJsonParseError::NoError)
    {
      this->test_title->setText(error.errorString());
      this->takeCentralWidget();
      this->setCentralWidget(this->main_test_widget.get());
    }
    else
    {
      QJsonObject jsonObj = doc.object();
      this->parseJSON(doc);
      this->setWindowTitle("PARSER OK!");
      this->setCentralWidget(this->test_questions[0].get());
    }
  }
}

auto MainWindow::parseJSON(const QJsonDocument &doc) -> void
{
  if (doc.isObject())
  {
    QJsonObject obj = doc.object();
    qDebug() << obj["PARAM_TITLE"].toString();
    qDebug() << obj["PARAM_TIME"].toString();
    QJsonArray jsonArray = obj["questions"].toArray();
    foreach (const QJsonValue &value, jsonArray)
    {
      QJsonObject tmp_obj = value.toObject();
      qDebug() << tmp_obj["type"].toString();
      if (tmp_obj["type"] == "multiple")
      {
        std::shared_ptr<QuestionWidget> questions;
        questions.reset(new MultipleQuestionWidget());
        qDebug() << "MULTIPLE ANSWERS: \n";
        foreach (const QJsonValue &value, tmp_obj["quests"].toArray())
        {
          QJsonObject question = value.toObject();
          questions->add_question(question.keys()[0]);
          qDebug() << question.keys()[0] << "ANSWER: " << question.take(question.keys()[0]).toString();
        }
        questions->create_layout();
        this->test_questions.push_back(questions);
      }
      if (tmp_obj["type"] == "single")
      {
        qDebug() << "SINGLE ANSWER: \n";
        foreach (const QJsonValue &value, tmp_obj["quests"].toArray())
        {
          QJsonObject question = value.toObject();
          qDebug() << question.keys()[0] << "ANSWER: " << question.take(question.keys()[0]).toString();
        }
      }
      if (tmp_obj["type"] == "multiple_image")
      {
        qDebug() << "MULTIPLE IMAGE ANSWERS: \n";
        qDebug() << tmp_obj["image"];
        foreach (const QJsonValue &value, tmp_obj["quests"].toArray())
        {
          QJsonObject question = value.toObject();
          qDebug() << question.keys()[0] << "ANSWER: " << question.take(question.keys()[0]).toString();
        }
      }
    }
  }
}

auto MainWindow::main() -> void
{
  this->setCentralWidget(this->main_widget.get());
}
auto MainWindow::returnToMain() -> void { this->main(); }

auto MainWindow::setMenuActions() -> void
{
  this->menu_file->addAction("OPEN TEST");
  this->menu_file->addAction("SAVE RESULT");
  this->menu_file->addAction("QUIT");
  this->menu_options->addAction("OPEN OPTIONS");
  this->menu_help->addAction("ABOUT");
  this->menu_help->addAction("ABOUT QT");
}

auto MainWindow::createMenuItems() -> void
{
  this->menu_bar.reset(new QMenuBar(this));
  this->menu_file.reset(new QMenu("FILE", this));
  this->menu_options.reset(new QMenu("OPTIONS", this));
  this->menu_help.reset(new QMenu("HELP", this));
}

auto MainWindow::createMenuBar() -> void
{
  this->menu_bar->addMenu(this->menu_file.get());
  this->menu_bar->addMenu(this->menu_options.get());
  this->menu_bar->addMenu(this->menu_help.get());
}