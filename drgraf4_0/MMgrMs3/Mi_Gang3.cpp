// Mouse.cpp : implementation file
//


#include "stdafx.h" 


#include "MsMath.h" 
/////////////////////
#include "drgraf.h"
#include "drgradoc.h"
/////////////////////
#include "ObjMgr.h"
#include "DListMgr.h"
///////////////////// elements
#include "Def_Elem.h"
#include "DrFE0D.h"
#include "DrFE1D.h"
#include "DrFE2D.h"
#include "DrEdge.h"
/////////////////////
#include "MI_GangN.h"
#include "MI_GangC.h"
#include "MI_GangP.h"
#include "MI_GangS.h"
#include "MI_Gang0.h" 
/////////////////////
#include "MI_Gang3.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////
IMPLEMENT_SERIAL(CMI_Gang3,CMI_Gang2,1)
#define new	DEBUG_NEW
#define	BUFF_SIZE			1024
/////////////////////////////////////////////////////////////////////////////
CMI_Gang3::CMI_Gang3()
{
}

CMI_Gang3::~CMI_Gang3()
{
}
////////////////////////////////////////////////////////////
int CMI_Gang3::Regen_MESH3D_Elements(CDrObject* pMeshNew,CDrObject* pMeshOld)		
{
	int nResult;
	////////////
	/////////
	return 0;
}


////////////////////////////////////////////////////////////
void CMI_Gang3::Serialize(CArchive& ar)
{

	CMI_Gang2::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CMI_Gang3:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CMI_Gang3:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
}
///////////////////////////////////// end of Module //////////////////////		
