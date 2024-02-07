#include "OptionWidget.hpp"
#include <QMainWindow>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QFile>

OptionWidget::OptionWidget(QMainWindow *parrent, const LangTranslation &t) : QWidget(parrent), translation(t)
{
    this->create_widgets();
    this->create_layout();
    this->connect_actions();
}

OptionWidget::~OptionWidget()
{
}

auto OptionWidget::create_widgets() -> void
{
    this->button_save = new QPushButton(this->translation.get_phrase("phrase_32"));
    this->lang_options = new QComboBox();
    this->options_info = new QLabel(this->translation.get_phrase("phrase_33"));
    this->restart_info = new QLabel(this->translation.get_phrase("phrase_34"));
    this->lang_options->addItem("en");
    this->lang_options->addItem("pl");
}

auto OptionWidget::create_layout() -> void
{
    this->main_layout = new QVBoxLayout(this);
    this->main_layout->addWidget(this->options_info);
    this->main_layout->addWidget(this->lang_options);
    this->main_layout->addWidget(this->button_save);
    this->setLayout(this->main_layout);
}

auto OptionWidget::connect_actions() -> void
{
    connect(this->button_save, SIGNAL(clicked()), this, SLOT(save_options()));
}

auto OptionWidget::save_options() -> void
{
    QFile options("./settings.json");

    if (options.open(QFile::ReadWrite))
    {
        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(options.readAll(), &error);
        QJsonObject obj = doc.object();
        obj["set_lang"] = this->lang_options->currentText();
        QJsonDocument result(obj);
        options.resize(0);
        options.write(result.toJson());
        options.close();
        this->main_layout->addWidget(this->restart_info);
        this->resize(this->main_layout->sizeHint());
    }
}