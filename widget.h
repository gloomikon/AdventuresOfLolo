#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <game.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    QRect   rectLolo;
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget  *ui;
    Game        *game;
    void        drawSurface();
    void        drawObjects();
    void        drawLolo();
protected:
    void    paintEvent(QPaintEvent *);
    void    keyPressEvent(QKeyEvent *);

};

#endif // WIDGET_H
