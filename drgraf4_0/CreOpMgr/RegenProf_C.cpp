// Mouse.cpp : implementation file
//


#include "stdafx.h" 

#include "Def_MouseAct.h"
#include "drgraf.h"
#include "drgrafrm.h"
#include "drgradoc.h"
#include "ObjMgr.h"
///////////////////// IGens
#include "Def_IGen.h"
/////////////////////
#include "MI_CProf.h" 
//////////////////////
#include "RegenProf_C.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
////////////////////////////////////
IMPLEMENT_SERIAL(CRegenProf_C,CMouse,1)
/////////////////////////////////////////////////////////////////////////////
CRegenProf_C::CRegenProf_C()
{
}

CRegenProf_C::~CRegenProf_C()
{
}

int CRegenProf_C::ReGen_EditedProf_C_Controls(CDrProf_C* pEditedProfile)
{
/*
	int nDegree,nDim,nCon_BZ;
	BOOL bClosed;
	//////////////////////////////////////////////////////////// Prepare
	CDrCurve* pCurve = pEditedProfile->GetCurve();
	///
	nDim	= pCurve->GetnDim_S();
	bClosed	= pCurve->IsClosed_S();
	nDegree	= pCurve->GetOrder_S() - 1;
	nCon_BZ = pCurve->GetnCon_BZ_S();
	///
	pWORLD  pCon_BZ = new WORLD [nCon_BZ]; 	
	pDOUBLE pWts_BZ = new double[nCon_BZ];
	///
	CMI_CProf MI_CProf;
	MI_CProf.GoDoIt(pEditedProfile,pCon_BZ,pWts_BZ,nCon_BZ,nDegree,bClosed,nDim);
	MI_CProf.SaveCoordsWtsinOldFoggies(pEditedProfile,pCon_BZ,pWts_BZ,nCon_BZ);
	//////
	delete [] pCon_BZ;
//	delete [] pWts_BZ;	// done in DrCurve delete
	////////////
	return 0;
*/
	/////////////////////////////////////////////// Circular Component Present
	// nCon_BZ might have been Changed because of 
	// Conics( eg. circle) number of segment change
	// so Create ALL New Control Nodes
	///////////////////////////////////////////////
	CMI_CProf MI_CProf;
	MI_CProf.GoDoIt(pEditedProfile);
	////////////////////////////////
	return MA_OK;
}

void CRegenProf_C::Serialize(CArchive& ar)
{

	CMouse::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" RegenProf_C:    Storing\n");	
		

	}
	else
	{
		TRACE(" RegenProf_C:    Loading\n");	

	
	}        
}

///////////////////////////////////// end of Module //////////////////////		


