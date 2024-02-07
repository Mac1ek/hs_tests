#ifndef _MULTIPLE_QUESTION_WIDGET_HPP__
#define _MULTIPLE_QUESTION_WIDGET_HPP__

#include "QuestionWidget.hpp"
#include <QWidget>
#include <QCheckBox>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

class MultipleQuestionWidget : virtual public QuestionWidget
{

public:
    auto create_layout() -> void;
    auto create_widgets() -> void;

public:
    MultipleQuestionWidget();
    ~MultipleQuestionWidget();

    auto add_title(const QString &) -> void;
    auto add_question(const QString &) -> void;
    auto get_answers() -> std::vector<QString> &;

private slots:
    auto setAnswer(bool) -> void;
};

#endif
