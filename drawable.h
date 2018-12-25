#ifndef DRAWABLE_H
#define DRAWABLE_H
class Widget;

class Drawable //Interface
{
public:
    virtual void drawSelf(Widget *w) = 0;
    virtual ~Drawable() = 0;
};

#endif // DRAWABLE_H
