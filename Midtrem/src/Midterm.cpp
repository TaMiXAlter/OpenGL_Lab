/*** freeglut***/
#include <freeglut.h>
#include <freeglut_std.h>
#include <GL/gl.h>
#include <iostream>
#include <iterator>
#include <vector>
#include <cstring>
#include <algorithm>



float WindowWidth = 500;
float WindowHeight = 500;

struct Vector3{
    float x;
    float y;
    float z;
};
struct Triangle{
    Triangle() = default;
    Triangle(Vector3 deltaA,Vector3 deltaB,Vector3 deltaC){
        a= deltaA;
        b= deltaB;
        c= deltaC;
    };
    Vector3 a;
    Vector3 b;
    Vector3 c;
};
struct Edges{
    Edges(){
        left = 0;
        right = 0;
        bottom = 0;
        top = 0;
        near = 0;
        far = 0;
    }
    float left;
    float right;
    float bottom;
    float top;
    float near;
    float far;
};
void ChangeSize(int , int );
void RenderScene(void);
void KeyBoardInput(unsigned char KeyCode, int x, int y );
void TimerFunc(int value);
/**Menu*/
void CreatMenu();
/***/

float RotaValueX;
float RotaValueY;
float RotaValueZ;

float TranslateValueX;
float TranslateValueY;
float TranslateValueZ;
void ResetAllProperty();
/***/
GLenum RenderMode;
bool IsRandomColor;
/**Camera auto adjust and movement*/
GLdouble EyeX,EyeY,EyeZ;
GLdouble CenterX,CenterY,CenterZ;
GLdouble ViewAngle = 170;
/**objData*/
std::vector<Triangle> MeshList;
Edges ObjEdges;
/**obj loader*/
bool loadOBJ(const char * path,std::vector <Triangle> & out_vertices,Edges &out_edgeData);
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(WindowWidth,WindowHeight);
    glutInitWindowPosition(600,80);
    glutCreateWindow("Midterm");

    IsRandomColor = true;
    RenderMode = GL_TRIANGLES;
    ResetAllProperty();
    loadOBJ( RESOURCE_DIR"octahedron.obj", MeshList,ObjEdges);


    CreatMenu();

    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    glutKeyboardFunc(KeyBoardInput );
    glutTimerFunc(100, TimerFunc,1);
    glutMainLoop();	//http://www.programmer-club.com.tw/ShowSameTitleN/opengl/2288.html
    return 0;
}
void GetBoundingBox(Edges& currentEdgesData, Vector3 newVertex){
    if(newVertex.x > currentEdgesData.right) currentEdgesData.right= newVertex.x;
    if(newVertex.x < currentEdgesData.left) currentEdgesData.left = newVertex.x;
    if(newVertex.y > currentEdgesData.top) currentEdgesData.top= newVertex.y;
    if(newVertex.y < currentEdgesData.bottom) currentEdgesData.bottom = newVertex.y;
    if(newVertex.z > currentEdgesData.far) currentEdgesData.far= newVertex.z;
    if(newVertex.z < currentEdgesData.near) currentEdgesData.near = newVertex.z;
}
bool loadOBJ(const char * path,std::vector <Triangle> & out_list,Edges & out_edgeData) {
    std::vector<Vector3> temp_vertices;
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("Impossible to open the file !\n");
        return false;
    }
    while (1) {

        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break; // EOF = End Of File. Quit the loop.

        if (strcmp(lineHeader, "v") == 0) {
            Vector3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            GetBoundingBox(out_edgeData,vertex);
//            std::cout<<out_edgeData.left<<"  "<<out_edgeData.right<<std::endl;
            temp_vertices.push_back(vertex);
        } else if (strcmp(lineHeader, "f") == 0) {
            unsigned int vertexIndex[3];
            int matches = fscanf(file, "%d %d %d\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);
            if (matches != 3) {
                printf("File can't be read by my loader D:\n");
                std::cout<<matches<<std::endl;
                return false;
            }

            out_list.push_back(Triangle(temp_vertices[vertexIndex[0]-1],temp_vertices[vertexIndex[1]-1],temp_vertices[vertexIndex[2]-1]));
        }


    }
    /**for test*/
//    for (int i = 0; i < out_list.size(); ++i) {
//
//        std::cout<<out_list[i].b.x<<out_list[i].b.y<<out_list[i].b.z<<std::endl;
//    }
//    for (int d = 0; d <6; ++d) {
//        std::cout<<out_edgeData.left<<out_edgeData.right<<std::endl;
//    }
//    return true;
}
void ChangeSize(int w, int h)
{
    printf("Window Size= %d X %d\n",w,h);
    glViewport(0, 0, w, h);
    WindowWidth = (float)w;
    WindowHeight = (float)h;
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    // 根據模型的尺寸和位置來調整視景體
    float modelWidth = ObjEdges.right - ObjEdges.left;
    float modelHeight = ObjEdges.top - ObjEdges.bottom;
    float modelDepth = ObjEdges.far - ObjEdges.near;
    float maxModelSize = std::max({modelWidth, modelHeight, modelDepth});
    float nearPlane = maxModelSize / 7.0f;
    float farPlane = maxModelSize * 10.0f;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-modelWidth / 2, modelWidth / 2, -modelHeight / 2, modelHeight / 2, nearPlane, farPlane);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(EyeX, EyeY, EyeZ, CenterX, CenterY, CenterZ, 0, 1, 0);
    EyeZ = ObjEdges.near - (ObjEdges.far - ObjEdges.near)/2;

    glViewport(0, 0, WindowWidth , WindowHeight);

    /**Rota*/
    glRotatef(RotaValueX,1,0,0);
    glRotatef(RotaValueY,0,1,0);
    glRotatef(RotaValueZ,0,0,1);
    glTranslated(TranslateValueX,TranslateValueY,TranslateValueZ);
    glBegin(RenderMode);
    glColor3f(1,1,1);
    for (int i = 0; i <MeshList.size(); ++i) {
        if(IsRandomColor){
            glColor3ub(rand()%255,rand()%255,rand()&255);
        }else{
            glColor3f(1,1,1);
        }
        glVertex3f(MeshList[i].a.x,MeshList[i].a.y,MeshList[i].a.z);
        glVertex3f(MeshList[i].b.x,MeshList[i].b.y,MeshList[i].b.z);
        glVertex3f(MeshList[i].c.x,MeshList[i].c.y,MeshList[i].c.z);
        if(RenderMode == GL_LINES)glVertex3f(MeshList[i].a.x,MeshList[i].a.y,MeshList[i].a.z);
    }
    glEnd();
    glFlush();
    glutSwapBuffers();

}
void KeyBoardInput(unsigned char KeyCode, int x, int y ){
    switch (KeyCode) {
        /**Rotation*/
        case 'a':
            RotaValueX += 1;
            break;
        case 's':
            RotaValueY += 1;
            break;
        case 'd':
            RotaValueZ += 1;
            break;
        /**Translate*/
        case 'q':
            TranslateValueX ++;
            break;
        case 'w':
            TranslateValueY ++;
            break;
        case 'e':
            TranslateValueZ +=5;
            break;
        /**Camera Location*/
        case 't':
            EyeX ++;
            break;
        case 'y':
            EyeY ++;
            break;
        case 'u':
            EyeZ ++;
            break;
        /**Camera LookAt*/
        case 'g':
            CenterX ++;
            break;
        case 'h':
            CenterY ++;
            break;
        case 'j':
            CenterZ ++;
            break;
        /**Reset*/
        case 'r':
            ResetAllProperty();
            EyeZ = ObjEdges.near - (ObjEdges.far - ObjEdges.near)/10;
            break;
    }

}

void MainMenu(int value){

}
void ResetObjDatas(){
    MeshList.clear();
    ObjEdges = Edges();
}
void AdjustObjData(){
    EyeZ = ObjEdges.far + (ObjEdges.far - ObjEdges.near)/10;
}
void ObjSelectMenu(int value) {
    switch (value) {
        case 0:
            ResetAllProperty();
            ResetObjDatas();
            loadOBJ(RESOURCE_DIR"octahedron.obj", MeshList,ObjEdges);
            AdjustObjData();
            break;
        case 1:
            ResetAllProperty();
            ResetObjDatas();
            loadOBJ(RESOURCE_DIR"gourd.obj", MeshList,ObjEdges);
            AdjustObjData();
            break;
        case 2:
            ResetAllProperty();
            ResetObjDatas();
            loadOBJ( RESOURCE_DIR"teapot.obj", MeshList,ObjEdges);
            AdjustObjData();
            break;
        case 3:
            ResetAllProperty();
            ResetObjDatas();
            loadOBJ( RESOURCE_DIR"teddy.obj", MeshList,ObjEdges);
            AdjustObjData();
            break;
    }
}
void RenderModeMenu(int value) {
    switch (value) {
        case 0:
            RenderMode = GL_POINTS;
            break;
        case 1:
            RenderMode = GL_LINES;
            break;
        case 2:
            RenderMode = GL_TRIANGLES;
            break;
    }
}
void ColorMenu(int value) {
    IsRandomColor = value;
}
void CreatMenu() {
    int objSelectMenu = glutCreateMenu(ObjSelectMenu);
    glutAddMenuEntry("Octahedron",0);
    glutAddMenuEntry("Gourd",1);
    glutAddMenuEntry("Teapot",2);
    glutAddMenuEntry("Teddy",3);

    int renderModeMenu = glutCreateMenu(RenderModeMenu);
    glutAddMenuEntry("Point",0);
    glutAddMenuEntry("Line",1);
    glutAddMenuEntry("TRIANGLES",2);

    int colorMenu = glutCreateMenu(ColorMenu);
    glutAddMenuEntry("White",0);
    glutAddMenuEntry("RandomColor",1);

    int mainMenu = glutCreateMenu(MainMenu);
    glutAddSubMenu("ObjSelect",objSelectMenu);
    glutAddSubMenu("RenderMode",renderModeMenu);
    glutAddSubMenu("Color",colorMenu);

    glutAttachMenu(GLUT_RIGHT_BUTTON);

}
void TimerFunc(int value){
    glutPostRedisplay();
    glutTimerFunc(100, TimerFunc, 1);
}
void ResetAllProperty(){
    RotaValueX = 0;
    RotaValueY = 0;
    RotaValueZ = 0;

    TranslateValueX=0;
    TranslateValueY=0;
    TranslateValueZ=0;


    EyeX = 0;
    EyeY = 0;
    //todo: change this to fit OBJ file
    EyeZ = -15;

    CenterX = 0;
    CenterY = 0;
    CenterZ = 0;
}



