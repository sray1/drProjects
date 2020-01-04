// FreeHand.cpp : implementation file
//

#include "stdafx.h"
 

#include "Def_Type.h"
#include "Def_Objs.h"
/////////////////////
#include "Ext_Draw.h"
#include "Def_Draw.h"
//#include <stdio.h>          canNOT use sscanf in DLL

#include "DrFreHnd.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//extern FAR sscanf(const char *,const char *,...);
/////////////////////////////
#define GREEN	RGB(0,255,0)
#define RED		RGB(255,0,0)
/////////////////////////
#define	FREEHAND_SIZE	3
/////////////////////////////////////////////////////////////////////////////
// CDrFreeHand
IMPLEMENT_SERIAL(CDrFreeHand, CDrObject,1)
/*
BEGIN_MESSAGE_MAP(CDrFreeHand, CDrObject)
	//{{AFX_MSG_MAP(CDrFreeHand)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/  
/////////////////////////////////////////////////////////////////////////////
CDrFreeHand::CDrFreeHand()
{  
    SetObjectType((int)FREEHAND);
    SetElemType((int)DRAW_OBJECT);          //  
	//////////////////////////////
    m_rectBounding.SetRectEmpty();
    //////////////////////////////
	 
} 

int CDrFreeHand::DealObjectDialog()
{ 
/*
	CFreeHandProp	dlg;
	if(dlg.DoModal() == IDOK)
		return 0;
	else
		return -1;
*/
	return 0;			
}
	
void CDrFreeHand::SetObjectInfo(CDrObject* pObject)
{
	
	CDrFreeHand* pAddFreeHand = (CDrFreeHand*) pObject;
	///////////////////////////////////////////////////////////////////
	m_nElemType			= pAddFreeHand->m_nElemType;
	m_rectBounding		= pAddFreeHand->m_rectBounding; // smallest rect that surrounds 
	m_nObjectType		= pAddFreeHand->m_nObjectType; 
	m_nObjectNo			= pAddFreeHand->m_nObjectNo;
	///////////
	SetPenInfo(pAddFreeHand->m_nPenWidth,pAddFreeHand->m_crPenColor,pAddFreeHand->m_nPenStyle);
	////////
	m_nLayer    		= pAddFreeHand->m_nLayer;
	//////////////////////////////////////////// 
	m_nFHNumber			= pAddFreeHand->m_nFHNumber;
	m_nViewNum	 		= pAddFreeHand->m_nViewNum;
	//////////////////////////////////////////////////
	if (pAddFreeHand->m_pointArray.GetSize()==0)
	{
		return;
	}
	for (int i=0; i < pAddFreeHand->m_pointArray.GetSize(); i++)
	{
		AddPoint(pAddFreeHand->GetPoint(i));
	}	
	////////////////////////////////////////////////
	m_bGenerated		= pAddFreeHand->m_bGenerated;			
	m_nLevel			= pAddFreeHand->m_nLevel;				 
	////////////////////
	return;
}		

void CDrFreeHand::GetObjectInfo(CDrObject* pObject)
{
	
	CDrFreeHand* pAddFreeHand = (CDrFreeHand*) pObject;
	///////////////////////////////////////////////////////////////////   
	pAddFreeHand->m_nElemType		= m_nElemType;
	pAddFreeHand->m_rectBounding	= m_rectBounding; // smallest rect that surrounds 
	pAddFreeHand->m_nObjectType		= m_nObjectType; 
	pAddFreeHand->m_nObjectNo		= m_nObjectNo;
	////////////////////////                                    
   	pAddFreeHand->GetPenInfo(m_nPenWidth,m_crPenColor,m_nPenStyle);
	/////////////////////// 
	pAddFreeHand->m_nLayer	   		= m_nLayer;
	///////////////////////////////////////////////////										
	pAddFreeHand->m_nFHNumber		= m_nFHNumber;
	pAddFreeHand->m_nViewNum 		= m_nViewNum;
	///////////////////////////////////////////
	if (m_pointArray.GetSize()==0)
	{
		return;
	}
	for (int i=0; i < m_pointArray.GetSize(); i++)
	{
		pAddFreeHand->AddPoint(GetPoint(i));
	}	
	///////////////////////////////////////////////////										
	pAddFreeHand->m_bGenerated				= m_bGenerated;			
	pAddFreeHand->m_nLevel					= m_nLevel;				 
	////////////////////
	return;
}		

void CDrFreeHand::DoDataView(CDC* PtrDC, int y)
{

	CString strCard;
	//////////////////////
	Pack_drPipe(&strCard);
	//////////////////////////// 
	PtrDC->TextOut(0,y,strCard);
	////////////////////////////
	return;
} 

void CDrFreeHand::Pack_drPipe(CString* pstrCard)
{

   	static CString name;
   	/////////////////////////
   	for (int i = 0;i<nMax_DrawTypes;i++)
   		if(DrTypes[i].num == FREEHAND) 
   		{
   			name = DrTypes[i].ObjName;
   			break;
   		}	
	/////////////////////////
	CString pad = " "; 
	int nSize = m_pointArray.GetSize();
	////////////////////////
	AddStr(pstrCard,&name,10);
	AddInt(pstrCard,m_nFHNumber);
	AddInt(pstrCard,m_nViewNum);
	AddInt(pstrCard,nSize);
	//////////// 
	return;

}   

void CDrFreeHand::InitDraw(CDC* PtrDC,BOOL bParallel,int nView,
					 	pMATRIX pViewM,pMATRIX pvv3DM,double dzMin,
						double dScale_U,double dScale_V)
{ 
	m_bParallel		= bParallel;
    m_nView			= nView;
	m_dScale_U		= dScale_U;		// vv3DToLP:U-direction  
	m_dScale_V		= dScale_V;		// vv3DToLP:V-direction
	m_ViewM			= *pViewM;		// viewers transform MATRIX
	m_vv3DM			= *pvv3DM;		// Window to 3D Viewport MATRIX
	m_dzMin			= dzMin; 
	///////////////////////////////////////////////////////////////// PreProcess
	FinishObject(m_nView);//	calc Bounding Rect for the view 
	/////////////
}
						
void CDrFreeHand::DoDrawView(CDC* PtrDC,BOOL bPenChange,int nViewNumber)
{

    ///////////////////////////////////////
	if(GetViewNum() != nViewNumber) return;
	/////////////////////////////////////// 
   	CPen    Pen;
   	CPen*   PtrOldPen;
	/////////////////////////////////////////////////// 
//	IF bLayerON = FALSE make PEN: DASHED or something     TO BE Done Later
    /////////////////////////////////////////////////// Pen
    if(!bPenChange)
    {
		// Create normal Pen for Node
	   	Pen.CreatePen (m_nPenStyle,m_nPenWidth,m_crPenColor); 
	}
	else		   	
	{
		// Create Green Pen 1 Pixel wide;
		int nPenColor = GREEN;
		int nPenWidth = 2;   
	   	Pen.CreatePen (m_nPenStyle,nPenWidth,nPenColor);
	}	   	
   	PtrOldPen = PtrDC->SelectObject(&Pen);
    ///////////////////////////////////////////// Draw 
	for (int i=0; i < m_pointArray.GetSize(); i++)
	{
		/////////////////////////////////////// Draw !!!
    	GoDoIt(PtrDC,GetPoint(i),i,nViewNumber);
        ///////////////////////////////////////
	}
   	PtrDC->SelectObject(PtrOldPen);   
   	Pen.DeleteObject(); 
	///////////////////////////////   	
    
}                            

void CDrFreeHand::GoDoIt(CDC* PtrDC,POINT pt,int nSequence,int nViewNumber)
{ 

    //////////////////////////////////// Line
    if(nSequence>0)
		PtrDC->LineTo(pt); 
	else if(!nSequence)
		PtrDC->MoveTo(pt); 
	///////////////////////////////   	
   	
}   

/////////////////////////////////////////////////////////////////////////////
void CDrFreeHand::FinishObject(int nViewNumber)
{
    /////////////////////////////////////// for Node Label, viewNumber unimportant
	if(GetViewNum() != nViewNumber) return;
	///////////////////////////////////////
	// Calculate the bounding rectangle.  It's needed for smart
	// repainting.

	if (m_pointArray.GetSize()==0)
	{
		m_rectBounding.SetRectEmpty();
		return;
	}
	CPoint pt = GetPoint(0);
	m_rectBounding = CRect(pt.x, pt.y, pt.x, pt.y);

	for (int i=1; i < m_pointArray.GetSize(); i++)
	{
		// If the point lies outside of the accumulated bounding
		// rectangle, then inflate the bounding rect to include it.
		pt = GetPoint(i);
		m_rectBounding.left     = min(m_rectBounding.left, pt.x);
		m_rectBounding.right    = max(m_rectBounding.right, pt.x);
		m_rectBounding.top      = max(m_rectBounding.top, pt.y);
		m_rectBounding.bottom   = min(m_rectBounding.bottom, pt.y);
	}

	// Add the pen width to the bounding rectangle.  This is necessary
	// to account for the width of the stroke when invalidating
	// the screen.
	m_rectBounding.InflateRect(CSize(m_nPenWidth, -(int)m_nPenWidth));
	return;
}

void CDrFreeHand::AddPoint(CPoint pt)
{
	m_pointArray.Add(MAKELONG(pt.x, pt.y));
}

BOOL CDrFreeHand::IsObjectHit(CDrObject* pObject,CClientDC* ptrDC,int nNet,
								POINT point,RECT* pRect,int nViewNumber)
{

	////////////////////////////////////////////////   
	CSize	Size;
	 
	CDrFreeHand* pFreeHand = (CDrFreeHand*)pObject;
	///////////////////////////////////////// Check m_nViewNum
	if((pFreeHand->GetViewNum()) == nViewNumber)
	{
		for(int j=0; j<m_pointArray.GetSize(); j++)
		{
			POINT pointTemp = pFreeHand->GetPoint(j);
			ptrDC->LPtoDP(&pointTemp);
			///////////////////////////////////////// Rectangle in
										   		   // Device Coordinate
			pRect->left 	= pointTemp.x - nNet;
			pRect->top		= pointTemp.y - nNet;
			pRect->right 	= pointTemp.x + nNet;
			pRect->bottom	= pointTemp.y + nNet;
			///////////////////////////////////////////////////////
			if((point.x>=pRect->left) && (point.x<=pRect->right) &&
				 (point.y>=pRect->top ) && (point.y<=pRect->bottom)) 
			{
				ptrDC->DPtoLP(pRect);
				return TRUE; 
			}
		}
	}	
	return FALSE;
} 

BOOL CDrFreeHand::IsKeyMatch(CDrObject* pObject, CString KeyID,UINT KeyNo)
{

	CDrFreeHand* pFreeHand = (CDrFreeHand*)(pObject);
	//////////////////////////////////////////////	 
	switch(KeyNo)
	{ 
	  case 1:      // KeyID should contain m_nFHNumber+m_nViewNum;   

		int nFHNum,nViewNum;
												// CANNOT use SSCANF in DLL
//		sscanf(KeyID,"%d%d",&nFHNum,&nViewNum); 
		nFHNum 		= atoi((const char*) KeyID);
		nViewNum	= atoi((const char*) KeyID + 5);
		///////////////////////////////////////////////
		if((pFreeHand->GetFreeHandNum() == nFHNum) &&
		   (pFreeHand->GetViewNum() == nViewNum)      )
			return TRUE;
		break;  
					
	  default:
	  	return FALSE;					
	}
	return FALSE;
} 

void CDrFreeHand::Serialize(CArchive& ar)
{

	CDrObject::Serialize( ar);              // must call base class Serializer
	//////////////////////////////////////
	BYTE	b;     
	WORD	nElementType,nObjectNo,nObjectType,nPenWidth,nPenStyle,nLayer,w;
	DWORD   crPenColor;
	
	if (ar.IsStoring())
	{
		TRACE( " FreeHand   :Storing\n");	// TODO: add loading code here

		ar	<<	/*int*/		(WORD)m_nElemType	// Type = PIPE = 2 in ElGlobal.h
			<<	/*int*/		(WORD)m_nObjectType
			<<	/*UINT*/	(WORD)m_nObjectNo 
			
			<<	/*BOOL*/	(BYTE)m_bMoved
			<<	/*CRect*/	m_rectBounding // smallest rect that surrounds 

			<<	/*UINT*/	(WORD)m_nPenWidth    // pen width for Pipe
			<<	/*COLORREF*/(DWORD)m_crPenColor
			<<	/*UINT*/	(WORD)m_nPenStyle 
			
			<<	/*UINT*/	(WORD)m_nLayer;
		//////////////////////////////////////////////////////	
		ar	<<	/*UINT*/(WORD)m_nFHNumber		// FreeHand Number
    		<<	/*int*/	(WORD)m_nViewNum;
		/*CDWordArray*/
		m_pointArray.Serialize(ar);   // series of connected points 
		ar	<<	/*POINT*/ 	m_pt[0];
		//////////////////////////////////////////////////////

 	}
	else
	{
	
		TRACE( " FreeHand   :Loading\n");	// TODO: add loading code here


		ar	>>	/*int*/		nElementType
			>>	/*int*/		nObjectType
			>>	/*UINT*/	nObjectNo;
			//////////////////////////
		ar	>>	/*BOOL*/b;
		m_bMoved = (BOOL)b;
		////////////////////	
		ar	>>	/*CRect*/	m_rectBounding // smallest rect that surrounds 

		  	>>	/*UINT*/	nPenWidth    // pen width for Pipe
			>>	/*COLORREF*/crPenColor
			>>	/*UINT*/	nPenStyle 
			>>	/*UINT*/	nLayer;
		//////////////////////////////////////////////////////	
		ar	>>	/*UINT*/w;
		m_nFHNumber = (UINT)w;		// FreeHand Number
    	ar	>>	/*int*/w;
    	m_nViewNum = (int)w;
		/*CDWordArray*/
		m_pointArray.Serialize(ar);   // series of connected points

		ar	>>	/*POINT*/	m_pt[0];
		//////////////////////////////////////////////////////
		m_nElemType		  	= 	(int)nElementType;		// Type = PIPE = 2 in ElGlobal.h
	    m_nObjectType		= 	(int)nObjectType;
	    m_nObjectNo			= 	(UINT)nObjectNo;
		m_nPenWidth 		=	(UINT)nPenWidth;    // pen width for FreeHand
		m_crPenColor 		= 	(COLORREF)crPenColor;
		m_nPenStyle 		= 	(UINT)nPenStyle; 
		m_nLayer			=	(UINT)nLayer;
	    /////////////////////////////        
 
	}        
	////////////////////////

} 

////////////////////// END OF MODULE ///////////////////////

