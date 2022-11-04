#pragma once
#include <stdbool.h>
#include <inttypes.h>
#include <cglm/cglm.h>
#include <GL/gl3w.h>
#include "shader.h"
#include "globals.h"

 float quadVertices[] = {
    // координаты  // цвета
    -0.8f,  0.8f,  0.0f, 1.0f, 0.0f,
     0.8f, -0.8f,  0.0f, 1.0f, 0.0f,
    -0.8f, -0.8f,  0.0f, 1.0f, 0.0f,
    -0.8f,  0.8f,  0.0f, 1.0f, 0.0f,
     0.8f, -0.8f,  0.0f, 1.0f, 0.0f,   
     0.8f,  0.8f,  0.0f, 1.0f, 0.0f,

    -1.0f,  1.0f,  1.0f, 0.0f, 0.0f,
     1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
    -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
    -1.0f,  1.0f,  1.0f, 0.0f, 0.0f,
     1.0f, -1.0f,  1.0f, 0.0f, 0.0f,   
     1.0f,  1.0f,  1.0f, 0.0f, 0.0f

	  		
};

typedef struct {
    char* actual;
    char* gui;
    
    uint16_t sizeX;
    uint16_t sizeY;
    GLuint VBO;
    GLuint EBO;
    GLuint VAO;
    GLuint prog;

    struct {
        vec2* shifts;
        float size;
    } m_Buffers4GL;
} MineMap;

void MineMap_assignSize( MineMap* m, uint16_t sizeX, uint16_t sizeY ) {
    m->sizeX = sizeX;
    m->sizeY = sizeY;
    m->actual = malloc( sizeof( char ) * sizeX * sizeY );
    m->gui = malloc( sizeof( char ) * sizeX * sizeY );
    memset( m->gui, 0, sizeX * sizeY );
}

void MineMap_gen( MineMap* m, uint16_t atX, uint16_t atY, uint16_t mineCount ) {
    
}

void MineMap_renderPrepare( MineMap* m ) {
    m->prog = getBasicProgram();
    glGenVertexArrays(1, &m->VAO);
    glBindVertexArray(m->VAO);

    glGenBuffers(1, &m->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m->VBO);

    glBufferData(
        GL_ARRAY_BUFFER, sizeof(quadVertices),
        quadVertices, GL_STATIC_DRAW
    );
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 2 * sizeof(GLfloat));
    glEnableVertexAttribArray(0); 
    glEnableVertexAttribArray(1);
}

void MineMap_render(MineMap* m, vec4 pos) {
    
    vec2* shifts = malloc( sizeof( vec2 ) * m->sizeX * m->sizeY );
    for( int i = 0; i < m->sizeX; i++ ) {
        for( int j = 0; j < m->sizeY; j++ ) {
            shifts[ i * m->sizeY + j ][ 0 ] = ( float ) i / (m->sizeX - 1) * 1.5 - 0.75;
            shifts[ i * m->sizeY + j ][ 1 ] = ( float ) j / (m->sizeY - 1) * 1.5 - 0.75;
        }
    }
    glUseProgram( m->prog );
    glProgramUniform2fv( m->prog, glGetUniformLocation( m->prog, "offsets" ), m->sizeX * m->sizeY, shifts );
    glProgramUniform1f( m->prog, glGetUniformLocation( m->prog, "aspectRatio" ), _Globals.aspectRatio );
    glProgramUniform1f( m->prog, glGetUniformLocation( m->prog, "cellSize" ), 0.049f );
    //finaly render instanced
    glBindVertexArray( m->VAO );
    //printf( "%i\n", m->sizeX * m->sizeY );
    glDrawArraysInstanced(GL_TRIANGLES, 0, 12, m->sizeX * m->sizeY);   
}

void MineMap_free( MineMap* m ) {
    free( m->actual );
    free( m->gui );
    free( m->m_Buffers4GL.shifts );
    free( m );
}