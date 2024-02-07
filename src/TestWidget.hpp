#ifndef _TEST_WIDGET_HPP__
#define _TEST_WIDGET_HPP__

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QStackedWidget>
#include <QLabel>
#include <QTimer>
#include <vector>
#include "QuestionWidget.hpp"
#include "LangTranslation.hpp"

class TestWidget : public QWidget
{
    std::vector<QuestionWidget *> test_questions;

    QLabel *summary_img_label, *summary_test_info, *label_logo, *title, *time, *summary_question_success;
    QPushButton *next_btn, *main_btn;
    QWidget *summary_widget, *central_widget;
    QStackedWidget *widgetsStack;

    QVBoxLayout *main_layout;
    QGridLayout *summary_layout, *start_layout;

    QTimer *testTimer;

    std::vector<std::vector<std::pair<QString, QString>>> answers;

    const LangTranslation &translation;

private:
    auto create_widgets() -> void;
    auto create_layouts() -> void;
    auto add_answers(std::vector<QString> &) -> void;

public:
    Q_OBJECT
public:
    TestWidget(QTimer *, const LangTranslation &);
    ~TestWidget();

    auto add_questionBlock(QuestionWidget *block) -> void;
    auto createStartPage(const QString, const QString) -> void;
    auto run() -> void;
    auto connect_widgets() -> void;
    auto reset_test() -> void;
    auto store_answers(std::vector<std::pair<QString, QString>> &a) -> void;
    auto addSumaryWindow() -> void;
    auto test_end_now() -> void;

public slots:
    auto start() -> void;
    auto nextQuestion() -> void;
};

#endif