#include "main.h"

#define deg2rad(a) a * M_PI / 180.0

typedef struct tpt {
    float x, y, z;
} tpt;

glsystem gls;

tpt curpos = {0.0f, 0.0f, 0.0f};
tpt stopos = {0.0f, 0.0f, 0.0f};
float gangle = 0;

void draw(float angle, tpt *curpos) {
    tpt endpos;

    endpos.x = curpos->x + 0.1 * cos(angle);
    endpos.y = curpos->y + 0.1 * sin(angle);
    endpos.z = curpos->z;

    glBegin(GL_LINES);
    glVertex3fv((float *) curpos);
    glVertex3fv((float *) &endpos);
    glEnd();

    curpos->x = endpos.x;
    curpos->y = endpos.y;
    curpos->z = endpos.z;
}

gstack <float> angles;
gstack <tpt> positions;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glLoadIdentity();
    glRotatef(90, 0, 0, 1);
    curpos.x = curpos.y = curpos.z = 0;
    gangle = 0;
    for (unsigned int i = 0; i < gls.chain.length(); ++i) {
        switch (gls.chain[i]) {
            case 'G':
            case 'F':
                draw(gangle, &curpos);
                break;
            case '+':
                gangle += deg2rad(25);
                break;
            case '-':
                gangle -= deg2rad(25);
                break;
            case '[':
                positions.push(curpos);
                angles.push(gangle);
                break;
            case ']':
                curpos = positions.pop();
                gangle = angles.pop();
                break;
        }
    }
    glPopMatrix();
    glutSwapBuffers();
}

void idle() {
    glutPostRedisplay();
}

void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-4, 4, -4, 4, -4, 4);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char *argv[]) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowSize(512, 512);
    glutInitWindowPosition(0, 0);

    glutCreateWindow("l-sys");

    init();

    gstack<int> gi;
    gi.push(1);
    gi.push(2);
    gi.push(3);
    gi.dump();

    // koch
    
        gls.addVariable('F');
        gls.addRule("F+F-F-F+F");
        gls.setStart("F");
    


    // sierpinski #1
    /*
    gls.addVariable('F');
    gls.addVariable('G');
    gls.addRule("F-G+F+G-F");
    gls.addRule("GG");
    gls.setStart("F-G-G");
     */

    // sierpinski #2
    
//    gls.addVariable('F');
//    gls.addVariable('G');
//    gls.addRule("G-F-G");
//    gls.addRule("F+G+F");
//    gls.setStart("F");
    

    // F-[[X]+X]+F[+FX]-X
    // FFF-[[X]+X]+F[+FX]-XF-[[X]+X]+F[+FX]-XFFFFF-[[X]+X]+F[+FX]-XF-[[X]+X]+F[+FX]-X
    //FF-[[F-[[X]+X]+F[+FX]-X]+F-[[X]+X]+F[+FX]-X]+FF[+FFF-[[X]+X]+F[+FX]-X]-F-[[X]+X]+F[+FX]-X

    gls.iterate(13);
    //gls.show();

    glutDisplayFunc(display);
    glutIdleFunc(idle);


    glutMainLoop();

    return 0;
}
