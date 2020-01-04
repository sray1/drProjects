// GrafObj.cpp : implementation file
//

#include "stdafx.h"     

#include "drgraf.h"
#include "drgradoc.h"

#include "drpen.h"
#include "drfont.h"

#include "SpecMgr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////////////////////////
// CSpecMgr
IMPLEMENT_SERIAL(CSpecMgr,CObject,1)
/*
BEGIN_MESSAGE_MAP(CSpecMgr,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CSpecMgr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
/////////////////////////////////////////////////////////////////////////////
CSpecMgr::CSpecMgr()
{
	////////////////////////
	m_nLastObjectNo 	= 0;
	m_nActiveObjectNo	= 0;
	m_nActiveObjectIndex=-1;
	////////////////////////
}
///////////////////////////////////////////////////////// helpers 
/////////////////////////////////////
static char FmtStr[] = "% 4d.%.2d  ";
///////////////////////////////////// 
//void CDrObject::SetFormatParam()
void CSpecMgr::SetFormatParam()
{

	///////////////////////////////////////////// 
	CDrGrafDoc* pDoc = (CDrGrafDoc*)(theApp.m_pDoc);
	CPrecision* pPrecision = pDoc->GetPrecision();
	////////////////////////////////////////////////
	UINT DecPlaces 	= pPrecision->GetPrecision();
	long lWorldBase = pPrecision->GetWorldBase();
	/////////////////////////////////////////////
	char c0;
	
	c0 = (9 - nDecPlaces) + '0';
	FmtStr[2] = c0;
	
	c0 = nDecPlaces + '0';
	FmtStr[7] = c0;
	
	return;
	
}	
////////////////////////////////////////////////////////// Helper
void CSpecMgr::SetMapFactor()
{
	///////////////////////////////////////////////////// Unit
//	char* MapModes[] ={"","MM_TEXT","MM_LOMETRIC","MM_HIMETRIC","MM_LOENGLISH",
//					  "MM_HIENGLISH","MM_TWIPS","MM_ISOMETRIC","MM-ANISOMETRIC"};

	double MapValues[]={0.,1.0,.1,.01,.01,.001,.000694,1.,1.};
	
//	UINT nUnitIndex = GetUnitIndex();
	double value 	= MapValues[GetMapModeIndex()];
	///////////////////////////////////////////////
	m_dMapFactor = value;
	//////////////////////////////////////
}	

void CSpecMgr::SetMapModeIndex()
{
	///////////////////////////////////////////////////// Unit
//	char* MapModes[] ={"","MM_TEXT","MM_LOMETRIC","MM_HIMETRIC","MM_LOENGLISH",
//					  "MM_HIENGLISH","MM_TWIPS","MM_ISOMETRIC","MM-ANISOMETRIC"};
/*
	CDrGrafDoc* pDoc = (CDrGrafDoc*)(theApp.m_pDoc);  
	CUnit* pUnit = (CUnit*)pObject->GetUnit();
	UINT nUnitIndex = pUnit->GetUnitIndex(); 
*/
	/////////////////////////////////////////////////////	
	CObjectBase* pObjectBase;
	int index = pObjectBase->GetObjectFirstIndex(UNIT);
	UINT nUnitIndex;
	if(index>=0)
	{	  
		CUnit* pUnit = (CUnit*)pObjectBase->GetObject(index);
		nUnitIndex = pUnit->GetUnitIndex();
	}
	else
	{
		AfxMessageBox(
			"Error:CMapFactor::SetMapModeIndex\n Unit Index Not Found");
		return;
	}		 	 
	/////////////////////////////////////////////////////
	switch(nUnitIndex)
	{
		case 0:
			m_nMapIndex = MM_HIENGLISH;                
			break;
				
		case 1:				// inches - Fractional	// TEMPORARY later
													// 1/16 or 1/32 etc.
													// Isotropic Mode Needed  
			m_nMapIndex = MM_HIENGLISH;                
			break;
				
		case 2:				// Feet
			m_nMapIndex = MM_LOENGLISH;                
			break;
				
		case 3:				// Feet - Fractional	// TEMPORARY later
													// 1/16 or 1/32 etc.
													// Isotropic Mode Needed  
			m_nMapIndex = MM_LOENGLISH;                
			break;
				
		case 4:				// Miles
			m_nMapIndex = MM_LOENGLISH;                
			break;	
			
		case 5:				// Millimeters
			m_nMapIndex = MM_HIMETRIC;                
			break;	
			
		case 6:				// Centimeters
			m_nMapIndex = MM_LOMETRIC;                
			break;	
			
		case 7: 			// Meters
			m_nMapIndex = MM_LOMETRIC;                
			break;	
			
		case 8: 			// Kilometers
			m_nMapIndex = MM_LOMETRIC;                
			break;	
			
	    default:
	        break;
	}
}	
///////////////////////////////////////////////////////////// Helpers	
void CSpecMgr::DStoSC(double* dpt)
{
	/////////////////////////////////////////////////
	CObjectBase* pObjectBase;
	CSpecMgr* pScaleFactor;
	int index = pObjectBase->GetObjectFirstIndex(SCALEFACTOR);
	if(index>=0)
		pScaleFactor = (CSpecMgr*)pObjectBase->GetObject(index);
	else
	{
		AfxMessageBox(
			"Error:CSpecMgr::DStoSC\n ScaleFactor Index Not Found");
		return;
	}		 	 
	///////////////////////////////////////////////// 
    double dScaleFactor = pScaleFactor->GetScaleFactor();
//    dScaleFactor       *= pDoc->GetMapFactor();
    *dpt = (*dpt) * dScaleFactor;    
    ///////////////////////////////////////////// 
    return;
}    

void CSpecMgr::SCtoDS(double* dpt)
{
	/////////////////////////////////////////////////
	CObjectBase* pObjectBase;
	CSpecMgr* pScaleFactor;
	int index = pObjectBase->GetObjectFirstIndex(SCALEFACTOR);
	if(index>=0)
		pScaleFactor = (CSpecMgr*)pObjectBase->GetObject(index);
	else
	{
		AfxMessageBox(
			"Error:CSpecMgr::SCtoDS\n ScaleFactor Index Not Found");
		return;
	}		 	 
	///////////////////////////////////////////////// 
    double dScaleFactor = pScaleFactor->GetScaleFactor();
	///////////////////////////////////////////////// 
//    dScaleFactor       *= pDoc->GetMapFactor();
    *dpt = (*dpt) / dScaleFactor;    
    ///////////////////////////////////////////// 
    return;
}    

void CSpecMgr::DStoSC(int* npt)
{
	/////////////////////////////////////////////////
	CObjectBase* pObjectBase;
	CSpecMgr* pScaleFactor;
	int index = pObjectBase->GetObjectFirstIndex(SCALEFACTOR);
	if(index>=0)
		pScaleFactor = (CSpecMgr*)pObjectBase->GetObject(index);
	else
	{
		AfxMessageBox(
			"Error:CSpecMgr::DStoSC\n ScaleFactor Index Not Found");
		return;
	}		 	 
	///////////////////////////////////////////////// 
    double dScaleFactor = pScaleFactor->GetScaleFactor();
	///////////////////////////////////////////////// 
//    dScaleFactor       *= pDoc->GetMapFactor();
    *npt = (int)( ((double)(*npt))*dScaleFactor);    
    ///////////////////////////////////////////// 
    return;
}    

void CSpecMgr::SCtoDS(int* npt)
{
	/////////////////////////////////////////////////
	CObjectBase* pObjectBase;
	CSpecMgr* pScaleFactor;
	int index = pObjectBase->GetObjectFirstIndex(SCALEFACTOR);
	if(index>=0)
		pScaleFactor = (CSpecMgr*)pObjectBase->GetObject(index);
	else
	{
		AfxMessageBox(
			"Error:CSpecMgr::SCtoDS\n ScaleFactor Index Not Found");
		return;
	}		 	 
	///////////////////////////////////////////////// 
    double dScaleFactor = pScaleFactor->GetScaleFactor();
	///////////////////////////////////////////////// 
//    dScaleFactor       *= pDoc->GetMapFactor();
    *npt = (int)( ((double)(*npt))/dScaleFactor);    
    ///////////////////////////////////////////// 
    return;
}    
void CSpecMgr::DStoSC(LONG* npt)
{
	/////////////////////////////////////////////////
	CObjectBase* pObjectBase;
	CSpecMgr* pScaleFactor;
	int index = pObjectBase->GetObjectFirstIndex(SCALEFACTOR);
	if(index>=0)
		pScaleFactor = (CSpecMgr*)pObjectBase->GetObject(index);
	else
	{
		AfxMessageBox(
			"Error:CSpecMgr::DStoSC\n ScaleFactor Index Not Found");
		return;
	}		 	 
	///////////////////////////////////////////////// 
    double dScaleFactor = pScaleFactor->GetScaleFactor();
	///////////////////////////////////////////////// 
//    dScaleFactor       *= pDoc->GetMapFactor();
    *npt = (LONG)( ((double)(*npt))*dScaleFactor);    
    ///////////////////////////////////////////// 
    return;
}    

void CSpecMgr::SCtoDS(LONG* npt)
{
	/////////////////////////////////////////////////
	CObjectBase* pObjectBase;
	CSpecMgr* pScaleFactor;
	int index = pObjectBase->GetObjectFirstIndex(SCALEFACTOR);
	if(index>=0)
		pScaleFactor = (CSpecMgr*)pObjectBase->GetObject(index);
	else
	{
		AfxMessageBox(
			"Error:CSpecMgr::SCtoDS\n ScaleFactor Index Not Found");
		return;
	}		 	 
	///////////////////////////////////////////////// 
    double dScaleFactor = pScaleFactor->GetScaleFactor();
	///////////////////////////////////////////////// 
//    dScaleFactor       *= pDoc->GetMapFactor();
    *npt = (LONG)( ((double)(*npt))/dScaleFactor);    
    ///////////////////////////////////////////// 
    return;
}    

void CSpecMgr::DStoSC(POINT* pt)
{
	/////////////////////////////////////////////////
	CObjectBase* pObjectBase;
	CSpecMgr* pScaleFactor;
	int index = pObjectBase->GetObjectFirstIndex(SCALEFACTOR);
	if(index>=0)
		pScaleFactor = (CSpecMgr*)pObjectBase->GetObject(index);
	else
	{
		AfxMessageBox(
			"Error:CSpecMgr::DStoSC\n ScaleFactor Index Not Found");
		return;
	}		 	 
	///////////////////////////////////////////////// 
    double dScaleFactor = pScaleFactor->GetScaleFactor();
	///////////////////////////////////////////////// 
//    dScaleFactor       *= pDoc->GetMapFactor();
    pt->x = (int)( ((double)(pt->x))*dScaleFactor);    
    pt->y = (int)( ((double)(pt->y))*dScaleFactor); 
    ///////////////////////////////////////////// 
    return;
}    
void CSpecMgr::SCtoDS(POINT* pt)
{
	/////////////////////////////////////////////////
	CObjectBase* pObjectBase;
	CSpecMgr* pScaleFactor;
	int index = pObjectBase->GetObjectFirstIndex(SCALEFACTOR);
	if(index>=0)
		pScaleFactor = (CSpecMgr*)pObjectBase->GetObject(index);
	else
	{
		AfxMessageBox(
			"Error:CSpecMgr::SCtoDS\n ScaleFactor Index Not Found");
		return;
	}		 	 
	///////////////////////////////////////////////// 
    double dScaleFactor = pScaleFactor->GetScaleFactor();
	///////////////////////////////////////////////// 
//    dScaleFactor       *= pDoc->GetMapFactor();
    pt->x = (int)( ((double)(pt->x))/dScaleFactor);    
    pt->y = (int)( ((double)(pt->y))/dScaleFactor); 
    ///////////////////////////////////////////// 
    return;
}    

void CSpecMgr::DStoSC(LPOINT3* pt)
{
	/////////////////////////////////////////////////
	CObjectBase* pObjectBase;
	CSpecMgr* pScaleFactor;
	int index = pObjectBase->GetObjectFirstIndex(SCALEFACTOR);
	if(index>=0)
		pScaleFactor = (CSpecMgr*)pObjectBase->GetObject(index);
	else
	{
		AfxMessageBox(
			"Error:CSpecMgr::DStoSC\n ScaleFactor Index Not Found");
		return;
	}		 	 
	///////////////////////////////////////////////// 
    double dScaleFactor = pScaleFactor->GetScaleFactor();
	///////////////////////////////////////////////// 
//    dScaleFactor       *= pDoc->GetMapFactor();
    pt->x = (LONG)( ((double)(pt->x))*dScaleFactor);    
    pt->y = (LONG)( ((double)(pt->y))*dScaleFactor); 
    pt->z = (LONG)( ((double)(pt->z))*dScaleFactor); 
    ///////////////////////////////////////////// 
    return;
}    

void CSpecMgr::SCtoDS(LPOINT3* pt)
{
	/////////////////////////////////////////////////
	CObjectBase* pObjectBase;
	CSpecMgr* pScaleFactor;
	int index = pObjectBase->GetObjectFirstIndex(SCALEFACTOR);
	if(index>=0)
		pScaleFactor = (CSpecMgr*)pObjectBase->GetObject(index);
	else
	{
		AfxMessageBox(
			"Error:CSpecMgr::SCtoDS\n ScaleFactor Index Not Found");
		return;
	}		 	 
	///////////////////////////////////////////////// 
    double dScaleFactor = pScaleFactor->GetScaleFactor();
	///////////////////////////////////////////////// 
//    dScaleFactor       *= pDoc->GetMapFactor();
    pt->x = (LONG)( ((double)(pt->x))/dScaleFactor);    
    pt->y = (LONG)( ((double)(pt->y))/dScaleFactor); 
    pt->z = (LONG)( ((double)(pt->z))/dScaleFactor); 
    ///////////////////////////////////////////// 
    return;
}    


void CSpecMgr::DStoSC(LPOINT* pt)
{
	/////////////////////////////////////////////////
	CObjectBase* pObjectBase;
	CSpecMgr* pScaleFactor;
	int index = pObjectBase->GetObjectFirstIndex(SCALEFACTOR);
	if(index>=0)
		pScaleFactor = (CSpecMgr*)pObjectBase->GetObject(index);
	else
	{
		AfxMessageBox(
			"Error:CSpecMgr::DStoSC\n ScaleFactor Index Not Found");
		return;
	}		 	 
	///////////////////////////////////////////////// 
    double dScaleFactor = pScaleFactor->GetScaleFactor();
	///////////////////////////////////////////////// 
//    dScaleFactor       *= pDoc->GetMapFactor();
    pt->x = (LONG)( ((double)(pt->x))*dScaleFactor);    
    pt->y = (LONG)( ((double)(pt->y))*dScaleFactor); 
    ///////////////////////////////////////////// 
    return;
}    
void CSpecMgr::SCtoDS(LPOINT* pt)
{
	/////////////////////////////////////////////////
	CObjectBase* pObjectBase;
	CSpecMgr* pScaleFactor;
	int index = pObjectBase->GetObjectFirstIndex(SCALEFACTOR);
	if(index>=0)
		pScaleFactor = (CSpecMgr*)pObjectBase->GetObject(index);
	else
	{
		AfxMessageBox(
			"Error:CSpecMgr::SCtoDS\n ScaleFactor Index Not Found");
		return;
	}		 	 
	///////////////////////////////////////////////// 
    double dScaleFactor = pScaleFactor->GetScaleFactor();
	///////////////////////////////////////////////// 
//    dScaleFactor       *= pDoc->GetMapFactor();
    pt->x = (LONG)( ((double)(pt->x))/dScaleFactor);    
    pt->y = (LONG)( ((double)(pt->y))/dScaleFactor); 
    ///////////////////////////////////////////// 
    return;
}    

void CSpecMgr::DStoSC(RECT* rect)
{
	/////////////////////////////////////////////////
	CObjectBase* pObjectBase;
	CSpecMgr* pScaleFactor;
	int index = pObjectBase->GetObjectFirstIndex(SCALEFACTOR);
	if(index>=0)
		pScaleFactor = (CSpecMgr*)pObjectBase->GetObject(index);
	else
	{
		AfxMessageBox(
			"Error:CSpecMgr::DStoSC\n ScaleFactor Index Not Found");
		return;
	}		 	 
	///////////////////////////////////////////////// 
    double dScaleFactor = pScaleFactor->GetScaleFactor();
	///////////////////////////////////////////////// 
 //    dScaleFactor       *= pDoc->GetMapFactor();
    rect->left   = (int)( ((double)(rect->left))*dScaleFactor);    
    rect->top    = (int)( ((double)(rect->top))*dScaleFactor); 
    rect->right  = (int)( ((double)(rect->right))*dScaleFactor);    
    rect->bottom = (int)( ((double)(rect->bottom))*dScaleFactor);    
    ///////////////////////////////////////////// 
    return;
}    

void CSpecMgr::SCtoDS(RECT* rect)
{
	/////////////////////////////////////////////////
	CObjectBase* pObjectBase;
	CSpecMgr* pScaleFactor;
	int index = pObjectBase->GetObjectFirstIndex(SCALEFACTOR);
	if(index>=0)
		pScaleFactor = (CSpecMgr*)pObjectBase->GetObject(index);
	else
	{
		AfxMessageBox(
			"Error:CSpecMgr::SCtoDS\n ScaleFactor Index Not Found");
		return;
	}		 	 
	///////////////////////////////////////////////// 
    double dScaleFactor = pScaleFactor->GetScaleFactor();
	///////////////////////////////////////////////// 
//    dScaleFactor       *= pDoc->GetMapFactor();
    rect->left   = (int)( ((double)(rect->left))/dScaleFactor);    
    rect->top    = (int)( ((double)(rect->top))/dScaleFactor); 
    rect->right  = (int)( ((double)(rect->right))/dScaleFactor);    
    rect->bottom = (int)( ((double)(rect->bottom))/dScaleFactor);    
    ///////////////////////////////////////////// 
    return;
}    
void CSpecMgr::DStoSC(LRECT* rect)
{
	/////////////////////////////////////////////////
	CObjectBase* pObjectBase;
	CSpecMgr* pScaleFactor;
	int index = pObjectBase->GetObjectFirstIndex(SCALEFACTOR);
	if(index>=0)
		pScaleFactor = (CSpecMgr*)pObjectBase->GetObject(index);
	else
	{
		AfxMessageBox(
			"Error:CSpecMgr::DStoSC\n ScaleFactor Index Not Found");
		return;
	}		 	 
	///////////////////////////////////////////////// 
    double dScaleFactor = pScaleFactor->GetScaleFactor();
	///////////////////////////////////////////////// 
//    dScaleFactor       *= pDoc->GetMapFactor();
    rect->left   = (long)( ((double)(rect->left))*dScaleFactor);    
    rect->top    = (long)( ((double)(rect->top))*dScaleFactor); 
    rect->right  = (long)( ((double)(rect->right))*dScaleFactor);    
    rect->bottom = (long)( ((double)(rect->bottom))*dScaleFactor);    
    ///////////////////////////////////////////// 
    return;
}    

void CSpecMgr::SCtoDS(LRECT* rect)
{
	/////////////////////////////////////////////////
	CObjectBase* pObjectBase;
	CSpecMgr* pScaleFactor;
	int index = pObjectBase->GetObjectFirstIndex(SCALEFACTOR);
	if(index>=0)
		pScaleFactor = (CSpecMgr*)pObjectBase->GetObject(index);
	else
	{
		AfxMessageBox(
			"Error:CSpecMgr::SCtoDS\n ScaleFactor Index Not Found");
		return;
	}		 	 
	///////////////////////////////////////////////// 
    double dScaleFactor = pScaleFactor->GetScaleFactor();
	///////////////////////////////////////////////// 
//    dScaleFactor       *= pDoc->GetMapFactor();
    rect->left   = (long)( ((double)(rect->left))/dScaleFactor);    
    rect->top    = (long)( ((double)(rect->top))/dScaleFactor); 
    rect->right  = (long)( ((double)(rect->right))/dScaleFactor);    
    rect->bottom = (long)( ((double)(rect->bottom))/dScaleFactor);    
    ///////////////////////////////////////////// 
    return;
}    

/////////////////////////////////////////////////////////////////////////////////////////		
// CSpecMgr serialization

void CSpecMgr::Serialize(CArchive& ar)
{

	CObject::Serialize( ar);              // must call base class Serializer
	//////////////////////////////////////
	WORD w;
	/////// 
	if (ar.IsStoring())
	{
		TRACE(" SpecMgr		:Storing\n");	// TODO: add storing code here 
		
		ar	<</*UINT*/	(WORD)m_nLastObjectNo		// Master Object Number:to be assigned to: 
									  				// All Elements & Non-Elements
			<</*UINT*/	(WORD)m_nActiveObjectNo     // Selected Object No
			<</*int*/	(WORD)m_nActiveObjectIndex  // Selected Object Index in List
			<</*int*/	(WORD)m_nActiveObjectType;	// Selected ObjectType;

	}
	else
	{
		TRACE(" SpecMgr		:Loading\n");	// TODO: add loading code here

		ar	>>	w;
		m_nLastObjectNo = (UINT)w;		// Master Object Number:to be assigned to: 
								  				// All Elements & Non-Elements
		ar	>>	w;
		m_nActiveObjectNo = (UINT)w;     // Selected Object No
		ar	>>	w;
		m_nActiveObjectIndex = (int)w;  // Selected Object Index in List
		ar	>>	w;
		m_nActiveObjectType = (int)w;	// Selected ObjectType;
		
	} 
	//////////////////////////////////////////////////
	CAxis* pAxis		  	=	GetAxis();			 
	///////////////////////////////////////	
	pAxis->Serialize(ar);  

}
/////////////////////////// End of Module /////////////////
