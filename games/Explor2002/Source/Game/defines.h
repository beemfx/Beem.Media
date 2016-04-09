#ifndef __DEFINES_H__
#define __DEFINES_H__

#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }

#define NUM_TILES 3
#define NUM_TILE_SETS 2


#define SCREEN_WIDTH 640 //pixels wide
#define SCREEN_HEIGHT 480 //pixels high
#define VIEW_WIDTH 640
#define VIEW_HEIGHT 480
#define COLOR_DEPTH 16 //number of bits to store colors
#define BACK_FUFFER_COUNT 1
#define TRANSPARENT_COLOR RGB(255,0,255) //transparent color

enum Direction{NORTH=0, EAST, SOUTH, WEST};
enum MoveType{FORWARD, BACKWARD, STRAFE_LEFT, STRAFE_RIGHT};
enum TurnType{LEFT, RIGHT};

enum TileType{WALL, DOOR};

#define TFRONT_SIZE 25

#endif