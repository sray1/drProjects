// Curve.cpp : implementation file
//


#include "stdafx.h"
/*
#include <Float.h>		// MSVC/INC for DBL_MAX,DBL_MIN
                  
/////////////////////
#include "Def_Type.h"
#include "DListMgr.h"
///////////////////// DrawOperationObjs
#include "Def_3D.h"        
#include "3DMath.h" 
#include "XForm.h"
////////////////////// ElemObjs
#include "Def_IGen.h"
#include "Ext_Cur.h"
#include "DrNode.h"
/////////////////////
#include "Curve.h"
#include "Curve_1.h"
#include "Curve_2.h"
#include "Curve_3.h"
////////////////////
*/
#include "Def_Objs.h"
#include "Def_Auxi.h"
#include "Ext_Auxi.h"

#include "AuxCur.h"
////////////////////

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CAuxCur
IMPLEMENT_SERIAL(CAuxCur, CDrCurve,1)
/*
BEGIN_MESSAGE_MAP(CAuxCur, CDrObject)
	//{{AFX_MSG_MAP(CAuxCur)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/ 
/////////////////////////////////////
#define	new DEBUG_NEW
#define	BUFF_SIZE	1024
/////////////////////////////////////////////////////////////////////////////
CAuxCur::CAuxCur()
{  
    //////////////////////////////	
    SetObjectType((int)AUXCUR);
    SetElemType((int)AUXI_OBJECT);          //
	//////////////////////////////	
} 

CAuxCur::~CAuxCur()
{  
    	
	///////////////////////////////// prepare
	CDrCurve::ReadyToDelete();
	///////////////////////////
}
void CAuxCur::SetObjectInfo(CDrObject* pObject)
{

	CDrCurve::SetObjectInfo(pObject);
	///////////////////////////////////   
	CAuxCur* pAdd = (CAuxCur*) pObject;
	///////////////////////////////////////////////////////// CURVEINFO
	//////////																																	
	return;
}		

void CAuxCur::GetObjectInfo(CDrObject* pObject)
{
	
	CDrCurve::GetObjectInfo(pObject);
	///////////////////////////////////   
	CAuxCur* pAdd = (CAuxCur*) pObject;
    ///////////////////////////////////////////////////////////////// CURVE 
	//////////																																	
	return;
}		

void CAuxCur::DoDataView(CDC* PtrDC, int y)
{

	CString strCard;
	//////////////////////
	Pack_drPipe(&strCard);
	//////////////////////////// 
	PtrDC->TextOut(0,y,strCard);
	////////////////////////////
	return;
} 

void CAuxCur::Pack_drPipe(CString* pstrCard)
{

   	static CString name;
   	/////////////////////////
   	for (int i = 0;i<nMax_AuxiTypes;i++)
   		if(AxTypes[i].num == AUXCUR) 
   		{
   			name = AxTypes[i].ObjName;
   			break;
   		}	
   /////////////////////////
   CString pad = " "; 
   ////////////////////////
//	m_CurveCard.bValve  = FALSE;  
   AddStr(pstrCard,&name,5); 
   AddStr(pstrCard,&pad,5);
	//////////// 
	return;

}   
///////////////////////////////////////////////////////////////////////////////////
void CAuxCur::Serialize(CArchive& ar)
{

	CDrCurve::Serialize( ar);              // must call base class Serializer
	//////////////////////////////////////
	
	if (ar.IsStoring())
	{
		TRACE( " AuxCur   :Storing\n");	// TODO: add loading code here
 	}
	else
	{
		TRACE( " AuxCur   :Loading\n");	// TODO: add loading code here
	}        
	////////////////////////

}
////////////////////// END OF MODULE ///////////////////////

