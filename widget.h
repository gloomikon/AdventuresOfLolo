#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <game.h>
#include <QTimer>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    QRect   rectLolo;
    explicit Widget(QWidget *parent = nullptr);
    unsigned int    steps = 0;
    unsigned int    direction = 6;
    QTimer          *timer;
    ~Widget();
public slots:
    void        ex_code();
private:
    Ui::Widget  *ui;
    Game        *game;
    std::string imgLolo = "lolo";
    void        drawSurface();
    void        drawObjects();
    void        drawLolo(std::string image);
protected:
    void    paintEvent(QPaintEvent *);
    void    keyPressEvent(QKeyEvent *);

};

#endif // WIDGET_H
