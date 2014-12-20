#include "main.h"
#include "point.h"

#define deg2rad(a) a * M_PI / 180.0

lsystem gls;
point curpos(0.0f, 0.0f, 0.0f);
float gangle = 0;

void draw(float angle) {
    point endpos;

    endpos.setx((curpos.getx()) + 4.0 * cos(angle));
    endpos.sety((curpos.gety()) + 4.0 * sin(angle));
    endpos.setz(curpos.getz());

    glBegin(GL_LINES);
    glVertex3f(curpos.getx(), curpos.gety(), curpos.getz());
    glVertex3f(endpos.getx(), endpos.gety(), endpos.getz());
    glEnd();


    curpos.setx(endpos.getx());
    curpos.sety(endpos.gety());
    curpos.setz(endpos.getz());
}

gstack <float> angles;
gstack <point> positions;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glLoadIdentity();
    glRotatef(90, 0, 0, 1);
    curpos.reset();
    gangle = 0;
    string chain = gls.getChain();
    for (uint32_t i = 0; i < chain.length(); ++i) {
        switch (chain[i]) {
            case '+':
                gangle += deg2rad(gls.getAngle());
                break;
            case '-':
                gangle -= deg2rad(gls.getAngle());
                break;
            case '[':
                positions.push(curpos);
                angles.push(gangle);
                break;
            case ']':
                curpos = positions.pop();
                gangle = angles.pop();
                break;
            default:
                draw(gangle);
                break;

        }
    }
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

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowSize(800, 600);
    glutInitWindowPosition(0, 0);

    glutCreateWindow("lsys");

    init();
    
    //gls.parse("samples/branch_a.ls");
    //gls.parse("samples/sierpinski_gasket.ls");
    gls.parse("samples/hexagonal_gosper_curve.ls");
    gls.iterate();

    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
