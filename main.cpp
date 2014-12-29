#include "main.h"
#include "point.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGT 600
#define SCREEN_DEPTH 40

//#define DRAW_BBOX
vector<point *> vertices;
bbox bb;
double scaleFactorX, scaleFactorY;

void draw() {
    
    // draw bbox    
#ifdef DRAW_BBOX
    glColor3f(0.5f, 0.5f, 0.5f);
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glBegin(GL_QUADS);
        glVertex2d(bb.getLowerRight().getx(), bb.getLowerRight().gety());
        glVertex2d(bb.getUpperLeft().getx(), bb.getLowerRight().gety());
        glVertex2d(bb.getUpperLeft().getx(), bb.getUpperLeft().gety());
        glVertex2d(bb.getLowerRight().getx(), bb.getUpperLeft().gety());
    glEnd();
#endif
    
    // TODO: fix drawing
    glColor3f(0.3f, 1.0f, 0.3f);
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    for (uint32_t i = 0; i < vertices.size() / 2; ++i) {
        glBegin(GL_LINES);
            glVertex3d(vertices[i * 2]->getx(), vertices[i * 2]->gety(), vertices[i * 2]->getz());
            glVertex3d(vertices[i * 2 + 1]->getx(), vertices[i * 2 + 1]->gety(), vertices[i * 2 + 1]->getz());
        glEnd();        
    }
    
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glLoadIdentity();

//    glRotatef(90, 0, 0, 1);
    // scale
    glScaled(scaleFactorX, scaleFactorY, 1.0f);

    // center
    glTranslated(-bb.getCenterX(), -bb.getCenterY(), 0);


    
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
    // 800x600
    glOrtho(-SCREEN_WIDTH / 2, SCREEN_WIDTH / 2, -SCREEN_HEIGT / 2,  SCREEN_HEIGT / 2, -SCREEN_DEPTH, SCREEN_DEPTH);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char *argv[]) {
    lsystem gls;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGT);
    glutInitWindowPosition(0, 0);

    glutCreateWindow("lsys");

    init();

    gls.parse("samples/dragon_curve.ls");
    vertices = gls.getVertices();  
    bb = gls.getBbox();
    
    scaleFactorX =  SCREEN_WIDTH / bb.getWidth();
    scaleFactorY = SCREEN_HEIGT / bb.getHeight();
    if (scaleFactorX > scaleFactorY) scaleFactorX = scaleFactorY; else scaleFactorY = scaleFactorX;

    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
