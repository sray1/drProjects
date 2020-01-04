#ifndef _STR_2D_H
#define _STR_2D_H 

#include "Str_Gen.h"           // card structures
///////////////////////////////////////////////////////////////// CARDS
//		"2D Element"
//////////////////////////////////////////////////////////////////////////
//		"2D-QUAD",			QUAD,		2,		"",			2,0,	0,	0,
//		"4 Node-QUAD",		QU_4,		2,		"",			2,4,	4,	0,
//		"8 Node-QUAD",		QU_8,		2,		"",			2,8,	4,	0,
//		"9 Node-QUAD",		QU_9,		2,		"",			2,9,	4,	0,
//		"12 Node-QUAD",		QU_12,		2,		"",			2,12,	4,	0,
//		"16 Node-QUAD",		QU_16,		2,		"",			2,16,	4,	0,
		/////////
//		"2D-TRIANGLE",		TRIANGLE,	2,		"",			2,0,	0,	0,
//		"3 Node-TRIANGLE",	TR_3,		2,		"",			2,3,	3,	0,
//		"6 Node-TRIANGLE",	TR_6,		2,		"",			2,6,	3,	0,
//		"9 Node-TRIANGLE",	TR_9,		2,		"",			2,9,	3,	0,
//		"10 Node-TRIANGLE",	TR_10,		2,		"",			2,10,	3,	0,
		/////////
//		"PLATE",			PLATE,		2,		"",			2,0,	0,	0,
		/////////
//		"THIN SHELL",		SHELL,		2,		"",			2,0,	0,	0,
////////////////////////////////////////////////////////////////////	  		
//******** Truss variables/ data structure **************/
typedef struct quad 
	{
		///////////////////////
 		CString		nid_k;  //
		UINT		nod_k;
		///////////////////////
    }QUADELEM, FAR *pQUADELEM;
////////////////////////////////////////////////////////////////////	  		
#endif
