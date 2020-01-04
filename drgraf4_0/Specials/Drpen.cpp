// DrPen.cpp : implementation of the CDrPen class
//

#include "stdafx.h"

#include "Def_Type.h"
#include "Def_Objs.h"
/////////////////////
#include "Ext_Spec.h"
#include "Def_Spec.h"

#include "DrPen.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrPen

IMPLEMENT_SERIAL(CDrPen,CDrObject,1)
/*
BEGIN_MESSAGE_MAP(CDrPen,CDrObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CDrPen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
//////////////////////////////////
 
CDrPen::CDrPen()
{
    SetObjectType((int)DRPEN);
    SetElemType((int)SPEC_OBJECT);          //  
	////////////////////////////// Pen	
	int nPenStyleConstants[] = {PS_SOLID,PS_DASH,PS_DOT,PS_DASHDOT,PS_DASHDOTDOT,0};
	CString PenStyleNames[] = {"Solid","Dash","Dot","Dash Dot","Dash Dot Dot",""};
	UINT	nPenStyleNameCount  = sizeof(PenStyleNames)/sizeof(PenStyleNames[0]);
	///////////////////////////////////
	for (UINT i=0;i<nPenStyleNameCount;i++)
	{
		m_PenStyleNames[i] 		= PenStyleNames[i];
		m_nPenStyleConstants[i]	= nPenStyleConstants[i];
	}	
	m_nPenStyleNameCount   = nPenStyleNameCount;
	/////////////////////////////////////////////////////////////////////////////
} 

void CDrPen::ReadDefaultDrPen()
{

	m_nPenStyleIndexDefault		= 0;	
	m_nPenStyleDefault 			= PS_SOLID;
	m_nPenWidthDefault 			= 0;             // 1 pixel
	m_nPenColorDefault 			= RGB(255,0,0);  // Red
	  	

}

void CDrPen::InitDrPen()
{

	////////////////////////////// Pen	
	int nPenStyleConstants[] = {PS_SOLID,PS_DASH,PS_DOT,PS_DASHDOT,PS_DASHDOTDOT,0};
	CString PenStyleNames[] = {"Solid","Dash","Dot","Dash Dot","Dash Dot Dot",""};
	UINT	nPenStyleNameCount  = sizeof(PenStyleNames)/sizeof(PenStyleNames[0]);
	///////////////////////////////////
	for (UINT i=0;i<nPenStyleNameCount;i++)
	{
		m_PenStyleNames[i] 		= PenStyleNames[i];
		m_nPenStyleConstants[i]	= nPenStyleConstants[i];
	}	
	m_nPenStyleNameCount   = nPenStyleNameCount;
    ///////////////////////////////////////////
	m_nPenStyleIndex= m_nPenStyleIndexDefault;	
	m_nPenWidth		= m_nPenWidthDefault;         // user-selected pen style (width) 
	m_nPenStyle		= m_nPenStyleDefault;
	m_nPenColor		= m_nPenColorDefault;
	m_nPenWidthOld	= m_nPenWidth;         
	m_nPenStyleOld	= m_nPenStyle;
	m_nPenColorOld	= m_nPenColor;
	//////////////////////////////
	ReplacePen();
 	/////////////
    
}
	
void CDrPen::SetObjectInfo(CDrObject* pObject)
{
	
	CDrPen* pDrPen = (CDrPen*) pObject;
	//////////////////////////////////////////////////
	m_nElemType			= pDrPen->m_nElemType;
	m_nObjectType		= pDrPen->m_nObjectType; 
	m_nObjectNo			= pDrPen->m_nObjectNo;
	///////////////////////////////////////////////// 
	m_nPenStyleIndex	= pDrPen->m_nPenStyleIndex;	
	m_nPenWidth			= pDrPen->m_nPenWidth;          
	m_nPenStyle			= pDrPen->m_nPenStyle;
	m_nPenColor			= pDrPen->m_nPenColor;
	m_nPenWidthOld		= pDrPen->m_nPenWidth;         
	m_nPenStyleOld		= pDrPen->m_nPenStyle;
	m_nPenColorOld		= pDrPen->m_nPenColor;
	//////////////////////////////
//	ReplacePen();
 	/////////////
    /////////////////////////////////////////////////

	return;
}		

void CDrPen::GetObjectInfo(CDrObject* pObject)
{
	
	CDrPen* pDrPen = (CDrPen*) pObject;
	//////////////////////////////////////////////////   
	pDrPen->m_nObjectType 		= m_nObjectType; 
	pDrPen->m_nElemType			= m_nElemType;	
	pDrPen->m_nObjectNo			= m_nObjectNo;
	///////////////////////////////////////////////// 
	pDrPen->m_nPenStyleIndex	= m_nPenStyleIndex;	
	pDrPen->m_nPenWidth			= m_nPenWidth;          
	pDrPen->m_nPenStyle			= m_nPenStyle;
	pDrPen->m_nPenColor			= m_nPenColor;
	pDrPen->m_nPenWidthOld		= m_nPenWidth;         
	pDrPen->m_nPenStyleOld		= m_nPenStyle;
	pDrPen->m_nPenColorOld		= m_nPenColor;
	/////////////////////////////////////////
	return;
}		

void CDrPen::DoDataView(CDC* PtrDC, int y)
{

	CString strCard;
	//////////////////////
	Pack_drPipe(&strCard);
	//////////////////////////// 
	PtrDC->TextOut(0,y,strCard);
	////////////////////////////
	return;
} 

void CDrPen::Pack_drPipe(CString* pstrCard)
{

   	static CString name;
   	/////////////////////////
   	for (int i = 0;i<nMax_SpecTypes;i++)
   		if(SpTypes[i].num == DRPEN) 
   		{
   			name = SpTypes[i].ObjName;
   			break;
   		}	
   			
   	static CString pad = " ";
  	////////////////////////
   	AddStr(pstrCard,&name,10);
	/////////////////////// 
	return;

}   

void CDrPen::Serialize(CArchive& ar)
{

	CDrObject::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	WORD w;
	DWORD dw;
	///////// 
	if (ar.IsStoring())
	{
		TRACE(" DrPen:    Storing\n");	// TODO: add storing code here
		
		///////////////////////////////////////////////////	
		ar	<</*int*/	(WORD)m_nElemType	
			<</*int*/	(WORD)m_nObjectType
			<</*UINT*/	(WORD)m_nObjectNo; 
		///////////////////////////////////////////////////////
		ar	<<	(WORD)m_nPenWidth	// user-selected pen style (width)  
			<<	(WORD)m_nPenStyle
			<<	(DWORD)m_nPenColor 
			<<	(WORD)m_nPenStyleIndex 
			
			<<	(WORD)m_nPenWidthOld         
			<<	(WORD)m_nPenStyleOld
			<<	(DWORD)m_nPenColorOld
			<<	(WORD)m_nPenStyleIndexOld 
			
			<<	(WORD)m_nPenWidthDefault         
			<<	(WORD)m_nPenStyleDefault
			<<	(DWORD)m_nPenColorDefault
 			<<	(WORD)m_nPenStyleIndexDefault;
 				//////////////////////////////
		ar.Write(/*CPen*/&m_PenCur, sizeof(CPen) );           // pen created according to
		///////////////////////////////////
		ar	<<	/*UINT*/(WORD)m_nPenStyleNameCount;
		for (UINT i=0;i<m_nPenStyleNameCount;i++)
		{
			ar	<<	m_PenStyleNames[i];
			ar	<<	/*int*/(WORD)m_nPenStyleConstants[i];
		}	
		///////////////////////////////////////////////////	

	}
	else
	{
		TRACE(" DrPen:    Loading\n");	// TODO: add loading code here

		///////////////////////////////////////////////////	
		ar	>>/*int*/w;
		m_nElemType = (int)w;	
		ar	>>/*int*/w;
		m_nObjectType = (int)w;
		ar	>>/*UINT*/w;
		m_nObjectNo = (UINT)w;
		///////////////////////////////////////////////////////
		ar	>>	w;
		m_nPenWidth = (int) w;	// user-selected pen style (width)  
		ar	>>	w;
		m_nPenStyle = (int) w;
		ar	>>	dw;
		m_nPenColor = (COLORREF) dw;
		ar	>>	w;
		m_nPenStyleIndex = (UINT) w; 
		
		ar	>>	w;
		m_nPenWidthOld = (int) w;	// user-selected pen style (width)  
		ar	>>	w;
		m_nPenStyleOld = (int) w;
		ar	>>	dw;
		m_nPenColorOld = (COLORREF) dw;
		ar	>>	w;
		m_nPenStyleIndexOld = (UINT) w;

		ar	>>	w;
		m_nPenWidthDefault = (int) w;	// user-selected pen style (width)  
		ar	>>	w;
		m_nPenStyleDefault = (int) w;
		ar	>>	dw;
		m_nPenColorDefault = (COLORREF) dw;
		ar	>>	w;
		m_nPenStyleIndexDefault = (UINT) w;
		//////////////////////////////
		ar.Read(/*CPen*/&m_PenCur, sizeof(CPen) );           // pen created according to
		///////////////////////////////////
		ar	>>	w;
		m_nPenStyleNameCount = (UINT) w; 
		for (UINT i=0;i<m_nPenStyleNameCount;i++)
		{
			ar	>>	m_PenStyleNames[i];
			ar	>>	/*int*/w;
			m_nPenStyleConstants[i] = (int)w;
		}	
		/////////////////////////////////////////	

	}        
	/////////////////////// 
	m_PenCur.Serialize(ar);
	///////////////////////
}

void CDrPen::ReplacePen()
{
	// Change the current pen to reflect the new user-specified data.
	m_PenCur.DeleteObject();
	m_PenCur.CreatePen(m_nPenStyle, m_nPenWidth, m_nPenColor); 
}
////////////////////////////////// end of module //////////////////
