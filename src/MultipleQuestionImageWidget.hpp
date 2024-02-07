#ifndef _MULTIPLE_QUESTION_IMAGE_WIDGET_HPP__
#define _MULTIPLE_QUESTION_IMAGE_WIDGET_HPP__

#include "MultipleQuestionWidget.hpp"
#include <QWidget>
#include <QGridLayout>
#include <QCheckBox>
#include <QPushButton>
#include <QLabel>
#include <vector>

class MultipleQuestionImageWidget : public MultipleQuestionWidget
{

private:
    QPixmap image;

    std::vector<std::pair<QLabel *, QCheckBox *>> questions;

    QLabel *label_image;

    auto create_layout() -> void;
    auto create_widgets() -> void;

public:
    MultipleQuestionImageWidget(QString);
    ~MultipleQuestionImageWidget();

    auto add_title(const QString &) -> void;
    auto add_question(const QString &) -> void;
    auto get_answers() -> std::vector<QString> &;

private slots:
    auto setAnswer(bool) -> void;
};

#endif