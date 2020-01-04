#ifndef _GLB_STAL_H
#define _GLB_STAL_H
////////////////////
#include "Def_StaL.h"
///////////////////////////////////////////////////////////// GLOBALS
typedef struct staLtypes 
	{
		char*   	ObjName;  	// internal name
		int			num;   		// number associated with element
		int			type;  		// -1 	= metacard
								// -2   = NONE
								// 0	= element
								// 1	= cardtype
								// 2	= elem+card both 
								// 3	= 3dObject
	}STALTYPES;
/////////////////////////////////////////////////////////////////	
STALTYPES	StaLTypes[] =
	{ 
		"",						-1,			-2,	
		"Curve Force_Moment",		CSTATIC,	2,
		"Patch Force_Moment",		PSTATIC,	2,
		"Solid Force_Moment",		SSTATIC,	2,
		"Force_Moment",				FORCE,		2,
		"Displace_Rotation",		DISPLACE,	2,
		"Pressure Load",			PRESSURE,	2,
		"Thermal Load",				THERMAL,	2,
		"Lump Wts.",				LUMPWT,		2
		///////////////////////////////////////////
	};
	int	nMax_StaLTypes = (sizeof (StaLTypes)/ sizeof(StaLTypes[0]) );  		
/////////////////////////////////////////////////////////////////////////////
#endif 

