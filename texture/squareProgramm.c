#include "squareProgramm.h"

void DataForSquare_draw( DataForSquare_t* in, Texture_t* out ){
    uint_fast16_t x0 = in->x0;
    uint_fast16_t x1 = in->x1;
    uint_fast16_t y0 = in->y0;
    uint_fast16_t y1 = in->y1;

    //for( int i = y0; i < y1; i++ ) {
    //    memcpy( &out->data[ out->sizeY * x0 + i ], &in->rgba, sizeof( uint64_t ) );
    //}
    //for( int i = x0 + 1; i < x1; i++ ) {
    //    memcpy( &out->data[ ( out->sizeY ) * i  + y0 ], &out->data[ out->sizeY * x0 + y0 ], sizeof( uint64_t ) * ( y1 - y0 ) );
    //}
    for( int i = x0; i < x1; i++ ) {
        for( int j = y0; j < y1; j++ ) {
            out->data[ ( out->sizeY ) * i  + j ] = in->rgba;
        }
    }
    
}