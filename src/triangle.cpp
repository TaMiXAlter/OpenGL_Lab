
#include "freeglut_std.h"
#include <GL/gl.h>
#include <any>
#include <iostream>
#include <iterator>
#include <stdio.h>
#include <math.h>
/*** freeglut***/
#include <freeglut.h>
struct Vector3{
    Vector3(float tx,float ty,float tz);
    float x;
    float y;
    float z;
};
Vector3::Vector3(float tx, float ty, float tz) {
    x = tx;
    y = ty;
    z = tz;
}

void ChangeSize(int , int );					 
void RenderScene(void);			
void MouseFunction(int button,int state,int x,int y);
void KeyBoardInput(unsigned char KeyCode, int x, int y );   
void TimerFunc(int value);
const float WindowWidth = 400;
const float WindowHeight = 400;
/***/
float RotaValueX;
float RotaValueY;
float RotaValueZ;

float TranslateValueX;
float TranslateValueY;
float TranslateValueZ;

float ScaleX;
float ScaleY;
float ScaleZ;

void ResetAllProperty();
/**lab3:my transform function*/
void MyRotation(float angle,float x,float y,float z);
void MyTranslate(float x,float y,float z);
void MyScale(float x,float y,float z);
/**lab4: mouse position to the opengl world*/
float AMousePositionX,AMousePositionY,BMousePositionX,BMousePositionY;
bool ABSwitch;
float RotaValueC;
int main(int argc, char** argv) 
{ 
   glutInit(&argc, argv); 
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB|GLUT_DEPTH); 
   glutInitWindowSize(WindowWidth,WindowHeight);
   glutInitWindowPosition(600,80);           
   glutCreateWindow("Simple Triangle");

   ResetAllProperty();

   glutReshapeFunc(ChangeSize); 
   glutDisplayFunc(RenderScene); 
   glutKeyboardFunc(KeyBoardInput );
    glutMouseFunc(MouseFunction);
   glutTimerFunc(100, TimerFunc,1);
   glutMainLoop();	//http://www.programmer-club.com.tw/ShowSameTitleN/opengl/2288.html
   return 0; 
} 
void ChangeSize(int w, int h) 
{ 
   printf("Window Size= %d X %d\n",w,h); 
   glViewport(0, 0, w, h);            
   glMatrixMode(GL_PROJECTION); 
   glLoadIdentity(); 
   glOrtho(-10,10,-10,10,-10,20);      
   glMatrixMode(GL_MODELVIEW); 
   glLoadIdentity(); 
} 

void RenderScene(void) 
{ 
   glEnable(GL_DEPTH_TEST);
   glClearColor(1.0, 1.0, 1.0, 1.0);     
   glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW); 
   glLoadIdentity(); 
   gluLookAt(0,0,10.f,0,0,0,0,1,0);


   float TraingleA[][3] = {{0,2,0},{-2,-2,0},{2,-2,0}};
   float TraingleB[][3] = {{0,2,-1},{-2,-2,-1},{2,-2,-1}};


    MyTranslate(TranslateValueX,TranslateValueY,TranslateValueZ);
    MyScale(ScaleX,ScaleY,ScaleZ);
    MyRotation(RotaValueX,1,0,0);
    MyRotation(RotaValueY,0,1,0);
    MyRotation(RotaValueZ,0,0,1);

    MyRotation(RotaValueC,AMousePositionX-BMousePositionX,AMousePositionY-BMousePositionY,0);
    /**draw line from origin to mouse*/
    bool AValid = AMousePositionX != 0 && AMousePositionY!=0;
    bool BValid = BMousePositionX != 0 && BMousePositionY!= 0;
    if(AValid){
        glBegin(GL_POINTS);
        glColor3f(0,1,1);
        glVertex3f(AMousePositionX,AMousePositionY,0);
        glEnd();
        if(BValid){
            glBegin(GL_LINES);
            glColor3f(0,1,1);
            glVertex3f(AMousePositionX,AMousePositionY,0);
            glVertex3f(BMousePositionX,BMousePositionY,0);
            glEnd();
        }
    }
    /**draw xyz lines*/
    glBegin(GL_LINES);
      glColor3f(1, 0, 0);
      glVertex3f(100, 0,0);
      glVertex3f(-100,0,0);
      glEnd();

      glBegin(GL_LINES);
      glColor3f(0, 1, 0);
      glVertex3f(0, 100,0);
      glVertex3f(0,-100,0);
      glEnd();

      glBegin(GL_LINES);
      glColor3f(0, 0, 1);
      glVertex3f(0, 0,100);
      glVertex3f(0,0,-100);
      glEnd();


      glBegin(GL_TRIANGLES);
         //Afront
         glColor3f( 1, 0, 0);
         glVertex3f(TraingleA[0][0], TraingleA[0][1], TraingleA[0][2]);
         glVertex3f(TraingleA[1][0], TraingleA[1][1], TraingleA[1][2]);
         glVertex3f(TraingleA[2][0], TraingleA[2][1], TraingleA[2][2]);

         //Bfront
         glColor3f(0, 0, 1);
         glVertex3f(TraingleB[0][0], TraingleB[0][1], TraingleB[0][2]);
         glVertex3f(TraingleB[2][0], TraingleB[2][1], TraingleB[2][2]);
         glVertex3f(TraingleB[1][0], TraingleB[1][1], TraingleB[1][2]);

       //left
         glColor3f( 0, 1, 0);
         glVertex3f(TraingleA[0][0], TraingleA[0][1], TraingleA[0][2]);
         glVertex3f(TraingleB[0][0], TraingleB[0][1], TraingleB[0][2]);
         glVertex3f(TraingleA[1][0], TraingleA[1][1], TraingleA[1][2]);
         glVertex3f(TraingleA[1][0], TraingleA[1][1], TraingleA[1][2]);
         glVertex3f(TraingleB[0][0], TraingleB[0][1], TraingleB[0][2]);
         glVertex3f(TraingleB[1][0], TraingleB[1][1], TraingleB[1][2]);

       //right
         glColor3f( 0, 1, 1);
         glVertex3f(TraingleA[0][0], TraingleA[0][1], TraingleA[0][2]);
         glVertex3f(TraingleA[2][0], TraingleA[2][1], TraingleA[2][2]);
         glVertex3f(TraingleB[2][0], TraingleB[2][1], TraingleB[2][2]);
         glVertex3f(TraingleA[0][0], TraingleA[0][1], TraingleA[0][2]);
         glVertex3f(TraingleB[2][0], TraingleB[2][1], TraingleB[2][2]);
         glVertex3f(TraingleB[0][0], TraingleB[0][1], TraingleB[0][2]);

       //bottom
         glColor3f( 1, 1, 0);
         glVertex3f(TraingleA[2][0], TraingleA[2][1], TraingleA[2][2]);
         glVertex3f(TraingleA[1][0], TraingleA[1][1], TraingleA[1][2]);
         glVertex3f(TraingleB[2][0], TraingleB[2][1], TraingleB[2][2]);
         glVertex3f(TraingleA[1][0], TraingleA[1][1], TraingleA[1][2]);
         glVertex3f(TraingleB[1][0], TraingleB[1][1], TraingleB[1][2]);
         glVertex3f(TraingleB[2][0], TraingleB[2][1], TraingleB[2][2]);
     glEnd();



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
      TranslateValueZ ++;
    break;
    /**scale*/
    case 'z':
        ScaleX++;
    break;
    case 'x':
      ScaleY++;
      break;
    case 'c':
      ScaleZ++;
      break;
    case 'r':
        ResetAllProperty();
        break;
    /**Custom Rotation*/
      case 'f':
          RotaValueC +=1;
          std::cout<< "XLine:"<<AMousePositionX-BMousePositionX<<"YLine:"<<AMousePositionY-BMousePositionY<<std::endl;
          break;
  }
}

void TimerFunc(int value){
  glutPostRedisplay();
  glutTimerFunc(100, TimerFunc, 1);
}

void MyTranslate(float x, float y,float z) {
    float rotMatrix[16];
    glGetFloatv(GL_MODELVIEW_MATRIX,rotMatrix);

    rotMatrix[12] =x;
    rotMatrix[13] = y;
    rotMatrix[14] = z;
    glMultMatrixf(rotMatrix);
}

void MyScale(float x, float y, float z) {
    float rotMatrix[16];
    rotMatrix[0] =x;
    rotMatrix[5] = y;
    rotMatrix[10] = z;
    rotMatrix[15] = 1.0f;
    glMultMatrixf(rotMatrix);
}

void MyRotation(float angle, float x, float y, float z) {
    GLfloat rotMatrix[16];
    float angleDeg2Rad = angle * (M_PI / 180.0f);

    float cosAngle = cos(angleDeg2Rad);
    float sinAngle = sin(angleDeg2Rad);

    float len = sqrt(x * x + y * y + z * z);

    if (len != 0) {
        x /= len;
        y /= len;
        z /= len;
    }

    float omc = 1.0f - cosAngle;

    rotMatrix[0] = x * x * omc + cosAngle;
    rotMatrix[1] = y * x * omc + z * sinAngle;
    rotMatrix[2] = x * z * omc - y * sinAngle;
    rotMatrix[3] = 0.0f;

    rotMatrix[4] = x * y * omc - z * sinAngle;
    rotMatrix[5] = y * y * omc + cosAngle;
    rotMatrix[6] = y * z * omc + x * sinAngle;
    rotMatrix[7] = 0.0f;

    rotMatrix[8] = x * z * omc + y * sinAngle;
    rotMatrix[9] = y * z * omc - x * sinAngle;
    rotMatrix[10] = z * z * omc + cosAngle;
    rotMatrix[11] = 0.0f;

    rotMatrix[12] = 0.0f;
    rotMatrix[13] = 0.0f;
    rotMatrix[14] = 0.0f;
    rotMatrix[15] = 1.0f;
    glMultMatrixf(rotMatrix);
}

void ResetAllProperty(){
    RotaValueX = 0;
    RotaValueY = 0;
    RotaValueZ = 0;

    TranslateValueX=0;
    TranslateValueY=0;
    TranslateValueZ=0;

    ScaleX =1;
    ScaleY =1;
    ScaleZ = 1;

    AMousePositionX = 0;
    AMousePositionY = 0;
    BMousePositionX = 0;
    BMousePositionY = 0;
    ABSwitch = true;
    RotaValueC = 0;
}

void MouseFunction(int button, int state, int x, int y) {
    switch (button) {
        case GLUT_LEFT_BUTTON:
            if(state == GLUT_DOWN){
                float NDCX = (2.f* x/WindowWidth)-1;
                float NDCY = -(2.f*y/WindowHeight-1);
                std::cout<< "X:"<<NDCX<<"Y:"<<NDCY  <<std::endl;
                if(ABSwitch){
                    AMousePositionX = NDCX*10;
                    AMousePositionY = NDCY*10;
                    ABSwitch = false;
                }else{
                    BMousePositionX = NDCX*10;
                    BMousePositionY = NDCY*10;
                    ABSwitch = true;
                }


            }
            break;
        default:
            break;
    }
}



