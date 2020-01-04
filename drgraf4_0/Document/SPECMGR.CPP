// drgradoc.cpp : implementation of the CDrGrafDoc class
//

#include "stdafx.h"
//#include "afxwin.h"   // m_hObject in DoTextFont

//#include "drgrafrm.h" 
#include "axisDlg.h"
#include "eyepzDLg.h"
#include "layerDlg.h"
#include "preciDlg.h"
#include "scaleDlg.h"
#include "unitDlg.h"

#include "drgradoc.h" 


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

////////////////////////////////
// CDrGrafDoc

IMPLEMENT_DYNCREATE(CDrGrafDoc, CDocument)

BEGIN_MESSAGE_MAP(CDrGrafDoc, CDocument)
	//{{AFX_MSG_MAP(CDrGrafDoc)
	ON_COMMAND(IDM_DRAW_PRECISION, OnDrawPrecision)
	ON_COMMAND(IDM_DRAW_SCALEFACTOR, OnDrawScalefactor)
	ON_COMMAND(IDM_DRAW_LAYER, OnDrawLayer)
	ON_COMMAND(IDM_EDIT_CLEARALL, OnEditClearall)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_CLEARALL, OnUpdateEditClearall)
	ON_COMMAND(ID_OPTIONS_PENCHANGE, OnOptionsPenchange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrGrafDoc construction/destruction

CDrGrafDoc::CDrGrafDoc()
{
	// TODO: add one-time construction code here 
	SetNewDocFile(TRUE);
}

CDrGrafDoc::~CDrGrafDoc()
{
}

BOOL CDrGrafDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	//////////////////// Set NewFile marker
	SetNewDocFile(TRUE);
	// (SDI documents will reuse this document)
	InitDocument();
	//////////////////// 
	return TRUE;
}
BOOL CDrGrafDoc::OnOpenDocument(const char* pszPathName)
{
	if (!CDocument::OnOpenDocument(pszPathName))
		return FALSE;
	//////////////////// Set NewFile marker
	SetNewDocFile(FALSE);
	// (SDI documents will reuse this document)
//	InitDocument();
	ReadDefaults();   // Just defaults   NO INITIALIZATION when OLD
	//////////////////// 
	return TRUE;
}   

void CDrGrafDoc::OnCloseDocument()
{
/*
	////////////////////////////////////////// InitMenu  
	CDrGrafFrame* pWnd = (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd); 
	
	pWnd->MDISetMenu(pWnd->GetInitMenu(),NULL); 
	pWnd->DrawMenuBar(); 
	////////////////////////////////////////// Hide Boxes
	pWnd->GetElementBox()->ShowWindow(FALSE);
	pWnd->GetDrawBox()->ShowWindow(FALSE);								
	////////////////////////////////////////// StatusBoxes      TO DO 
*/	
	CDocument::OnCloseDocument();
	return;
} 

void CDrGrafDoc::InitDocument()
{
///////////////////                                Readin Defaults
	ReadDefaults();
///////////////////                                Initialize Member Data
	Initialize();	
//	Default Document Size;	
//	m_sizeDoc = m_sizeDocDefault;
}
// CDrGrafDoc serialization

void CDrGrafDoc::Serialize(CArchive& ar) 
{
	CDocument::Serialize(ar);
	///////////////////////
	if (ar.IsStoring())
	{
		TRACE(" Document	:Storing\n");	// TODO: add storing code here
	}
	else
	{
		TRACE(" Document    :Loading\n");		// TODO: add loading code here
	}
	////////////////////////////////////////////////
	GetUnit()->Serialize(ar);			 
	GetPrecision()->Serialize(ar);	
	GetScaleFactor()->Serialize(ar);
	GetMapFactor()->Serialize(ar);			 
	GetLayer()->Serialize(ar);			 
	GetDataWindow()->Serialize(ar);
	GetDrPen()->Serialize(ar);			 
	GetHitNet()->Serialize(ar);			 
	GetZoom()->Serialize(ar);  
	GetBooleans()->Serialize(ar);
	////////////////////////////////////////////// Mouse
	GetMouseMgr()->Serialize(ar);	   
	//////////////////////////////////////////////			 
	GetObjectMgr()->Serialize(ar);
	//////////////////////////////////////////////

}


/////////////////////////////////////////////////////////////////////////////
// CDrGrafDoc diagnostics

#ifdef _DEBUG
void CDrGrafDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDrGrafDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}

#endif //_DEBUG 
				
void CDrGrafDoc::OnEditClearall()
{      
	 
	////////////////////////////////////
	CString strDel 	 =	"This will DELETE EVERYTHING!";
	strDel 			+=  "\nEVERYTHING will be zip,nada,caput !!"; 
	strDel			+=	"\nAre You REALLY Sure !!!"; 
	if(AfxMessageBox(strDel,MB_YESNO) == IDNO)
		return;
	//////////////////////////////////////////////////////// GO DELETE EVERYTHING	
	DeleteContents();    
	SetModifiedFlag();   	// Document has been modified
							// needed during File Close
	UpdateAllViews(NULL);
	/////////////////////
}

void CDrGrafDoc::OnUpdateEditClearall(CCmdUI* pCmdUI)
{
	//////////////////////////////////////////////////////////  
	CGrafObject* pObjectMgr = GetObjectMgr(); 
	////////////////////////////////////
	BOOL bOn   =	!(pObjectMgr->GetObjectList()->IsEmpty());
	////////////////////////////////////
	pCmdUI->Enable(bOn);
	// TODO: Add your command update UI handler code here
	
}

void CDrGrafDoc::DeleteContents()
{
	//////////////////////////////////////////////////////////  
	CGrafObject* pObjectMgr = GetObjectMgr();
	//////////////////////////////////////
	while (!(pObjectMgr->GetObjectList()->IsEmpty()) )
		delete pObjectMgr->GetObjectList()->RemoveHead();
}
//////////////////// End of Module ///////////////////////////////////
