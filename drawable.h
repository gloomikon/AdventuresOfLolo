#ifndef DRAWABLE_H
#define DRAWABLE_H
class Widget;

class Drawable //Interface
{
public:
    Drawable();
    virtual void drawSelf(Widget *w);
    //virtual ~Drawable();
};

#endif // DRAWABLE_H
