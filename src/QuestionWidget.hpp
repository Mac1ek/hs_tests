#ifndef _QUESTION_WIDGET_HPP__
#define _QUESTION_WIDGET_HPP__

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QString>
#include <QJsonArray>

class QuestionWidget : public QWidget
{
    Q_OBJECT

protected:
    std::vector<std::pair<QLabel *, QCheckBox *>> questions;

    QPushButton *button_next;
    QLabel *label_title;

    QHBoxLayout *btnLayout;
    QGridLayout *gridLayout;
    QVBoxLayout *mainLayout;

    std::vector<QString> answers;

public:
    QuestionWidget();
    virtual ~QuestionWidget();
    virtual void add_title(const QString &) = 0;
    virtual void add_question(const QString &) = 0;
    virtual void create_layout() = 0;
    virtual auto get_answers() -> std::vector<QString> & = 0;
};

#endif
