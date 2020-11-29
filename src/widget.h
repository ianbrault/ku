#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

/*
** abstract QWidget subclass to support key registration and dispatch
*/
class Widget : public QWidget
{
    Q_OBJECT

public:
    virtual void onKeyEvent(QKeyEvent*) = 0;
};

#endif // WIDGET_H
