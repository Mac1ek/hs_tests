#include "LangTranslation.hpp"
#include <QFile>
#include <QObject>
#include <QJsonArray>
#include <QJsonDocument>

LangTranslation::LangTranslation(const QString l = QString("pl"))
{
    this->lang = l;
    QFile file(QObject::tr(":/settings/lang.json"));
    if (file.open(QFile::ReadOnly))
    {

        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &error);
        this->lang_phrases = doc.object();
    }
}

LangTranslation::~LangTranslation()
{
}

auto LangTranslation::get_phrase(const QString phrase) const -> const QString
{
    int i = 0;
    for (QJsonValueRef value : this->lang_phrases[this->lang].toArray())
    {
        if (value.toObject().keys()[0] == phrase)
        {
            return value.toObject()[phrase].toString();
        }
    }
    return QObject::tr("__UNKNOWN__PHRASE__ %1").arg(phrase);
}

auto LangTranslation::set_lang(const QString &l) -> void
{
    this->lang = l;
}