#include "ownopenglwidget.h"
#include <QDebug>
#include <QtMath>
#include <QtCore>

OwnOpenglWidget::OwnOpenglWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    this->GL_Setup(800, 600);

    pl = new SplineControl();

    int totalLenght;

    std::vector<Vec2Node>* line = &pl->path.points;

    float multiVal = 0.025f;

    line->push_back({10 * multiVal, 41 * multiVal});
    line->push_back({20 * multiVal, 21 * multiVal});
    line->push_back({30 * multiVal, 41 * multiVal});

    line->push_back({60 * multiVal, 41 * multiVal});
    line->push_back({70 * multiVal, 21 * multiVal});
    line->push_back({80 * multiVal, 71 * multiVal});
//    line->push_back({90 * multiVal, 71 * multiVal});
//    line->push_back({100 * multiVal, 71 * multiVal});




    selectedNode = 1;

//    GL_Setup(300, 300);

    viewPercent = 0.2f;

//    for(int i = 0; i < line.size(); i++)
//    {
//        drawLine
//    }


}

void OwnOpenglWidget::GL_Setup(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_DEPTH_TEST);
    //gluPerspective(45, (float)width / height, .1, 100);
    glMatrixMode(GL_MODELVIEW);
}

void OwnOpenglWidget::translate(float x, float y)
{
    pl->path.points.at(selectedNode).x += x;
    pl->path.points.at(selectedNode).y += y;
}

void OwnOpenglWidget::drawLine(Vec2Node a, Vec2Node b, Vec4Node color)
{
    glBegin(GL_LINES);
    glColor3f(color.x, color.y, color.z);
    glVertex2f( a.x , a.y);
    glVertex2f( b.x, b.y);
    glLineWidth(3);
    glEnd();
}

void OwnOpenglWidget::DrawCircle(float cx, float cy, float r, int num_segments, Vec4Node color) {
    glBegin(GL_LINE_LOOP);

    glColor3f(color.x, color.y, color.z);
    for (int ii = 0; ii < num_segments; ii++)   {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle
        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component
        glVertex2f(x + cx, y + cy);//output vertex
    }
    glLineWidth(3);
    glEnd();
}

void OwnOpenglWidget::initializeGL()
{
    glClearColor(1, 1, 1, 1);
}

void OwnOpenglWidget::paintGL()
{

    totalSize = 0;
//    drawLine({-0.5, 0}, {0.5, 0.5});

    qDebug() << "\n///////////////////////" ;

    float size = (float)pl->path.points.size();
    for(float t = 0; t < size - 0.01; t += 0.01f)
    {
        Vec2Node pos;
        Vec2Node pos1;
        if(t >= size)
        {
            pos1 = pl->path.GetSplinePoint(0, true);
            pos = pl->path.GetSplinePoint(size, true);
        }
        else
        {
            pos1 = pl->path.GetSplinePoint(t + 0.01f, true);
            pos = pl->path.GetSplinePoint(t, true);
        }


        pos.x *= viewPercent;
        pos.y *= viewPercent;

        pos1.x *= viewPercent;
        pos1.y *= viewPercent;



        drawLine(pos, pos1);

    }



    for(int t = 0; t < pl->path.points.size(); t++)
    {


        Vec2Node pos = pl->path.GetSplinePoint(t, true);
        qDebug() << " {{" <<  pos.x << "}, {" << pos.y << "}} " ;

        pos.x *= viewPercent;
        pos.y *= viewPercent;

        if(selectedNode == t)
        {
            DrawCircle(pos.x, pos.y, 0.01f, 16, {1, 0, 0, 1});
        }
        else
            DrawCircle(pos.x, pos.y, 0.005f, 8);
    }

//    for (float t = 0; t < 1; t+= 0.01f)
//    {

//        Vec2Node pos = pl->path.GetSplineGradient(t, false);


//        pos.x *= viewPercent;
//        pos.y *= viewPercent;
//        if(1 == t)
//        {
//            DrawCircle(pos.x, pos.y, 0.01f, 16, {1, 0, 0, 1});
//        }
//        else
//            DrawCircle(pos.x, pos.y, 0.005f, 8);

//    }
//    GL_Setup(300, 300);

}



