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
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

     QTimer          *timer;
public slots:
    void        ex_code();
private:
    Ui::Widget  *ui;
    Game        *game;
    void        drawSurface();
    void        drawObjects();
    void        updBg(Personages *p);
    void        drawLolo();
protected:
    void    paintEvent(QPaintEvent *);
    void    keyPressEvent(QKeyEvent *);

};

#endif // WIDGET_H
