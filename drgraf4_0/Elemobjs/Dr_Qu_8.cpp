// Plat.cpp : implementation file
//


#include "stdafx.h"
#include "limits.h"

#include "3DMath.h"
#include "XForm.h"
////////////////////// elObjs
#include "Ext_Elem.h"
#include "Def_Elem.h"
#include "DrFE0D.h"
//////////////
#include "Dr_Qu_8.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////
//#define COMBO_NIDJ_LOC 	9     // Location of NidJ in element ComboBox
////////////////////////////
#define GREEN	RGB(0,255,0)
#define RED		RGB(255,0,0)
/////////////////////////////////////////////////////////////////////////////
// CDr_Qu_8
IMPLEMENT_SERIAL(CDr_Qu_8, CDrFE2D,1)
/*
BEGIN_MESSAGE_MAP(CDr_Qu_8, CDrFE2D)
	//{{AFX_MSG_MAP(CDr_Qu_8)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/  
/////////////////////////////////////////////////////////////////////////////
CDr_Qu_8::CDr_Qu_8()
{  
    	
	m_ElTypeID		= "QU_8";
	m_ElTypeNum		= QU_8;
    //////////////////////////////	
    SetObjectType((int)QU_8);
    SetElemType((int)EL2D_OBJECT);          //
	////////////////////////////
	 
} 

CDr_Qu_8::~CDr_Qu_8()
{
	/////////////////////////// empty all the lists
	ReadyToDelete();
	///////////////////////////
}	

void CDr_Qu_8::DoFormattedCardView(CString* pstrCard,CString& strFmt)
{
	m_bFormatted = TRUE;	// DrObject Element
//	Pack_drPipe(pstrCard);
} 

void CDr_Qu_8::DoUnFormattedCardView(CString* pstrCard)
{
	m_bFormatted = FALSE;	// DrObject Element
	Pack_drPipe(pstrCard);
	///////////////////////////////
} 

void CDr_Qu_8::DoDataView(CDC* PtrDC, int y)
{

	CString strCard;
	//////////////////////
	Pack_drPipe(&strCard);
	//////////////////////////// 
	PtrDC->TextOut(0,y,strCard);
	////////////////////////////
	return;
} 

void CDr_Qu_8::Pack_drPipe(CString* pstrCard)
{
	static CString name;
	POSITION	pos;
	int			i; 
	CString blank = "";
   	/////////////////////////
   	for (i = 0;i<nMax_ElemTypes;i++)
   		if(ElTypes[i].num == QU_8) 
   		{
   			name = ElTypes[i].ObjName;
   			break;
   		}	
	/////////////////////////
	CString pad = " "; 
	//////////////////////////////////////////////////// Name (OverRidden)
	name = "QU_8";
	AddStr(pstrCard,&name,10);
	//////////////////////////////////////////////////// ElementNum
	AddStr(pstrCard,&m_ElNumID,5);
	//////////////////////////////////////////////////// LineID
	AddStr(pstrCard,&m_line_id,5);
	//////////////////////////////////////////////////// Nodes:All
	for (i = 0;i<m_nNodes;i++)
	{
		pos = m_FE0DList.FindIndex(i);
		CDrFE0D* pNode = (CDrFE0D*)m_FE0DList.GetAt(pos);
		AddStr(pstrCard,&((pNode->GetNodeCard())->id),5);
	}
	//////////////////////////////////////////////////// ReleaseID
	for (i = 0;i<m_nCorners;i++)
		AddStr(pstrCard,&(m_rid[i]),5);
	//////////////////////////////////////////////////// Property
	AddStr(pstrCard,&m_pid,5);
	//////////////////////////////////////////////////// Material
	AddStr(pstrCard,&m_mid,5);
	//////////////////////////////////////////////////// ThickNess
	AddDouble(pstrCard,m_Thkness);
	///////
	return;
}
						
void CDr_Qu_8::DoDrawView(CDC* PtrDC,BOOL bPenChange)
{

    ///////////////////////////////////////////// Draw 
	GoDoIt(PtrDC,bPenChange);
   	//////////////////////////////////////////
    
}                            

void CDr_Qu_8::GoDoIt(CDC* PtrDC,BOOL bPenChange)
{ 
	CDListMgr* 	pList;
	POSITION 	pos;
    ////////////////
   	CPen    Pen;
   	CPen*   PtrOldPen;
   	                        
	/////////////////////////////////////////////////// 
//	IF bLayerON = FALSE make PEN: DASHED or something     TO BE Done Later
    /////////////////////////////////////////////////// Pen
   	Pen.CreatePen (m_nPenStyle,m_nPenWidth,m_crPenColor); 
   	PtrOldPen = PtrDC->SelectObject(&Pen);
	/////////////////////////////////////// Generated Nodes
	pList = GetFE0DList();
	//////////////////////
	int i;
	pWORLD pPtEye;
	//////////////////////////////////////////////////////
	if(!pList->IsEmpty())
	{
		/////////////////////////////////////// Memory
		pPtEye = new WORLD[m_nCorners+1];
		if(!pPtEye)
		return;
		/////////////////////////////////////// GetNodes
		pWORLD pPt; 	
		for (i = 0;i<m_nCorners;i++)
		{
			pos = pList->FindIndex(i); 
			/////////////////////
			CDrFE0D* pNode = (CDrFE0D*)pList->GetNextObject(pos);
			//////////////////////////////////
			pPt = pPtEye+i;
			*pPt = *(pNode->GetEyePos());
			/////////////////////////////
		}
		*(pPtEye+m_nCorners) = *pPtEye;	// last = first
    	//////////////////////////////////// Line			
//		PtrDC->Polyline(pPtMem,nMaxCorner+1);
		int iold = 0; 
		for(i=1;i<=m_nCorners;i++)    //closed
		{
			DrawLine3D(PtrDC,pPtEye+iold,pPtEye + i,TRUE);  //TRUE = XFormed; FALSE= NOT XFormed
			iold = i; 
		}
		//////////////
		delete [] pPtEye;
	}	
	//////////////////////////////////////////////////////   	
   	PtrDC->SelectObject(PtrOldPen);   
   	Pen.DeleteObject(); 
}   
/////////////////////////////////////////////////////////////////////////////
BOOL CDr_Qu_8::IsKeyMatch(CString KeyID,UINT KeyNo)
{
	return FALSE;
}
	
BOOL CDr_Qu_8::IsObjectHit(int nNet,POINT point)
{
	if(CDrFE2D::IsObjectHit(nNet,point,0))
		return TRUE;
	else
		return FALSE;
}

void CDr_Qu_8::Serialize(CArchive& ar)
{

	CDrFE2D::Serialize( ar);              // must call base class Serializer
	//////////////////////////////////////
	if (ar.IsStoring())
	{
		TRACE( " CDr_Qu_8   :Storing\n");	// TODO: add loading code here

 	}
	else
	{
	
		TRACE( " CDr_Qu_8   :Loading\n");	// TODO: add loading code here

	}        
	//////////////////////////////////////////////////////

}

////////////////////// END OF MODULE ///////////////////////

