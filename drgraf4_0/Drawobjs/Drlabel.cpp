// Label.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>

#include "Def_Type.h"
#include "Def_Objs.h"

#include "XForm.h"
/////////////////////
#include "Ext_Draw.h"
#include "Def_Draw.h"
#include "Def_Elem.h"	// for m_MeshElemType = NONE

#include "DrLabel.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////
#define MAX_DRAWVIEW	4
//////////////////////
#define GREEN	RGB(0,255,0)
#define RED		RGB(255,0,0)
/////////////////////////////////////////////////////////////////////////////
// CDrLabel
IMPLEMENT_SERIAL(CDrLabel, CDrObject,1)
/*
BEGIN_MESSAGE_MAP(CDrLabel, CDrObject)
	//{{AFX_MSG_MAP(CDrLabel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/  
/////////////////////////////////////////////////////////////////////////////
CDrLabel::CDrLabel()
{
  
    SetObjectType((int)LABEL);
    SetElemType((int)DRAW_OBJECT);          //  
	////////////////////////
	m_bMoved		= FALSE;
	///////////////////////	
	m_pt->x = 0;
	m_pt->y = 0;
	//////////////////////////////
    m_rectBounding.SetRectEmpty();
    //////////////////////////////
	m_MeshElemType = (UINT)NONE;	 
} 

int CDrLabel::DealObjectDialog()
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
	
void CDrLabel::SetObjectInfo(CDrObject* pObject)
{
	
	CDrLabel* pLabel = (CDrLabel*) pObject;
	///////////////////////////////////////////////////////////////////
	m_nObjectType		= pLabel->m_nObjectType; 
	m_nObjectNo			= pLabel->m_nObjectNo;
	m_nElemType			= pLabel->m_nElemType; 
	////////////////////////////////////////////	
	m_bMoved		    = pLabel->m_bMoved;

    for( int i = 0; i<MAX_LABEL_DRAW_PT; i++)              // 
    {
    	m_pDrNode[i] 	= pLabel->m_pDrNode[i];
	}	
	for(i = 0;i<MAX_DRAWVIEW;i++)							
    	m_pt[i] 		= pLabel->m_pt[i];
	/////////////////////////////////// 
	m_nLayer    		= pLabel->m_nLayer;
	m_rectBounding		= pLabel->m_rectBounding; // smallest rect that surrounds 
	m_lf		 		= pLabel->m_lf;
	m_Color		 		= pLabel->m_Color;
	m_nType		 		= pLabel->m_nType;
	m_nViewNum	 		= pLabel->m_nViewNum;
	m_Text		 		= pLabel->m_Text;
	m_RBCorner   		= pLabel->m_RBCorner;
	m_nTilt				= pLabel->m_nTilt;
	////////////////////////////////////////////////
	m_bGenerated		= pLabel->m_bGenerated;			
	m_nLevel			= pLabel->m_nLevel;				 
    /////////////////////////////////////////
	return;
}		

void CDrLabel::GetObjectInfo(CDrObject* pObject)
{
	
	CDrLabel* pLabel = (CDrLabel*) pObject;
	///////////////////////////////////////////////////////////////////   
	pLabel->m_nObjectType 		= m_nObjectType; 
	pLabel->m_nElemType			= m_nElemType;	
	pLabel->m_nObjectNo			= m_nObjectNo;
	////////////////////////////////////////////	
	pLabel->m_bMoved		    = m_bMoved;

    for( int i = 0; i<MAX_LABEL_DRAW_PT; i++)              // 
    {
    	pLabel->m_pDrNode[i] 	= m_pDrNode[i];
    }	
	for(i = 0;i<MAX_DRAWVIEW;i++)							
    	pLabel->m_pt[i] 		= m_pt[i];
	////////////////////////////////////////////////////////   
	pLabel->m_nLayer		    = m_nLayer;
	pLabel->m_rectBounding		= m_rectBounding; // smallest rect that surrounds 
	pLabel->m_lf		 		= m_lf;
	pLabel->m_Color		 		= m_Color;
	pLabel->m_nType		 		= m_nType;
	pLabel->m_nViewNum	 		= m_nViewNum;
	pLabel->m_Text		 		= m_Text;
	pLabel->m_RBCorner   		= m_RBCorner;
	pLabel->m_nTilt				= m_nTilt;
	///////////////////////////////////////////////////										
	pLabel->m_bGenerated		= m_bGenerated;			
	pLabel->m_nLevel			= m_nLevel;				 
	////////////////////
	return;
}		

void CDrLabel::DoDataView(CDC* PtrDC, int y)
{

	CString strCard;
	//////////////////////
	Pack_drPipe(&strCard);
	//////////////////////////// 
	PtrDC->TextOut(0,y,strCard);
	////////////////////////////
	return;
} 

void CDrLabel::Pack_drPipe(CString* pstrCard)
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
	 
POINT CDrLabel::GetCorner(int nViewNum)
{

	switch((UINT)nViewNum)
	{
		case VIEW12: 
			return m_pt[0];
				
		case VIEW23: 
			return m_pt[1];
				
		case VIEW31: 
			return m_pt[2];
				
		case VIEWISO: 
			return m_pt[3];
				
		default: 
			break;
	}
	//////////////////
	POINT pt;
	pt.x = 0;
	pt.y = 0;
	return pt;
}
	 
void CDrLabel::SetCorner(POINT Corner,int nViewNum)
{

	switch((UINT)nViewNum)
	{
		case VIEW12: 
			m_pt[0] = Corner;
			return;
				
		case VIEW23: 
			m_pt[1] = Corner;
			return;
				
		case VIEW31: 
			m_pt[2] = Corner;
			return;
				
		case VIEWISO: 
			m_pt[3] = Corner;
			return;
				
		default: 
			break;
	}
	return;
}
				
void CDrLabel::GetRawCoords(long* lCoord, int* pnPrecision, int index)
{

	//////////////////////////////////////////
   	lCoord[0] 		= m_pDrNode[index]->GetNodeCard()->x;
   	lCoord[1] 		= m_pDrNode[index]->GetNodeCard()->y;
   	lCoord[2]		= m_pDrNode[index]->GetNodeCard()->z;
   	*pnPrecision 	= m_pDrNode[index]->GetPrecision();
   	////////////////////////////////////////// 
   	return;
    
}

void CDrLabel::InitDraw(CDC* PtrDC,BOOL bParallel,int nView,
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
	if(GetType() == LABEL_NODE)
		if (!IsMoved()) 
			/////////////////////////////////////// Xform & Project
			Corner_3Dto2D();
	//////////////////////// 
	FinishObject((CClientDC*)PtrDC,m_nView);//	calc Bounding Rect for the view 
	/////////////
}
						
void CDrLabel::Corner_3Dto2D()
{ 
    
    int		nMax, nPrecision, index;
	long 	lCoord[3];
	POINT 	pt;
	////////////////////////////////
	nMax = GetMaxCorners();
	////////////////////////////////////////////// Get point 
	WORLD ptIn,ptOut;
	/////////////////
    for( int i = 0; i<nMax; i++)              // fill up m_pt[]
    {
   		///////////////////////////////////////////// get Raw Pt.
   		GetRawCoords(lCoord, &nPrecision, i);
		///////////////////////////////////////////// 
		ptIn.x = (double)lCoord[0];
		ptIn.y = (double)lCoord[1];
		ptIn.z = (double)lCoord[2];
		//////////////////////////////////////// Transform
		CXForm XForm(m_bParallel);

		XForm.Transform(&ptIn,&ptOut,&m_ViewM);
		//////////////////////////////////////// Clip
		
		//////////////////////////////////////// Project
		XForm.Project(&m_vv3DM,&ptOut,&ptIn);
		//////////////////////////////////////// Logical
		pt.x = (int)(ptIn.x * m_dScale_U);
		pt.y = (int)(ptIn.y * m_dScale_V);
		///////////////////////////////////////////// Set 2D pt. back
		index = i;
		////////// find index based on viewnumber
		        // because of NodeLabel Complexity
		if(m_nView == VIEW12)
			index = 0;
		else	
		if(m_nView == VIEW23)
			index = 1;
		else	
		if(m_nView == VIEW31)
			index = 2;
		else	
		if(m_nView == VIEWISO)
			index = 3;
		//////////////////////////////////////	save
		SetProjectedCoords(pt,index);
		////////////////////////////////////// 
	}	
	///////
	return; 
	
} 

void CDrLabel::DoDrawView(CDC* PtrDC,BOOL bPenChange,int nViewNumber)
{

    /////////////////////////////////////// for Node Label, viewNumber unimportant
	if((GetViewNum() != nViewNumber) && (GetType() != LABEL_NODE)) return;
	///////////////////////////////////////////// 
	CString text = GetText();
	///////////////////////////////////////////////
	POINT pt = GetCorner(nViewNumber);
	//////////////////////////////////
	GoDoIt(PtrDC,&pt,text,bPenChange,m_nView);
   	///////////////////////////////////////////////
    
}                            

void CDrLabel::GoDoIt(CDC* PtrDC,POINT* pt,CString text,BOOL bPenChange,int nViewNumber)
{ 

	/////////////////////////////////////////////////// 
//	IF bLayerON = FALSE make PEN: DASHED or something     TO BE Done Later
    //////////////////////////////// Select Font/Color
 	// set font.
    CFont	Font;
    CFont*	pOldFont;
	Font.DeleteObject();
	LOGFONT lf;
    /////////////////////////////////////////////////// Font Double
	if(bPenChange)
	{
		lf = m_lf;
		////////////////
		lf.lfWeight		= FW_BOLD;
		lf.lfItalic		= TRUE;
		lf.lfUnderline	= TRUE;
		////////////////
		Font.CreateFontIndirect(&lf);
		pOldFont = (CFont*)(PtrDC->SelectObject(&Font));
	}
	else
	{
		lf = m_lf;
		////////////////
		lf.lfWeight		= FW_THIN;
		////////////////
		Font.CreateFontIndirect(&lf);
		pOldFont = (CFont*)(PtrDC->SelectObject(&Font));
	}
	//////////////////////////////// Color
	PtrDC->SetTextColor(GetColor());	   	
	//////////////////////////////// Mode
	PtrDC->SetBkMode(TRANSPARENT);	   	
    //////////////////////////////// Label Out
    
    if (!m_nTilt)
		PtrDC->TextOut(pt->x,pt->y,text);
	else	
		DrawRotatedString(PtrDC, pt, text, (double)m_nTilt);
	//////////////////////////////// Get Original Font back
	if(pOldFont != NULL)
		PtrDC->SelectObject(pOldFont);
	Font.DeleteObject();
   	
}   

void CDrLabel::DrawRotatedString(CDC* pDC, POINT* s, CString str, double angle)
{
	CBrush		brush;
	CDC 		DCm1,DCm2;
	CBitmap		BM1,BM2;
	CRect		r;
	int			l,w,c;
	TEXTMETRIC	tm;
	///////////////////////////////////////////////// 
 	/////////////////////////////////////////////////
	brush.CreateSolidBrush( RGB(0,0,0) );	// assumed BLACK Window
	l = strlen(str);
	c = (w = (pDC->GetTextExtent(str, l )).cx );  // according to current Font
	pDC->GetTextMetrics(&tm );
	r.SetRect(0, 0, w, -w );    // Logical
	//////////////////////////////
	DCm1.CreateCompatibleDC(pDC);
	DCm2.CreateCompatibleDC(pDC);
	pDC->LPtoDP(&r);
	BM1.CreateCompatibleBitmap(pDC, r.Width(), r.Height() );
	BM2.CreateCompatibleBitmap(pDC, r.Width(), r.Height() );
	pDC->DPtoLP(&r);
	DCm1.SelectObject(&BM1);
	DCm2.SelectObject(&BM2);
	DCm1.SetMapMode(pDC->GetMapMode() );
	DCm2.SetMapMode(pDC->GetMapMode() );
    ////////////////////////////////////
	r.NormalizeRect();
	DCm1.FillRect(&r, &brush );	// erase the bitmap
	DCm2.FillRect(&r, &brush );	// erase the bitmap 
	brush.DeleteObject();
	DCm1.SetBkMode(TRANSPARENT); 
	/////////////////////////////////////////////// font & Forecolor
    CFont	Font;
    CFont*	pOldFont;
	Font.DeleteObject();
	Font.CreateFontIndirect(&m_lf);
	pOldFont = (CFont*)(DCm1.SelectObject(&Font));
//	DCm1.SetTextColor(pDC->GetTextColor() );
	DCm1.SetTextColor(GetColor() );
	
	POINT ptLeftTop;
	ptLeftTop.x = 0; 
	ptLeftTop.y = (int)(((c-tm.tmHeight)*0.5) + 0.5);
	
	DCm1.TextOut(ptLeftTop.x, -ptLeftTop.y, str, l );	// draw the string
	 
	if(pOldFont != NULL)
		DCm1.SelectObject(pOldFont);
	//////////////////////////////////////// r is being reused/ I am Lazy!
	int width  = r.Width();
	int height = r.Height();
	r.left   = ptLeftTop.x;
	r.top    = -ptLeftTop.y;
	r.right  = width;
	r.bottom = height;
	////////////////////////////////////////
	RotateBitMap( &DCm1, &DCm2, &r, angle );
	////////////////////////////////////////
	POINT ptOrg;
	ptOrg.x = 0;
	ptOrg.y = 0;
	DCm2.DPtoLP(&ptOrg);
//	pDC->TextOut(s->x,s->y,".",1);	// draw the end marker
	pDC->BitBlt
		(s->x - r.left, s->y - r.top, width, -height,
									 &DCm2, ptOrg.x, ptOrg.y, SRCCOPY );
	///////////
	DCm1.DeleteDC();
	DCm2.DeleteDC();
	BM1.DeleteObject();
	BM2.DeleteObject();
	/////////////////////////////////////
}

void CDrLabel::RotateBitMap(CDC* pdcSrc,CDC* pdcDst,CRect* r,double angle)
{

	///////////////////////
	POINT ptLeftTop;
	ptLeftTop.x	= r->left;
	ptLeftTop.y = r->top;
	///////////////////////
	register
		short	x,y,
				xMx	= (short)r->right,       // storing width
				yMx	= (short)r->bottom;      // storing height

	double		a	= angle * 0.017453292519943;

	register
		double
				txcr, txsr,
				sr	= sin(a),
				cr	= cos(a),
				cX	= -xMx * 0.5,
				cY	= -yMx * 0.5,
				tycr= cY * cr,
				tysr= cY * sr;
	double
		cXcr	= cX * cr,
		cXsr	= cX * sr;

	DWORD	dwColor;

	for( y = 0; y < yMx; y++, tycr += cr, tysr += sr )
	{
		for( x = 0, txcr = cXcr, txsr = cXsr; x < xMx; x++, txcr += cr, txsr += sr )
			if( (dwColor = pdcSrc->GetPixel( x, -y )) != RGB(0,0,0) )	// assumed BLACK Window
				pdcDst->SetPixel(
					 (int)(txcr  + tysr - cX + 0.5),
					-(int)(-txsr + tycr - cY + 0.5),
					dwColor
				);
	}				
	//////////////////////////////////////////////// Left Top Corner
	int xLT =  (int)( cXcr  + (-ptLeftTop.y+cY)*sr - cX + 0.5);
	int yLT = -(int)(-cXsr  + (-ptLeftTop.y+cY)*cr - cY + 0.5);
	r->left = xLT;
	r->top  = yLT;
	////////////
			
}

/////////////////////////////////////////////////////////////////////////////
void CDrLabel::FinishObject(CClientDC* pDC,int nViewNumber)
{ 

    /////////////////////////////////////// for Node Label, viewNumber unimportant
	if((GetViewNum() != nViewNumber) && (GetType() != LABEL_NODE)) return;
	///////////////////////////////////////////// 
	// Calculate the bounding rectangle.  It's needed for smart
	// repainting.
	/////////////////////////////////////////////
	POINT pt = GetCorner(nViewNumber);
	//////////////////////////////////
	m_rectBounding.left   = pt.x;
	m_rectBounding.top    = pt.y;
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
	//////////////////////////////////////// 	Set Right Bottom Corner	
	POINT addLOG;
	int nLen = m_Text.GetLength();
	addLOG.x = nWidth*nLen;  // Logical Coord.
	addLOG.y = nHeight;
	SetOtherCorner(addLOG);
	/////////////////////////////// 
    POINT ptOther = GetOtherCorner(); // addition for other corner
    POINT pt2;
    pt2.x = pt.x + ptOther.x;
    /////////////////////////////// Rotated string
    if(m_nTilt)
    {
    	pt2.y = pt.y - ptOther.x;			// Square area:
    	m_rectBounding.left -= ptOther.x;   // 2*widthx2*width 
		m_rectBounding.top  += ptOther.x;   // invalidation
    }	
    else	
    	pt2.y = pt.y - ptOther.y;
    /////////////////////////////	
	m_rectBounding.right  = pt2.x;
	m_rectBounding.bottom = pt2.y;
    //////////////////////////////////
	return; 
	
}

BOOL CDrLabel::IsKeyMatch(CDrObject* pObject, CString KeyID,UINT KeyNo)
{

	CDrLabel* pLabel = (CDrLabel*)(pObject);
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

BOOL CDrLabel::IsObjectHit(CClientDC* ptrDC,int nNet,
								POINT point,CRect* pRect,int nViewNumber)
{
	////////////// 
	CSize	Size; 
   	/////////////////////////////////////// for Node Label, viewNumber unimportant
	if((GetViewNum() != nViewNumber) &&
		 (GetType() != LABEL_NODE)) return FALSE; 
   	///////////////////////////////////////// Transformed/Projected or Screen
	POINT ptC = GetCorner(nViewNumber);
	//////////////////////////////////
	pRect->left = ptC.x;
   	pRect->top	= ptC.y;
   	///////////////////////////////////////// get FontSize etc.
	CFont	Font;
	Font.DeleteObject();
	Font.CreateFontIndirect(&m_lf);
	CFont* pOldFont = (CFont*) ptrDC->SelectObject(&Font);
	Size		  = ptrDC->GetTextExtent(m_Text,m_Text.GetLength());
	ptrDC->SelectObject(pOldFont);
	////////////////////////////////////////////////////////////
   	pRect->right  = pRect->left + Size.cx; 
   	pRect->bottom = pRect->top  - Size.cy; // Logical
   	///////////////////////////////////////////////////////////// Change to Device 
   	POINT pt;
   	pt = point;
   	CRect NetRect;
   	NetRect.left 	= pRect->left;
   	NetRect.top 	= pRect->top; 
   	NetRect.right	= pRect->right;
   	NetRect.bottom	= pRect->bottom;
   	////////////////////////////////
   	ptrDC->LPtoDP(&NetRect);
	NetRect.NormalizeRect();
   	ptrDC->LPtoDP(&pt);
//    	if((point.x>=pRect->left) && (point.x<=pRect->right) &&
//       		(point.y<=pRect->top ) && (point.y>=pRect->bottom)) 
	if(NetRect.PtInRect(pt))
       	return TRUE; 
	else
		return FALSE;
}

void CDrLabel::Serialize(CArchive& ar)
{

	CDrObject::Serialize( ar);              // must call base class Serializer
	//////////////////////////////////////     
	WORD	nElementType,nObjectNo,nObjectType,nLayer,w;
	DWORD   dw;
	BYTE	b;
	if (ar.IsStoring())
	{
		TRACE( " Label	:Storing\n");	// TODO: add storing code here

		ar	<<	/*int*/		(WORD)	m_nElemType	// Type = PIPE = 2 in ElGlobal.h
			<<	/*int*/		(WORD)	m_nObjectType
			<<	/*UINT*/	(WORD)	m_nObjectNo 
			//////////////////////////////////////
			<<	/*BOOL*/	(BYTE)	m_bMoved
			//////////////////////////////////////
			<<	/*CRect*/	m_rectBounding // smallest rect that surrounds 

			<<	/*UINT*/	(WORD)	m_nLayer;
		ar	<<	/*POINT*/ 	m_pt[0];
		ar	<<	/*COLORREF*/(DWORD)	m_Color		// Text Color
			<<	/*CString*/			m_Text		// Label Card
			<<	/*POINT*/			m_RBCorner	//  Add x,y for RightBottom Corner
			<<	/*int*/		(WORD)	m_nIndex	// nodeId index or other based on m_ntype
			<<	/*int*/		(WORD)	m_nType		// we save coord in node and use here
												// -1 = Node Label(for All Views: default)
												//  0 = Label
			<<	/*int*/		(WORD)	m_nViewNum							
			<<	/*int*/		(WORD)	m_nRotation	// for rotating text
			<<	/*int*/		(WORD)	m_nTilt
			<<	/*int*/		(WORD)	m_nShift;
		for(int i = 0;i<MAX_DRAWVIEW;i++)							
			ar	>>/*POINT*/ m_pt[i];  
		/////////////////////////////////////////////	
		ar.Write(/*LOGFONT*/	&m_lf,sizeof(LOGFONT) );
		/////////////////////////////////////////////
		//////////////////////////////////////////////////////
		for ( i=0; i< MAX_LABEL_DRAW_PT;i++)	
			ar.WriteObject(m_pDrNode[i]);
		//////////////////////////////////////////////////////

 	}
	else
	{
		TRACE(" Label	:Loading\n");	// TODO: add loading code here

		ar	>>	/*int*/		nElementType
			>>	/*int*/		nObjectType
			>>	/*UINT*/	nObjectNo;
		//////////////////////////////////////
		ar	>>	b;
		m_bMoved = (BOOL)b;
		//////////////////////////////////////
		ar	>>	/*CRect*/	m_rectBounding // smallest rect that surrounds 

			>>	/*UINT*/	nLayer;
		ar	>>	/*POINT*/	m_pt[0];
		ar	>>	/*COLORREF*/dw;
		m_Color = (COLORREF) dw;		// Text Color
		///////////////////////
		ar	>>	/*CString*/			m_Text		// Label Card
			>>	/*POINT*/			m_RBCorner	//  Add x,y for RightBottom Corner
			>>	/*int*/w;
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
		for(int i = 0;i<MAX_DRAWVIEW;i++)							
			ar	>>/*POINT*/ m_pt[i];  
		/////////////////////////////////////////////	
		ar.Read(/*LOGFONT*/	&m_lf,sizeof(LOGFONT) );
		/////////////////////////////////////////////
		//////////////////////////////////////////////////////	
		for ( i=0; i< MAX_LABEL_DRAW_PT;i++)	
			m_pDrNode[i] = (CDrNode*)ar.ReadObject(RUNTIME_CLASS(CDrNode));
		//////////////////////////////////////////////////////
		m_nElemType		  	= 	(int)nElementType;		// Type = PIPE = 2 in ElGlobal.h
    	m_nObjectType		= 	(int)nObjectType;
    	m_nObjectNo			= 	(UINT)nObjectNo;
		m_nLayer			=	(UINT)nLayer;
    	/////////////////////////////        

	}        
	////////////////////////

} 
/////////////////////// END of MODULE /////////////////

