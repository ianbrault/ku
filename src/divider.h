#ifndef DIVIDER_H
#define DIVIDER_H

#include <QPen>
#include <QWidget>

class Divider : public QWidget
{
    Q_OBJECT

public:
    Divider(QWidget* parent = nullptr);
    ~Divider();

protected:
    // override QWidget events here
    void paintEvent(QPaintEvent*) override;

private:
    QPen m_pen;
};

#endif // DIVIDER_H
