#include "MultipleQuestionWidget.hpp"
#include <memory>
#include <QLabel>

MultipleQuestionWidget::MultipleQuestionWidget() : QuestionWidget()
{
    this->mainLayout.reset(new QGridLayout(this));
}

MultipleQuestionWidget::~MultipleQuestionWidget()
{
}

void MultipleQuestionWidget::add_question(const QString &q)
{
    std::shared_ptr<QCheckBox> answer;
    std::shared_ptr<QLabel> question;
    question.reset(new QLabel(q));
    question->setWordWrap(true);
    question->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    question->setStyleSheet(tr("QLabel { border: 1px solid #DDD; }"));
    answer.reset(new QCheckBox(this));
    this->questions.push_back(std::make_pair(question, answer));
}

void MultipleQuestionWidget::create_layout()
{
    unsigned int i = 0;
    for (auto q : this->questions)
    {
        this->mainLayout->addWidget(q.first.get(), i, 0);
        this->mainLayout->addWidget(q.second.get(), i, 1);
        ++i;
    }
    this->mainLayout->setAlignment(Qt::AlignCenter);
    this->setLayout(this->mainLayout.get());
}