#ifndef _MULTIPLE_QUESTION_WIDGET_HPP__
#define _MULTIPLE_QUESTION_WIDGET_HPP__

#include "QuestionWidget.hpp"
#include <QWidget>
#include <QCheckBox>
#include <QGridLayout>
#include <QLabel>

class MultipleQuestionWidget : public QuestionWidget {

private:
    std::vector<std::pair<std::shared_ptr<QLabel>, std::shared_ptr<QCheckBox> > > questions;

    std::shared_ptr<QGridLayout> mainLayout;

public:
    Q_OBJECT

public:
    MultipleQuestionWidget();
    ~MultipleQuestionWidget();

    void add_question(const QString& q);
    void create_layout();

};

#endif
