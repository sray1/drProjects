#ifndef _STR_1D_H
#define _STR_1D_H 

#include "Str_Gen.h"           // card structures
//////////////////////////////////////////////////////////////////////////
//		"PIPE",				PIPE,		2,		"PIPE",		1,2,	1,	0,
//		"ELBOW",			ELBOW,		2,		"ELBOW",	-1,0,	0,	0,
//		"BEAM",				BEAM,		2,		"BEAM",		1,2,	1,	0,
//		"TRUSS",			TRUSS,		2,		"TRUSS",	1,2,	1,	0,
//////////////////////////////////////////////////////////////////////////
//******** Truss variables/ data structure **************/
typedef struct trusselem 
	{
		///////////////////////
 		CString		nid_k;  //
		UINT		nod_k;
		///////////////////////
    }TRUSSELEM, FAR *pTRUSSELEM;
//******** Beam variables/ data structure **************/
typedef struct beamelem 
	{
		///////////////////////
 		CString		nid_k;  //
		UINT		nod_k;
		///////////////////////
   }BEAMELEM, FAR *pBEAMELEM;
//******** Pipe variables/ data structure **************/
typedef struct pipeelem
	{
		///////////////////////
		CString		siid[MAX_CORNERS_2D]; 
		UINT		si[MAX_CORNERS_2D];		
		BOOL		bValve;
		///////////////////////
    }PIPEELEM, FAR *pPIPEELEM;
//****** Elbow variables/ data structure **************/
typedef struct elbowelem
	{
		///////////////////////
		CString		nid_cc,nid_ti;
		UINT		n_cc,n_ti;
		CString		nid_a,nid_b;
		UINT		n_a,n_b;
		CString		sid_i,sid_j;		// Stress Indices
		UINT		s_i,s_j;		
		///////////////////////
	}ELBOWELEM, FAR *pELBOWELEM;
////////////////////////////////////////////////////////////////////	  		
#endif
