#pragma once
#include <cglm/cglm.h>
#include <inttypes.h>
#include <GL/gl3w.h>

typedef struct Texture_s {
    uint32_t* data;
    uint16_t sizeX, sizeY;
} Texture_t;

void Texture_init( uint16_t sizeX, uint16_t sizeY, Texture_t* out );;

void Texture_free( Texture_t* in );

GLuint Texture_toGL( Texture_t* in );