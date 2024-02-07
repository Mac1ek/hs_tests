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
    virtual auto add_title(const QString &) -> void = 0;
    virtual auto add_question(const QString &) -> void = 0;
    virtual auto create_layout() -> void = 0;
    virtual auto get_answers() -> std::vector<QString> & = 0;
public slots:
    virtual void setAnswer(bool) = 0;
};

#endif
