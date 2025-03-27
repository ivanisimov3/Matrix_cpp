#ifndef FIGURE_H
#define FIGURE_H

class Figure {
protected:
    int width, height;
    virtual void drawSelf() = 0;
    virtual bool isAlive() = 0;

public:
    virtual ~Figure() = default;
};



#endif //FIGURE_H