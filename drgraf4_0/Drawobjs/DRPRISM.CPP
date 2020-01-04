// prism.cpp : implementation file
//
#include "stdafx.h"

#include "DrPrism.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrism
/*
BEGIN_MESSAGE_MAP(CPrism, CGrafObject)
	//{{AFX_MSG_MAP(CPrism)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
/////////////////////////////////////////////////////////////////////////////
CPrism::CPrism(UINT nLength,UINT nWidth,UINT nHeight)
{
	
	m_Coord[0][0] = 0.0;
	m_Coord[1][0] = 0.0;
	m_Coord[2][0] = 0.0;

	m_Coord[0][1] = 0.0;
	m_Coord[1][1] = (double) nHeight;
	m_Coord[2][1] = 0.0;

	m_Coord[0][2] = (double) nLength;
	m_Coord[1][2] = (double) nHeight;
	m_Coord[2][2] = 0.0;

	m_Coord[0][3] = (double) nLength;
	m_Coord[1][3] = 0.0;
	m_Coord[2][3] = 0.0;

	m_Coord[0][4] = 0.0;
	m_Coord[1][4] = 0.0;
	m_Coord[2][4] = (double) nWidth;

	m_Coord[0][5] = 0.0;
	m_Coord[1][5] = (double) nHeight;
	m_Coord[2][5] = (double) nWidth;

	m_Coord[0][6] = (double) nLength;
	m_Coord[1][6] = (double) nHeight;
	m_Coord[2][6] = (double) nWidth;

	m_Coord[0][7] = (double) nLength;
	m_Coord[1][7] = 0.0;
	m_Coord[2][7] = (double) nWidth;

}
	

void CPrism::DrawPrism(CDC* PtrDC,POINT Origin,double Tran[][3])
{
	
   	CPen    Pen;
   	CPen*   PtrOldPen;
//   	CBrush  Brush;
//   	CBrush* PtrOldBrush;
	
    ///////////////////////////////////////////////////
// Create Green Pen 3 Pixel wide;   
   	Pen.CreatePen (PS_SOLID,3,0x00ff00);
   	PtrOldPen = PtrDC->SelectObject(&Pen);
//    PtrOldBrush= (CBrush*)PtrDC->SelectStockObject(NULL_BRUSH); 
//    PtrOldBrush= PtrDC->SelectObject(&Brush);
/*
	CString str;
	char buf[200];
	sprintf(buf,"DrawPrism");
	AfxMessageBox(str=buf);
	sprintf(buf,"m_Coord:\n 00 10 20..."); 
	str = buf;
	sprintf(buf,"\n %f %f %f ",m_Coord[0][0],m_Coord[1][0],m_Coord[2][0]); 
    str += buf;
	sprintf(buf,"\n %f %f %f ",m_Coord[0][1],m_Coord[1][1],m_Coord[2][1]); 
    str += buf;
	sprintf(buf,"\n %f %f %f ",m_Coord[0][2],m_Coord[1][2],m_Coord[2][2]); 
    str += buf;
	sprintf(buf,"\n %f %f %f ",m_Coord[0][3],m_Coord[1][3],m_Coord[2][3]); 
    str += buf;
	sprintf(buf,"\n %f %f %f ",m_Coord[0][4],m_Coord[1][4],m_Coord[2][4]); 
    str += buf;
	sprintf(buf,"\n %f %f %f ",m_Coord[0][5],m_Coord[1][5],m_Coord[2][5]); 
    str += buf;
	sprintf(buf,"\n %f %f %f ",m_Coord[0][6],m_Coord[1][6],m_Coord[2][6]); 
    str += buf;
	sprintf(buf,"\n %f %f %f ",m_Coord[0][7],m_Coord[1][7],m_Coord[2][7]); 
    str += buf;
    AfxMessageBox(str);
    
*/    
    // Transform points 3 to 2
   	double Coord[3];
    for (int i = 0;(UINT)i< MAX_PT; i++)
    {   
    	for(int j = 0;j<3; j++)
    		Coord[j] = m_Coord[j][i];  
/*    		
	sprintf(buf,"Coord:\n 0 1 2..."); 
	str = buf;
	sprintf(buf,"\n %f\n %f\n %f ",Coord[0],Coord[1],Coord[2]); 
    str += buf;
	AfxMessageBox(str); 
	
	sprintf(buf,"Tran:\n 00 01 02..."); 
	str = buf;
	sprintf(buf,"\n %f %f %f ",Tran[0][0],Tran[0][1],Tran[0][2]); 
    str += buf;
	sprintf(buf,"\n %f %f %f ",Tran[1][0],Tran[1][1],Tran[1][2]); 
    str += buf;
	AfxMessageBox(str);
*/	
		m_pt[i] = TransformPoint3to2(Coord,Tran);
	// Shift prism to Origin
		m_pt[i].x = Origin.x + m_pt[i].x;
		m_pt[i].y = Origin.y + m_pt[i].y;
	}
	/////////////////////////////// Draw	
    GoConnect(PtrDC,m_pt);
    /////////////////////////////
//    PtrDC->SelectObject(PtrOldBrush);             
//    Brush.DeleteObject(); 
/*
	CString str;
	char buf[500];
	AfxMessageBox(str=buf);	 
*/
	///////////////////////////////   	
   	PtrDC->SelectObject(PtrOldPen);   
   	Pen.DeleteObject();

} 

void CPrism::GoConnect(CDC* PtrDC,POINT* pt)
{
	PtrDC->MoveTo(pt[0].x,pt[0].y);
	PtrDC->LineTo(pt[1].x,pt[1].y);
	PtrDC->LineTo(pt[2].x,pt[2].y);
	PtrDC->LineTo(pt[3].x,pt[3].y);
	PtrDC->LineTo(pt[0].x,pt[0].y);
    ////////////////////////////////
	PtrDC->MoveTo(pt[4].x,pt[4].y);
	PtrDC->LineTo(pt[5].x,pt[5].y);
	PtrDC->LineTo(pt[6].x,pt[6].y);
	PtrDC->LineTo(pt[7].x,pt[7].y);
	PtrDC->LineTo(pt[4].x,pt[4].y);
    ////////////////////////////////
 	PtrDC->MoveTo(pt[4].x,pt[4].y);
	PtrDC->LineTo(pt[0].x,pt[0].y);
    ////////////////////////////////
 	PtrDC->MoveTo(pt[5].x,pt[5].y);
	PtrDC->LineTo(pt[1].x,pt[1].y);
    ////////////////////////////////
 	PtrDC->MoveTo(pt[6].x,pt[6].y);
	PtrDC->LineTo(pt[2].x,pt[2].y);
    ////////////////////////////////
 	PtrDC->MoveTo(pt[7].x,pt[7].y);
	PtrDC->LineTo(pt[3].x,pt[3].y);
   
}   
    
    
POINT CPrism::TransformPoint3to2(double* Coord,double Tran[][3])
{                                                              
///////////////////////////////////////////////////// Transform

	double sum,Temp[2];
	POINT pt;
/*	
	CString str;
	char buf[1024];
	sprintf(buf,"Coord:\n 0 1 2..."); 
	str = buf;
	sprintf(buf,"\n %f\n %f\n %f ",Coord[0],Coord[1],Coord[2]); 
    str += buf;
	AfxMessageBox(str); 
	
	sprintf(buf,"Tran:\n 00 01 02..."); 
	str = buf;
	sprintf(buf,"\n %f %f %f ",Tran[0][0],Tran[0][1],Tran[0][2]); 
    str += buf;
	sprintf(buf,"\n %f %f %f ",Tran[1][0],Tran[1][1],Tran[1][2]); 
    str += buf;
	AfxMessageBox(str);
*/	 
	
	for (int i =0;i<2;i++)
	{         
		sum = 0.0;
    	for (int j=0;j<3;j++)
			sum += Coord[j] * Tran[i][j];
		Temp[i] = sum;
/*		 
	sprintf(buf,"i Coord[j] Tran[i][j] sum Temp[i]...\n"); 
	str = buf;
	sprintf(buf,"%u %f %f %f %f ",i,Coord[j],Tran[i][j],sum,Temp[i]); 
	str += buf;
    AfxMessageBox(str);
*/	
	}        
	pt.x = (UINT)Temp[0];
	pt.y = (UINT)Temp[1]; 
/*	
	sprintf(buf,"Tran2to3: pt.x = %u, pt.y = %u", pt.x,pt.y);
	AfxMessageBox(str=buf);
*/	
	return (pt);
}		
