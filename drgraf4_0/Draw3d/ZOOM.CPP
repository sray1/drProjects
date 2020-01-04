// Zoom.cpp : implementation of the CZoom class
//

#include "Zoom.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZoom

IMPLEMENT_SERIAL(CZoom,CObject,1)
/*
BEGIN_MESSAGE_MAP(CZoom,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CZoom)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
//////////////////////////////////
 
CZoom::CZoom()
{
	////////////////////////////////////////////////  Get Doc Info
//	CDrGrafDoc* pDoc = (CDrGrafDoc*)(theApp.m_pDoc);  
//	if( pDoc->IsNewDocFile())
//	{
		ReadDefaultZoom();
 		InitializeZoom(); 
//	} 		
} 

void CZoom::ReadDefaultZoom()
{


}

void CZoom::InitializeZoom()
{

		///////////////////////
		m_ZoomFactor12.x = 1.0;
		m_ZoomFactor12.y = 1.0;
		m_ZoomFactor12.z = 1.0;

		m_ZoomFactor23.x = 1.0;
		m_ZoomFactor23.y = 1.0;
		m_ZoomFactor23.z = 1.0;

		m_ZoomFactor31.x = 1.0;
		m_ZoomFactor31.y = 1.0;
		m_ZoomFactor31.z = 1.0;

		m_ZoomFactorISO.x = 1.0;
		m_ZoomFactorISO.y = 1.0;
		m_ZoomFactorISO.z = 1.0;
		/////////////////////// 
        
}
	

void CZoom::Serialize(CArchive& ar)
{

	CObject::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	WORD w;
	/////// 
	if (ar.IsStoring())
	{
		TRACE(" Zoom:    Storing\n");	// TODO: add storing code here
		
		ar.Write(&m_ZoomFactor12 ,sizeof(WORLD)  );
		ar.Write(&m_ZoomFactor23 ,sizeof(WORLD)  );
		ar.Write(&m_ZoomFactor31 ,sizeof(WORLD)  );
		ar.Write(&m_ZoomFactorISO,sizeof(WORLD)  );

	}
	else
	{
		TRACE(" Zoom:    Loading\n");	// TODO: add loading code here

		ar.Read(&m_ZoomFactor12 ,sizeof(WORLD)  );
		ar.Read(&m_ZoomFactor23 ,sizeof(WORLD)  );
		ar.Read(&m_ZoomFactor31 ,sizeof(WORLD)  );
		ar.Read(&m_ZoomFactorISO,sizeof(WORLD)  );

	}        
	///////////////
}

void CZoom::SetZoomFactor(WORLD NewZoomFactor,int n_ViewNumber)
{ 

	switch(n_ViewNumber)
	{
		case VIEW12:
			m_ZoomFactor12.x = NewZoomFactor.x;
			m_ZoomFactor12.y = NewZoomFactor.y;
			m_ZoomFactor12.z = NewZoomFactor.z;
			break;     
			
		case VIEW23:
			m_ZoomFactor23.x = NewZoomFactor.x;
			m_ZoomFactor23.y = NewZoomFactor.y;
			m_ZoomFactor23.z = NewZoomFactor.z;
			break;     
			
		case VIEW31:
			m_ZoomFactor31.x = NewZoomFactor.x;
			m_ZoomFactor31.y = NewZoomFactor.y;
			m_ZoomFactor31.z = NewZoomFactor.z;
			break;  
			
		case VIEWISO:
			m_ZoomFactorISO.x = NewZoomFactor.x;
			m_ZoomFactorISO.y = NewZoomFactor.y;
			m_ZoomFactorISO.z = NewZoomFactor.z;
			break;  
			
		default:
			break;	
		}
		return;
					
}

WORLD CZoom::GetZoomFactor(int nViewNumber)
{

	WORLD Null;
	Null.x = 0.;
	Null.y = 0.;
	Null.z = 0.;
	////////////////////
	switch(nViewNumber)
	{
		case VIEW12:
			return m_ZoomFactor12;
		case VIEW23:
			return m_ZoomFactor23;
		case VIEW31:
			return m_ZoomFactor31;
		case VIEWISO:
			return m_ZoomFactorISO;
		default:
			break;	
		}
		return Null;
					
}
	
////////////////////////////////// end of module //////////////////
