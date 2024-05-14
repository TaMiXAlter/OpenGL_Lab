#include "freeglut_std.h"
#include <GL/gl.h>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

int WindowWidth = 500;
int WindowHeight = 500;

void ChangeSize(int , int );
void RenderScene(void);
void MouseFunction(int button,int state,int x,int y);
void KeyBoardInput(unsigned char KeyCode, int x, int y );
void TimerFunc(int value);
void CreatMenu();
struct Vector3{
    float x;
    float y;
    float z;
};
struct Vector2{
    Vector2() = default;
    Vector2(float x_, float y_) : x(x_), y(y_) {}
    float x;
    float y;
};

float dimentions = 15;
float GridLenth;
float Edge = 9;
void DrawPixel(float x,float y,float r,float g,float b);
int GetCoordinate(float V0x,float V0y,float V1x,float V1y);
std::vector<Vector2> Points;
/**Fill Space (Half Space)*/
float CrossProduct(const Vector2& a, const Vector2& b) {
    /**if positive -> Clock wise
     *    negative -> Counter clock wise
     *    (for vector B to vector A)*/
    return a.x * b.y - a.y * b.x;
}

//lab9
std::vector<Vector2> FillArray;
int DrawAmount = 1;
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(WindowWidth,WindowHeight);
    glutInitWindowPosition(600,80);
    glutCreateWindow("Gird");

    CreatMenu();
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    glutMouseFunc(MouseFunction);
    glutKeyboardFunc(KeyBoardInput);
    glutTimerFunc(100, TimerFunc,1);
    glutMainLoop();
    return 0;
}

void ChangeSize(int w, int h)
{
    printf("Window Size= %d X %d\n",w,h);
    glViewport(0, 0, w, h);
    WindowWidth = w;
    WindowHeight = h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10,10,-10,10,-10,20);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void RenderScene(void)
{
// Set up first viewport
    glClearColor(0, 0, 0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 10.0, 0, 0, 0, 0, 1, 0);


    glViewport(0, 0, WindowWidth, WindowHeight);

    /**Draw Grid*/
    GridLenth = Edge/dimentions;
    for (float i = -dimentions*GridLenth; i <= dimentions*GridLenth+GridLenth/2; i += GridLenth) {
        glBegin(GL_LINES);
        glColor3f(1,1,1);
        glVertex3f(-dimentions*GridLenth,i,1);
        glVertex3f(dimentions*GridLenth,i,1);
        glVertex3f(i,dimentions*GridLenth,1);
        glVertex3f(i,-dimentions*GridLenth,1);
        glEnd();
    }


    /**Fill with Half Space*/
    if(Points.size()>2){
        float Xmin = std::min_element(Points.begin(), Points.end(), [](const Vector2& a, const Vector2& b) { return a.x < b.x; })->x;
        float Xmax = std::max_element(Points.begin(), Points.end(), [](const Vector2& a, const Vector2& b) { return a.x < b.x; })->x;
        float Ymin = std::min_element(Points.begin(), Points.end(), [](const Vector2& a, const Vector2& b) { return a.y < b.y; })->y;
        float Ymax = std::max_element(Points.begin(), Points.end(), [](const Vector2& a, const Vector2& b) { return a.y < b.y; })->y;

        for (float y = Ymin; y <= Ymax; y++)
        {
            for (float x = Xmin; x <= Xmax; ++x)
            {
                Vector2 p(x, y);
                int winding_number = 0;
                /**counting the number of the point if it is in Right side or Left side with Cross Product(叉積)*/
                for (int i = 0; i < Points.size(); i++)
                {
                    int j = (i + 1) % Points.size();
                    Vector2 a = Points[i];
                    Vector2 b = Points[j];
                    if (CrossProduct(Vector2(b.x - a.x, b.y - a.y), Vector2(p.x - a.x, p.y - a.y)) >= 0)
                        winding_number++;
                    else
                        winding_number--;
                }
                /**for ccw || cw */
                if (std::abs(winding_number) == Points.size())
                {
                    FillArray.emplace_back(x,y);
                }
            }
        }



        for (int i = 0; i < DrawAmount; ++i) {
            DrawPixel(FillArray[i].x,FillArray[i].y,1,1,1);
        }
        DrawAmount++;
    }

    /**Draw Line*/
    if(Points.size()>1){
        for (int i = 0; i < Points.size(); ++i) {
            /**get point*/
            Vector2 Vertex0,Vertex1;
            if(i == Points.size()-1){
                Vertex0 = Points[i];
                Vertex1 = Points[0];
            }else{
                Vertex0 = Points[i];
                Vertex1 = Points[i+1];
            }
            /**Draw*/
            int dx = std::abs(Vertex1.x - Vertex0.x);
            int dy = std::abs(Vertex1.y - Vertex0.y);

            int x = Vertex0.x;
            int y = Vertex0.y;
            int d = 2 * dy - dx;
            int delE = 2 * dy;
            int delNE = 2 * (dy - dx);

            int xIncrement = (Vertex1.x > Vertex0.x) ? 1 : -1;
            int yIncrement = (Vertex1.y > Vertex0.y) ? 1 : -1;

            if (dx >= dy) {
                while (x != Vertex1.x) {
                    if (d <= 0) {
                        d += delE;
                        x += xIncrement;
                        DrawPixel(x, y, 0, 1, 0); // Green for E point
                    } else {
                        d += delNE;
                        x += xIncrement;
                        y += yIncrement;
                        DrawPixel(x, y, 0, 0, 1); // Blue for NE point
                    }
                }
            } else {
                d = 2 * dx - dy; // Use d based on dy
                while (y != Vertex1.y) {
                    if (d <= 0) {
                        d += 2 * dx;
                        y += yIncrement;
                        DrawPixel(x, y, 0, 0, 1); // Blue for N point
                    } else {
                        d += 2 * (dx - dy);
                        x += xIncrement;
                        y += yIncrement;
                        DrawPixel(x, y, 0, 1, 0); // Green for E point
                    }
                }
            }



        }
    }
    /**Draw Point*/
    if(!Points.empty()){
        for (int i = 0; i < Points.size(); ++i) {
            if(Points[i].x<=dimentions && Points[i].x>-dimentions && Points[i].y<=dimentions && Points[i].y >-dimentions){
                //畫出來
                DrawPixel(Points[i].x,Points[i].y,1,0,0);
            }
        }
    }

    glutSwapBuffers();
}
int GetCoordinate(float V0x,float V0y,float V1x,float V1y){
    /**get coordinate
 *  1. v1.x > v0.x && v1.y > v0.y && 0<m<1
 *  2. v1.x > v0.x && v1.y > v0.y && m>1
 *  3. v1.x < v0.x && v1.y > v0.y && m<-1
 *  4. v1.x < v0.x && v1.y > v0.y && -1<m<0
 *  5. v1.x < v0.x  && v1.y < v0.y && m<1
 *  6. v1.x < v0.x && v1.y < v0.y && m>1
 *  7. v1.x > v0.x  && v1.y < v0.y && m<-1
 *  8. v1.x > v0.x  && v1.y < v0.y && 0>m>-1*/
    int coordinate = 0;
    bool isV1xLarger = V1x > V0x;
    bool isV1yLarger = V1y> V0y;
    float m = (V1y-V0y)/(V1x-V0x);
    if(isV1xLarger){
        if(isV1yLarger){
            if(m<=1)coordinate = 1;
            if(m>1) coordinate = 2;
        }else{
            if(m<=-1) coordinate = 7;
            if(m>-1) coordinate = 8;
        }
    }else{
        if(isV1yLarger){
            if(m<=-1) coordinate = 3;
            if(m>-1) coordinate = 4;
        } else{
            if(m<=1) coordinate = 5;
            if(m>1) coordinate = 6;
        }
    }
    return coordinate;
}
void DrawPixel(float x,float y,float r,float g,float b){
    glBegin(GL_QUADS);
    glColor3f(r,g,b);
    glVertex3f(GridLenth*x,GridLenth*y,1);
    glVertex3f(GridLenth*x,GridLenth*(y-1),1);
    glVertex3f(GridLenth*(x-1),GridLenth*(y-1),1);
    glVertex3f(GridLenth*(x-1),GridLenth*y,1);
    glEnd();
}
void TimerFunc(int value){
    glutPostRedisplay();
    glutTimerFunc(50, TimerFunc, 1);
}

void MouseFunction(int button, int state, int x, int y) {
    int Px,Py;
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        //計算方格位置
        float NDCx = (2.f*x/WindowWidth)-1;
        float NDCy = (-2.f*y/WindowHeight)+1;
        Px = ceil((NDCx*10)/GridLenth) ;
        Py = ceil((NDCy*10)/GridLenth);
        Points.push_back(Vector2(Px,Py));
        std::cout<<Px << " "<< Py<< std::endl;
        if(Points.size() >1){
            std::cout<<"Coordinate: " << GetCoordinate(Points[Points.size()-2].x,Points[Points.size()-2].y,Px,Py)<< std::endl;
        }
    }
}
void KeyBoardInput(unsigned char KeyCode, int x, int y ){
    switch (KeyCode) {
        case 'r':
            Points.clear();
            FillArray.clear();
            DrawAmount=1;
            break;
    }
}
void DimentionMenu(int value){
    switch (value) {
        case 0:
            dimentions = 10;
            break;
        case 1:
            dimentions = 15;
            break;
        case 2:
            dimentions = 20;
            break;
    }
}
void CreatMenu(){
    int DimentionSelect = glutCreateMenu(DimentionMenu);
    glutAddMenuEntry("10",0);
    glutAddMenuEntry("15",1);
    glutAddMenuEntry("20",2);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}