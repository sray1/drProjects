#ifndef _STR_GEN_H
#define _STR_GEN_H 


#include <afxtempl.h>	// CList
#include "DListMgr.h"	// List
/////////////////////////////////////////////////////////////////////////////
/*
//////////////////////////////	
//			Moved to Str_Mesh	  		
//////////////////////////////	
#define MAX_CORNERS_1D		2
#define MAX_CORNERS_2D		4
#define MAX_CORNERS_3D		21
#define MAX_EDGENODE_MID	2	// inter Nodes o----M1----M2----o : 2= Cubic 
#define MAX_EDGES_1D		1
#define MAX_EDGES_2D		4
#define MAX_EDGES_3D		12
#define MAX_FACES_2D		1
#define MAX_FACENODE_MID	4	// inter Nodes o-----o-----o----o : 4= Cubic 
								// inter Nodes o----M4-<---M3----o : CounterClockwise 
								// inter Nodes o----M1-->-M2----o :	from Outside  
								// inter Nodes o-----o-----o----o :  
#define MAX_FACES_3D		6
#define MAX_SOLIDNODE_MID	4	// : 4= Cubic 
#define	MAX_LOADS			4
*/
//////////////////////////////////////////////////////////////////// 0D
//******* Node variables / data structure *************/
typedef struct nodecard
	{
		UINT		ElNum;			// mesh node number
		CString		id;     		// Node Card
		CString		sup_id;         // pad 10 char field
		CString		nid_r;
		long		x;
		long		y;
		long		z;
		BOOL		bnid_c;			// control Node
		BOOL		bnid_m;			// mesh node
		CString		load_id;
		CString		disp_id;
		UINT		num_min;		// band-minimized
	}NODECARD, FAR *pNODECARD;
//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////	  		
#endif
