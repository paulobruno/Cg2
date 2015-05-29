#include "FlatButton.h"

FlatButton::FlatButton(QWidget * parent)
    : QPushButton(parent)
{
    setFlat(true);
}

void FlatButton::leaveEvent(QEvent * e)
{
    setFlat(true);
    QPushButton::leaveEvent(e);
}

void FlatButton::enterEvent(QEvent * e)
{
    setFlat(false);
    QPushButton::enterEvent(e);
}
