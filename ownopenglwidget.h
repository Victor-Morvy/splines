#ifndef OWNOPENGLWIDGET_H
#define OWNOPENGLWIDGET_H

#include "misc.h"
#include <QApplication>
#include <QKeyEvent>
#include <QOpenGLWidget>

class OwnOpenglWidget : public QOpenGLWidget
{
public:
    OwnOpenglWidget(QWidget* parent);

    void drawLine(Vec2Node a, Vec2Node b, Vec4Node color = {0.5, 0.5, 0.5, 1});

    void initializeGL();

    void paintGL();


    void GL_Setup(int width, int height);

    void DrawCircle(float cx, float cy, float r, int num_segments, Vec4Node color  = {0.5, 0.5, 0.5, 1});


    float totalSize;

    SplineControl* pl;

    int selectedNode ;

    float viewPercent;

    void translate(float x, float y);
};

#endif // OWNOPENGLWIDGET_H
