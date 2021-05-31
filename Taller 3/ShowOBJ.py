## =========================================================================
## @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
## =========================================================================
## Install OpenGL: pip3 install PyOpenGL PyOpenGL_accelerate
## =========================================================================

from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *
from Mesh.MeshAnimal import *
from Mesh.MeshLego import *
from Mesh.MeshRana import *
from Mesh.MeshSkull import *
from Mesh.MeshNave import *
from Mesh.MeshPC import *
from Mesh.MeshEspada import *
from Mesh.MeshArana import *
from Mesh.MeshToilet import *
from Mesh.MeshPerro import *

import math, sys

## -------------------------------------------------------------------------
## Some global variables: DON'T DO THIS IN REAL LIFE APPLICATIONS!!!!
## -------------------------------------------------------------------------
camera_angle  = 0
camera_pos    = 0
camera_height = 0

meshAnimal = MeshAnimal()
meshLego = MeshLego()
meshRana = MeshRana()
meshSkull = MeshSkull()
meshNave = MeshNave()
meshPC = MeshPC()
meshEspada = MeshEspada()
meshArana = MeshArana()
meshToilet = MeshToilet()
meshPerro = MeshPerro()


## -------------------------------------------------------------------------
def init( ):
  global camera_angle, camera_pos, camera_height, mesh

  camera_angle = 0
  camera_height = -300
  camera_pos = meshSkull.m_MaxVertex[ 2 ] * 2

  glClearColor( 0.0, 0.0, 0.0, 0.0 )

  glShadeModel( GL_SMOOTH )
  glLightfv( GL_LIGHT0, GL_POSITION, [ 0.0, 0.0, 0.0, 1.0 ] )
  # glLightfv( GL_LIGHT0, GL_AMBIENT, [ 1.0, 1.0, 1.0, 1.0 ] )
  glLightfv( GL_LIGHT0, GL_DIFFUSE, [ 1.0, 1.0, 1.0, 1.0 ] )

  glEnable( GL_LIGHTING )
  glEnable( GL_LIGHT0 )

  glEnable( GL_DEPTH_TEST )
# end def

## -------------------------------------------------------------------------
def draw( ):
  global camera_angle, camera_pos, camera_height, mesh

  # -- Clear framebuffer
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT )

  # -- Draw stuff
  glMatrixMode( GL_MODELVIEW )
  glLoadIdentity( )

  # -- Camera
  camera_z = camera_pos * math.cos( camera_angle )
  camera_x = camera_pos * math.sin( camera_angle )
  gluLookAt( camera_x, camera_height, camera_z, 0, 0, 0, 0, 1, 0 )

  # -- Scene
  #drawOrthoBase( )

  glPushMatrix()

  glPushMatrix()
  meshSkull.draw2()
  glPopMatrix()

  glPushMatrix()
  glTranslatef(-30, 0, 0)
  glRotate(90, 1, 0, 0)
  meshAnimal.draw2()
  glPopMatrix()

  glPushMatrix()
  glTranslatef(10, 0, 0)
  glScale(0.5, 0.5, 0.5)
  glRotate(90, 1, 0, 0)
  meshLego.draw2()
  glPopMatrix()

  glPushMatrix()
  glTranslatef(50, 0, 0)
  glScale(5.5, 5.5, 5.5)
  glRotate(90, 0, 0, 0)
  meshRana.draw2()
  glPopMatrix()

  glPushMatrix()
  glTranslatef(-70, 10, 0)
  glScale(4.5, 4.5, 4.5)
  glRotate(90, 1, 0, 0)
  meshNave.draw2()
  glPopMatrix()

  glPushMatrix()
  glTranslatef(75, 10, 0)
  glScale(0.5, 0.5, 0.5)
  glRotate(45, 1, 0, 0)
  meshEspada.draw2()
  glPopMatrix()
  
  glPushMatrix()
  glTranslatef(-100, 0, 10)
  glScale(5.5, 5.5, 5.5)
  glRotate(180, 1, 1, 1)
  meshPC.draw2()
  glPopMatrix()

  glPushMatrix()
  glTranslatef(100, 0, 0)
  glScale(0.2, 0.2, 0.2)
  glRotate(90, 1, 0, 0)
  glRotate(45, 0, 6, 0)
  meshArana.draw2()
  glPopMatrix()

  glPushMatrix()
  glTranslatef(-120, 0, 20)
  glScale(1, 1, 1)
  glRotate(90, 0, 0, 0)
  meshToilet.draw2()
  glPopMatrix()

  glPushMatrix()
  glTranslatef(135,0,0)
  meshPerro.draw2()
  glPopMatrix()

  glPopMatrix()

  # -- Prepare next frame
  glutSwapBuffers( )
# end def

## -------------------------------------------------------------------------
def reshape( width, height ):
  # Compute aspect ratio of the new window
  aspect = width
  if height != 0:
    aspect /= height
  # end if

  # Set the viewport to cover the new window
  glViewport( 0, 0, width, height )

  # Compute projection
  glMatrixMode( GL_PROJECTION )
  glLoadIdentity( )
  gluPerspective( 45, aspect, 1e-2, 3000 )
# end def

## -------------------------------------------------------------------------
def keyboard( key, x, y ):
  global camera_angle, camera_pos, camera_height
  if key == b'q' or key == b'Q':
    sys.exit( 0 )
  elif key == b'a' or key == b'A':
    camera_angle -= 1e-1
    glutPostRedisplay( )
  elif key == b'd' or key == b'D':
    camera_angle += 1e-1
    glutPostRedisplay( )
  elif key == b'w' or key == b'W':
    camera_pos -= 1e-1
    glutPostRedisplay( )
  elif key == b's' or key == b'S':
    camera_pos += 1e-1
    glutPostRedisplay( )
  elif key == b'z' or key == b'Z':
    camera_height -= 1
    glutPostRedisplay( )
  elif key == b'c' or key == b'C':
    camera_height += 1
    glutPostRedisplay( )
  # end if
# end def

## -------------------------------------------------------------------------
## ---------------------------------- MAIN ---------------------------------
## -------------------------------------------------------------------------

# Prepare window
glutInit( )
glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH )
glutInitWindowSize( 700, 700 )
glutInitWindowPosition( 0, 0 )
wind = glutCreateWindow( "Museo" )

# Prepare OpenGL
meshSkull.read("./Objetos/Skull/12140_Skull_v3_L2.obj")
meshAnimal.read("./Objetos/Animal/Alien Animal.obj")
meshLego.read("./Objetos/Lego/lego obj.obj")
meshRana.read("./Objetos/Rana/12268_banjofrog_v1_L3.obj")
meshNave.read("./Objetos/Nave/Intergalactic_Spaceship-(Wavefront).obj")
meshPC.read("./Objetos/PC/Lowpoly_Notebook_2.obj")
meshEspada.read("./Objetos/Espada/Sting-Sword-lowpoly.obj")
meshArana.read("./Objetos/Arana/Only_Spider_with_Animations_Export.obj")
meshToilet.read("./Objetos/Toilet/10778_Toilet_V2.obj")
meshPerro.read("./Objetos/Perro/10680_Dog_v2.obj")

init( )

# Associate callbacks
glutDisplayFunc( draw )
glutReshapeFunc( reshape )
glutKeyboardFunc( keyboard )

# Main loop
glutMainLoop( )

## eof - ShowOBJ.py
