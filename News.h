#ifndef NEWS_H
#define NEWS_H

#include <QString>
#include <QDate>

class News
{
public:
    News();
    News(const QString& text,
         const QString& title = QString{},
         const QDate& date = QDate{});
    
    const QString& getTitle() const;
    const QString& getText () const;
    const QDate&   getDate () const;
    
private:
    QString m_title;
    QString m_text;
    QDate   m_date;
};

#endif // NEWS_H
