/* =========================================================================
 * @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
 * =========================================================================
 * g++ -std=c++17 BaseShapes.cxx -lGL -lglut -o BaseShapes
 * =========================================================================
 */

#include <cmath>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

// -------------------------------------------------------------------------
void ortho_base()
{
    float cur_color[4];
    float lw;

    glGetFloatv(GL_CURRENT_COLOR, cur_color);
    glGetFloatv(GL_LINE_WIDTH, &lw);

    glLineWidth(2);
    glBegin(GL_LINES);
    {
        glColor3f(1, 0, 0);
        glVertex2f(0, 0);
        glVertex2f(5, 0);

        glColor3f(0, 1, 0);
        glVertex2f(0, 0);
        glVertex2f(0, 5);
    }
    glEnd();

    glColor3fv(cur_color);
    glLineWidth(lw);
}

// -------------------------------------------------------------------------
void circle(int mode = GL_LINE_LOOP, int samples = 100)
{
    float pi2 = atan(1.0) * 8.0;

    glBegin(mode);
    {
        for (int i = 0; i < samples; i++)
        {
            float w = pi2 * (float(i) / float(samples));
            glVertex2f(std::cos(w), std::sin(w));
        } // end for
    }
    glEnd();
}

// -------------------------------------------------------------------------
void square(int mode = GL_LINE_LOOP)
{
    glBegin(mode);
    {
        glVertex2f(-1, -1);
        glVertex2f(1, -1);
        glVertex2f(1, 1);
        glVertex2f(-1, 1);
    }
    glEnd();
}

// -------------------------------------------------------------------------
void triangle(int mode = GL_LINE_LOOP)
{
    float s3 = sqrt(3.0);
    glBegin(mode);
    {
        glVertex2f(-1, -s3 / 3.0);
        glVertex2f(1, -s3 / 3.0);
        glVertex2f(0, s3 / 1.5);
    }
    glEnd();
}

// -------------------------------------------------------------------------
void reshape(int width, int height)
{
    // Viewport
    glViewport(0, 0, width, height);

    // Prepare projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10, 10, -10, 10, -1, 1);
}

void house()
{
    //Estructura
    glLoadIdentity();
        glScalef(2, 3.5, 1);
        square();

    //Techo
    glLoadIdentity();
        glTranslatef(0, 4.4, 0);
        glScalef(3.5, 1.5, 1);
        triangle();

   glLoadIdentity();
}

void car(){
    //Piso
    glLoadIdentity();
        glTranslatef(-6, -3.3, 0);
        glScalef(3, 0.2, 1);
        square();

    //Llantas
    glLoadIdentity();
        glTranslatef(-8.5, -2.6, 0);
        glScalef(0.5, 0.5, 1);
        circle();

    glLoadIdentity();
        glTranslatef(-6.5, -2.6, 0);
        glScalef(0.5, 0.5, 1);
        circle();

    //Carroza
    glLoadIdentity();
        glTranslatef(-7.5, -1.1, 0);
        glScalef(1.5, 1, 1);
        square();

    //Motor
    glLoadIdentity();
        glTranslatef(-5.2, -1.4, 0);
        glScalef(0.8, 0.7, 1);
        square();

    glLoadIdentity();
}

void tree(){

    //Tronco
    glLoadIdentity();
        glTranslatef(5, -1.8, 0);
        glScalef(0.7, 1.7, 1);
        square();

    //Copas
    glLoadIdentity();
        glTranslatef(5, 0.8, 0);
        glScalef(1.5, 1.5, 1);
        triangle();

    glLoadIdentity();
        glTranslatef(5, 1.3, 0);
        glScalef(1.5, 1.5, 1);
        triangle();

    glLoadIdentity();
        glTranslatef(5, 1.8, 0);
        glScalef(1.5, 1.5, 1);
        triangle();

    glLoadIdentity();

}

void houseDetails(){

    //Ventanas
    glLoadIdentity();
        glTranslatef(1, 2, 0);
        glScalef(0.5, 0.7, 1);
        square();

    glLoadIdentity();
        glTranslatef(-1, 2, 0);
        glScalef(0.5, 0.7, 1);
        square();

    glLoadIdentity();
        glTranslatef(1, 0.2, 0);
        glScalef(0.5, 0.7, 1);
        square();

    glLoadIdentity();
        glTranslatef(-1, 0.2, 0);
        glScalef(0.5, 0.7, 1);
        square();

    //Puerta
    glLoadIdentity();
        glTranslatef(0, -2.5, 0);
        glScalef(0.5, 1, 1);
        square();

   glLoadIdentity();

}

void carDetails(){

    glLoadIdentity();
        glTranslatef(-8.5, -2.6, 0);
        glScalef(0.2, 0.2, 1);
        circle();

    glLoadIdentity();
        glTranslatef(-6.5, -2.6, 0);
        glScalef(0.2, 0.2, 1);
        circle();
}

// -------------------------------------------------------------------------
void draw()
{
    // Clear framebuffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw stuff
    glMatrixMode(GL_MODELVIEW);

    house();
    car();
    tree();

    houseDetails();
    carDetails();
    
    ortho_base();

    // Prepare next frame
    glutSwapBuffers();
}

// -------------------------------------------------------------------------
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(0, 0);

    glutCreateWindow("Basic shapes in OpenGL");

    glutDisplayFunc(draw);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return (0);
}

// eof - BaseShapes.cxx