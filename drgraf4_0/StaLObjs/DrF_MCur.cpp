// Curve.cpp : implementation file
//


#include "stdafx.h"
                  
/////////////////////
#include "Def_Objs.h"
#include "Def_Stal.h"
#include "Ext_Stal.h"

#include "DrF_MCur.h"
////////////////////

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
////////////////////////////
#define GREEN	RGB(0,255,0)
#define RED		RGB(255,0,0)
/////////////////////////////////////////////////////////////////////////////
// CDrF_MCur
IMPLEMENT_SERIAL(CDrF_MCur, CDrCurve,1)
/*
BEGIN_MESSAGE_MAP(CDrF_MCur, CDrCurve)
	//{{AFX_MSG_MAP(CDrF_MCur)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/ 
/////////////////////////////////////
#define	new DEBUG_NEW
#define	BUFF_SIZE	1024
/////////////////////////////////////////////////////////////////////////////
CDrF_MCur::CDrF_MCur()
{  
    	
    //////////////////////////////	
    SetObjectType((int)CFORCE);
    SetElemType((int)GENR_OBJECT);          //
    //////////////////////////////
	
} 

CDrF_MCur::~CDrF_MCur()
{  
}

void CDrF_MCur::DoDataView(CDC* PtrDC, int y)
{

	CString strCard;
	//////////////////////
	Pack_drPipe(&strCard);
	//////////////////////////// 
	PtrDC->TextOut(0,y,strCard);
	////////////////////////////
	return;
} 

void CDrF_MCur::Pack_drPipe(CString* pstrCard)
{

   	static CString name;
   	/////////////////////////
   	for (int i = 0;i<nMax_StaLTypes;i++)
   		if(StaLTypes[i].num == CFORCE) 
   		{
   			name = StaLTypes[i].ObjName;
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
void CDrF_MCur::Serialize(CArchive& ar)
{

	CDrCurve::Serialize( ar);              // must call base class Serializer
	//////////////////////////////////////
	
	if (ar.IsStoring())
	{
		TRACE( " Force  :Storing\n");	// TODO: add loading code here




 	}
	else
	{
	
		TRACE( " Force   :Loading\n");	// TODO: add loading code here


    //////////////////////////////////////////////        

	}        
	////////////////////////

}
////////////////////// END OF MODULE ///////////////////////

