// Mouse.cpp : implementation file
//


#include "stdafx.h" 

#include "drgraf.h"
#include "drgrafrm.h"
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
///////////////////// dialogMgr
//#include "VDlgMgr.h"  
//////////////////////
#include "Vu_Rot.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
////////////////////////////////////
IMPLEMENT_SERIAL(CVu_Rot,CMouse,1)
/////////////////////////////////////////////////////////////////////////////
CVu_Rot::CVu_Rot()
{

}

CVu_Rot::~CVu_Rot()
{
}

int CVu_Rot::Do_VU_Rotate()
{
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	//////////////////////////////////////////////////////////////////
	pDoc->SetModifiedFlag();
	pDoc->UpdateAllViews(NULL);
	///////////////////////////////
	return 0;
}	 
	
/////////////////////////////////////////////////////////////////////////////////////// F_M
UINT CVu_Rot::ReSetToolID(UINT OperID)
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCur;
	////////////////
	CString str;
	UINT ID;
	/////////////////////////////
	switch(OperID)
	{
		//////////////////////////////////////////// Edit
		case VU_ROTATE:

			//////////////////////////////////////////// TaskID
			strCur = "Ready for Rotating the View@";
			/////////////////////////////////////
			pWnd->SetDrawBoxStatus(FALSE);
			///////////////////////////// String
			str = "ROTATE";
			pWnd->SetstrOperID(str);
			////////////////////////
			ID = VU_ROTATE;

			return ID;
			//////////////////
	}
	return UNONE;
}

void CVu_Rot::Serialize(CArchive& ar)
{

	CMouse::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" Vu_Rot:    Storing\n");	
		

	}
	else
	{
		TRACE(" Vu_Rot:    Loading\n");	

	
	}        
}

///////////////////////////////////// end of Module //////////////////////		


