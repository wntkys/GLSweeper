#pragma once

#include <stdbool.h>
#include <inttypes.h>
#include <cglm/cglm.h>
#include <GL/gl3w.h>

#include "../common/shader.h"
#include "../common/globals.h"
#include "../texture/texture.h"

typedef struct MineMap_s {
    char* actual;
    char* gui;
    
    uint16_t sizeX;
    uint16_t sizeY;
    GLuint VBO;
    GLuint EBO;
    GLuint VAO;
    GLuint prog;
    GLuint tex;

    struct {
        vec2* shifts;
        float size;
    } m_Buffers4GL;
} MineMap_t;

void MineMap_assignSize( MineMap_t* m, uint16_t sizeX, uint16_t sizeY );

void MineMap_gen( MineMap_t* m, uint16_t atX, uint16_t atY, uint16_t mineCount );

void MineMap_renderPrepare( MineMap_t* m, Texture_t* t );

void MineMap_render(MineMap_t* m, vec4 pos);

void MineMap_free( MineMap_t* m );