#include <stdlib.h>
#include <inttypes.h>

#include "texture.h"

typedef struct DataForSquare_s {
    uint32_t rgba;
    uint_fast16_t x0, y0, x1, y1;
} DataForSquare_t;

void DataForSquare_draw( DataForSquare_t* in, Texture_t* out );