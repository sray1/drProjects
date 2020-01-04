#ifndef _EXT_SPEC_H
#define _EXT_SPEC_H 
////////////////////

typedef struct sptypes 
	{
		char*   	ObjName;  	// internal name
		int			num;   		// number associated with object
		int			type;  		// 0 	= tool
								// 1	= specs
								// 2	= operation
		char*		otherName; 	// name,if needed
	}SPTYPES;
extern SPTYPES FAR SpTypes[];
extern int nMax_SpecTypes;
//////////////////////////
#endif
