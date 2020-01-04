// drgradoc.cpp : implementation of the CDrGrafDoc class
//

#include "stdafx.h"

#include "drgraf.h"

#include "drgradoc.h"

#include <math.h>


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
////////////////////////////////
static double pi = acos(0.)*2.;

////////////////////////////////
void CDrGrafDoc::SetTranArray(double Tran[][3])
{
    //////////////////////////////////////
	double cosT,cosR,sinT,sinR;
	//////////////////////////////////////// 	
	cosT =  cos(((double)m_nTilt)*pi/180.);
	sinT =  sin(((double)m_nTilt)*pi/180.);
	cosR =  cos(((double)m_nRotation)*pi/180.);
	sinR =  sin(((double)m_nRotation)*pi/180.);
    //////////////////////////////////////////////////////////// Fill Array
    // NOTE: RIGHTHandedScrew(RHS)
    //	     Positive Rotation: Anticlockwise about the axis
    //							pointing AWAY FROM origin
    //	     Positive Tilt    : Anticlockwise about the axis
    //							pointing INTO origin
    ////////////////////////////////////////////////////////////
    // UP & X or Y Vertical
	
	Tran[0][0] =  cosR;
	Tran[1][0] = -sinT*sinR;
	Tran[0][1] =  0;
	Tran[1][1] =  cosT;
	Tran[0][2] = -sinR;
	Tran[1][2] = -cosR*sinT; 
////////////////////////////////////////// D O  N O T  N E E D 
/*	
	//////////////////////// Z(2) Vertical UP: Y(3) INTO the paper to keep RHS
	if(m_nVertical == 3 && m_nPositive == 1)
	{
		Tran[0][2] = -Tran[0][2];
		Tran[1][2] = -Tran[1][2];
	}
	if(m_nPositive == 2)
	{
		Tran[1][1] = -Tran[1][1];
		if(m_nVertical == 2)  // DOWN  & Y(2) Vertical:
		{
			Tran[0][2] = -Tran[0][2];  // Axis 1 	 Ist into paper
			Tran[1][2] = -Tran[1][2];  // Axis 1 	 2nd into paper
    	}
	}    	
	/////////////////////////  
*/
/*
    ///////////////////////////////////////   
	
	CString str;
	char buf[1024];
	sprintf(buf,"DocSetTran\n  m_nTilt =%u\n  nRotation = %u ",
	 		m_nTilt,m_nRotation );
	AfxMessageBox(str=buf);	 
				
    /////////////////////////// Get Transformation Array
	sprintf(buf,"DocSetTran- Tran\n  00=%f 01=%f 02=%f\n  10=%f 11=%f 12=%f",
		Tran[0][0],Tran[0][1],Tran[0][2],Tran[1][0],Tran[1][1],Tran[1][2]);
	AfxMessageBox(str=buf);	 
    //////////////////////////////////////
*/		
}

void CDrGrafDoc::UpdateTranArray(double Tran[][3])
{
    //////////////////////////////////////
	for(int i =0; i<2;i++) 
		for(int j =0; j<3;j++) 
			m_dTran[i][j] = Tran[i][j];
}
				

void CDrGrafDoc::GetTranArray(double Tran[][3])
{
    ///////////////////////////////////////   
/*	
	CString str;
	char buf[1024];
	sprintf(buf,"DocGetTran  m_nTiltDefault =%u nRotation = %u ",
	 		m_nTilt,m_nRotation );
	AfxMessageBox(str=buf);	 
				
    /////////////////////////// Get Transformation Array
	sprintf(buf,"DocGetTran- m_dTran\n  00=%f 01=%f 02=%f\n  10=%f 11=%f 12=%f",
		m_dTran[0][0],m_dTran[0][1],m_dTran[0][2],m_dTran[1][0],m_dTran[1][1],m_dTran[1][2]);
	AfxMessageBox(str=buf);	 
    ////////////////////////////////////// 
*/    
	for(int i =0; i<2;i++)
	{ 
		for(int j =0; j<3;j++) 
			Tran[i][j] = m_dTran[i][j];
    }
} 

void CDrGrafDoc::GetTranOldArray(double Tran[][3])
{
    //////////////////////////////////////
	for(int i =0; i<2;i++) 
		for(int j =0; j<3;j++) 
			Tran[i][j] = m_dTranOld[i][j];
}
				
void CDrGrafDoc::SetTranOldArray(double Tran[][3])
{
    //////////////////////////////////////
	for(int i =0; i<2;i++) 
		for(int j =0; j<3;j++) 
			m_dTranOld[i][j] = Tran[i][j];
}
				
void CDrGrafDoc::GetTranDefaultArray(double Tran[][3])
{
    //////////////////////////////////////
	for(int i =0; i<2;i++) 
		for(int j =0; j<3;j++) 
			Tran[i][j] = m_dTranDefault[i][j];
}
				
void CDrGrafDoc::SetTranDefaultArray(double Tran[][3])
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
