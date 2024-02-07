#ifndef _LANG_TRANSLATION_HPP__
#define _LANG_TRANSLATION_HPP__

#include <QString>
#include <QJsonObject>

class LangTranslation
{
    QJsonObject lang_phrases;
    QString lang;

public:
    LangTranslation(const QString);
    ~LangTranslation();
    auto get_phrase(const QString) const -> const QString;
    auto set_lang(const QString &) -> void;
};

#endif