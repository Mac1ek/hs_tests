#ifndef _SINGLE_QUESTION_WIDGET_HPP__
#define _SINGLE_QUESTION_WIDGET_HPP__

#include "QuestionWidget.hpp"
#include <QWidget>

class SingleQuestionWidget : virtual public QuestionWidget
{

private:
    QImage image;

public:
    SingleQuestionWidget();
    ~SingleQuestionWidget();
};

#endif