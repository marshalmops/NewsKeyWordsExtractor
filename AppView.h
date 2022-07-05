#ifndef APPVIEW_H
#define APPVIEW_H

#include <QWidget>

class AppView : public QWidget
{
    Q_OBJECT
    
public:
    AppView(QWidget *parent = nullptr);
    ~AppView();
};
#endif // APPVIEW_H
