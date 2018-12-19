#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <game.h>
#include <QTimer>
#include <QPainter>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public slots:
    void        moving();
    void        shooting();
    void        acting();

private:
    Ui::Widget  *ui;
    Game        *game;
    void        drawCell(int x, int y, Personage *p = nullptr);
    void        drawSurface();
    void        drawObjects();
    void        drawShoots();
    void        updBg(Personage *p);
    void        updShootBg(Personage *p);
    void        drawLolo();
    QTimer      *timer;

protected:
    void    paintEvent(QPaintEvent *);
    void    keyPressEvent(QKeyEvent *);
public:
    void        connectTimers();
    Game*       getGame();
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();


};

#endif // WIDGET_H
