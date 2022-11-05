#include "lineProgramm.h"

void _DataForLine_Private_plotLineLow(uint_fast16_t x0, uint_fast16_t y0, uint_fast16_t x1, uint_fast16_t y1, uint64_t rgba, Texture_t* out);
void _DataForLine_Private_plotLineHigh(uint_fast16_t x0, uint_fast16_t y0, uint_fast16_t x1, uint_fast16_t y1, uint64_t rgba, Texture_t* out);

void DataForLine_draw( DataForLine_t* in, Texture_t* out ) {
    if ( abs( in->y1 - in->y0 ) < abs( in->x1 - in->x0 ) ) {
        if ( in->x0 > in->x1 )
            _DataForLine_Private_plotLineLow( in->x1, in->y1, in->x0, in->y0, in->rgba, out );
        else
            _DataForLine_Private_plotLineLow( in->x0, in->y0, in->x1, in->y1, in->rgba, out );
    } else {
        if ( in->y0 > in->y1 )
            _DataForLine_Private_plotLineHigh( in->x1, in->y1, in->x0, in->y0, in->rgba, out );
        else
            _DataForLine_Private_plotLineHigh( in->x0, in->y0, in->x1, in->y1, in->rgba, out );
    }
}

void _DataForLine_Private_plotLineLow(uint_fast16_t x0, uint_fast16_t y0, uint_fast16_t x1, uint_fast16_t y1, uint64_t rgba, Texture_t* out) {
    uint_fast16_t dx = x1 - x0;
    uint_fast16_t dy = y1 - y0;
    uint_fast16_t yi = 1;
    if ( dy < 0 ) {
        yi = -1;
        dy = -dy;
    }
    uint_fast16_t D = (2 * dy) - dx;
    uint_fast16_t y = y0;

    for (uint_fast16_t x = x0; x < x1; x++) {
        *( uint64_t* )( out->data + ( ( ( x * out->sizeY ) + y ) ) ) = rgba;
        if ( D > 0 ) {
            y = y + yi;
            D = D + ( 2 * ( dy - dx ) );
        }
        else
            D = D + 2 * dy;
    }
}

void _DataForLine_Private_plotLineHigh(uint_fast16_t x0, uint_fast16_t y0, uint_fast16_t x1, uint_fast16_t y1, uint64_t rgba, Texture_t* out) {
    uint_fast16_t dx = x1 - x0;
    uint_fast16_t dy = y1 - y0;
    uint_fast16_t xi = 1;
    if ( dx < 0 ) {
        xi = -1;
        dx = -dx;
    }
    uint_fast16_t D = (2 * dy) - dx;
    uint_fast16_t x = x0;

    for (uint_fast16_t y = y0; y < y1; y++) {
        *( uint64_t* )( out->data + ( ( ( x * out->sizeY ) + y ) ) ) = rgba;
        if ( D > 0 ) {
            x = x + xi;
            D = D + ( 2 * ( dy - dx ) );
        }
        else
            D = D + 2 * dy;
    }
}