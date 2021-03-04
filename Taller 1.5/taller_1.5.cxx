/* -------------------------------------------------------------------------
 * @author Leonardo Fl�rez-Valencia (florez-l@javeriana.edu.co)
 * -------------------------------------------------------------------------
 * Compilation on linux:
 *
 * g++ -std=c++17 line_experiments.cxx -lGL -lGLU -lglut -o line_experiments
 *
 * -------------------------------------------------------------------------
 */

#include <cstring>
#include <iostream>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

using namespace std;

// -------------------------------------------------------------------------
int Width, Height;
int ClickX0, ClickY0, ClickX1, ClickY1;
int NumberOfClicks;
unsigned char* Screen;

// -------------------------------------------------------------------------
void DDA( int x0, int y0, int x1, int y1 ){
	float dx, dy, absoluteDx, absoluteDy, step, x, y;

	dx = x1 - x0;
	dy = y1 - y0;
	absoluteDx = dx;
	absoluteDy = dy;

	if (dx < 0){
    absoluteDx = dx * -1;
  } 
	if (dy < 0){
    absoluteDy = dy * -1;
  }
	
	if(absoluteDy < absoluteDx){
    step = absoluteDx;
  } 
	else {
    step = absoluteDy;
  }												
	
	dx = dx / step;
	dy = dy / step;

  x = x0;
  y = y0;

  for(int i = 1; i < step; i++){
    Screen[ (int)((y * Height) + x)] += 1;
    x = x + dx;
    y = y + dy;
  } 

}

// -------------------------------------------------------------------------
void Bresenham( int x0, int y0, int x1, int y1 ){

  int dx, dy, yi, xi, d, y, x, absoluteDx, absoluteDy;

  dx = x1 - x0;
  dy = y1 - y0;

  absoluteDy = dy;
  absoluteDx = dx;

  yi = 1;
  xi = 1;

  if(dy < 0){
    yi = -1;
    dy = dy * -1;
  }

  if(dx < 0){
    xi = -1;
    dx = dx * -1;
  }

  y = y0;
  x = x0;

  if((dx > dy) && (absoluteDx > 0) && (absoluteDy > 0)){
    d = (2 * dy) - dx;

    for(float x = x0; x < x1; x++){
      Screen[ (int)(( y * Height ) + x) ] += 2;

      if(d > 0){
        y = y + yi;
        d = d - (2 * dx);
      }
      d = d + (2 * dy);
    }
  }

  else if ((dx < dy) && (absoluteDx > 0) && (absoluteDy > 0)) {
    d = (2 * dx) - dy;

    for(float y = y0; y < y1; y++){
      Screen[ (int)(( y * Height ) + x) ] += 2;

      if(d > 0){
        x = x + xi;
        d = d - (2 * dy);
      }
      d = d + (2 * dx);
    }
  }

  else if((dx < dy) && (absoluteDy > 0) && (absoluteDx < 0)){

    d = (2 * dy) - dx;

    for(float y = y0; y < y1; y++){
      Screen[ (int)(( y * Height ) + x) ] += 2;

      if(d > 0){
        x = x + xi;
        d = d - (2 * dy);
      }
      d = d + (2 * dx);
    }
  }

  else if((dx > dy) && (absoluteDy > 0) && (absoluteDx < 0)){

    d = (2 * dy) - dx;

    for(float x = x0; x > x1; x--){
      Screen[ (int)(( y * Height ) + x) ] += 2;

      if(d > 0){
        y = y + yi;
        d = d - (2 * dx);
      }
      d = d + (2 * dy);
    }
  }

  else if((dx > dy) && (absoluteDy < 0) && (absoluteDx < 0)){

    d = (2 * dy) - dx;

    for(float x = x0; x > x1; x--){
      Screen[ (int)(( y * Height ) + x) ] += 2;

      if(d > 0){
        y = y + yi;
        d = d - (2 * dx);
      }
      d = d + (2 * dy);
    }
  }

  else if((dx < dy) && (absoluteDy < 0) && (absoluteDx < 0)){

    d = (2 * dy) - dx;

    for(float y = y0; y > y1; y--){
      Screen[ (int)(( y * Height ) + x) ] += 2;

      if(d > 0){
        x = x + xi;
        d = d - (2 * dy);
      }
      d = d + (2 * dx);
    }
  }

  else if((dx < dy) && (absoluteDy < 0) && (absoluteDx > 0)){
    d = (2 * dy) - dx;

    for(float y = y0; y > y1; y--){
      Screen[ (int)(( y * Height ) + x) ] += 2;

      if(d > 0){
        x = x + xi;
        d = d - (2 * dy);
      }
      d = d + (2 * dx);
    }
  }

  else {
    d = (2 * dy) - dx;

    for(float x = x0; x < x1; x++){
      Screen[ (int)(( y * Height ) + x) ] += 2;

      if(d > 0){
        y = y + yi;
        d = d - (2 * dx);
      }
      d = d + (2 * dy);
    }
  }
}

// -------------------------------------------------------------------------
void Init( ){
  glClearColor( 0.2, 0.2, 0.2, 0.0 );
  gluOrtho2D( 0.0f, float( Width ), 0.0f, float( Height ) );
}

// -------------------------------------------------------------------------
void MouseCbk( int button, int state, int x, int y ){
  if(button == GLUT_LEFT_BUTTON && state == GLUT_UP){
    if(NumberOfClicks == 0){
      ClickX0 = x;
      ClickY0 = Height - y;
      NumberOfClicks++;
      std::memset( Screen, 0, Width * Height );
    }

    else{
      ClickX1 = x;
      ClickY1 = Height - y;

      DDA( ClickX0, ClickY0, ClickX1, ClickY1 );
      Bresenham( ClickX0, ClickY0, ClickX1, ClickY1 );

      NumberOfClicks = 0;
    } // end if
    glutPostRedisplay( );
  } // end if
}

// -------------------------------------------------------------------------
void DisplayCbk( ){
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glPointSize( 3 );
  glBegin( GL_POINTS );
  unsigned int k = 0;
  for( unsigned int j = 0; j < Height; ++j ){
    for( unsigned int i = 0; i < Width; ++i ){
      if( Screen[ k ] > 0 ){
        if( Screen [k] == 1 ){
          glColor3f( 1, 0, 0 );
        } 
        else if( Screen[k] == 2 ){
          glColor3f( 0, 1, 0 );
        } 
        else{
          glColor3f( 0, 0, 1 );
        }             
        glVertex2i( i, j );
      } // end if
      k++;
    } // end for
  } // end for
  glEnd( );

  glutSwapBuffers( );
}

// -------------------------------------------------------------------------
int main( int argc, char* argv[] ){
  if( argc < 3 ){
    std::cerr << "Usage: " << argv[ 0 ] << " width height" << std::endl;
    return( 1 );
  } // end if

  Width = std::atoi( argv[ 1 ] );
  Height = std::atoi( argv[ 2 ] );
  NumberOfClicks = 0;
  Screen = new unsigned char[ Width * Height ];

  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
  glutInitWindowPosition( 50, 50 );
  glutInitWindowSize( Width, Height );
  glutCreateWindow( "Line experiments" );

  glutDisplayFunc( DisplayCbk );
  glutMouseFunc( MouseCbk );

  Init( );
  glutMainLoop( );

  delete Screen;

  return( 0 );
}

// eof - line_experiments.cxx
