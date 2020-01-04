// Booleans.cpp : implementation of the CBooleans class
//

#include "stdafx.h"

#include "Def_Type.h"
#include "Def_View.h"
#include "Def_Objs.h"
/////////////////////
#include "Ext_Spec.h"
#include "Def_Spec.h"

#include "Booleans.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBooleans

IMPLEMENT_SERIAL(CBooleans,CDrObject,1)
/*
BEGIN_MESSAGE_MAP(CBooleans,CDrObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CBooleans)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
//////////////////////////////////
 
CBooleans::CBooleans()
{
    SetObjectType((int)BOOLEANS);
    SetElemType((int)SPEC_OBJECT);          //  
} 

void CBooleans::ReadDefaultBooleans()
{
}


void CBooleans::InitBooleans()
{

	/////////////////////////////////////////// Menu
	m_bBLineOn			= TRUE;
	m_bSingleSegOn		= TRUE;
	m_bSoundOn			= TRUE;
 	m_bAutoAcceptOn		= FALSE;
 	m_bCoonSocksOff		= FALSE;
	m_bDialogOn			= FALSE;
	m_bDragOn			= FALSE;
	m_bRubberBandOn		= TRUE;
	m_bRefreshOn 		= TRUE;
    /////////////////////////////////////////// Views
	m_bStViewActive		= FALSE;
	m_bSpViewActive		= FALSE;
	m_bHsViewActive		= FALSE;
	//
	m_b12ViewActive		= TRUE;
	m_b23ViewActive		= FALSE;
	m_b31ViewActive		= FALSE;
	m_bIsoViewActive	= FALSE;
	m_bDataViewActive	= FALSE;
	m_bMeshDataViewActive	= FALSE;
	m_bDeckViewActive	= FALSE;
	m_bFormDataViewActive	= FALSE;
    /////////////////////////////////////////// Mode
    m_bInputMode 		= TRUE;
    m_bOutputMode		= FALSE;
    //////////////////////////
	m_bZoomEnable12		= FALSE;
	m_bZoomEnable23		= FALSE;
	m_bZoomEnable31		= FALSE;
	m_bZoomEnableISO	= FALSE;
	
	m_bZoomFit12		= FALSE;
	m_bZoom12			= FALSE;
	m_bZoomFit23		= FALSE;
	m_bZoom23 			= FALSE;
	m_bZoomFit31		= FALSE;
	m_bZoom31 			= FALSE;
	m_bZoomFitISO		= FALSE;
	m_bZoomISO 			= FALSE;
    ////////////////////////////////
    
}
	
void CBooleans::SetObjectInfo(CDrObject* pObject)
{
	
	CBooleans* pBooleans = (CBooleans*) pObject;
	//////////////////////////////////////////////////
	m_nElemType			= pBooleans->m_nElemType;
	m_nObjectType		= pBooleans->m_nObjectType; 
	m_nObjectNo			= pBooleans->m_nObjectNo;
	/////////////////////////////////////////// Menu
	m_bSoundOn			= pBooleans->m_bSoundOn;
	m_bAutoAcceptOn     = pBooleans->m_bAutoAcceptOn;
	m_bCoonSocksOff     = pBooleans->m_bCoonSocksOff;
	m_bDialogOn      	= pBooleans->m_bDialogOn;
	m_bDragOn        	= pBooleans->m_bDragOn;
	m_bRubberBandOn  	= pBooleans->m_bRubberBandOn;
	m_bRefreshOn	 	= pBooleans->m_bRefreshOn;
    /////////////////////////////////////////// Views
	m_bStViewActive  	= pBooleans->m_bStViewActive;
	m_bSpViewActive  	= pBooleans->m_bSpViewActive;
	m_bHsViewActive  	= pBooleans->m_bHsViewActive;
	//
	m_b12ViewActive  	= pBooleans->m_b12ViewActive;
	m_b23ViewActive  	= pBooleans->m_b23ViewActive;
	m_b31ViewActive  	= pBooleans->m_b31ViewActive;
	m_bIsoViewActive 	= pBooleans->m_bIsoViewActive;
	m_bDataViewActive	= pBooleans->m_bDataViewActive;
	m_bMeshDataViewActive	= pBooleans->m_bMeshDataViewActive;
	m_bFormDataViewActive	= pBooleans->m_bFormDataViewActive;
    /////////////////////////////////////////// Mode
    m_bInputMode 	 	= pBooleans->m_bInputMode;
    m_bOutputMode	 	= pBooleans->m_bOutputMode;
    //////////////////////////
	m_bZoomEnable12		= pBooleans->m_bZoomEnable12;
	m_bZoomEnable23		= pBooleans->m_bZoomEnable23;
	m_bZoomEnable31		= pBooleans->m_bZoomEnable31;
	m_bZoomEnableISO	= pBooleans->m_bZoomEnableISO;
	
	m_bZoomFit12 		= pBooleans->m_bZoomFit12;
	m_bZoom12			= pBooleans->m_bZoom12;
	m_bZoomFit23 		= pBooleans->m_bZoom23;
	m_bZoom23 			= pBooleans->m_bZoom23;
	m_bZoomFit31 		= pBooleans->m_bZoomFit31;
	m_bZoom31 			= pBooleans->m_bZoom31;
	m_bZoomFitISO 		= pBooleans->m_bZoomFitISO;
	m_bZoomISO 			= pBooleans->m_bZoomISO;
    /////////////////////////////////////////////////

	return;
}		

void CBooleans::GetObjectInfo(CDrObject* pObject)
{
	
	CBooleans* pBooleans = (CBooleans*) pObject;
	//////////////////////////////////////////////////   
	pBooleans->m_nObjectType 		= m_nObjectType; 
	pBooleans->m_nElemType			= m_nElemType;	
	pBooleans->m_nObjectNo			= m_nObjectNo;
	/////////////////////////////////////////// Menu
	pBooleans->m_bSoundOn     		= m_bSoundOn;
	pBooleans->m_bAutoAcceptOn     	= m_bAutoAcceptOn;
	pBooleans->m_bCoonSocksOff     	= m_bCoonSocksOff;
	pBooleans->m_bDialogOn      	= m_bDialogOn;
	pBooleans->m_bDragOn        	= m_bDragOn;
	pBooleans->m_bRubberBandOn  	= m_bRubberBandOn;
	pBooleans->m_bRefreshOn	 		= m_bRefreshOn;
    /////////////////////////////////////////// Views
	pBooleans->m_bStViewActive  	= m_bStViewActive;
	pBooleans->m_bSpViewActive  	= m_bSpViewActive;
	pBooleans->m_bHsViewActive  	= m_bHsViewActive;
	//
	pBooleans->m_b12ViewActive  	= m_b12ViewActive;
	pBooleans->m_b23ViewActive  	= m_b23ViewActive;
	pBooleans->m_b31ViewActive  	= m_b31ViewActive;
	pBooleans->m_bIsoViewActive 	= m_bIsoViewActive;
	pBooleans->m_bDataViewActive	= m_bDataViewActive;
	pBooleans->m_bMeshDataViewActive	= m_bMeshDataViewActive;
	pBooleans->m_bFormDataViewActive	= m_bFormDataViewActive;
    /////////////////////////////////////////// Mode
    pBooleans->m_bInputMode 	 	= m_bInputMode;
    pBooleans->m_bOutputMode	 	= m_bOutputMode;
    //////////////////////////
	pBooleans->m_bZoomEnable12		= m_bZoomEnable12;
	pBooleans->m_bZoomEnable23		= m_bZoomEnable23;
	pBooleans->m_bZoomEnable31		= m_bZoomEnable31;
	pBooleans->m_bZoomEnableISO		= m_bZoomEnableISO;
	
	pBooleans->m_bZoomFit12 		= m_bZoomFit12;
	pBooleans->m_bZoom12			= m_bZoom12;
	pBooleans->m_bZoomFit23 		= m_bZoom23;
	pBooleans->m_bZoom23 			= m_bZoom23;
	pBooleans->m_bZoomFit31 		= m_bZoomFit31;
	pBooleans->m_bZoom31 			= m_bZoom31;
	pBooleans->m_bZoomFitISO 		= m_bZoomFitISO;
	pBooleans->m_bZoomISO 			= m_bZoomISO;
	/////////////////////////////////////////
	return;
}		

void CBooleans::DoDataView(CDC* PtrDC, int y)
{

	CString strCard;
	//////////////////////
	Pack_drPipe(&strCard);
	//////////////////////////// 
	PtrDC->TextOut(0,y,strCard);
	////////////////////////////
	return;
} 

void CBooleans::Pack_drPipe(CString* pstrCard)
{

   	static CString name;
   	/////////////////////////
   	for (int i = 0;i<nMax_SpecTypes;i++)
   		if(SpTypes[i].num == BOOLEANS) 
   		{
   			name = SpTypes[i].ObjName;
   			break;
   		}	
   			
   	static CString pad = " ";
  	////////////////////////
   	AddStr(pstrCard,&name,10);
	/////////////////////// 
	return;

}   

void CBooleans::Serialize(CArchive& ar)
{

	CDrObject::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	BYTE b;
	WORD w;
	/////// 
	if (ar.IsStoring())
	{
		TRACE(" Booleans:    Storing\n");	
	/////////////////////////////////////////// Zoom/MainView
		ar	<</*int*/	(WORD)m_nElemType	
			<</*int*/	(WORD)m_nObjectType
			<</*UINT*/	(WORD)m_nObjectNo 
		///////////////////////////////////
			<</*BOOL*/	(BYTE)m_bAutoAcceptOn
			<</*BOOL*/	(BYTE)m_bCoonSocksOff
			<</*BOOL*/	(BYTE)m_bDialogOn
			<</*BOOL*/	(BYTE)m_bElementOn
			<</*BOOL*/	(BYTE)m_bDragOn
			<</*BOOL*/	(BYTE)m_bRubberBandOn
			<</*BOOL*/	(BYTE)m_bRefreshOn
  			///////////////////////////////////////// Views
			<</*BOOL*/	(BYTE)m_b12ViewActive
			<</*BOOL*/	(BYTE)m_b23ViewActive
			<</*BOOL*/	(BYTE)m_b31ViewActive
			<</*BOOL*/	(BYTE)m_bIsoViewActive
   			<</* BOOL*/	(BYTE)m_bDataViewActive 
    		/////////////////////////////////////////// Mode
			<</*BOOL*/	(BYTE)m_bInputMode
			<</*BOOL*/	(BYTE)m_bOutputMode
 	/////////////////////////////////////////// Zoom/MainView
			<</*BOOL*/	(BYTE)m_bZoomEnable12
			<</*BOOL*/	(BYTE)m_bZoomEnable23
			<</*BOOL*/	(BYTE)m_bZoomEnable31
			<</*BOOL*/	(BYTE)m_bZoomEnableISO
			<</*BOOL*/	(BYTE)m_bZoomFit12
			<</*BOOL*/	(BYTE)m_bZoomFit23
			<</*BOOL*/	(BYTE)m_bZoomFit31
			<</*BOOL*/	(BYTE)m_bZoomFitISO
			<</*BOOL*/	(BYTE)m_bZoom12
			<</*BOOL*/	(BYTE)m_bZoom23
			<</*BOOL*/	(BYTE)m_bZoom31
			<</*BOOL*/	(BYTE)m_bZoomISO;
			/////////////////////////////

	}
	else
	{
		TRACE(" Booleans:    Loading\n");	

		/////////////////////
		ar	>>/*int*/w;
		m_nElemType = (int)w;	
		ar	>>/*int*/w;
		m_nObjectType = (int)w;
		ar	>>/*UINT*/w;
		m_nObjectNo = (UINT)w;
		///////////////////// 
		ar	>>/*BOOL*/b;
		m_bAutoAcceptOn = (BOOL)b;
		ar	>>/*BOOL*/b;
		m_bCoonSocksOff = (BOOL)b;
		ar	>>/*BOOL*/b;
		m_bDialogOn = (BOOL)b;
		ar	>>/*BOOL*/b;
		m_bElementOn = (BOOL)b;
		ar	>>/*BOOL*/b;
		m_bDragOn = (BOOL)b;
		ar	>>/*BOOL*/b;
		m_bRubberBandOn = (BOOL)b;
		ar	>>/*BOOL*/b;
		m_bRefreshOn = (BOOL)b;
  		///////////////////////////////////////// Views
		ar	>>/*BOOL*/b;
		m_b12ViewActive = (BOOL)b;
		ar	>>/*BOOL*/b;
		m_b23ViewActive = (BOOL)b;
		ar	>>/*BOOL*/b;
		m_b31ViewActive = (BOOL)b;
		ar	>>/*BOOL*/b;
		m_bIsoViewActive = (BOOL)b;
		ar	>>/*BOOL*/b;
		m_bDataViewActive = (BOOL)b;
    	/////////////////////////////////////////// Mode
		ar	>>/*BOOL*/b;
		m_bInputMode = (BOOL)b;
		ar	>>/*BOOL*/b;
		m_bOutputMode = (BOOL)b;;
		//////////////////////////////////////////// Zoom
 		ar	>>/*BOOL*/b;
		m_bZoomEnable12 = (BOOL)b;
		ar	>>/*BOOL*/b;
		m_bZoomEnable23 = (BOOL)b;
		ar	>>/*BOOL*/b;
		m_bZoomEnable31 = (BOOL)b;
		ar	>>/*BOOL*/b;
		m_bZoomEnableISO = (BOOL)b;
		
 		ar	>>/*BOOL*/b;
		m_bZoomFit12 = (BOOL)b;
		ar	>>/*BOOL*/b;
		m_bZoomFit23 = (BOOL)b;
		ar	>>/*BOOL*/b;
		m_bZoomFit31 = (BOOL)b;
		ar	>>/*BOOL*/b;
		m_bZoomFitISO = (BOOL)b;
		
 		ar	>>/*BOOL*/b;
		m_bZoom12 = (BOOL)b;
		ar	>>/*BOOL*/b;
		m_bZoom23 = (BOOL)b;
		ar	>>/*BOOL*/b;
		m_bZoom31 = (BOOL)b;
		ar	>>/*BOOL*/b;
		m_bZoomISO = (BOOL)b; 
		/////////////////////

	}        
	///////////////
	
}   

////////////////////////////////////////////////////// MainView
BOOL CBooleans::IsZoomEnabled(int nViewNumber)
{

	switch(nViewNumber)
	{
		case VIEW12:
			return m_bZoomEnable12;
		case VIEW23:
			return m_bZoomEnable23;
		case VIEW31:
			return m_bZoomEnable31;
		case VIEWISO:
			return m_bZoomEnableISO;
        	
        default:
        	break;
        	
        }   
        return 0;
}        

void CBooleans::SetZoomEnabled(int nViewNumber,BOOL bTF)
{

	switch(nViewNumber)
	{
		case VIEW12:
			m_bZoomEnable12 = bTF;
			break;
		case VIEW23:
			m_bZoomEnable23 = bTF;
			break;
		case VIEW31:
			m_bZoomEnable31 = bTF;
			break;
		case VIEWISO:
			m_bZoomEnableISO = bTF;
			break;
        	
        default:
        	break;
        	
        }   
        return;
}        

BOOL CBooleans::IsZoomOn(int nStatusType,int nViewNumber)
{

	switch(nStatusType)
	{
		case ZOOM_USER:
			if(nViewNumber == VIEW12)
				return m_bZoom12;
			if(nViewNumber == VIEW23)
				return m_bZoom23;
			if(nViewNumber == VIEW31)
				return m_bZoom31;
			if(nViewNumber == VIEWISO)
				return m_bZoomISO;
	
        	break; 
        	
		case ZOOM_FIT:
			if(nViewNumber == VIEW12)
				return m_bZoomFit12;
			if(nViewNumber == VIEW23)
				return m_bZoomFit23;
			if(nViewNumber == VIEW31)
				return m_bZoomFit31;
			if(nViewNumber == VIEWISO)
				return m_bZoomFitISO;
	
        	break;
        	
        default:
        	break;
        	
        }   
        return 0;
}        

BOOL CBooleans::ToggleZoom(int nStatusType,int nViewNumber)
{

	switch(nStatusType)
	{
		case ZOOM_USER:
			if(nViewNumber == VIEW12)
				m_bZoom12  = !m_bZoom12;
			if(nViewNumber == VIEW23)
				m_bZoom23  = !m_bZoom23;
			if(nViewNumber == VIEW31)
				m_bZoom31  = !m_bZoom31;
			if(nViewNumber == VIEWISO)
				m_bZoomISO = !m_bZoomISO;
			break;
	
        	
		case ZOOM_FIT:
			if(nViewNumber == VIEW12)
				m_bZoomFit12 = !m_bZoomFit12;
			if(nViewNumber == VIEW23)
				m_bZoomFit23 = !m_bZoomFit23;
			if(nViewNumber == VIEW31)
				m_bZoomFit31 = !m_bZoomFit31;
			if(nViewNumber == VIEWISO)
				m_bZoomFitISO = !m_bZoomFitISO;
			break;
	
        	
        default:
        	break;
        	
        }   
        return 0;
}        
                               
////////////////////////////////// end of module //////////////////
