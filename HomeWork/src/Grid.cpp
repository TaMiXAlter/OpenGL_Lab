#include "freeglut_std.h"
#include <GL/gl.h>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <algorithm>
int WindowWidth = 500;
int WindowHeight = 500;
struct Vector2{
    Vector2() = default;
    Vector2(float x_, float y_) : x(x_), y(y_) {}
    float x;
    float y;
};
struct Vertex{
    Vertex() = default;
    Vertex(float _x,float _y,float _r,float _g , float _b):x(_x), y(_y),r(_r),g(_g),b(_b){}
    Vertex(const Vertex& other) : x(other.x), y(other.y), r(other.r), g(other.g), b(other.b) {}
    Vertex& operator=(const Vertex& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
            r = other.r;
            g = other.g;
            b = other.b;
        }
        return *this;
    }
    bool operator==(const Vertex& other) const {
        return x == other.x && y == other.y && r == other.r && g == other.g && b == other.b;
    }

    bool operator!=(const Vertex& other) const {
        return !(*this == other);
    }
    float x,y,r,g,b;
};
struct ActiveEdge {
    float yMax;       // yMax
    float xIntersect;  // xNow
    float dxPerScan;   // DeltaX
    Vertex v1, v2;     //start point and end point
};

void ChangeSize(int , int );
void RenderScene(void);
void MouseFunction(int button,int state,int x,int y);
void KeyBoardInput(unsigned char KeyCode, int x, int y );
void TimerFunc(int value);
void CreatMenu();

float dimentions = 15;
float GridLenth;
float EdgeDistence = 9;
void DrawPixel(float x,float y,float r,float g,float b);
int GetCoordinate(float V0x,float V0y,float V1x,float V1y);
//std::vector<Vector2> Points;
/**Fill Space (Half Space)*/
float CrossProduct(const Vector2& a, const Vector2& b) {
    /**if positive -> Clock wise
     *    negative -> Counter clock wise
     *    (for vector B to vector A)*/
    return a.x * b.y - a.y * b.x;
}
void HalfSpace();
void DrawLine();
void Craws();
//lab9 Animation
std::vector<Vector2> FillArray;
int DrawAmount = 1;
/**Lab 10 Crow's*/
std::vector<Vertex> Points;
int main(int argc, char** argv)
{
    //for Random
    srand (static_cast <unsigned> (time(0)));

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
    GridLenth = EdgeDistence / dimentions;
    for (float i = -dimentions*GridLenth; i <= dimentions*GridLenth+GridLenth/2; i += GridLenth) {
        glBegin(GL_LINES);
        glColor3f(1,1,1);
        glVertex3f(-dimentions*GridLenth,i,1);
        glVertex3f(dimentions*GridLenth,i,1);
        glVertex3f(i,dimentions*GridLenth,1);
        glVertex3f(i,-dimentions*GridLenth,1);
        glEnd();
    }


    /**Fill */
    if(Points.size()>2){
        Craws();
    }

//    /**Draw Line*/
//    if(Points.size()==2){
//        DrawLine();
//    }
//    /**Draw Point*/
//    if(!Points.empty()){
//        for (int i = 0; i < Points.size(); ++i) {
//            if(Points[i].x<=dimentions && Points[i].x>-dimentions && Points[i].y<=dimentions && Points[i].y >-dimentions){
//                //畫出來
//                DrawPixel(Points[i].x,Points[i].y,Points[i].r,Points[i].g,Points[i].b);
//            }
//        }
//    }

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
    glutTimerFunc(100, TimerFunc, 1);
}

void MouseFunction(int button, int state, int x, int y) {
    int Px,Py;
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        //計算方格位置
        float NDCx = (2.f*x/WindowWidth)-1;
        float NDCy = (-2.f*y/WindowHeight)+1;
        Px = ceil((NDCx*10)/GridLenth) ;
        Py = ceil((NDCy*10)/GridLenth);
        // Random Color
        float Rr = (float)(rand()) / (float)(RAND_MAX);
        float Rg = (float)(rand()) / (float)(RAND_MAX);
        float Rb = (float)(rand()) / (float)(RAND_MAX);
        Points.push_back(Vertex(Px,Py,Rr,Rg,Rb));
        // show value
        std::cout<<Px << " "<< Py<< std::endl;
        if(Points.size() >1){
            std::cout<<"Coordinate: " << GetCoordinate(Points[Points.size()-2].x,Points[Points.size()-2].y,Px,Py)<< std::endl;
        }
      

    }
}
void KeyBoardInput(unsigned char KeyCode, int x, int y ){
    switch (KeyCode) {
        case 'r':
            //for Random
            srand (static_cast <unsigned> (time(0)));

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
void HalfSpace(){
    float Xmin = std::min_element(Points.begin(), Points.end(), [](const Vertex& a, const Vertex& b) { return a.x < b.x; })->x;
    float Xmax = std::max_element(Points.begin(), Points.end(), [](const Vertex& a, const Vertex& b) { return a.x < b.x; })->x;
    float Ymin = std::min_element(Points.begin(), Points.end(), [](const Vertex& a, const Vertex& b) { return a.y < b.y; })->y;
    float Ymax = std::max_element(Points.begin(), Points.end(), [](const Vertex& a, const Vertex& b) { return a.y < b.y; })->y;

    for (float y = Ymin+1; y <Ymax; y++)
    {
        for (float x = Xmin+1; x <Xmax; x++)
        {
            Vector2 p(x, y);
            int winding_number = 0;
            /**counting the number of the point if it is in Right side or Left side with Cross Product(叉積)*/
            for (int i = 0; i < Points.size(); i++)
            {
                int j = (i + 1) % Points.size();
                Vertex a = Points[i];
                Vertex b = Points[j];
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
void DrawLine(){
    for (int i = 0; i < Points.size(); ++i) {
        /**get point*/
        Vertex Vertex0,Vertex1;

        Vertex0 = Points[i];
        Vertex1 = Points[(i+1)%Points.size()];

        /**Draw*/
        int dx = std::abs(Vertex1.x - Vertex0.x);
        int dy = std::abs(Vertex1.y - Vertex0.y);

        int x = Vertex0.x;
        int y = Vertex0.y;
        int d;
        int delE = 2 * dy;
        int delNE = 2 * (dy - dx);

        int xIncrement = (Vertex1.x > Vertex0.x) ? 1 : -1;
        int yIncrement = (Vertex1.y > Vertex0.y) ? 1 : -1;
        //color
        float length = sqrt(dx * dx + dy * dy);
        float r = Vertex0.r;
        float g = Vertex0.g;
        float b = Vertex0.b;
        float dr = (Vertex1.r - Vertex0.r) / length;
        float dg = (Vertex1.g - Vertex0.g) / length;
        float db = (Vertex1.b - Vertex0.b) / length;


        if (dx >= dy) {
            d = 2 * dy - dx;
            while (x != Vertex1.x) {
                DrawPixel(x, y, r, g, b);
                if (x != Vertex1.x) {
                    r += dr;
                    g += dg;
                    b += db;
                }
                if (d <= 0) {
                    d += delE;
                    x += xIncrement;
                } else {
                    d += delNE;
                    x += xIncrement;
                    y += yIncrement;
                }
            }
        } else {
            d = 2 * dx - dy;
            while (y != Vertex1.y) {
                DrawPixel(x, y, r, g, b);
                if (y != Vertex1.y) {
                    r += dr;
                    g += dg;
                    b += db;
                }
                if (d <= 0) {
                    d += 2 * dx;
                    y += yIncrement;
                } else {
                    d += 2 * (dx - dy);
                    x += xIncrement;
                    y += yIncrement;
                }
            }
        }
    }
}

void UpdateActiveEdgeTable(std::vector<ActiveEdge>& Edges, int scanY) {
    // remove
    Edges.erase(std::remove_if(Edges.begin(), Edges.end(), [scanY](const ActiveEdge& edge) {
        return edge.yMax <= scanY;
    }), Edges.end());

    // Update
    for (size_t i = 0; i < Points.size(); ++i) {
        const Vertex& v1 = Points[i];
        const Vertex& v2 = Points[(i + 1) % Points.size()];
        if (v1.y == v2.y) continue;

        float yMin = std::min(v1.y, v2.y);
        float yMax = std::max(v1.y, v2.y);
        if (yMin <= scanY && scanY < yMax) {
            float xIntersect = (v1.y < v2.y) ? v1.x : v2.x;
            float dxPerScan = (v2.x - v1.x) / (v2.y - v1.y);

            auto it = std::find_if(Edges.begin(), Edges.end(), [v1, v2](const ActiveEdge& edge) {
                return (edge.v1 == v1 && edge.v2 == v2) || (edge.v1 == v2 && edge.v2 == v1);
            });

            if (it == Edges.end()) {
                Edges.push_back({yMax, xIntersect, dxPerScan, v1, v2});
            }
        }
    }
}

void InterpolateColor(int x, float t, float& r, float& g, float& b, const Vertex& v1, const Vertex& v2) {
    r = std::max(0.0f, std::min(1.0f, v1.r * (1 - t) + v2.r * t));
    g = std::max(0.0f, std::min(1.0f, v1.g * (1 - t) + v2.g * t));
    b = std::max(0.0f, std::min(1.0f, v1.b * (1 - t) + v2.b * t));
}

void Craws() {
    float minY = Points[0].y;
    float maxY = Points[0].y;

    // Find Max min
    for (const Vertex& v : Points) {
        minY = std::min(minY, v.y);
        maxY = std::max(maxY, v.y);
    }

    std::vector<ActiveEdge> activeEdges;

    // Scan
    for (int scanY = static_cast<int>(std::ceil(minY)); scanY <= static_cast<int>(std::floor(maxY)); ++scanY) {
        UpdateActiveEdgeTable(activeEdges, scanY);

        // Sort
        std::sort(activeEdges.begin(), activeEdges.end(), [](const auto& e1, const auto& e2) {
            return e1.xIntersect < e2.xIntersect;
        });

        // Fill
        for (size_t i = 0; i + 1 < activeEdges.size(); i += 2) {
            int x1 = static_cast<int>(std::ceil(activeEdges[i].xIntersect));
            int x2 = static_cast<int>(std::floor(activeEdges[i + 1].xIntersect));


            for (int x = x1; x <= x2; ++x) {
                float r, g, b;
                float t = (x - activeEdges[i].xIntersect) / (activeEdges[i + 1].xIntersect - activeEdges[i].xIntersect);
                InterpolateColor(x, t, r, g, b, activeEdges[i].v1, activeEdges[i].v2);

                DrawPixel(x, scanY, r, g, b);
            }
        }

        // UpDate
        for (auto& edge : activeEdges) {
            edge.xIntersect += edge.dxPerScan;
        }
    }
}