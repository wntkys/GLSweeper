#pragma once

#include <inttypes.h>

#include "texture.h"
#include "lineProgramm.h"

#include "squareProgramm.h"

typedef struct TextureProg_s {
    char* dataAndCommands;
    uint8_t length;
    char* name;
} TextureProg_t;

void TextureProg_run( TextureProg_t* in, Texture_t* out );