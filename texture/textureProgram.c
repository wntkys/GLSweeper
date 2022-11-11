#include "textureProgram.h"


void TextureProg_run( TextureProg_t* in, Texture_t* out ) {
    uint16_t commandsShift = 0;
    char command;
    do {
        command = in->dataAndCommands[ commandsShift ];
        commandsShift++;
        switch (command)
        {
        case 0: { //end
            return;
        break;}
        case 1: { //line
            DataForLine_t* data = ( DataForLine_t* )( in->dataAndCommands + commandsShift );
            DataForLine_draw( data, out ); 
            commandsShift += sizeof( DataForLine_t );
        break;}
        case 2: {//square
            DataForSquare_t* data = ( DataForSquare_t* )( in->dataAndCommands + commandsShift );
            DataForSquare_draw( data, out ); 
            commandsShift += sizeof( DataForSquare_t );
        break;}
        }
    } while ( true );
    
}