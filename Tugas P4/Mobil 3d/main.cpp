// Nama	: Fauzan Hadi
// NIM	: 24060123140176 

#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

float angleX = 0.0f, angleY = 0.0f, deltaAngleX = 0.0f, deltaAngleY = 0.0f, ratio;
float x = 0.0f, y = 1.75f, z = 15.0f;
float lx = 0.0f, ly = 0.0f, lz = -1.0f;
int deltaMove = 0, deltaStrafe = 0, deltaUp = 0, h, w;
int bitmapHeight = 12;

void Reshape(int w1, int h1)
{
    if (h1 == 0)
        h1 = 1;
    w = w1;
    h = h1;
    ratio = 1.0f * w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45, ratio, 0.1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
}

void orientMe(float ang)
{
    lx = sin(angleX);
    ly = sin(angleY);
    lz = -cos(angleX);
    glLoadIdentity();
    gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
}

void moveMeFlat(int i)
{
    x = x + i * (lx) * 0.01;
    z = z + i * (lz) * 0.01;
    glLoadIdentity();
    gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
}

void strafeMeFlat(int i)
{
    x = x + i * (lz) * 0.01;
    z = z - i * (lx) * 0.01;
    glLoadIdentity();
    gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
}

void moveMeUp(int i)
{
    y += i * 0.01;
    glLoadIdentity();
    gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
}

void Grid()
{
    double i;
    const float Z_MIN = -50, Z_MAX = 50;
    const float X_MIN = -50, X_MAX = 50;
    const float gap = 1.5;
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_LINES);
    for (i = Z_MIN; i < Z_MAX; i += gap)
    {
        glVertex3f(i, 0, Z_MIN);
        glVertex3f(i, 0, Z_MAX);
    }

    for (i = X_MIN; i < X_MAX; i += gap)
    {
        glVertex3f(X_MIN, 0, i);
        glVertex3f(X_MAX, 0, i);
    }
    glEnd();
}

void drawWheel(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glColor3f(0.0f, 0.0f, 0.0f);
    glutSolidTorus(0.2, 0.4, 20, 20); 
    
    // Velg 
    glColor3f(1.0f, 1.0f, 1.0f);
    glutSolidTorus(0.1, 0.2, 20, 20);
    glPopMatrix();
}

void Mobil()
{
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f); 
    glScalef(3.0f, 3.0f, 3.0f); 
    
    // Badan mobil
    glPushMatrix();
    glScalef(2.5f, 1.0f, 1.2f); 
    glutSolidCube(1.0);
    glPopMatrix();
    
    // Atap mobil
    glPushMatrix();
    glTranslatef(0.0f, 0.8f, 0.0f);
    glScalef(1.5f, 0.8f, 1.2f);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // Kaca depan 
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(0.0f, 0.9f, 0.51f);
    glScalef(1.2f, 0.6f, 0.1f);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // Lampu samping kanan
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glTranslatef(1.3f, 0.3f, 0.2f);
    glutSolidSphere(0.1, 20, 20);
    glTranslatef(0.0f, 0.0f, -0.4f);
    glutSolidSphere(0.1, 20, 20);
    glPopMatrix();
    
    // Lampu samping kiri
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.8f);
    glTranslatef(-1.3f, 0.3f, 0.2f);
    glutSolidSphere(0.1, 20, 20);
    glTranslatef(0.0f, 0.0f, -0.4f);
    glutSolidSphere(0.1, 20, 20);
    glPopMatrix();
    
    // Roda mobil dengan velg putih
    drawWheel(-1.0f, -0.5f, 0.8f);
    drawWheel(1.0f, -0.5f, 0.8f);
    drawWheel(-1.0f, -0.5f, -0.8f);
    drawWheel(1.0f, -0.5f, -0.8f);
    
    glPopMatrix();
}

void display()
{
    if (deltaMove)
        moveMeFlat(deltaMove);
    if (deltaStrafe)
        strafeMeFlat(deltaStrafe);
    if (deltaUp)
        moveMeUp(deltaUp);
    if (deltaAngleX)
    {
        angleX += deltaAngleX;
        orientMe(angleX);
    }
    if (deltaAngleY)
    {
        angleY += deltaAngleY;
        orientMe(angleY);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Grid();
    Mobil();

    glutSwapBuffers();
    glFlush();
}

void pressKey(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        deltaAngleY = -0.01f;
        break;
    case GLUT_KEY_RIGHT:
        deltaAngleY = 0.01f;
        break;
    case GLUT_KEY_UP:
        deltaMove = 1;
        break;
    case GLUT_KEY_DOWN:
        deltaMove = -1;
        break;
    }
}

void releaseKey(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
    case GLUT_KEY_RIGHT:
        deltaAngleY = 0.0f;
        break;
    case GLUT_KEY_UP:
    case GLUT_KEY_DOWN:
        deltaMove = 0;
        break;
    }
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
        deltaMove = 1;
        break;
    case 's':
        deltaMove = -1;
        break;
    case 'd':
        deltaStrafe = -1;
        break;
    case 'a':
        deltaStrafe = 1;
        break;
    case 'q':
        deltaUp = 1;
        break;
    case 'e':
        deltaUp = -1;
        break;
    case 'l':
        deltaAngleX = 0.001f;
        break;
    case 'j':
        deltaAngleX = -0.001f;
        break;
    case 'k':
        deltaAngleY = -0.001f;
        break;
    case 'i':
        deltaAngleY = 0.001f;
        break;
    }
}

void releaseKey(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
    case 's':
        deltaMove = 0;
        break;
    case 'a':
    case 'd':
        deltaStrafe = 0;
        break;
    case 'q':
    case 'e':
        deltaUp = 0;
        break;
    case 'i':
    case 'k':
        deltaAngleY = 0.0f;
        break;
    case 'j':
    case 'l':
        deltaAngleX = 0.0f;
        break;
    }
}

void lighting()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    // Parameter pencahayaan
    GLfloat light_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f }; // warna ambient
    GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // warna diffuse
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // warna specular
       GLfloat light_position[] = { 0.0f, 20.0f, 10.0f, 1.0f }; // posisi lampu

    // Parameter material
    GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f }; // warna ambient material
    GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f }; // warna diffuse material
    GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // warna specular material
    GLfloat high_shininess[] = { 100.0f }; // tingkat shininess material

    // Set parameter pencahayaan
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    // Set parameter material
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}

void init(void)
{
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Mobil");
    glutIgnoreKeyRepeat(1);
    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(releaseKey);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(Reshape);
    lighting();
    init();
    glutMainLoop();
    return 0;
}
