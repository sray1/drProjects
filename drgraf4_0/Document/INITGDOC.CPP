// drgradoc.cpp : implementation of the CDrGrafDoc class
//

#include "stdafx.h"
#include "drgraf.h"

#include "node.h"
#include "drgradoc.h"
#include "grafdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////// INITIALIZE 
void CDrGrafDoc::InitializeDraw()
{
	CGrafDoc* pGrDoc = (CGrafDoc*)(theApp.m_pDoc);
////////////////////////////// Set Layer Info.
	UINT	i,j;
//                          save
	m_nCurrentLayer    = m_nCurrentLayerDefault;
	m_nCurrentLayerOld = m_nCurrentLayerDefault;
//                          initialize 			
	for(i=0;i<MAX_LAYER;i++)
	{      
		for(j=0;j<2;j++)
		{
			m_nLayer   [i][j] = m_nLayerDefault[i][j];  
			m_nLayerOld[i][j] = m_nLayerDefault[i][j];
		}			
	}
////////////////////////////// Pen	
	int nPenStyleConstants[] = {PS_SOLID,PS_DASH,PS_DOT,PS_DASHDOT,PS_DASHDOTDOT,0};
	CString PenStyleNames[] = {"Solid","Dash","Dot","Dash Dot","Dash Dot Dot //	     Positive Rotation: Anticlockwise about the axis
    //							pointing AWAY FROM origin
    //	     Positive Tilt    : Anticlockwise about the axis
    //							pointing INTO origin
    ////////////////////////////////////////////////////////////
	Tran[0][0] =  cosR;
	Tran[1][0] = -sinT*sinR;
	Tran[0][1] =  0;
	Tran[1][1] =  cosT;
	Tran[0][2] = -sinR;
	Tran[1][2] = -cosR*sinT;
////////////////////////////////////////////////// D O N O T  N E E D	
/*	
    // UP & X or Y Vertical
	
	TranPenColor		= m_nPenColorDefault;
	m_nPenWidthOld	= m_nPenWidth;         
	m_nPenStyleOld	= m_nPenStyle;
	m_nPenColorOld	= m_nPenColor;
	//////////////////////////////
	pGrDoc->ReplacePen();
////////////////////////////// Set SearchNet		
	m_nSearchNet    = m_nSearchNetDefault;
	m_nSearchNetOld = m_nSearchNetDefault;
	  	
////////////////////////////// Set Axis Info	
//    m_nAxes[3];
//    m_nVertical;
//    m_nPositive;
	pGrDoc->GetAxesDefault(m_nAxes);
	pGrDoc->GetAxesDefault(m_nAxesOld);
    m_nVertical          = 	m_nVerticalDefault;
    m_nVerticalOld       = 	m_nVerticalDefault;
	m_nPositive          =  m_nPositiveDefault;
	m_nPositiveOld       =  m_nPositiveDefault;
	
/////////////////////////////// Set Eye Position
    m_nTilt              =	m_nTiltDefault;
    m_nRotation          =  m_nRotationDefault;
    m_nIncrement         =  m_nIncrementDefault;
    m_nTiltOld           =	m_nTiltDefault;
    m_nRotationOld       =  m_nRotationDefault;
    m_nIncrementOld      =  m_nIncrementDefault;
    /////////////////////////// Set Transformation Array
    pGrDoc->GetTranDefaultArray(m_dTran);
    pGrDoc->GetTranDefaultArray(m_dTranOld);
}
