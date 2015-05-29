#include "ResponsiveMenu.h"

ResponsiveMenu::ResponsiveMenu(QWidget * parent)
    : QMenu(parent)
{
}

void ResponsiveMenu::leaveEvent(QEvent * e)
{
    setStyleSheet("background-color: white;color: black;");
    QMenu::leaveEvent(e);
}

void ResponsiveMenu::enterEvent(QEvent * e)
{
    setStyleSheet("background-color: grey;color: white;");
    QMenu::enterEvent(e);
}
