#ifndef _QUESTION_WIDGET_HPP__
#define _QUESTION_WIDGET_HPP__

#include <QString>
#include <QWidget>
#include <QJsonArray>

class QuestionWidget: public QWidget
{
    Q_OBJECT
public:
QuestionWidget();
virtual ~QuestionWidget();
virtual void add_question(const QString&) = 0;
virtual void create_layout() = 0;
};

#endif
