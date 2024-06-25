#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif
#include <iostream>


float object_top = 0.675;
float water_Top = 0.19;
float object_Speed = 0.010;
float water_Speed = 0.0020;
bool start_Animation = false;
bool object_TouchesWater = false;

void Animation_display() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    // Left side static glass
    glColor3f(0.0, 0.0, 0.0);

    glRectf(-0.795, -0.55, -0.805, 0.75); // Left black border

    glRectf(-0.205, -0.55, -0.195, 0.75);  // Right black border

    glColor3f(0.0, 0.0, 0.0);
    glRectf(-0.8, -0.55, -0.2, -0.5); //bottom black border

    glColor3f(0.0, 0.0, 1.0); // blue water
    glRectf(-0.8, -0.5, -0.2, 0.19);


    // Right side animated glass
    glColor3f(0.0, 0.0, 0.0);
    glRectf(0.195, -0.55, 0.205, 0.75); // Left black border

    glRectf(0.795, -0.55, 0.805, 0.75); // Right black border

    glColor3f(0.0, 0.0, 0.0);
    glRectf(0.2, -0.55, 0.8, -0.5); //bottom black border

    glColor3f(0.0, 0.0, 1.0); //blue water
    glRectf(0.2, -0.5, 0.8, water_Top);


    //black object
    glPushMatrix();
    glTranslatef(0.0, object_top, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glRectf(0.35, 0.15, 0.675, 0.45);
    glPopMatrix();
    // red arrow
    glPushMatrix();
    glTranslatef(0.9, water_Top , 0.0);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.05, 0.0);
    glVertex2f(0.0, 0.05);
    glVertex2f(0.05, 0.0);
    glEnd();
    glPopMatrix();
    if (start_Animation == true) {
        object_top = object_top - object_Speed;
        if ( object_top <= water_Top) {
            object_TouchesWater = true;
        }
        if (object_top < -0.676) {
            start_Animation = false;
        }
    }

    if (object_TouchesWater == true) {
        water_Top =  water_Top + water_Speed;
        if (water_Top > 0.37) {
            water_Top = 0.37;
        }
    }

    glFlush();
}

void timer(int) {
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'm') {
            start_Animation = true;
            object_top = 0.675;
            water_Top = 0.19;
            object_TouchesWater = false;

     } else if (key == 'e') {
        exit(0);
     }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(480, 600);
    glutCreateWindow("The property of matter that it takes space.");
    glutDisplayFunc(Animation_display);
    glutTimerFunc(16, timer, 0);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
