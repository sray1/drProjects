// axis.cpp : implementation file
//
#include "stdafx.h" 

//#include "globals.h" 
#include "3DMath.h" 
#include "DrawView.h" 
////////////////////
#include "DrAxis.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
////////////////////////////////
/*
BEGIN_MESSAGE_MAP(CAxis,CGrafObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CAxis)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/

IMPLEMENT_DYNAMIC(CAxis,CObject)
//////////////////////////////////////////////
// CAxis
//////////////////////////////////////////////
CAxis::CAxis()                // 
{
} 
CAxis::CAxis(UINT nLen)                // 
{
	C3DMath Math3D; 
	///////////////////////////////////////// 
	m_nLength	=  nLen;
	double dLen	= (double)m_nLength;
	/////////////////////////////////////////
	Math3D.Set3DPts(&m_Coord[0],0   ,0   ,0   );
	Math3D.Set3DPts(&m_Coord[1],dLen,0   ,0   );
	Math3D.Set3DPts(&m_Coord[2],0   ,dLen,0   );
	Math3D.Set3DPts(&m_Coord[3],0   ,0   ,dLen);
    ///////////////////////////////// Tag
    int nTag = m_nLength + 5;
    double dTag = (double)nTag;
    ///////////////////////////
	Math3D.Set3DPts(&m_Coord[4],dTag,0   ,0   );
	Math3D.Set3DPts(&m_Coord[5],0   ,dTag,0   );
	Math3D.Set3DPts(&m_Coord[6],0   ,0   ,dTag);
	///////////////////////////////// Prism
	double dLe3	= dLen/3;
	double dLe2	= 2*dLe3;
	/////////////////////
	Math3D.Set3DPts(&m_Coord[7] ,dLe3,0   ,0	);
	Math3D.Set3DPts(&m_Coord[8] ,dLe3,dLe3,0	);
	Math3D.Set3DPts(&m_Coord[9] ,0   ,dLe3,0	);
	
	Math3D.Set3DPts(&m_Coord[10],0   ,0   ,dLe2);
	Math3D.Set3DPts(&m_Coord[11],dLe3,0   ,dLe2);
	Math3D.Set3DPts(&m_Coord[12],dLe3,dLe3,dLe2);
	Math3D.Set3DPts(&m_Coord[13],   0,dLe3,dLe2);
    //////////////////////////////////////////////
    
}

void CAxis::DrawAxes(CDC* PtrDC,POINT Origin,CView* pView)
{

	CDrawView* pDrawView = (CDrawView*)pView;
	/////////////////////////////////////////	
	WORLD 	Cin,Cout,Dest,Dest0;
	//////////////
    for (int i = 0;(UINT)i< MAX_PT_AXIS; i++)
    {   
   		Cin = m_Coord[i];  
    	///////////////////////////// XForm
		pDrawView->Transform(&Cin,&Cout); 
    	///////////////////////////// Project
		pDrawView->Project(&Cout,&Dest,FALSE);
		if(i==0)
			Dest0 = Dest;
		/////////////////////////////////////// Translate by Dest0
		Dest.x -= Dest0.x;
		Dest.y -= Dest0.y;
		Dest.z -= Dest0.z;
		/////////////////////////////////////// scale with CW:Dimension
		double Width_U,Width_V;
		pDrawView->GetCWDim(&Width_U,&Width_V); 
		////////////////////////////
		m_pt[i].x = (UINT)(Dest.x * Width_U); 
		m_pt[i].y = (UINT)(Dest.y * Width_V); 
	// Shift Axis to Origin
		m_pt[i].x = Origin.x + m_pt[i].x;
		m_pt[i].y = Origin.y + m_pt[i].y;
	}
	/////////////////////////////// Draw	
    GoDoIt(PtrDC,m_pt);
    /////////////////////////////
} 

void CAxis::GoDoIt(CDC* PtrDC,POINT* pt)
{
    char*  AxesTag[3]={"X","Y","Z"}; 
    ///////////////////////////////////////// Axes
	PtrDC->MoveTo(pt[0].x,pt[0].y);
	PtrDC->LineTo(pt[1].x,pt[1].y);
	///////////////////////////////
	PtrDC->MoveTo(pt[0].x,pt[0].y);
	PtrDC->LineTo(pt[2].x,pt[2].y);
	///////////////////////////////
	PtrDC->MoveTo(pt[0].x,pt[0].y);
	PtrDC->LineTo(pt[3].x,pt[3].y);
	///////////////////////////////////////// Prism
	PtrDC->MoveTo(pt[7].x,pt[7].y);
	PtrDC->LineTo(pt[8].x,pt[8].y);
	PtrDC->LineTo(pt[9].x,pt[9].y);
	
	PtrDC->MoveTo(pt[10].x,pt[10].y);
	PtrDC->LineTo(pt[11].x,pt[11].y);
	PtrDC->LineTo(pt[12].x,pt[12].y);
	PtrDC->LineTo(pt[13].x,pt[13].y);
	PtrDC->LineTo(pt[10].x,pt[10].y);
	
	PtrDC->MoveTo(pt[11].x,pt[11].y);
	PtrDC->LineTo(pt[ 7].x,pt[ 7].y);
	PtrDC->MoveTo(pt[12].x,pt[12].y);
	PtrDC->LineTo(pt[ 8].x,pt[ 8].y);
	PtrDC->MoveTo(pt[13].x,pt[13].y);
	PtrDC->LineTo(pt[ 9].x,pt[ 9].y);
    ///////////////////////////////////////// Tag
    COLORREF OldCol = PtrDC->SetTextColor(RGB(0,255,0));
	PtrDC->TextOut(pt[4].x,pt[4].y,AxesTag[0],1); 
	PtrDC->TextOut(pt[5].x,pt[5].y,AxesTag[1],1); 
	PtrDC->TextOut(pt[6].x,pt[6].y,AxesTag[2],1); 
    PtrDC->SetTextColor(OldCol);
	/////////////////////////////////////////
}   
//////////////////////////////////// end of module ///////////////





