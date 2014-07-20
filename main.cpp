#include "main.h"
#include "point.h"

#define deg2rad(a) a * M_PI / 180.0

glsystem gls;
point curpos(0.0f, 0.0f, 0.0f);
float gangle = 0;

void draw(float angle) {
    point endpos;

    endpos.setx((curpos.getx()) + 2.0 * cos(angle));
    endpos.sety((curpos.gety()) + 2.0 * sin(angle));
    endpos.setz(curpos.getz());

    //    curpos.dump("curpos: ");
    //    endpos.dump("endpos: ");

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


    // sierpinski #1
    //    gls.addPair('F', "G-F-G");
    //    gls.addPair('G', "F+G+F");
    //    gls.setAngle(60);
    //    gls.setStart("F");



    // branching
    //    gls.addPair('F', "F[+F]F[-F]F");
    //    gls.setAngle(27.5);
    //    gls.setStart("F");

    gls.addPair('X', "F[+X][-X]FX");
    gls.addPair('F', "FF");
    gls.setAngle(25.7);
    gls.setStart("X");


    //    gls.addPair('F', "FF-F-F-F-F-F+F");
    //    gls.setAngle(90);
    //    gls.setStart("F-F-F-F");

    //tree #1

    //    gls.addVariable('X');
    //    gls.addVariable('F');
    //    gls.addRule("F-[[X]X]F[FX]-X");
    //    gls.addRule("FF");
    //    gls.setStart("X");

    // tree #2

    //    gls.addVariable('X');
    //    gls.addVariable('F');
    //    gls.addRule("F[X]F[-X]X");
    //    gls.addRule("FF");
    //    gls.setStart("X");

    // tree #3

    //        gls.addVariable('F');
    //        gls.addRule("FF-[-FFF][F-F-F]");
    //        gls.setStart("F");

    // koch


    //        gls.addVariable('F');
    //        gls.addVariable('X');
    //        gls.addRule("F-[[X]+X]+F[+FX]-X");
    //        gls.setStart("F");


    // sierpinski #1

    //        gls.addVariable('F');
    //        gls.addVariable('G');
    //        gls.addRule("F-G+F+G-F");
    //        gls.addRule("GG");
    //        gls.setStart("F-G-G");


    // sierpinski #2




    // F-[[X]+X]+F[+FX]-X
    // FFF-[[X]+X]+F[+FX]-XF-[[X]+X]+F[+FX]-XFFFFF-[[X]+X]+F[+FX]-XF-[[X]+X]+F[+FX]-X
    //FF-[[F-[[X]+X]+F[+FX]-X]+F-[[X]+X]+F[+FX]-X]+FF[+FFF-[[X]+X]+F[+FX]-X]-F-[[X]+X]+F[+FX]-X

    gls.iterate(6);
    //gls.show();

    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
