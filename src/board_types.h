#ifndef BOARD_TYPES_H
#define BOARD_TYPES_H

#include <Qt>
#include <QDebug>

enum InputMode
{
    Normal,
    Corner,
    Center,
};

enum Direction
{
    None,
    Up,
    Down,
    Left,
    Right,
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

#endif // BOARD_TYPES_H
