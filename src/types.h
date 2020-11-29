#ifndef TYPES_H
#define TYPES_H

#include <Qt>
#include <QDebug>

enum InputMode
{
    Normal,
    Corner,
    Center,
    InputModeMax,
};

inline QString inputModeToString(InputMode m)
{
    QString s;

    switch (m)
    {
    case InputMode::Normal:
        s = QString("Normal");
        break;
    case InputMode::Corner:
        s = QString("Corner");
        break;
    case InputMode::Center:
        s = QString("Center");
        break;
    default:
        // unreachable
        assert(0);
    }

    return s;
}

enum Direction
{
    None,
    Up,
    Down,
    Left,
    Right,
    DirectionMax,
};

inline Direction keyToDirection(int key)
{
    Direction dir;

    switch(key)
    {
    case Qt::Key_Up: case Qt::Key_K:
        dir = Up;
        break;
    case Qt::Key_Down: case Qt::Key_J:
        dir = Down;
        break;
    case Qt::Key_Left: case Qt::Key_H:
        dir = Left;
        break;
    case Qt::Key_Right: case Qt::Key_L:
        dir = Right;
        break;
    default:
        dir = None;
    };

    return dir;
}

#endif // TYPES_H
