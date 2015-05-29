#ifndef RESPONSIVEMENU_H
#define RESPONSIVEMENU_H


#include <QMenu>
#include <QEvent>


class ResponsiveMenu : public QMenu
{
    public:

        ResponsiveMenu(QWidget * parent = 0);


    protected:

        void enterEvent(QEvent *e);
        void leaveEvent(QEvent *e);
};

#endif // RESPONSIVEMENU_H
