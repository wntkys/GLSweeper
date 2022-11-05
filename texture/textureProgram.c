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
        break;}
        }
    } while ( true );
    
}