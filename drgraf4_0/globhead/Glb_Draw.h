#ifndef _GLB_DRAW_H
#define _GLB_DRAW_H 

#include "Def_Draw.h"
#include "Str_Draw.h"
//****************************************************************/ 
////////////////////////////////////////////////////////
DRTYPES	DrTypes[] =
	{ 
		"",					-1,				-2,		"",
		"LABEL",			LABEL,			1,		"",
		"FREEHAND",			FREEHAND,		1,		"",
		"RECT_FILL",		RECT_FILL,		1,		"",
		"RECT_HOLLOW",		RECT_HOLLOW,	1,		"",
		"RRECT_FILL",		RRECT_FILL,		1,		"",
		"RRECT_HOLLOW",		RRECT_HOLLOW,	1,		"",
		"CIRCLE_FILL",		CIRCLE_FILL,	1,		"",
		"CIRCLE_HOLLOW",	CIRCLE_HOLLOW,	1,		"",
		"LINE",				LINE,			1,		"",
		"AXIS",				AXIS,			1,		"",
		"GRID",				GRID,			1,		""
        ///////////////
    	
};
	int	nMax_DrawTypes = (sizeof (DrTypes)/ sizeof(DrTypes[0]) );  		
///////////////////////////////////
#endif
