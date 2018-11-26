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

private:
    Ui::Widget  *ui;
    Game        *game;
    void        drawCell(int x, int y, Personages *p = nullptr);
    void        drawSurface();
    void        drawObjects();
    void        drawShoots();
    void        updBg(Personages *p);
    void        updShootBg(Personages *p);
    void        drawLolo();
    QTimer      *timer;
protected:
    void    paintEvent(QPaintEvent *);
    void    keyPressEvent(QKeyEvent *);
public:
    explicit Widget(QWidget *parent = nullptr);
    Game    *getGame();
    ~Widget();


};

#endif // WIDGET_H
