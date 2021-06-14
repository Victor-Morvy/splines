#ifndef MISC_H
#define MISC_H

#include <vector>
#include <iostream>
#include <math.h>



struct Vec4Node
{
    float x, y, z, w;
};

struct Vec2Node
{
    float x;
    float y;

    float lenght;
};

struct sSpline
{
    std::vector<Vec2Node> points;

    Vec2Node GetSplinePoint(float t, bool bLooped = false)
    {
        int p0, p1, p2, p3;

        if(!bLooped)
        {
            p1 = (int)t + 1;
            p2 = p1 + 1;
            p3 = p2 + 1;
            p0 = p1 - 1;
        }
        else
        {
            p1 = (int)t;
            p2 = (p1 + 1) % points.size();
            p3 = (p2 + 1) % points.size();
            p0 = p1 >= 1 ? p1 - 1: points.size() - 1;
        }
        t = t - (int)t;


        float tt = t*t;
        float ttt = tt * t;

        float q1 = -ttt + 2.0f * tt - t;
        float q2 = 3.0f*ttt - 5.0f*tt+2.0f;
        float q3 = -3.0f*ttt + 4.0f*tt + t;
        float q4 = ttt - tt;

        float tx = points[p0].x * q1 + points[p1].x * q2 + points[p2].x * q3 + points[p3].x * q4;

        float ty = points[p0].y * q1 + points[p1].y * q2 + points[p2].y * q3 + points[p3].y * q4;

        return {tx, ty};
    }

    Vec2Node GetSplineGradient(float t, bool bLooped = false)
    {
        int p0, p1, p2, p3;

        if(!bLooped)
        {
            p1 = (int)t + 1;
            p2 = p1 + 1;
            p3 = p2 + 1;
            p0 = p1 - 1;
        }
        else
        {
            p1 = (int)t;
            p2 = (p1 + 1) % points.size();
            p3 = (p2 + 1) % points.size();
            p0 = p1 >= 1 ? p1 - 1: points.size() - 1;
        }
        t = t - (int)t;


        float tt = t*t;
        float ttt = tt * t;

        float q1 = -3.0f * tt + 4.0f * t - 1;
        float q2 = 9.0f*tt - 10.0f * t;
        float q3 = -9.0f*tt + 8.0 * t + 1.0f;
        float q4 = 3.0f*tt - 2.0f*t;

        float tx = points[p0].x * q1 + points[p1].x * q2 + points[p2].x * q3 + points[p3].x * q4;

        float ty = points[p0].y * q1 + points[p1].y * q2 + points[p2].y * q3 + points[p3].y * q4;

        return {tx, ty};
    }

    float GetAngle(float t)
    {
        Vec2Node p1 = GetSplinePoint(t);
        Vec2Node v = GetSplineGradient(t);
        float r = atan2(-v.y, v.x);
        return r;
    }

    float getSizeAt(int index, int precision = 16)
    {
        float lineSize = 0;

        Vec2Node p1 = points.at(index);
        Vec2Node p2 = points.at(index+1);

//        stance(vetorial.x, vetorial.y);

//        float size = (float)points.size();
        float size = precision;
        for(float t = (float)index; t < t+1.0f; t += 1.0f/precision)
        {
            Vec2Node pos;
            Vec2Node pos1;
//            if(t >= size)
//            {
//                pos1 = GetSplinePoint(0, true);
//                pos = GetSplinePoint(size, true);
//            }
//            else
            {
                pos1 = GetSplinePoint(t + 0.01f, true);
                pos = GetSplinePoint(t, true);
            }

            Vec2Node vetorial = {pos.x - pos1.x, pos.y - pos1.y};

            lineSize += sqrt(pow(vetorial.x, 2) + pow(vetorial.y, 2));


        }

        return lineSize;
    }

    float GetTotalSize()
    {

    }
};

class SplineControl
{
public:

    SplineControl(std::vector<Vec2Node>* p)
    {
        path.points = *p;
    }


    SplineControl(){}

    sSpline path;

};

class Misc
{
public:
    Misc();


    Vec2Node Lerp2d(Vec2Node a, Vec2Node b, float t);
    Vec2Node Quadratic2d(Vec2Node a, Vec2Node b, Vec2Node c, float t);
    Vec2Node Cubic2d(Vec2Node a, Vec2Node b, Vec2Node c, Vec2Node d, float t);
};

#endif // MISC_H
