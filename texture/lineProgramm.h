#pragma once

#include <math.h>
#include <inttypes.h>

#include "texture.h"

typedef struct DataForLine_s {
    uint64_t rgba;
    uint_fast16_t x0, y0, x1, y1;
} DataForLine_t;

void DataForLine_draw( DataForLine_t* in, Texture_t* out );