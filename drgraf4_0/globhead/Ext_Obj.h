#ifndef _EXT_OBJ_H
#define _EXT_OBJ_H 


typedef struct objtypes 
	{
		LPCTSTR   	Name;  		// internal name
		UINT		ID;   		// number associated with element
	}OBJTYPES;
	
extern OBJTYPES FAR ObjTypes[];
extern int nMax_ObjectTypes;
////////////////////////////
#endif

