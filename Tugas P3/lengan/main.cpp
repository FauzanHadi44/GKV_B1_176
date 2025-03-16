#include <GL/glut.h>

// Variabel untuk rotasi sendi utama (shoulder, elbow, wrist)
static int shoulder = 0, elbow = 0, wrist = 0;

// Variabel untuk rotasi setiap jari (2 sendi per jari)
static int finger1_base = 0, finger1_tip = 0;  // Jempol
static int finger2_base = 0, finger2_tip = 0;  // Telunjuk
static int finger3_base = 0, finger3_tip = 0;  // Tengah
static int finger4_base = 0, finger4_tip = 0;  // Manis
static int finger5_base = 0, finger5_tip = 0;  // Kelingking

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

// Fungsi untuk menggambar satu jari dengan dua segmen (sendi)
void drawFinger(float x, float y, float z, int baseAngle, int tipAngle, float scale) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef((GLfloat)baseAngle, 0.0, 0.0, 1.0);
    glTranslatef(scale / 2, 0.0, 0.0);
    
    // Segment pertama jari (pangkal)
    glPushMatrix();
    glScalef(scale, 0.1, 0.1);
    glutWireCube(1.0);
    glPopMatrix();

    // Segment kedua jari (ujung)
    glTranslatef(scale / 2, 0.0, 0.0);
    glRotatef((GLfloat)tipAngle, 0.0, 0.0, 1.0);
    glTranslatef(scale / 4, 0.0, 0.0);
    glPushMatrix();
    glScalef(scale / 2, 0.1, 0.1);
    glutWireCube(1.0);
    glPopMatrix();

    glPopMatrix();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    // Gerakan bahu
    glTranslatef(-1.0, 0.0, 0.0);
    glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    glPushMatrix();
    glScalef(2.0, 0.5, 1.0);
    glutWireCube(1.0);
    glPopMatrix();

    // Gerakan siku
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    glPushMatrix();
    glScalef(2.0, 0.5, 1.0);
    glutWireCube(1.0);
    glPopMatrix();

    // Gerakan pergelangan tangan
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)wrist, 0.0, 0.0, 1.0);
    glTranslatef(0.5, 0.0, 0.0);
    glPushMatrix();
    glScalef(1.2, 0.6, 0.3);  // Ukuran telapak tangan diperbesar agar lebih proporsional
    glutWireCube(1.0);
    glPopMatrix();

    // Gambar 5 jari dengan sendi
    drawFinger(0.4, 0.3, 0.0, finger1_base, finger1_tip, 0.5);  // Jari jempol
    drawFinger(0.5, 0.2, 0.0, finger2_base, finger2_tip, 0.7);  // Jari telunjuk
    drawFinger(0.5, 0.05, 0.0, finger3_base, finger3_tip, 0.75);  // Jari tengah
    drawFinger(0.5, -0.1, 0.0, finger4_base, finger4_tip, 0.7);  // Jari manis
    drawFinger(0.4, -0.25, 0.0, finger5_base, finger5_tip, 0.5);  // Jari kelingking

    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 's': shoulder = (shoulder + 5) % 360; break;
        case 'S': shoulder = (shoulder - 5) % 360; break;
        case 'e': elbow = (elbow + 5) % 360; break;
        case 'E': elbow = (elbow - 5) % 360; break;
        case 'w': wrist = (wrist + 5) % 360; break;
        case 'W': wrist = (wrist - 5) % 360; break;

        // Menekuk jari
        case '1': finger1_base = (finger1_base + 5) % 90; break;
        case '!': finger1_tip = (finger1_tip + 5) % 90; break;
        case '2': finger2_base = (finger2_base + 5) % 90; break;
        case '@': finger2_tip = (finger2_tip + 5) % 90; break;
        case '3': finger3_base = (finger3_base + 5) % 90; break;
        case '#': finger3_tip = (finger3_tip + 5) % 90; break;
        case '4': finger4_base = (finger4_base + 5) % 90; break;
        case '$': finger4_tip = (finger4_tip + 5) % 90; break;
        case '5': finger5_base = (finger5_base + 5) % 90; break;
        case '%': finger5_tip = (finger5_tip + 5) % 90; break;

        // Meluruskan jari
        case 'q': finger1_base = (finger1_base - 5) % 90; break;
        case 'Q': finger1_tip = (finger1_tip - 5) % 90; break;
        case 'a': finger2_base = (finger2_base - 5) % 90; break;
        case 'A': finger2_tip = (finger2_tip - 5) % 90; break;
        case 'z': finger3_base = (finger3_base - 5) % 90; break;
        case 'Z': finger3_tip = (finger3_tip - 5) % 90; break;
        case 'x': finger4_base = (finger4_base - 5) % 90; break;
        case 'X': finger4_tip = (finger4_tip - 5) % 90; break;
        case 'c': finger5_base = (finger5_base - 5) % 90; break;
        case 'C': finger5_tip = (finger5_tip - 5) % 90; break;

        case 27: exit(0); break;  // Escape key untuk keluar
        default: break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 600);
    glutCreateWindow("Tugas No2 Lengan");
    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}

