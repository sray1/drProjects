#ifndef _STAL_EXT_H
#define _STAL_EXT_H 


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
	
extern STALTYPES FAR StaLTypes[];
extern int nMax_StaLTypes;
////////////////////////////
#endif

