// dlg_grid.cpp : implementation file
//

#include "stdafx.h"

#include "Def_Objs.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h" 
/////////////////////
#include "ObjMgr.h"
#include "NewObjs.h"
#include "DListMgr.h"
///////////////////// ElemObjs
#include "Def_IGen.h"
#include "DrNode.h"
///////////////////// DrawObjs
#include "Def_Draw.h"
///////////////////// SpecObjs
#include "Def_Spec.h"
#include "drpen.h"
#include "Layer.h"
#include "precison.h"
#include "mapfacto.h"
////////////////////
#include "dlg_grid.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_Grid dialog


CDlg_Grid::CDlg_Grid(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_Grid::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_Grid)
	m_AlignNid	= "";
	m_bBack 	= TRUE;
	m_bAlign 	= FALSE;
	m_bBottom 	= TRUE;
	m_FromNid 	= "";
	m_MaxNid 	= "";
	m_MinNid 	= "";
	m_ToNid 	= "";
	m_bFront 	= FALSE;
	m_bFull 	= FALSE;
	m_GridID 	= "";
	m_bLeft 	= TRUE;
	m_bRight 	= FALSE;
	m_bRotate 	= FALSE;
	m_nStepX 	= 10;
	m_nStepY 	= 10;
	m_nStepZ 	= 10;
	m_bTop 		= FALSE;
	m_bConX 	= FALSE;
	m_bConY 	= FALSE;
	m_bConZ 	= FALSE;
	//}}AFX_DATA_INIT 
	m_bGrType	= FALSE;	// 0(FALSE) = draw/ 1(TRUE)= data 
	m_bDraw		= FALSE;	// 0(FALSE) = BackGround / 1(TRUE)= ForeGround

}

void CDlg_Grid::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_Grid)
	DDX_CBString(pDX, IDC_ALIGN_NODE, m_AlignNid);
	DDX_Check(pDX, IDC_BACK, m_bBack);
	DDX_Check(pDX, IDC_ALIGN, m_bAlign);
	DDX_Check(pDX, IDC_BOTTOM, m_bBottom);
	DDX_CBString(pDX, IDC_CNODE_FROM, m_FromNid);
	DDX_CBString(pDX, IDC_CNODE_MAX, m_MaxNid);
	DDX_CBString(pDX, IDC_CNODE_MIN, m_MinNid);
	DDX_CBString(pDX, IDC_CNODE_TO, m_ToNid);
	DDX_Check(pDX, IDC_FRONT, m_bFront);
	DDX_Check(pDX, IDC_FULL, m_bFull);
	DDX_Text(pDX, IDC_GRIDID, m_GridID);
	DDX_Check(pDX, IDC_LEFT, m_bLeft);
	DDX_Check(pDX, IDC_RIGHT, m_bRight);
	DDX_Check(pDX, IDC_ROTATE, m_bRotate);
	DDX_Text(pDX, IDC_STEP_X, m_nStepX);
	DDX_Text(pDX, IDC_STEP_Y, m_nStepY);
	DDX_Text(pDX, IDC_STEP_Z, m_nStepZ);
	DDX_Check(pDX, IDC_TOP, m_bTop);
	DDX_Check(pDX, IDC_XCON, m_bConX);
	DDX_Check(pDX, IDC_YCON, m_bConY);
	DDX_Check(pDX, IDC_ZCON, m_bConZ);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_Grid, CDialog)
	//{{AFX_MSG_MAP(CDlg_Grid)
	ON_BN_CLICKED(IDC_ALIGN, OnAlign)
	ON_BN_CLICKED(IDC_BACK, OnBack)
	ON_BN_CLICKED(IDC_BACKGROUND, OnBackground)
	ON_BN_CLICKED(IDC_BOTTOM, OnBottom)
	ON_BN_CLICKED(IDC_FOREGROUND, OnForeground)
	ON_BN_CLICKED(IDC_FRONT, OnFront)
	ON_BN_CLICKED(IDC_FULL, OnFull)
	ON_BN_CLICKED(IDC_LEFT, OnLeft)
	ON_BN_CLICKED(IDC_RIGHT, OnRight)
	ON_BN_CLICKED(IDC_ROTATE, OnRotate)
	ON_BN_CLICKED(IDC_TOP, OnTop)
	ON_BN_CLICKED(IDC_XCON, OnXcon)
	ON_BN_CLICKED(IDC_YCON, OnYcon)
	ON_BN_CLICKED(IDC_ZCON, OnZcon)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlg_Grid message handlers

BOOL CDlg_Grid::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	///////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	///////////////////////////////////////////////
	int nMax = pDListMgr->GetSpecificObjectCount(NODE);
	if(nMax)
		FillListAllNodeIDs();   //  with Nodes
	/////////////////
	CWnd* pWndCtrl = GetDlgItem(IDC_GRIDID);
	pWndCtrl->SetFocus();
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
	return FALSE;  // return TRUE  unless you set the focus to a control
	
}

void CDlg_Grid::OnOK()
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
	/////////////////////////////////////////////
	int nActiveIndex;
    CDrGrid* pAdd 	= (CDrGrid*)(pObjectMgr->AddToDataBase(nActiveIndex,GRID));
    SetInfoForDataBase(pAdd);
    //////////////////////////////////////////////////////////////////////////////// Invalidate
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nActiveIndex,GRID);
	//////////////////////////////////////////////////////////
	CDialog::OnOK();
}

void CDlg_Grid::OnCancel()
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CDlg_Grid::OnAlign()
{
	m_bAlign 	= !m_bAlign;
}

void CDlg_Grid::OnBack()
{
	m_bBack 	= !m_bBack;
}

void CDlg_Grid::OnBackground()
{
	m_bDraw		= FALSE;	// 0(FALSE) = BackGround / 1(TRUE)= ForeGround
}

void CDlg_Grid::OnBottom()
{
	m_bBottom 	= !m_bBottom;
}

void CDlg_Grid::OnForeground()
{
	m_bDraw		= TRUE;	// 0(FALSE) = BackGround / 1(TRUE)= ForeGround
}

void CDlg_Grid::OnFront()
{
	m_bFront 	= !m_bFront;
}

void CDlg_Grid::OnFull()
{
	m_bFull 	= !m_bFull;
}

void CDlg_Grid::OnLeft()
{
	m_bLeft 	= !m_bLeft;
}

void CDlg_Grid::OnRight()
{
	m_bRight 	= !m_bRight;
}

void CDlg_Grid::OnRotate()
{
	m_bRotate 	= !m_bRotate;
}

void CDlg_Grid::OnTop()
{
	m_bTop 		= !m_bTop;
}

void CDlg_Grid::OnXcon()
{
	m_bConX 	= !m_bConX;
}

void CDlg_Grid::OnYcon()
{
	m_bConY 	= !m_bConY;
}

void CDlg_Grid::OnZcon()
{
	m_bConZ 	= !m_bConZ;
}

void CDlg_Grid::FillListAllNodeIDs()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	///////////////////////////////////////////////
	CWnd* pWndCtrl;
	//////////////////////////
	CString CID;
	
	int nMaxNodes = pDListMgr->GetSpecificObjectCount(NODE);//
	if (nMaxNodes<=0)
		return; 
	/////////////////	
	CDrObject* 	pObject;			        
	
	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
		if(pObject->GetObjectType() == NODE)
		{ 
			CDrNode* pNode = (CDrNode*)pObject;
   			CString CID		= pNode->GetNodeCard()->id;
   			/////////////////////////////////
			pWndCtrl = GetDlgItem(IDC_ALIGN_NODE);
   		    ((CComboBox*)(pWndCtrl))->AddString(CID);
   			/////////////////////////////////
			pWndCtrl = GetDlgItem(IDC_CNODE_MIN);
   		    ((CComboBox*)(pWndCtrl))->AddString(CID);
   			/////////////////////////////////
			pWndCtrl = GetDlgItem(IDC_CNODE_MAX);
   		    ((CComboBox*)(pWndCtrl))->AddString(CID);
   			/////////////////////////////////
			pWndCtrl = GetDlgItem(IDC_CNODE_FROM);
   		    ((CComboBox*)(pWndCtrl))->AddString(CID);
   			/////////////////////////////////
			pWndCtrl = GetDlgItem(IDC_CNODE_TO);
   		    ((CComboBox*)(pWndCtrl))->AddString(CID);
   		    /////////////////////////////////
		}	   		     
   	}
} 

void CDlg_Grid::SetInfoForDataBase(CDrGrid* pDrObject)
{

	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CDrPen*	pDrPen				= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer				= (CLayer*)pObjectMgr->GetSpecObject(LAYER);
	/////////////////////////////////////////////////////////////	
    pDrObject->SetObjectType((int)GRID);
    pDrObject->SetElemType((int)DRAW_OBJECT);          // globals
    pDrObject->SetLevelType((int)LEVEL_GRAPA);          // globals
    //////////////////////////////
	pDrObject->SetObjectID(m_GridID);
	/////////////////////////////////////////// GrInfo
	GR_INFO gi;
	gi.gridtype  	= 0;
	gi.screenful	= m_bFull;
	gi.alignment	= m_bAlign;
	gi.left  		= m_bLeft;
	gi.right  		= m_bRight;
	gi.top  		= m_bTop;
	gi.bottom  		= m_bBottom;
	gi.back  		= m_bBack;
	gi.front  		= m_bFront;
	gi.connectX 	= m_bConX;
	gi.connectY   	= m_bConY; 
	gi.connectZ   	= m_bConZ; 
	gi.rotation   	= m_bRotate; 
	pDrObject->SetGrInfo(gi);
	//////////////////////////
	WORLD S;
	S.x = m_nStepX;
	S.y = m_nStepY;
	S.z = m_nStepZ;
	pDrObject->SetStep(S);
	//////////////////////
	pDrObject->SetAngle((double)0);        // for now
	WORLD Anc = {0,0,0};
	pDrObject->SetAnchor(Anc);        // for now
	///////////////////////////////////////////////// Nodes
	///////////////////////////////////////////////////////// store node pointers 
	int index;
	//////////////////////////////////////////////////////////////////////
	CString nid[2];
	int nEnds = 2;
	/////////////////
	nid[0] = m_MinNid; 
	nid[1] = m_MaxNid; 
	/////////////////////////////////////////////////////  
	CDListMgr* 	pDListMgr	= pObjectMgr->GetObjectList(NODE);
    for(int i=0;i<nEnds;i++)
    {
		if(( index = pObjectMgr->GetObjectIndexfromKey(NODE,nid[i],1))>=0)
		{
			CDrNode* pDrNode = (CDrNode*)pDListMgr->GetObject(index);
  			pDrObject->GetNodeList()->InsertObject(pDrNode);
			//////////////////////////////// save Current Grid Pointer in Nodes
			pDrNode->GetElemList()->InsertObject(pDrObject);
		}			
	
  	}
  	//////////////////////////////////////////////// DataGrid Nodes						*TODO*	
	////////////////////////////////////////////////	
	pDrObject->SetPenInfo_G(pDrPen->GetWidth(),pDrPen->GetColor(),pDrPen->GetStyle());
	pDrObject->SetPenInfo_C(pDrPen->GetWidth(),pDrPen->GetColor(),pDrPen->GetStyle());
	pDrObject->SetLayer(pLayer->GetCurrentLayer());
	//////////////////
	return;
	
} 
////////////////////////////////// end of module //////////////////////
