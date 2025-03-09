// Nama	: Fauzan Hadi
// NIM	: 24060123140176

#include <GL/glut.h>
#include <cmath>

#define PI 3.1415926535898

// Variabel posisi mobil
float carX = 0.0f;
float carY = -0.3f;
float carAngle = 0.0f;
float wheelRotation = 0.0f;

// Kecepatan gerak dan rotasi
float moveSpeed = 0.02f;
float rotateSpeed = 3.0f;

// Status tombol ditekan
bool keyStates[256] = {false};
bool specialKeyStates[256] = {false};

// Fungsi menangani input keyboard saat tombol ditekan
void handleKeypress(unsigned char key, int x, int y) {
    keyStates[key] = true;
}

// Fungsi menangani input keyboard saat tombol dilepas
void handleKeyRelease(unsigned char key, int x, int y) {
    keyStates[key] = false;
}

// Fungsi menangani input dari tombol panah (special keys)
void handleSpecialKeypress(int key, int x, int y) {
    specialKeyStates[key] = true;
}

// Fungsi menangani tombol panah saat dilepas
void handleSpecialKeyRelease(int key, int x, int y) {
    specialKeyStates[key] = false;
}

// Fungsi menggambar lingkaran (untuk roda, daun pohon)
void drawCircle(float x, float y, float radius, int segments, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; i++) {
        float theta = 2.0f * PI * float(i) / float(segments);
        float dx = radius * cosf(theta);
        float dy = radius * sinf(theta);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}

// Fungsi menggambar roda dengan jari-jari
void drawWheel(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glRotatef(wheelRotation, 0.0f, 0.0f, 1.0f);

    // Ban luar (hitam)
    drawCircle(0, 0, 0.12, 30, 0.0f, 0.0f, 0.0f);

    // Velg (abu-abu terang)
    drawCircle(0, 0, 0.06, 30, 0.7f, 0.7f, 0.7f);

    glPopMatrix();
}

// Fungsi menggambar mobil sesuai referensi
void drawCar() {
    glPushMatrix();
    glTranslatef(carX, carY, 0.0f);
    glRotatef(carAngle, 0.0f, 0.0f, 1.0f);

    // ** Bagian bawah mobil **
    glColor3f(0.0f, 0.0f, 0.8f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.5, -0.1);
    glVertex2f(0.5, -0.1);
    glVertex2f(0.45, 0.15);
    glVertex2f(-0.45, 0.15);
    glEnd();

    // ** Bagian atap mobil **
    glColor3f(0.0f, 0.0f, 0.6f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.3, 0.15);
    glVertex2f(0.3, 0.15);
    glVertex2f(0.2, 0.3);
    glVertex2f(-0.2, 0.3);
    glEnd();
    
        // ** Jendela Kiri **
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.2, 0.17);
    glVertex2f(-0.05, 0.17);
    glVertex2f(-0.05, 0.28);
    glVertex2f(-0.18, 0.28);
    glEnd();

    // ** Jendela Kanan **
    glBegin(GL_POLYGON);
    glVertex2f(0.2, 0.17);
    glVertex2f(0.05, 0.17);
    glVertex2f(0.05, 0.28);
    glVertex2f(0.18, 0.28);
    glEnd();


    // ** Roda Mobil **
    drawWheel(-0.35, -0.15);
    drawWheel(0.35, -0.15);

    glPopMatrix();
}

// Fungsi menggambar jalan dengan garis putus-putus
void drawRoad() {
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0, -0.4);
    glVertex2f(1.0, -0.4);
    glVertex2f(1.0, -0.7);
    glVertex2f(-1.0, -0.7);
    glEnd();

    // Garis putus-putus
    glColor3f(1.0f, 1.0f, 1.0f);
    for (float i = -1.0; i < 1.0; i += 0.2) {
        glBegin(GL_POLYGON);
        glVertex2f(i, -0.54);
        glVertex2f(i + 0.1, -0.54);
        glVertex2f(i + 0.1, -0.52);
        glVertex2f(i, -0.52);
        glEnd();
    }
}

// Fungsi menggambar pohon
void drawTree(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    // Batang pohon
    glColor3f(0.5f, 0.3f, 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.02, -0.1);
    glVertex2f(0.02, -0.1);
    glVertex2f(0.02, 0.1);
    glVertex2f(-0.02, 0.1);
    glEnd();

    // Daun pohon
    drawCircle(0.0f, 0.15f, 0.07, 30, 0.0f, 0.8f, 0.0f);

    glPopMatrix();
}

// Fungsi update untuk animasi mobil
void update(int value) {
    float radians = carAngle * PI / 180.0f;
    float moveX = cos(radians) * moveSpeed;
    float moveY = sin(radians) * moveSpeed;

    if (keyStates['w'] || specialKeyStates[GLUT_KEY_UP]) {
        carX += moveX;
        carY += moveY;
        wheelRotation -= 10.0f;
    }
    if (keyStates['s'] || specialKeyStates[GLUT_KEY_DOWN]) {
        carX -= moveX;
        carY -= moveY;
        wheelRotation += 10.0f;
    }
    if (keyStates['a'] || specialKeyStates[GLUT_KEY_LEFT]) {
        carAngle += rotateSpeed;
    }
    if (keyStates['d'] || specialKeyStates[GLUT_KEY_RIGHT]) {
        carAngle -= rotateSpeed;
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

// Fungsi tampilan utama
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawRoad();
    
    // Pohon di sisi kiri & kanan jalan
    drawTree(-0.9, -0.3);
    drawTree(0.9, -0.3);
    drawTree(-0.7, -0.3);
    drawTree(0.7, -0.3);
    drawTree(-0.5, -0.3);
    drawTree(0.5, -0.3);

    drawCar();
    glFlush();
}

// Fungsi utama
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Tugas Mobil");

    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeypress);
    glutKeyboardUpFunc(handleKeyRelease);
    glutSpecialFunc(handleSpecialKeypress);
    glutSpecialUpFunc(handleSpecialKeyRelease);
    glutTimerFunc(0, update, 0);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    glutMainLoop();
    return 0;
}
