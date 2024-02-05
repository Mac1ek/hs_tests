#include "TestWidget.hpp"

TestWidget::TestWidget(QTimer *timer) : testTimer(timer)
{
    this->create_widgets();
    this->connect_widgets();
    this->create_layouts();
}

TestWidget::~TestWidget()
{
}

auto TestWidget::create_widgets() -> void
{

    QPixmap pixmap(tr(":/images/logo.png"));
    this->label_logo = new QLabel();
    this->label_logo->setPixmap(pixmap);
    this->central_widget = new QWidget();
    this->main_btn = new QPushButton("Rozpocznij test");
    this->next_btn = new QPushButton("NASTĘPNE PYTANIE");
    this->widgetsStack = new QStackedWidget();
    this->summary_question_success = new QLabel();
    this->summary_question_success->setStyleSheet(tr("QLabel { color: #1D1; text-weight: bold; background: rgb(100, 100, 100); )}"));
    this->summary_question_success->setWordWrap(true);
}

auto TestWidget::create_layouts() -> void
{

    this->start_layout = new QGridLayout();
    this->main_layout = new QVBoxLayout();
}

auto TestWidget::createStartPage(const QString title, const QString t) -> void
{
    this->title = new QLabel(tr("<b>%1</b>").arg(title));
    this->time = new QLabel(tr("<b>CZAS TESTU</b>: %1 <b>MINUT</b>").arg(t.toUInt()));
    this->start_layout->addWidget(this->label_logo, 0, 0, Qt::AlignHCenter);
    this->start_layout->addWidget(this->title, 1, 0, Qt::AlignTop | Qt::AlignHCenter);
    this->start_layout->addWidget(this->time, 2, 0, Qt::AlignTop | Qt::AlignHCenter);
    this->start_layout->addWidget(this->main_btn, 3, 0, Qt::AlignTop | Qt::AlignHCenter);

    this->central_widget->setLayout(this->start_layout);

    this->widgetsStack->addWidget(this->central_widget);
    this->main_layout->addWidget(this->widgetsStack);

    this->setLayout(this->main_layout);
}

auto TestWidget::connect_widgets() -> void
{
    this->connect(this->next_btn, SIGNAL(clicked()), this, SLOT(nextQuestion()));
    this->connect(this->main_btn, SIGNAL(clicked()), this, SLOT(nextQuestion()));
}

auto TestWidget::start() -> void
{
    this->main_layout->addWidget(this->widgetsStack);
    this->main_layout->addWidget(this->next_btn);
    this->main_layout->addStretch(1);
}

auto TestWidget::add_questionBlock(QuestionWidget *w) -> void
{
    this->widgetsStack->addWidget(w);
}

auto TestWidget::nextQuestion() -> void
{
    if (this->widgetsStack->currentIndex() > 0)
    {
        static_cast<QuestionWidget *>(widgetsStack->widget(this->widgetsStack->currentIndex()))->get_answers();
        this->add_answers(static_cast<QuestionWidget *>(widgetsStack->widget(this->widgetsStack->currentIndex()))->get_answers());
    }
    if (this->widgetsStack->currentIndex() == (this->widgetsStack->count() - 1))
    {
        this->addSumaryWindow();
        this->widgetsStack->setCurrentIndex(this->widgetsStack->currentIndex() + 1);
        this->next_btn->hide();
    }
    if (!this->testTimer->isActive())
        this->testTimer->start(1000);
    this->widgetsStack->setCurrentIndex(this->widgetsStack->currentIndex() + 1);
    if (this->widgetsStack->currentIndex() > 0)
    {
        this->main_layout->addWidget(this->next_btn);
    }
}

auto TestWidget::addSumaryWindow() -> void
{
    this->summary_widget = new QWidget();
    this->summary_layout = new QGridLayout();
    this->summary_img_label = new QLabel();
    this->summary_test_info = new QLabel();
    QPixmap pixmap(tr(":/images/logo.png"));
    this->summary_img_label->setPixmap(pixmap);

    unsigned int i = 0, correct = 0, fail = 0, questions_num = 0, correct_summary = 0;
    for (std::vector<std::pair<QString, QString>> answers_block : this->answers)
    {
        for (std::pair<QString, QString> answer : answers_block)
        {
            if (answer.first == "TRUE" && answer.second == "FALSE")
            {
                ++fail;
            }
            else if (answer.first == "TRUE" && answer.second == "TRUE")
            {
                ++correct;
            }
            if (answer.second == "TRUE")
            {
                ++correct_summary;
            }
            ++questions_num;
        }
    }
    double a = correct;
    double b = correct_summary;
    double summary_result = (a / b) * 100.0;
    this->summary_layout->addWidget(this->summary_img_label, 0, 0, Qt::AlignHCenter);
    this->summary_test_info->setText(tr("ILOŚĆ PYTAŃ: %1, ILOŚĆ POPRAWNYCH ODPOWIEDZI <b>%2</b>, ILOŚĆ NIEPOPRAWNYCH ODPOWIEDZI; <b>%3</b>").arg(questions_num).arg(correct).arg(fail));
    this->summary_question_success->setText(tr("W TEŚCIE ZNAJDOWAŁO SIĘ <b>%1</b> POPRAWNYCH ODPOWIEDZI, ODPOWIEDZIAŁEŚ NA <b>%2</b> PROCENT POPRAWNYCH ODPOWIEDZI (POPRAWNIE)").arg(correct_summary).arg(summary_result));
    this->summary_layout->addWidget(this->summary_test_info, 1, 0, Qt::AlignTop | Qt::AlignHCenter);
    this->summary_layout->addWidget(summary_question_success, 2, 0, Qt::AlignTop | Qt::AlignHCenter);

    this->summary_widget->setLayout(this->summary_layout);
    this->widgetsStack->addWidget(this->summary_widget);
}

auto TestWidget::add_answers(std::vector<QString> &a) -> void
{
    unsigned int i = 0;
    for (std::pair<QString, QString> &answer : this->answers[this->widgetsStack->currentIndex() - 1])
    {
        answer.first = a[i];
        ++i;
    }
}

auto TestWidget::store_answers(std::vector<std::pair<QString, QString>> &a) -> void
{
    this->answers.push_back(a);
}

auto TestWidget::reset_test() -> void
{
    this->widgetsStack->setCurrentIndex(0);
}

auto TestWidget::test_end_now() -> void
{
    this->addSumaryWindow();
    this->widgetsStack->setCurrentIndex(this->widgetsStack->count() - 1);
    this->next_btn->hide();
}