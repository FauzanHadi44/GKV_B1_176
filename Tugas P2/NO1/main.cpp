// Nama	: Fauzan Hadi
// NIM	: 24060123140176

#include <GL/glut.h>
#include <cmath>

void Lingkaran(void) {
    glClear(GL_COLOR_BUFFER_BIT); 

    glColor3f(0.0f, 0.0f, 0.0f);  

    float radius = 0.5f;
    int jumlah_titik = 100; 

    glBegin(GL_POLYGON); 
    for (int i = 0; i < jumlah_titik; i++) {
        float sudut = 2.0f * 3.1415926f * i / jumlah_titik;
        float x = radius * cos(sudut);
        float y = radius * sin(sudut);
        glVertex2f(x, y);
    }
    glEnd();

    glFlush();
}

void Init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); 
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("NO1 Lingkaran");

    Init(); 
    glutDisplayFunc(Lingkaran);
    glutMainLoop();

    return 0;
}

