#include "main.h"
#include "point.h"



vector<point *> vertices;

void draw() {

    for (uint32_t i = 0; i < vertices.size() / 2; ++i) {
        glBegin(GL_LINES);

        glVertex3d(vertices[i * 2]->getx(), vertices[i * 2]->gety(), vertices[i * 2]->getz());
        cout << vertices[i * 2]->getx() << endl;
        glVertex3d(vertices[i * 2 + 1]->getx(), vertices[i * 2 + 1]->gety(), vertices[i * 2 + 1]->getz());

        glEnd();
    }

}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glLoadIdentity();
    glRotatef(90, 0, 0, 1);
    draw();
    glPopMatrix();
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            exit(0);
    }
}

void idle() {
    glutPostRedisplay();
}

void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-400, 400, -300, 300, -40, 40);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char *argv[]) {
    lsystem gls;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowSize(800, 600);
    glutInitWindowPosition(0, 0);

    glutCreateWindow("lsys");

    init();

    gls.parse("samples/branch_f.ls");
    vertices = gls.getVertices();

    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
