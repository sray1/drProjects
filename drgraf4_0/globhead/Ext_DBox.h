#ifndef _DBEXTERN_H
#define _DBEXTERN_H 
////////////////////////
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

extern DBTYPES FAR DbTypes[];
extern int nMax_DBoxTypes;
extern AFX_EXTENSION_MODULE NEAR extensionDBox_DLL;
/////////////////////////// 
#endif
