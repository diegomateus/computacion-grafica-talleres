## =========================================================================
## @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
## =========================================================================

import math, re
from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *

'''
'''
class MeshLego:
  '''
  '''
  m_Vertices = []
  m_Normals = []
  m_Texture = []
  m_Faces = [ [], [], [] ]
  m_MinVertex = []
  m_MaxVertex = []
  m_GravityCenter = []
  m_List = -1

  '''
  '''
  def __init__( self ):
    pass
  # end def

  '''
  '''
  def read( self, filename ):

    self.m_Vertices = []
    self.m_Normals = []
    self.m_Texture = []
    self.m_Faces = [ [], [], [] ]
    self.m_MinVertex = [ math.inf, math.inf, math.inf ]
    self.m_MaxVertex = [ -math.inf, -math.inf, -math.inf ]
    self.m_GravityCenter = [ 0.0, 0.0, 0.0 ]
    self.m_List = -1

    file_stream = open( filename, "r" )
    lines = file_stream.readlines( )
    for line in lines:
      tokens = list( filter( None, re.split( " |\t|\n", line ) ) )
      if len( tokens ) > 0:
        if tokens[ 0 ] == "v":
          vertex = [ float( t ) for t in tokens[ 1: ] ]
          if len( vertex ) == 3:
            vertex.append( 1.0 )
          # end if
          self.m_Vertices.append( vertex )

          # Update bounding box
          for i in range( 3 ):
            if vertex[ i ] < self.m_MinVertex[ i ]:
              self.m_MinVertex[ i ] = vertex[ i ]
            # end if
            if vertex[ i ] > self.m_MaxVertex[ i ]:
              self.m_MaxVertex[ i ] = vertex[ i ]
            # end if
            self.m_GravityCenter[ i ] += vertex[ i ]
          # end for

        elif tokens[ 0 ] == "vn":
          self.m_Normals.append( [ float( t ) for t in tokens[ 1: ] ] )
        elif tokens[ 0 ] == "vp":
          print( "WARNING: vp!!!" )
        elif tokens[ 0 ] == "vt":
          texture = [ float( t ) for t in tokens[ 1: ] ]
          while len( texture ) < 3:
            texture.append( 0.0 )
          # end while
          self.m_Texture.append( texture )
        elif tokens[ 0 ] == "f":
          ids = [ re.split( "/", t ) for t in tokens[ 1: ] ]
          f = [ [], [], [] ]
          for i in ids:
            while len( i ) < 3:
              i.append( '' )
            # end while
            for j in range( 3 ):
              if i[ j ] != '':
                f[ j ].append( int( i[ j ] ) - 1 )
              # end if
            # end for
          # end for
          self.m_Faces[ 0 ].append( f[ 0 ] )
          self.m_Faces[ 1 ].append( f[ 1 ] )
          self.m_Faces[ 2 ].append( f[ 2 ] )
        elif tokens[ 0 ] == "l":
          print( "WARNING: l!!!" )
        # end if
      # end if
    # end for
    for i in range( 3 ):
      self.m_GravityCenter[ i ] /= float( len( self.m_Vertices ) )
    # end for
  # end def

  '''
  '''
  def draw1( self ):
    faces = self.m_Faces[ 0 ]
    normals = self.m_Faces[ 2 ]
    nFaces = len( faces )
    nNormals = len( normals )
    for i in range( nFaces ):
      f = faces[ i ]
      mode = GL_POINTS
      if len( f ) == 2:
        mode = GL_LINES
      elif len( f ) == 3:
        mode = GL_TRIANGLES
      elif len( f ) == 4:
        mode = GL_QUADS
      elif len( f ) > 4:
        mode = GL_POLYGON
      # end if

      n = None
      if nFaces == nNormals:
        n = normals[ i ]
      # end if

      glMaterialfv( GL_FRONT, GL_AMBIENT, [ 0.3451, 0.5647, 0.8824, 1.0 ] ) #Ka
      glMaterialfv( GL_FRONT, GL_DIFFUSE, [ 0.3451, 0.5647, 0.8824, 1.0 ] ) #Kd
      glMaterialfv( GL_FRONT, GL_SPECULAR, [ 0.3500, 0.3500, 0.3500, 1.0 ] ) #Ks
      glMaterialfv( GL_FRONT, GL_SHININESS, [ 32 ] ) #NS

      glBegin( mode )
      for j in range( len( f ) ):
        if n != None:
          glNormal3fv( self.m_Normals[ n[ j ] ] )
        # end if
        glVertex4fv( self.m_Vertices[ f[ j ] ] )
      # end for
      glEnd( )
    # end for
  # end def

  '''
  '''
  def draw2( self ):
    # Compile list, if needed
    if self.m_List == -1:
      self.m_List = glGenLists( 1 )
      glNewList( self.m_List, GL_COMPILE )
      self.draw1( )
      glEndList( )
    # end if

    # Real draw
    glCallList( self.m_List )
  # end def

# end class

## eof - Mesh.py