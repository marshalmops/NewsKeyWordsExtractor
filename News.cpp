#include "News.h"


News::News()
    : m_title{},
      m_text{},
      m_date{}
{
    
}

News::News(const QString &text, 
           const QString &title, 
           const QDate &date)
    : m_title{title},
      m_text{text},
      m_date{date}
{
    
}

const QString &News::getTitle() const
{
    return m_title;
}

const QString &News::getText() const
{
    return m_text;
}

const QDate &News::getDate() const
{
    return m_date;
}
