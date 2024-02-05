#include "MultipleQuestionImageWidget.hpp"

#include "MultipleQuestionWidget.hpp"
#include <memory>
#include <QLabel>

MultipleQuestionImageWidget::MultipleQuestionImageWidget(QString image_path):image(image_path)
{
    this->create_widgets();
}

MultipleQuestionImageWidget::~MultipleQuestionImageWidget()
{
}

auto MultipleQuestionImageWidget::add_title(const QString &t) -> void
{
    this->label_title->setText(tr("<b>%1</b>").arg(t));
}

auto MultipleQuestionImageWidget::add_question(const QString &q) -> void
{
    QCheckBox *answer;
    QLabel *question;
    question = new QLabel(q);
    question->setWordWrap(true);
    question->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    question->setStyleSheet(tr("QLabel { border: 1px solid #DDD; }"));
    answer = new QCheckBox(this);
    this->questions.push_back(std::make_pair(question, answer));
}

auto MultipleQuestionImageWidget::create_widgets() -> void
{
    this->button_next = new QPushButton("NASTĘPNE PYTANIE");
    this->label_title = new QLabel();
}

auto MultipleQuestionImageWidget::create_layout() -> void
{
    this->mainLayout = new QVBoxLayout();
    this->gridLayout = new QGridLayout();
    this->label_image = new QLabel();
    this->label_image->setPixmap(image.scaled(QSize(700, 500), Qt::KeepAspectRatio));
    this->gridLayout->addWidget(this->label_title, 0, 0);
    this->gridLayout->addWidget(this->label_image, 1, 0, Qt::AlignHCenter);
    unsigned int i = 2;
    for (auto q : this->questions)
    {
        q.first->setWordWrap(true);
        this->gridLayout->addWidget(q.first, i, 0);
        this->gridLayout->addWidget(q.second, i, 1);
        connect(q.second, SIGNAL(toggled(bool)), this, SLOT(setAnswer(bool)));
        this->answers.push_back("FALSE");
        ++i;
    }
    this->gridLayout->setAlignment(Qt::AlignCenter);
    this->mainLayout->addLayout(this->gridLayout);
    this->setLayout(this->mainLayout);
}

auto MultipleQuestionImageWidget::setAnswer(bool ch) -> void
{
    unsigned int i = 0;
    for (auto q : this->questions)
    {
        if (q.second->isChecked())
        {
            this->answers[i] = "TRUE";
        }
        else
        {
            this->answers[i] = "FALSE";
        }
        ++i;
    }
}

auto MultipleQuestionImageWidget::get_answers() -> std::vector<QString> &
{
    return this->answers;
}