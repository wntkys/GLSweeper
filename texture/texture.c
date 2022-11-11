#include "texture.h"

void Texture_init( uint16_t sizeX, uint16_t sizeY, Texture_t* out ) {
    out->sizeY = sizeY;
    out->sizeX = sizeX;
    out->data = ( uint32_t* )malloc( sizeX * sizeY * sizeof( uint32_t ) );
    memset( out->data, 0, sizeY * sizeX * sizeof(uint32_t) );
}

void Texture_free( Texture_t* in ) {
    free( in->data );
    free( in );
}

GLuint Texture_toGL( Texture_t* in ) {
    uint32_t texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, in->sizeX,
                 in->sizeY, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 in->data);
    glGenerateMipmap(GL_TEXTURE_2D);
    return texture;
}