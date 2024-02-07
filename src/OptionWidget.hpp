#ifndef _OPTION_WIDGET_HPP__
#define _OPTION_WIDGET_HPP__

#include <QWidget>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include "LangTranslation.hpp"

class OptionWidget : public QWidget
{
    Q_OBJECT

    QVBoxLayout *main_layout;
    QComboBox *lang_options;
    QPushButton *button_save;
    QLabel *options_info, *restart_info;

    const LangTranslation &translation;

public:
    OptionWidget(QMainWindow *, const LangTranslation &);
    ~OptionWidget();

private:
    auto create_widgets() -> void;
    auto create_layout() -> void;
    auto connect_actions() -> void;

private slots:
    auto save_options() -> void;
};

#endif