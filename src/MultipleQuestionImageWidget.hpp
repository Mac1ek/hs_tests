#ifndef _MULTIPLE_QUESTION_IMAGE_WIDGET_HPP__
#define _MULTIPLE_QUESTION_IMAGE_WIDGET_HPP__

#include "QuestionWidget.hpp"
#include <QWidget>
#include <QGridLayout>
#include <QCheckBox>
#include <QLabel>
#include <vector>

class MultipleQuestionImageWidget: public QuestionWidget {
    Q_OBJECT
    QPixmap image;
    QGridLayout* layout;
    std::vector<std::pair<QLabel, QCheckBox> > answers;
    public:
    MultipleQuestionImageWidget(std::vector<QString>& q) {
        this->layout = new QGridLayout();
        this->create_widgets(q);
    }
    const MultipleQuestionImageWidget& get_widget() {
        return *this;
    }
    void create_widgets(std::vector<QString>&q) {
        for(unsigned int i = 0; i< q.size(); ++i) {
            QLabel* l = new QLabel(q[i]);
            layout->addWidget(l, i, 0);
            QCheckBox* box = new QCheckBox();
            layout->addWidget(box, i, 1);
        }
    }
};

#endif