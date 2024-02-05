#include "MainWindow.hpp"
#include "MultipleQuestionWidget.hpp"
#include "MultipleQuestionImageWidget.hpp"
#include "version.hpp"

#include <QApplication>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QMessageBox>
#include <QScrollArea>
#include <QSizePolicy>
#include <QScrollBar>
#include <QThread>
#include <windows.h>
#include <vector>
#include <random>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
  test_widget = nullptr;
  this->timer = new QTimer();
}

MainWindow::~MainWindow() {}

auto MainWindow::showMainWindow() -> void
{
  this->showSplashScreen();
  this->createMainWidgets();
  this->createMainLayout();
  this->connectActions();
  this->setCentralWidget(this->main_widget);
  QThread::msleep(1000);
  delete this->splash_screen;
  this->splash_screen = nullptr;
  this->show();
}

auto MainWindow::showSplashScreen() -> void
{
  QPixmap pixmap(tr(":/images/logo.png"));
  this->splash_screen = new QSplashScreen(pixmap);
  this->splash_screen->show();
}

auto MainWindow::createMainWidgets() -> void
{
  this->createMenuItems();
  this->createMenuActions();
  this->createMenuBar();

  QPixmap pixmap(tr(":/images/logo.png"));
  this->test_widget = new TestWidget(this->timer);
  this->label_logo = new QLabel(this);
  this->label_logo->setPixmap(pixmap);
  this->main_btn = new QPushButton("Co robimy ?", this);
  this->btn_menu = new QMenu();
  this->btn_menu->addAction("Otwórz test");
  this->btn_menu->addAction("Pokaż log");
  this->btn_menu->addAction("Kończymy");
  this->main_btn->setMenu(this->btn_menu);
  this->main_widget = new QWidget();

  this->setMenuBar(this->menu_bar);

  this->test_title = new QLabel("");
  this->main_test_widget = new QWidget();
  this->statusBar = new QStatusBar();

  this->setStatusBar(this->statusBar);
}

auto MainWindow::createMainLayout() -> void
{
  this->main_layout = new QGridLayout();
  this->main_layout->addWidget(this->label_logo, 0, 0, Qt::AlignHCenter);
  this->main_layout->addWidget(this->main_btn, 1, 0, Qt::AlignTop | Qt::AlignHCenter);
  this->main_widget->setLayout(this->main_layout);
}

auto MainWindow::connectActions() -> void
{
  this->connectMenuFile();
  this->connectMenuOptions();
  this->connectMenuHelp();
  this->connectTestButton();
}
auto MainWindow::connectMenuFile() -> void
{
  this->connect(this->menu_file->actions()[2], SIGNAL(triggered()), this, SLOT(close()));
  this->connect(this->menu_file->actions()[3], SIGNAL(triggered()), this, SLOT(returnToMain()));
}

auto MainWindow::connectMenuOptions() -> void
{
  connect(timer, &QTimer::timeout, this, &MainWindow::updateTimer);
}

auto MainWindow::connectMenuHelp() -> void
{
  this->connect(this->menu_help->actions()[0], SIGNAL(triggered()), this, SLOT(showAbout()));
  this->connect(this->menu_help->actions()[1], SIGNAL(triggered()), this, SLOT(showAboutQt()));
}

auto MainWindow::connectTestButton() -> void
{
  this->connect(this->btn_menu->actions()[0], SIGNAL(triggered()), this, SLOT(openTest()));
  this->connect(this->btn_menu->actions()[2], SIGNAL(triggered()), this, SLOT(quitApp()));
}

auto MainWindow::quitApp() -> void
{
  this->close();
}

auto MainWindow::showAbout() -> void
{
  QMessageBox::about(this, tr("version %1").arg(HS_TEST_VERSION), tr("%1").arg(HS_TEST_VERSION_INFO));
}

auto MainWindow::showAboutQt() -> void { qApp->aboutQt(); }

auto MainWindow::openTest() -> void
{
  QString test_file = QFileDialog::getOpenFileName(this, "Wybierz test: ", QDir::currentPath(), "Test (*.json);;All files (*)");
  if (!test_file.isEmpty())
    this->prepareTestJson(test_file);
}

auto MainWindow::prepareTestJson(const QString &file) -> void
{
  QFile test(file);

  if (test.open(QFile::ReadOnly))
  {
    this->test_doc = new QJsonDocument();

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(test.readAll(), &error);

    if (error.error != QJsonParseError::NoError)
    {
      this->test_title->setText(error.errorString());
      this->setCentralWidget(this->main_test_widget);
    }
    else
    {
      QJsonObject jsonObj = doc.object();
      if (this->parseJSON(doc))
      {
        this->prepareTestWindow();
      }
    }
  }
}

auto MainWindow::prepareTestWindow() -> void
{
  QScrollArea *scrollArea = new QScrollArea();
  scrollArea->setWidgetResizable(true);
  this->test_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  scrollArea->setWidget(this->test_widget);

  scrollArea->verticalScrollBar()->setStyleSheet("QScrollBar:vertical {"
                                                 "    border: 1px solid grey;"
                                                 "    background: lightgrey;"
                                                 "    width: 15px;"
                                                 "    margin: 0 0 0 0;"
                                                 "}");

  scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  this->test_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  scrollArea->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

  this->setCentralWidget(scrollArea);
  this->resize(scrollArea->widget()->sizeHint());
}

auto MainWindow::addMultipleQuestionWidget(const QJsonObject &test_obj, std::default_random_engine &rand_engine) -> void
{
  std::vector<QJsonObject> quest_block;
  foreach (const QJsonValue &value, test_obj["quests"].toArray())
  {
    QJsonObject question = value.toObject();
    quest_block.push_back(question);
  }

  std::shuffle(quest_block.begin(), quest_block.end(), rand_engine);

  QuestionWidget *questions = new MultipleQuestionWidget();
  questions->add_title(test_obj["title"].toString());

  for (QJsonObject question : quest_block)
  {
    questions->add_question(question.keys()[0]);
    this->answers.push_back(std::make_pair(tr("FALSE"), question.take(question.keys()[0]).toString()));
  }

  this->test_widget->store_answers(this->answers);
  this->answers.clear();
  questions->create_layout();
  this->test_widget->add_questionBlock(questions);
}

auto MainWindow::addMultipleQuestionImageWidget(const QJsonObject &test_obj, std::default_random_engine &rand_engine) -> void
{
  std::vector<QJsonObject> quest_block;
  foreach (const QJsonValue &value, test_obj["quests"].toArray())
  {
    QJsonObject question = value.toObject();
    quest_block.push_back(question);
  }
  std::shuffle(quest_block.begin(), quest_block.end(), rand_engine);

  QuestionWidget *questions = new MultipleQuestionImageWidget(test_obj["image"].toString());
  questions->add_title(test_obj["title"].toString());

  for (QJsonObject question : quest_block)
  {
    questions->add_question(question.keys()[0]);
    this->answers.push_back(std::make_pair(tr("FALSE"), question.take(question.keys()[0]).toString()));
  }

  this->test_widget->store_answers(this->answers);
  this->answers.clear();
  questions->create_layout();
  this->test_widget->add_questionBlock(questions);
}

auto MainWindow::parseJSON(const QJsonDocument &doc) -> bool
{
  if (doc.isObject())
  {
    QJsonObject obj = doc.object();
    this->setWindowTitle(tr("STRUKTURA TESTU OK: %1").arg(obj["PARAM_TITLE"].toString()));
    this->test_widget->createStartPage(obj["PARAM_TITLE"].toString(), obj["PARAM_TIME"].toString());
    this->countdown = obj["PARAM_TIME"].toString().toUInt() * 60;

    QJsonArray jsonArray = obj["questions"].toArray();
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rand_engine(seed);

    foreach (const QJsonValue &value, jsonArray)
    {
      QJsonObject test_obj = value.toObject();
      if (test_obj["type"] == "multiple")
      {
        this->addMultipleQuestionWidget(test_obj, rand_engine);
      }
      else if (test_obj["type"] == "multiple_image")
      {
        this->addMultipleQuestionImageWidget(test_obj, rand_engine);
      }
      else if (test_obj["type"] == "single")
      {
        this->addSingleQuestionImageWidget(test_obj, rand_engine);
      }
      else {
        return false;
      }
    }
    return true;
  }
  else
  {
    return false;
  }
}

auto MainWindow::addSingleQuestionImageWidget(const QJsonObject &test_obj, std::default_random_engine &rand_engine) -> void
{
  // TODO
  foreach (const QJsonValue &value, test_obj["quests"].toArray())
  {
    QJsonObject question = value.toObject();
  }
}

auto MainWindow::updateTimer() -> void
{
  if (countdown == 0)
  {
    this->timer->stop();
    this->statusBar->showMessage("Czas się skończył!");
    qApp->beep();
    this->test_widget->test_end_now();
  }
  else
  {
    --countdown;
    this->statusBar->showMessage("Czas: " + this->formatTime(countdown));
  }
}

auto MainWindow::formatTime(int seconds) -> QString
{
  QTime time(0, 0, 0);
  time = time.addSecs(seconds);
  return time.toString("mm:ss");
}

auto MainWindow::returnToMain() -> void
{
  if (this->test_widget != nullptr)
  {
    delete test_widget;
    test_widget = nullptr;
  }
  this->timer->stop();
  QPixmap pixmap(tr(":/images/logo.png"));
  this->test_widget = new TestWidget(this->timer);
  this->label_logo = new QLabel(this);
  this->label_logo->setPixmap(pixmap);
  this->main_btn = new QPushButton("Co robimy ?", this);
  this->btn_menu = new QMenu();
  this->btn_menu->addAction("Otwórz test");
  this->btn_menu->addAction("Pokaż log");
  this->btn_menu->addAction("Kończymy");
  this->main_btn->setMenu(this->btn_menu);
  this->main_widget = new QWidget();
  this->main_layout = new QGridLayout();
  this->main_layout->addWidget(this->label_logo, 0, 0, Qt::AlignHCenter);
  this->main_layout->addWidget(this->main_btn, 1, 0, Qt::AlignTop | Qt::AlignHCenter);
  this->main_widget->setLayout(this->main_layout);
  this->setCentralWidget(this->main_widget);
  this->connectTestButton();
}

auto MainWindow::createMenuActions() -> void
{
  this->menu_file->addAction("OTWÓRZ TEST");
  this->menu_file->addAction("ZAPISZ WYNIK");
  this->menu_file->addAction("ZAKOŃCZ");
  this->menu_file->addAction("ZRESETUJ TEST");
  this->menu_options->addAction("OPCJE");
  this->menu_help->addAction("O PROGRAMIE");
  this->menu_help->addAction("ABOUT QT");
}

auto MainWindow::createMenuItems() -> void
{
  this->menu_bar = new QMenuBar(this);
  this->menu_file = new QMenu("PLIK", this);
  this->menu_options = new QMenu("OPCJE", this);
  this->menu_help = new QMenu("POMOC", this);
}

auto MainWindow::createMenuBar() -> void
{
  this->menu_bar->addMenu(this->menu_file);
  this->menu_bar->addMenu(this->menu_options);
  this->menu_bar->addMenu(this->menu_help);
}
