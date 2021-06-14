#include "misc.h"

Misc::Misc()
{

}


Vec2Node Misc::Lerp2d(Vec2Node a, Vec2Node b, float t)
{
    if(t > 1)
        t = 1;
    else if (t < 0)
        t = 0;

    Vec2Node tmp = {b.x - a.x, b.y - a.y};
    tmp.x *= t;
    tmp.y *= t;

    return {tmp.x+a.x, tmp.y+a.y};

}

Vec2Node Misc::Quadratic2d(Vec2Node a, Vec2Node b, Vec2Node c, float t)
{
    Vec2Node tmp = {powf((1.0f-t), 2.0f) * a.x + 2.0f*(1.0f-t)*t*b.x + powf(t,2)*c.x,
                   powf((1-t),2) * a.y + 2*(1-t)*t*b.y + powf(t,2)*c.y};
    return tmp;
}

Vec2Node Misc::Cubic2d(Vec2Node a, Vec2Node b, Vec2Node c, Vec2Node d, float t)
{
    Vec2Node tmp = {powf((1-t), 3)*a.x+3*(powf((1-t), 2))*t*b.x+3*(1-t)*(powf(t,2))*b.x + (powf(t, 3))*d.x,
                   (powf((1-t), 3)*a.y+3*(powf((1-t), 2))*t*b.y+3*(1-t)*(powf(t,2))*b.y + (powf(t, 3))*d.y)};
    return tmp;
}
