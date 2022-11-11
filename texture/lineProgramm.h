#pragma once

#include <math.h>
#include <inttypes.h>
#include <GL/gl3w.h>

#include "texture.h"

typedef struct DataForLine_s {
    uint32_t rgba;
    uint_fast16_t x0, y0, x1, y1;
} DataForLine_t;

void DataForLine_draw( DataForLine_t* in, Texture_t* out );