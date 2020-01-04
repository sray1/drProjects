// drgradoc.cpp : implementation of the CDrGrafDoc class
//

#include "stdafx.h"
#include <math.h>

//#include "node.h" 
#include "drgraf.h"
#include "drgradoc.h"
#include "grafdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

////////////////////////////////
static double pi = acos(0.)*2.;

/////////////////////////////////////////////////////////////// Read Defaults
void CDrGrafDoc::ReadDefaultsDraw()
{
////////////////////////////// Set SearchNet in pixels		
//    m_nSearchNet;                  
	m_nSearchNetDefault = 10;
	  	
//////////////////////////////////////////////////TEMPORARILY being Set HERE
//                                                Later Read in from DOC FILE
////////////////////////////// Set Layer Info.
	m_nLayerDefault[0][0] = 1;
	m_nLayerDefault[0][1] = 0;  	//Ist Layer=Current(Later Read in from INI)	
//                          save
	m_nCurrentLayerDefault    = 0;
//                          initialize 			
	for(UINT i=1;i<MAX_LAYER;i++)
	{
		m_nLayerDefault[i][0] = 1;  //    InActive
		m_nLayerDefault[i][1] = 1;  //	   NOT Current
	}
	m_nLayerDefault[MAX_LAYER-1][0] = 0;  	//Last Layer ALWAYS Active
////////////////////////////// Set Pen
	m_nPenStyleDefault = PS_SOLID;
	m_nPenStyleIndex   = 0;	
	m_nPenWidthDefault = 1;
	m_nPenColorDefault = RGB(255,0,0);  // Red
////////////////////////////// Set Axis Info	
//    m_nAxes[3];
//    m_nVertical;
//    m_nPositive;

	m_nAxesDefault[0]    = 1;
	m_nAxesDefault[1]    = 2;
	m_nAxesDefault[2]    = 3;

	m_nVerticalDefault   = 2;   // Y axis              
	m_nPositiveDefault   = 1;   // Upward              
	
/////////////////////////////// Set Eye Position
//    m_nTilt;
//    m_nRotation;
//    m_nIncrement; 
	m_nTiltDefault       = 30;
	m_nRotationDefault   = 30;
	m_nIncrementDefault  =  5; 
	////////////////////////////////////////////////
	CGrafDoc* pGrDoc = (CGrafDoc*)(theApp.m_pDoc);
    pGrDoc->SetTranDefaultArray(m_dTranDefault);
    ////////////////////////////////////////////////
	
}            

void CGrafDoc::GetAxesDefault(UINT* nAxes)
{
	for(int i = 0;i<3;i++)
		nAxes[i] = m_nAxesDefault[i];
}

void CGrafDoc::SetAxesDefault(UINT* nAxes)
{
	for(int i = 0;i<3;i++)
		m_nAxesDefault[i] = nAxes[i];
}

void CGrafDoc::GetTranDefaultArray(double Tran[][3])
{
    //////////////////////////////////////
	for(int i =0; i<2;i++) 
		for(int j =0; j<3;j++) 
			Tran[i][j] = m_dTranDefault[i][j];
}
				
void CGrafDoc::SetTranDefaultArray(double Tran[][3])
{
    ////////////////////////////////////// Default : Y VERTICAL & UP
	double cosT,cosR,sinT,sinR;             
	////////////////////////
	
	cosT =  cos(((double)m_nTiltDefault)*pi/180.0);
	sinT =  sin(((double)m_nTiltDefault)*pi/180.0);
	cosR =  cos(((double)m_nRotationDefault)*pi/180.0);
	sinR =  sin(((double)m_nRotationDefault)*pi/180.0);
    //////////////////////////////////////////////////////////// Fill Array
    // NOTE: RIGHTHandedScrew(RHS)
    //	     Positive Rotation: Anticlockwise about the axis
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
	
	Tran[0][0] =  cosR;
	Tran[1][0] = -sinT*sinR;
	Tran[0][1] =  0;
	Tran[1][1] =  cosT;
	Tran[0][2] = -sinR;
	Tran[1][2] = -cosR*sinT;
	//////////////////////// Z(2) Vertical UP: Y(3) INTO the paper to keep RHS
	if(m_nVerticalDefault == 3 && m_nPositiveDefault == 1)
	{
		Tran[0][2] = -Tran[0][2];
		Tran[1][2] = -Tran[1][2];
	}
	if(m_nPositiveDefault == 2)
	{
		Tran[1][1] = -Tran[1][1];
		if(m_nVerticalDefault == 2)  // DOWN  & Y(2) Vertical:
		{
			Tran[0][2] = -Tran[0][2];  // Axis 1 	 Ist into paper
			Tran[1][2] = -Tran[1][2];  // Axis 1 	 2nd into paper
    	}
	}    	
	/////////////////////////   
*/	
    ///////////////////////////////////////   
/*	
	CString str;
	char buf[1024];
	sprintf(buf,"DocSetTranDefault\n  m_nTiltDefault =%u\n  nRotationDefault = %u ",
	 		m_nTiltDefault,m_nRotationDefault );
	AfxMessageBox(str=buf);	 
				
    /////////////////////////// Get Transformation Array
	sprintf(buf,"DocSetTran- \n  cosT=%f\n  sinT=%f\n  cosR=%f\n  sinR=%f",
								 cosT,sinT,cosR,sinT	);
	AfxMessageBox(str=buf);	 
	sprintf(buf,"DocSetTran- Tran\n  00=%f 01=%f 02=%f\n  10=%f 11=%f 12=%f",
		Tran[0][0],Tran[0][1],Tran[0][2],Tran[1][0],Tran[1][1],Tran[1][2]);
	AfxMessageBox(str=buf);	 
    //////////////////////////////////////
*/
}
