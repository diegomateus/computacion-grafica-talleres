// =========================================================================
// @author Andrea Rueda-Olarte (rueda-andrea@javeriana.edu.co )
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co )
// =========================================================================
// compilation: g++ -std=c++17 introOpenGL.cxx -lglut -lGLU -lGL
// =========================================================================

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>
#include <iostream>

using namespace std;

void pintarCirculoRojo(double radio, double centroX, double centroY) {

    double x, y;

    glPointSize(3);
    glColor3d(0.733, 0.0, 0.0);

    for (double i = 0; i < 6.26; i = i + 0.02) {
        x = (radio * cos(i)); //calculo de x
        y = (radio * sin(i)); //calculo de y

        x = x + centroX;
        y = y + centroY;

        glBegin(GL_POINTS);

            glVertex2d(x, y);

        glEnd();
    }
}

void pintarFlechaRoja(double radio, double centroX, double centroY, double pos) {

    glPointSize(3);
    glColor3d(0.733, 0.0, 0.0);

    double x = centroX + (radio * pos);
    double y = centroY;

    glBegin(GL_POINTS);

        glVertex2d(x + (13.0 * pos * -1), y);
        glVertex2d(x + (12.0 * pos * -1), y);
        glVertex2d(x + (11.0 * pos * -1), y);
        glVertex2d(x + (10.0 * pos * -1), y);

        glVertex2d(x + (13.0 * pos * -1), y - 1.0);
        glVertex2d(x + (13.0 * pos * -1), y + 1.0);
        glVertex2d(x + (13.0 * pos * -1), y - 2.0);
        glVertex2d(x + (13.0 * pos * -1), y + 2.0);
        glVertex2d(x + (13.0 * pos * -1), y - 3.0);
        glVertex2d(x + (13.0 * pos * -1), y + 3.0);

        glVertex2d(x + (12.0 * pos * -1), y - 1.0);
        glVertex2d(x + (12.0 * pos * -1), y + 1.0);
        glVertex2d(x + (12.0 * pos * -1), y - 2.0);
        glVertex2d(x + (12.0 * pos * -1), y + 2.0);

        glVertex2d(x + (11.0 * pos * -1), y - 1.0);
        glVertex2d(x + (11.0 * pos * -1), y + 1.0);


    glEnd();
}

void pintarPrimeraCircunferenciaAzul(double radio, double centroX, double centroY) {

    double x, y;

    glColor3d(0.0, 0.0, 0.501);
    glPointSize(6);

    for (double i = 0; i < 6.2; i = i + 0.05) {
        x = (radio * cos(i)); //calculo de x
        y = (radio * sin(i)); //calculo de y

        x = x + centroX;
        y = y + centroY;

        glBegin(GL_POINTS);

        if ((x > centroX && x < centroX + 50.0 && y > centroY)
            || (x > centroX && y < centroY + 136.0 && y > centroY + 106.0)
            || (x > centroX + 60.0 && y < centroY)
            || (x < centroX - 20.0 && y > centroY)
            || (x < centroX - 50.0 && y < centroY)) {

            glVertex2d(x, y);
            glVertex2d(x, y + 1);
            glVertex2d(x, y - 1);
            glVertex2d(x + 1, y);
            glVertex2d(x - 1, y);
        }

        glEnd();
    }
}

void pintarSegundaCircunferenciaAzul(double radio, double centroX, double centroY) {

    double x, y;

    glColor3d(0.0, 0.0, 0.501);
    glPointSize(6);

    for (double i = 0; i < 6.2; i = i + 0.05) {

        x = (radio * cos(i)); //calculo de x
        y = (radio * sin(i)); //calculo de y

        x = x + centroX;
        y = y + centroY;

        glBegin(GL_POINTS);

        if ((x > centroX && x < centroX + 85.0) && (y > centroY)
            || (x > centroX && y < centroY + 176.0 && y > centroY + 136.0)
            || (x > centroX && y < centroY + 60.0 && y > centroY + 30.0)
            || (x > centroX && y < centroY - 60.0 && y > centroY - 150.0)
            || (x < centroX && y < centroY - 150.0 && y > centroY - 220.0)
            || (x < centroX && y < centroY + 130.0 && y > centroY + 90.0)
            || (x < centroX - 50.0 && x > centroX - 115.0) && (y > centroY)) {

            glVertex2d(x, y);
            glVertex2d(x, y + 1);
            glVertex2d(x, y - 1);
            glVertex2d(x + 1, y);
            glVertex2d(x - 1, y);
        }

        glEnd();
    }
}

void pintarLinea(double inicio, double fin, double x, float rojo, float verde, float azul, float tam) {

    glPointSize(tam);

    for (double y = inicio; y <= fin; y = y + 2) {

        glBegin(GL_POINTS);
            glColor3f(rojo, verde, azul);
            glVertex2d(x, y);
            glColor3f(0.0, 0.0, 0.0);
            glVertex2d(x + 1, y + 1);

        glEnd();
    }

    glBegin(GL_POINTS);

        glColor3f(0.0, 0.0, 0.0);
        glVertex2d(x, inicio - 5);
        glVertex2d(x, fin + 5);
        glVertex2d(x, inicio - 10);
        glVertex2d(x, fin + 10);

    glEnd();
}

void pintarOjo(double centroX, double centroY, double pos) {

    pintarLinea(centroY - 40, centroY + 15, centroX + (125 * pos), 0.0, 0.0, 0.0, 5);
    pintarLinea(centroY - 45, centroY + 20, centroX + (120 * pos), 0.5, 0.5, 0.5, 5);
    pintarLinea(centroY - 55, centroY + 30, centroX + (115 * pos), 0.5, 0.5, 0.5, 5);
    pintarLinea(centroY - 65, centroY + 40, centroX + (110 * pos), 0.5, 0.5, 0.5, 5);
    pintarLinea(centroY - 70, centroY + 45, centroX + (105 * pos), 0.5, 0.5, 0.5, 5);
    pintarLinea(centroY - 75, centroY + 40, centroX + (100 * pos), 0.5, 0.5, 0.5, 5);
    pintarLinea(centroY - 80, centroY + 35, centroX + (95 * pos), 0.5, 0.5, 0.5, 5);
    pintarLinea(centroY - 85, centroY + 30, centroX + (90 * pos), 0.5, 0.5, 0.5, 5);
    pintarLinea(centroY - 90, centroY + 25, centroX + (85 * pos), 0.5, 0.5, 0.5, 5);
    pintarLinea(centroY - 95, centroY + 20, centroX + (80 * pos), 0.5, 0.5, 0.5, 5);
    pintarLinea(centroY - 95, centroY + 15, centroX + (75 * pos), 0.5, 0.5, 0.5, 5);
    pintarLinea(centroY - 95, centroY + 10, centroX + (70 * pos), 0.5, 0.5, 0.5, 5);
    pintarLinea(centroY - 95, centroY + 5, centroX + (65 * pos), 0.5, 0.5, 0.5, 5);
    pintarLinea(centroY - 95, centroY, centroX + (60 * pos), 0.5, 0.5, 0.5, 5);
    pintarLinea(centroY - 95, centroY - 5, centroX + (55 * pos), 0.5, 0.5, 0.5, 5);
    pintarLinea(centroY - 90, centroY - 10, centroX + (50 * pos), 0.5, 0.5, 0.5, 5);
    pintarLinea(centroY - 90, centroY - 15, centroX + (45 * pos), 0.5, 0.5, 0.5, 5);
    pintarLinea(centroY - 85, centroY - 20, centroX + (40 * pos), 0.5, 0.5, 0.5, 5);
    pintarLinea(centroY - 80, centroY - 25, centroX + (35 * pos), 0.5, 0.5, 0.5, 5);
    pintarLinea(centroY - 75, centroY - 30, centroX + (30 * pos), 0.5, 0.5, 0.5, 5);
    pintarLinea(centroY - 65, centroY - 40, centroX + (25 * pos), 0.5, 0.5, 0.5, 5);
    pintarLinea(centroY - 60, centroY - 45, centroX + (20 * pos), 0.0, 0.0, 0.0, 5);
}

void detalleOjo(double centroX, double centroY, double pos) {

    glColor3f(0.0, 0.0, 0.0);
    glPointSize(5);

    glBegin(GL_POINTS);

        glVertex2d(centroX + (120 * pos), centroY + 35);
        glVertex2d(centroX + (115 * pos), centroY + 45);
        glVertex2d(centroX + (105 * pos), centroY + 55);
        glVertex2d(centroX + (120 * pos), centroY - 60);
        glVertex2d(centroX + (115 * pos), centroY - 70);
        glVertex2d(centroX + (25 * pos), centroY - 25);
        glVertex2d(centroX + (25 * pos), centroY - 80);

    glEnd();
}



void myInit(){

    glClearColor(0.3, 0.0, 0.0, 0.1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 700, 0, 700);
}

void myDisplay(){

    const double centroX = 325;
    const double centroY = 350;

    double r1 = 210;
    double r2 = 225;
    double r3 = 260;
    double r4 = 275;

    glClear(GL_COLOR_BUFFER_BIT);

    pintarCirculoRojo(r1, centroX, centroY);
    pintarCirculoRojo(r4, centroX, centroY);
    pintarFlechaRoja(r4, centroX, centroY, -1);
    pintarFlechaRoja(r4, centroX, centroY, 1);
    pintarPrimeraCircunferenciaAzul(r2, centroX, centroY);
    pintarSegundaCircunferenciaAzul(r3, centroX, centroY);
    pintarOjo(centroX, centroY, 1);
    pintarOjo(centroX, centroY, -1);
    detalleOjo(centroX, centroY, 1);
    detalleOjo(centroX, centroY, -1);

    glFlush();
}

void myResize(int w, int h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
}

int main(int argc, char** argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 700);//Tamano de la ventana
    glutInitWindowPosition(50, 50);//Posicion con respecto a la pantalla

    glutCreateWindow("Spidey sign");

    glutDisplayFunc(myDisplay);
    glutReshapeFunc(myResize);
    myInit();

    glutMainLoop();

    return(0);
}

// eof - introOpenGL.cxx