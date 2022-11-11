#include "mineMap.h"

 float quadVertices[] = {
    // координаты  // цвета
    -1.0f,  1.0f,  0.0f, 1.0f,
     1.0f, -1.0f,  1.0f, 0.0f,
    -1.0f, -1.0f,  0.0f, 0.0f,
    -1.0f,  1.0f,  0.0f, 1.0f,
     1.0f, -1.0f,  1.0f, 0.0f,   
     1.0f,  1.0f,  1.0f, 1.0f
};


void MineMap_assignSize( MineMap_t* m, uint16_t sizeX, uint16_t sizeY ) {
    m->sizeX = sizeX;
    m->sizeY = sizeY;
    m->actual = malloc( sizeof( char ) * sizeX * sizeY );
    m->gui = malloc( sizeof( char ) * sizeX * sizeY );
    memset( m->gui, 0, sizeX * sizeY );
}

void MineMap_gen( MineMap_t* m, uint16_t atX, uint16_t atY, uint16_t mineCount ) {
    
}

void MineMap_renderPrepare( MineMap_t* m, Texture_t* t ) {
    m->tex = Texture_toGL( t );
    m->prog = getBasicProgram();
    glGenVertexArrays(1, &m->VAO);
    glBindVertexArray(m->VAO);

    glGenBuffers(1, &m->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m->VBO);

    glBufferData(
        GL_ARRAY_BUFFER, sizeof(quadVertices),
        quadVertices, GL_STATIC_DRAW
    );
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof( GLfloat ), 0 ); // pos
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof( GLfloat ), ( void* ) ( 2 * sizeof( GLfloat ) ) ); // textureCoords
    glEnableVertexAttribArray(0); 
    glEnableVertexAttribArray(1);
}

void MineMap_render(MineMap_t* m, vec4 pos) {
    
    vec2* shifts = malloc( sizeof( vec2 ) * m->sizeX * m->sizeY );
    for( int i = 0; i < m->sizeX; i++ ) {
        for( int j = 0; j < m->sizeY; j++ ) {
            shifts[ i * m->sizeY + j ][ 0 ] = ( float ) i / (m->sizeX - 1) * 1.5 - 0.75;
            shifts[ i * m->sizeY + j ][ 1 ] = ( float ) j / (m->sizeY - 1) * 1.5 - 0.75;
        }
    }
    glUseProgram( m->prog );
    glProgramUniform2fv( m->prog, glGetUniformLocation( m->prog, "offsets" ), m->sizeX * m->sizeY, ( GLfloat* )&shifts[0] );
    glProgramUniform1f( m->prog, glGetUniformLocation( m->prog, "aspectRatio" ), G_Globals.aspectRatio );
    glProgramUniform1f( m->prog, glGetUniformLocation( m->prog, "cellSize" ), 0.05f );
    //finaly render instanced
    glBindVertexArray( m->VAO );
    glDrawArraysInstanced(GL_TRIANGLES, 0, 12, m->sizeX * m->sizeY);   
}

void MineMap_free( MineMap_t* m ) {
    free( m->actual );
    free( m->gui );
    free( m->m_Buffers4GL.shifts );
    free( m );
}