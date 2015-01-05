#include "main.h"
#include "point.h"
#include "config.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
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
        glVertex2d(bb.getLowerRight().getX(), bb.getLowerRight().getY());
        glVertex2d(bb.getUpperLeft().getX(), bb.getLowerRight().getY());
        glVertex2d(bb.getUpperLeft().getX(), bb.getUpperLeft().getY());
        glVertex2d(bb.getLowerRight().getX(), bb.getUpperLeft().getY());
    glEnd();
#endif
    
    // TODO: fix drawing
    glColor3f(0.3f, 1.0f, 0.3f);
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    for (uint32_t i = 0; i < vertices.size() / 2; ++i) {
        glBegin(GL_LINES);
            glVertex3d(vertices[i * 2]->getX(), vertices[i * 2]->getY(), vertices[i * 2]->getZ());
            glVertex3d(vertices[i * 2 + 1]->getX(), vertices[i * 2 + 1]->getY(), vertices[i * 2 + 1]->getZ());
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

void initGL(double screenWidth, double screenHeight, double screenDepth) {
    glMatrixMode(GL_PROJECTION);
    
    glLoadIdentity();
    // 800x600
    glOrtho(-screenWidth / 2, screenWidth / 2, -screenHeight / 2,  screenHeight / 2, -screenDepth, screenDepth);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}



int main(int argc, char *argv[]) {
    lsystem gls;
    config c("config.cfg");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

    uint32_t screenWidth = c.getValue("SCREEN_WIDTH") != "" ? atoi(c.getValue("SCREEN_WIDTH").c_str()) : SCREEN_WIDTH;
    uint32_t screenHeight = c.getValue("SCREEN_HEIGHT") != "" ? atoi(c.getValue("SCREEN_HEIGHT").c_str()) : SCREEN_HEIGHT;
        
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(0, 0);

    glutCreateWindow(c.getValue("APP_NAME").c_str());

    initGL(screenWidth, screenHeight, SCREEN_DEPTH);

    gls.parse("samples/dragon_curve.ls");
    vertices = gls.getVertices();  
    bb = gls.getBbox();
    
    scaleFactorX =  screenWidth / bb.getWidth();
    scaleFactorY = screenHeight / bb.getHeight();
    if (scaleFactorX > scaleFactorY) scaleFactorX = scaleFactorY; else scaleFactorY = scaleFactorX;

    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
