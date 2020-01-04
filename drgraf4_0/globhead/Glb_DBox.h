#ifndef _DBGLOBAL_H
#define _DBGLOBAL_H
//****************************************************************/ 
#include "Def_Draw.h"
//////////////////////////////////////////// tools can not use EDIT/MOVE	
#include "Def_Spec.h"
////////////////////////////////////////////////////////
typedef struct dbtypes 
	{
		char*   	ObjName;  	// internal name
		int			num;   		// number associated with object
		int			type;  		// 0 	= edit & move tool(for button management)
								// 1	= object that can be edited & moved
								// 2	= independent tool other than move/edit
								// 3	= 3dObject
		char*		otherName; 	// name,if needed
	}DBTYPES;
/////////////////////////////////////////////////////////////////	
DBTYPES	DbTypes[] =
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
        ///////////////
		"GRID",				GRID,			2,		"",
		"ZOOM_SELECT",		ZOOM_SELECT,	2,		"",
    	"DIMENSION",		DIMENSION,		2,		"",
    	"DRFONT",			DRFONT,			2,		"",
    	"BRUSH",			BRUSH,			2,		"",
        ///////////////
		"EDIT",				D_EDIT,			0,		"",
		"MOVE",				D_MOVE,			0,		""
        ///////////////
    	
};
	int	nMax_DBoxTypes = (sizeof (DbTypes)/ sizeof(DbTypes[0]) );  		
/////////////////////////////////
#endif
