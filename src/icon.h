#ifndef ICON_H
#define ICON_H

#include <QLabel>

class Icon : public QLabel
{
    Q_OBJECT

public:
    Icon(QString icon_path, int icon_size, QWidget* parent = nullptr);
    ~Icon();
};

#endif // ICON_H
