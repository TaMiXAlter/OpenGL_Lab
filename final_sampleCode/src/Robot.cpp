// Shadow.cpp
// OpenGL SuperBible
// Demonstrates simple planar shadows
// Program by Richard S. Wright Jr.

#include "GLTools.h"
#include "freeglut_std.h"
#include "math3d.h"

// These values need to be available globally
// Light values and coordinates
GLfloat  ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
GLfloat  diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat  specular[] = { 1.0f, 1.0f, 1.0f, 1.0f};
/**4 different light pos*/
GLfloat LightPoses[][4] = {
        { -75.0f, 150.0f, -50.0f, 0.0f },
        { 50.0f, 100.0f, 25.0f, 0.0f },
        { -25.0f, 75.0f, 25.0f, 0.0f },
        {25.f,200.f,-10,0}
};
GLfloat* lightPos = LightPoses[0];

GLfloat  specref[] =  { 1.0f, 1.0f, 1.0f, 1.0f };

float bd,hd,la,lh,ra,rh,ll,lf,rl,rf;
// Transformation matrix to project shadow
M3DMatrix44f shadowMat;

void DrawBox(float x, float y, float z, float w, float h, float d) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(w, h, d);
    glutSolidCube(1.0);
    glScalef(1, 1, 1);
    glPopMatrix();
}
void ColorApply(float r , float g ,float b,bool isShadow){
    if(isShadow){
        glColor3ub(0,0,0);
    }else{
        glColor3ub(r,g,b);
    }
};

void DrawRobot(bool isShadow){
    glPushMatrix();
    /**Body*/
    glRotatef(bd,0,0,1);
    ColorApply(155,0,155,isShadow);
    DrawBox(0,0,0,30,40,10);
        /**Head*/
        glPushMatrix();
        glRotatef(hd,0,0,1);
        ColorApply(255,0,0,isShadow);
        DrawBox(0,30,0,10,10,10);
        glPopMatrix();
        /**Left arm*/
        glPushMatrix();
        glRotatef(la,0,0,1);
        ColorApply(155,155,0,isShadow);
        DrawBox(30.f,10.f,0,20,5,5);
            /**Left hand*/
                glPushMatrix();
                glRotatef(lh,0,0,1);
                ColorApply(75,75,0,isShadow);
                DrawBox(50.f,10.f,0,10,5,5);
                glPopMatrix();
        glPopMatrix();
        /**Right arm*/
        glPushMatrix();
        glRotatef(ra,0,0,1);
        ColorApply(155,155,0,isShadow);
        DrawBox(-30.f,10.f,0,20,5,5);
            /**Right hand*/
            glPushMatrix();
            glRotatef(rh,0,0,1);
            ColorApply(75,75,0,isShadow);
            DrawBox(-50.f,10.f,0,10,5,5);
            glPopMatrix();
        glPopMatrix();
        /**Right Leg*/
        glPushMatrix();
        glRotatef(rl,0,0,1);
        ColorApply(0,155,155,isShadow);
        DrawBox(-10.f,-35.f,0,5,20,5);
            /**Right feet*/
            glPushMatrix();
            glRotatef(rf,0,0,1);
            ColorApply(0,75,155,isShadow);
            DrawBox(-10.f,-50.f,0,5,3,10);
            glPopMatrix();
        glPopMatrix();
        /**Left Leg*/
        glPushMatrix();
        glRotatef(ll,0,0,1);
        ColorApply(0,155,155,isShadow);
        DrawBox(10.f,-35.f,0,5,20,5);
            /**Left feet*/
            glPushMatrix();
            glRotatef(lf,0,0,1);
            ColorApply(0,75,155,isShadow);
            DrawBox(10.f,-50.f,0,5,3,10);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}
// Called to draw scene
void RenderScene(void)
{
    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw the ground, we do manual shading to a darker green
    // in the background to give the illusion of depth
    glBegin(GL_QUADS);
    glColor3ub(0,32,0); //light green ground
    glVertex3f(400.0f, -150.0f, -200.0f);
    glVertex3f(-400.0f, -150.0f, -200.0f);
    glColor3ub(0,255,0);  // make it in green gradient
    glVertex3f(-400.0f, -150.0f, 200.0f);
    glVertex3f(400.0f, -150.0f, 200.0f);
    glEnd();

    // Save the matrix state and do the rotations
    glPushMatrix();

    // Draw jet at new orientation, put light in correct position
    // before rotating the jet
    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);

    /**Robot*/
    DrawRobot(false);
    glPopMatrix();
    // Get ready to draw the shadow and the ground
    // First disable lighting and save the projection state
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glPushMatrix();

    // Multiply by shadow projection matrix
    glMultMatrixf((GLfloat *)shadowMat);

    glColor3ub(0,0,0);
    /**Robot Shadow*/
    DrawRobot(true);

    // Restore the projection to normal
    glPopMatrix();

    // Draw the light source
    glPushMatrix();
    glTranslatef(lightPos[0],lightPos[1], lightPos[2]);
    glColor3ub(255,255,0);
    glutSolidSphere(5.0f,10,10);
    glPopMatrix();

    // Restore lighting state variables
    glEnable(GL_DEPTH_TEST);

    // Display the results
    glutSwapBuffers();
}

// This function does any needed initialization on the rendering
// context.
void SetupRC()
{
    // Any three points on the ground (counter clockwise order)
    M3DVector3f points[3] = {{ -30.0f, -149.0f, -20.0f },
                             { -30.0f, -149.0f, 20.0f },
                             { 40.0f, -149.0f, 20.0f }};

    glEnable(GL_DEPTH_TEST);	// Hidden surface removal
    glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
    glEnable(GL_CULL_FACE);		// Do not calculate inside of jet

    // Setup and enable light 0
    glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
    glLightfv(GL_LIGHT0,GL_SPECULAR,specular);
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
    glEnable(GL_LIGHT0);

    // Enable color tracking
    glEnable(GL_COLOR_MATERIAL);

    // Set Material properties to follow glColor values
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // All materials hereafter have full specular reflectivity
    // with a high shine
    glMaterialfv(GL_FRONT, GL_SPECULAR,specref);
    glMateriali(GL_FRONT,GL_SHININESS,128);

    // Light blue background
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f );

    // Get the plane equation from three points on the ground
    M3DVector4f vPlaneEquation;
    m3dGetPlaneEquation(vPlaneEquation, points[0], points[1], points[2]);

    // Calculate projection matrix to draw shadow on the ground
    m3dMakePlanarShadowMatrix(shadowMat, vPlaneEquation, lightPos);

    glEnable(GL_NORMALIZE);
}

void AddAngle(float& a){
    if(a<20){
        a++;
    } else{
        a= -20;
    }
}
void KeyBoardInput(unsigned char KeyCode, int x, int y ) {
/**Apply different light pos*/
    switch (KeyCode) {
        case '1':
            AddAngle(bd);
            break;
        case '2':
            AddAngle(hd);
            break;
        case '3':
            AddAngle(la);
            break;
        case '4':
            AddAngle(lh);
            break;
        case '5':
            AddAngle(ra);
            break;
        case '6':
            AddAngle(rh);
            break;
        case '7':
            AddAngle(ll);
            break;
        case '8':
            AddAngle(lf);
            break;
        case '9':
            AddAngle(rl);
            break;
        case '0':
            AddAngle(rf);
            break;

    }


    SetupRC();
}
void ChangeSize(int w, int h)
{
    GLfloat fAspect;

    // Prevent a divide by zero
    if(h == 0)
        h = 1;


    // Set Viewport to window dimensions
    glViewport(0, 0, w, h);

    // Reset coordinate system
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    fAspect = (GLfloat)w/(GLfloat)h;
    gluPerspective(60.0f, fAspect, 200.0, 500.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Move out Z axis so we can see everything
    glTranslatef(0.0f, 0.0f, -400.0f);
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
}
void TimerFunc(int value){
    glutPostRedisplay();

    glutTimerFunc(100, TimerFunc, 1);
}
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Shadow");
    glutReshapeFunc(ChangeSize);
    glutKeyboardFunc(KeyBoardInput);
    glutTimerFunc(100, TimerFunc,1);
    glutDisplayFunc(RenderScene);
    SetupRC();
    glutMainLoop();

    return 0;
}
