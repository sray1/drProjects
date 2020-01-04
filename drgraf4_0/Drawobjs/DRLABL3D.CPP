// Label.cpp : implementation file
//

#include "stdafx.h"

#include "drextern.h"
#include "drdefine.h"

#include "label.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////
#define GREEN	RGB(0,255,0)
#define RED		RGB(255,0,0)
#define NODE_LABEL			-1
/////////////////////////////////////////////////////////////////////////////
// CDrLabel3D
IMPLEMENT_SERIAL(CDrLabel3D, CDrObject,1)
/*
BEGIN_MESSAGE_MAP(CDrLabel3D, CDrObject)
	//{{AFX_MSG_MAP(CDrLabel3D)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/  
/////////////////////////////////////////////////////////////////////////////
CDrLabel3D::CDrLabel3D()
{  
	
	m_pt->x = 0.0;
	m_pt->y = 0.0;
	//////////////////////////////
    m_rectBounding.SetRectEmpty();
    //////////////////////////////
	 
} 

int CDrLabel3D::DealObjectDialog()
{
/*
	CEditLabel	dlg;
	if(dlg.DoModal() == IDOK)
		return 0;
	else
		return -1;
*/
	return 0;			
}
	
void CDrLabel3D::SetObjectInfo(CDrObject* pObject)
{
	
	CDrLabel3D* pLabel = (CDrLabel3D*) pObject;
	///////////////////////////////////////////////////////////////////
	m_nElemType			= pLabel->m_nElemType;
	m_rectBounding		= pLabel->m_rectBounding; // smallest rect that surrounds 
	m_nObjectType		= pLabel->m_nObjectType; 
	m_nObjectNo			= pLabel->m_nObjectNo;
	m_nLayer    		= pLabel->m_nLayer;
	/////////////////////////////////// 
	m_lf		 		= pLabel->m_lf;
	m_Color		 		= pLabel->m_Color;
	m_nType		 		= pLabel->m_nType;
	m_nViewNum	 		= pLabel->m_nViewNum;
	m_Text		 		= pLabel->m_Text;
	m_Corner			= pLabel->m_Corner;
	m_nPrecision		= pLabel->m_nPrecision;
/*
	m_Corner23	 		= pLabel->m_Corner23;
	m_Corner31	 		= pLabel->m_Corner31;
	m_CornerIso	 		= pLabel->m_CornerIso;
	m_RBCorner   		= pLabel->m_RBCorner;
*/
    /////////////////////////////////////////

	return;
}		

void CDrLabel3D::GetObjectInfo(CDrObject* pObject)
{
	
	CDrLabel3D* pLabel = (CDrLabel3D*) pObject;
	///////////////////////////////////////////////////////////////////   
	pLabel->m_nObjectType 		= m_nObjectType; 
	pLabel->m_nLayer		    = m_nLayer;
	pLabel->m_nElemType			= m_nElemType;	
	pLabel->m_nObjectNo			= m_nObjectNo;
	/////////////////////////////////// 
	pLabel->m_lf		 		= m_lf;
	pLabel->m_Color		 		= m_Color;
	pLabel->m_nType		 		= m_nType;
	pLabel->m_nViewNum	 		= m_nViewNum;
	pLabel->m_Text		 		= m_Text;
	pLabel->m_Corner			= m_Corner;
	pLabel->m_nPrecision		= m_nPrecision;
/*	
	pLabel->m_Corner23	 		= m_Corner23;
	pLabel->m_Corner31	 		= m_Corner31;
	pLabel->m_CornerIso	 		= m_CornerIso; 
	pLabel->m_RBCorner   		= m_RBCorner;
*/	
	/////////////////////////////////////////
	return;
}		

void CDrLabel3D::DoDataView(CDC* PtrDC, int y)
{

	CString strCard;
	//////////////////////
	Pack_drPipe(&strCard);
	//////////////////////////// 
	PtrDC->TextOut(0,y,strCard);
	////////////////////////////
	return;
} 

void CDrLabel3D::Pack_drPipe(CString* pstrCard)
{

   	static CString name;
   	/////////////////////////
   	for (int i = 0;i<nMax_DrawTypes;i++)
   		if(DrTypes[i].num == LABEL) 
   		{
   			name = DrTypes[i].ObjName;
   			break;
   		}	
   	/////////////////////////
   	CString text = GetText();
   	CString pad = " ";
  	////////////////////////
   	AddStr(pstrCard,&name,5);
   	AddStr(pstrCard,&text,5);
	/////////////////////// 
	return;

}   
	 
void CDrLabel3D::DoDrawView(CDC* PtrDC,BOOL bPenChange,int nViewNumber)
{

    /////////////////////////////////////// for Node Label, viewNumber unimportant
	if((GetViewNum() != nViewNumber) && (GetType() != NODE_LABEL)) return;
	///////////////////////////////////////////// 
	CString text = GetText();
//	m_pt[0]		 = GetCorner(nType,nViewNumber);
	///////////////////////////////////////////// Transform/Project
	long Coord[3];
   	Coord[0] = GetCorner().x;
   	Coord[1] = GetCorner().y;
   	Coord[2] = GetCorner().z;
   	/////////////////
	SetEndPointCoord(Coord,m_nPrecision,m_pt,0);
	/////////////////////////////////////////////
	GoDoIt(PtrDC,m_pt,text,bPenChange);
   	//////////////////////////////////////////
    
}                            

void CDrLabel3D::GoDoIt(CDC* PtrDC,POINT* pt,CString text,BOOL bPenChange)
{ 

	/////////////////////////////////////////////////// 
//	IF bLayerON = FALSE make PEN: DASHED or something     TO BE Done Later
    //////////////////////////////// Select Font/Color
 	// set font.
    CFont	Font;
    CFont*	pOldFont;
	Font.DeleteObject();
	Font.CreateFontIndirect(&m_lf);
	pOldFont = (CFont*)(PtrDC->SelectObject(&Font));
    /////////////////////////////////////////////////// Font Color
	if(!bPenChange)
    {
		PtrDC->SetTextColor(m_Color);
	}	   	
	else
	{
		// Create Green Pen 1 Pixel wide;
		COLORREF crColor = GREEN;
		PtrDC->SetTextColor(crColor);
	}	   	
    //////////////////////////////// Label Out
	PtrDC->TextOut(pt->x,pt->y,text);
	//////////////////////////////// Get Original Font back
	if(pOldFont != NULL)
		PtrDC->SelectObject(pOldFont);
   	
}   

/////////////////////////////////////////////////////////////////////////////
void CDrLabel3D::FinishObject(CClientDC* pDC,int nViewNumber)
{ 

	// Calculate the bounding rectangle.  It's needed for smart
	// repainting.
    /////////////////////////////////////// for Node Label, viewNumber unimportant
	if((GetViewNum() != nViewNumber) && (GetType() != NODE_LABEL)) return;
	///////////////////////////////////////////// Transform/Project 
	long Coord[3];
   	Coord[0] = GetCorner().x;
   	Coord[1] = GetCorner().y;
   	Coord[2] = GetCorner().z;
   	/////////////////
	SetEndPointCoord(Coord,m_nPrecision,m_pt,0);
	//////////////////////////////////
	m_rectBounding.left   = m_pt[0].x;
	m_rectBounding.top    = m_pt[0].y;
	///////////////////////////////////////// set font to get TextMetric.
    CFont	Font;
    CFont*	pOldFont;
	Font.DeleteObject();
	Font.CreateFontIndirect(&m_lf);
	pOldFont = (CFont*)(pDC->SelectObject(&Font));
	TEXTMETRIC	tm;
	pDC->GetTextMetrics(&tm);
	int nWidth = tm.tmMaxCharWidth;
	int nHeight= tm.tmHeight;
	pDC->SelectObject(pOldFont);
	//////////////////////////////////////// 	Right Bottom Corner	
	POINT addLOG;
	int nLen = GetText().GetLength();
	addLOG.x = nWidth*nLen;  // Logical Coord.
	addLOG.y = nHeight;
	///////////////////
    m_pt[0].x += addLOG.x; 
    m_pt[0].y -= addLOG.y; 
	m_rectBounding.right  = m_pt[0].x;
	m_rectBounding.bottom = m_pt[0].y;
    //////////////////////////////////
	return; 
	
}

BOOL CDrLabel3D::IsKeyMatch(CDrObject* pObject, CString KeyID,UINT KeyNo)
{

	CDrLabel3D* pLabel = (CDrLabel3D*)(pObject);
	////////////////////////////////////////	
	switch(KeyNo)
	{ 
		case 1:         // LabelID

			if((pLabel->GetText()) ==KeyID)
				return TRUE;
			break; 
				
	    case 2:	
					
	  	default:
	  		return FALSE;					
	}
	return FALSE;
}

void CDrLabel3D::Serialize(CArchive& ar)
{

	CDrObject::Serialize( ar);              // must call base class Serializer
	//////////////////////////////////////     
	WORD	nElementType,nObjectNo,nObjectType,nLayer,w;
	DWORD   dw;
	if (ar.IsStoring())
	{
		TRACE( " Label	:Storing\n");	// TODO: add storing code here

		ar	<<	/*int*/		(WORD)	m_nElemType	// Type = PIPE = 2 in ElGlobal.h
			<<	/*int*/		(WORD)	m_nObjectType
			<<	/*UINT*/	(WORD)	m_nObjectNo
			<<	/*CRect*/	m_rectBounding // smallest rect that surrounds 
											// Pipe Ends measured in MM_LOENGLISH units
											// (0.01 inches, with Y-axis inverted)
			<<	/*UINT*/	(WORD)	m_nLayer;
		ar	<<	/*POINT*/ 	m_pt[0];
		ar	<<	/*COLORREF*/(DWORD)	m_Color		// Text Color
			<<	/*CString*/			m_Text		// Label Card
			<<	/*int*/		(WORD)	m_nPrecision// precision
			<<	/*int*/		(WORD)	m_nIndex	// nodeId index or other based on m_ntype
			<<	/*int*/		(WORD)	m_nType		// we save coord in node and use here
												// -1 = Node Label(for All Views: default)
												//  0 = Label
			<<	/*int*/		(WORD)	m_nViewNum							
			<<	/*int*/		(WORD)	m_nRotation	// for rotating text
			<<	/*int*/		(WORD)	m_nTilt
			<<	/*int*/		(WORD)	m_nShift
			<<	/*POINT*/			m_pt[0];  
		/////////////////////////////////////////////	
		ar.Write(/*POINT3*/		&m_Corner,sizeof(POINT3) );
		ar.Write(/*LOGFONT*/	&m_lf,sizeof(LOGFONT) );
		/////////////////////////////////////////////

 	}
	else
	{
		TRACE(" Label	:Loading\n");	// TODO: add loading code here

		ar	>>	/*int*/		nElementType
			>>	/*int*/		nObjectType
			>>	/*UINT*/	nObjectNo
			>>	/*CRect*/	m_rectBounding // smallest rect that surrounds 
											// Pipe Ends measured in MM_LOENGLISH units
											// (0.01 inches, with Y-axis inverted)
			>>	/*UINT*/	nLayer;
		ar	>>	/*POINT*/	m_pt[0];
		ar	>>	/*COLORREF*/dw;
		m_Color = (COLORREF) dw;		// Text Color
		///////////////////////
		ar	>>	/*CString*/			m_Text		// Label Card 
			>>	/*int*/w;
		m_nPrecision = (int)w;	
		ar	>>	/*int*/w;
		m_nIndex = (int) w; 		// nodeId index or other based on m_ntype
		ar	>>	/*int*/w;
		m_nType	 = (int) w;	// we save coord in node and use here
							// -1 = Node Label(for All Views: default)
							//  0 = Label
		ar	>>	/*int*/w;
		m_nViewNum = (int) w;							
		ar	>>	/*int*/w;
		m_nRotation = (int) w;							
		ar	>>	/*int*/w;
		m_nTilt = (int) w;							
		ar	>>	/*int*/w;
		m_nShift = (int) w;							
		ar	>>/*POINT*/ m_pt[0];  
		/////////////////////////////////////////////	
		ar.Read(/*POINT3*/	&m_Corner,sizeof(POINT3) );
		ar.Read(/*LOGFONT*/	&m_lf,sizeof(LOGFONT) );
		/////////////////////////////////////////////
		m_nElemType		  	= 	(int)nElementType;		// Type = PIPE = 2 in ElGlobal.h
    	m_nObjectType		= 	(int)nObjectType;
    	m_nObjectNo			= 	(UINT)nObjectNo;
		m_nLayer			=	(UINT)nLayer;
    	/////////////////////////////        

	}        
	////////////////////////

} 
/*
POINT CDrLabel3D::GetCorner(int nType,int nViewNum)
{ 
		switch(nViewNum)           // NodeType Label(applies to all View)
		{		
			case VIEW12:
				return m_Corner;
			case VIEW23:
				return m_Corner23;
			case VIEW31:
				return m_Corner31;
			case VIEWISO:
				return m_CornerIso;
			default:
				m_Corner.x = 0;
				m_Corner.y = 0;
				return m_Corner;
				break;
		}
}		
						 
void CDrLabel3D::SetCorner(int nType,LPOINT Corner,int nViewNum)
{

		switch(nViewNum)            
		{
			case VIEW12:
				m_Corner = Corner;
				break;
			case VIEW23:
				m_Corner23 = Corner;
				break;
			case VIEW31:
				m_Corner31 = Corner;
				break;
			case VIEWISO:
				m_CornerIso = Corner;
				break;
			default:
				break;
		}
	
}

void CDrLabel3D::SetOtherCorner(POINT Corner)
{

	m_RBCorner = Corner;    // RightBottom
	
}
*/	
BOOL CDrLabel3D::IsObjectHit(CDrObject* pObject,CClientDC* ptrDC,int nNet,
								POINT point,RECT* pRect,int nViewNumber)
{

	CDrLabel3D* pLabel = (CDrLabel3D*)pObject;
    //////////////////////////////////////
	if(pLabel->GetObjectType() == LABEL)
	{
	    /////////////////////////////////////// for Node Label, viewNumber unimportant
		if((GetViewNum() != nViewNumber) && (GetType() != NODE_LABEL)) return FALSE;
		///////////////////////////////////////////// Transform/Project 
		long Coord[3];
 	  	Coord[0] = GetCorner().x;
	   	Coord[1] = GetCorner().y;
	   	Coord[2] = GetCorner().z; 
	   	//////////////////
		SetEndPointCoord(Coord,m_nPrecision,m_pt,0);
		///////////////////////////////////////////// 
		CSize	Size; 
       	
		pRect->left = m_pt[0].x;
    	pRect->top	= m_pt[0].y;
    	///////////////////////////////////////// get FontSize etc.
		CFont	Font;
		Font.DeleteObject;
		Font.CreateFontIndirect(&(pLabel->m_lf));
		CFont* pOldFont = (CFont*) ptrDC->SelectObject(&Font);
		Size		  = ptrDC->GetTextExtent(pLabel->m_Text,
										(pLabel->m_Text).GetLength());
		ptrDC->SelectObject(pOldFont);
		////////////////////////////////////////////////////////////
    	pRect->right  = pRect->left + Size.cx; 
    	pRect->bottom = pRect->top  - Size.cy; // Logical
    	////////////////////////////// Assumed View12
    	if((point.x>=pRect->left) && (point.x<=pRect->right) &&
       		(point.y<=pRect->top ) && (point.y>=pRect->bottom)) 
    	{
	       	return TRUE; 
    	}
    	///////////////////
	}
	return FALSE;
}
/////////////////////// END of MODULE /////////////////

