// grafobj.h : header file
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _OBJECTMGR_
#define _OBJECTMGR_

#include "drobject.h"
#include "dListMgr.h"
///////////////////// Mesh 
#include "MsDefine.h"
///////////////////// ToolBox Mgrs 
#include "eboxmgr.h" 
#include "dboxmgr.h"
//////////////////// 
#define MAX_LABEL_DRAW_PT	1
//////////////////////////////////////////////// DataRowHint Class
class CDataRowHint : public CObject
{
public:
	CDataRowHint();
	DECLARE_DYNAMIC(CDataRowHint)
};
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CObjectMgr
/////////////////////////////////////////////////////////////////////////////
class CObjectMgr : public CObject
{
// Construction
public:
	CObjectMgr();
	DECLARE_SERIAL(CObjectMgr)

public:
 
	virtual BOOL		IsSceneChanged(){return m_bSceneChanged;};
	virtual void		SetSceneChanged(BOOL bSC){m_bSceneChanged = bSC;};
	virtual BOOL		IsViewChanged(){return m_bViewChanged;};
	virtual void		SetViewChanged(BOOL bVC){m_bViewChanged = bVC;};
	//////////////////////
	virtual void Init();
	/////////////////////
//	CSize 		GetDocSize(LPOINT3 WinExtWIC,int nViewNumber);
	CSize 		GetDocSize();
    ///////////////////////////////////////////////////////////// ToolBoxes
	virtual CEBoxMgr*	GetEBoxMgr(){return &m_EBoxMgr;};
	virtual	CDBoxMgr*	GetDBoxMgr(){return &m_DBoxMgr;};
	/////////////////////////////////////////////////////////////// to assign to new object
	virtual	long		GetLastObjectNo(){return m_nLastObjectNo;};
	virtual	void		BumpLastObjectNo(){m_nLastObjectNo++;};
	////////////////////////////////////////////////////////////// ListObjects
	virtual	CDListMgr*	GetObj3DList(){return &m_Obj3DList;};
	virtual	int			GetObj3DCount(){return m_Obj3DList.GetCount();};
	virtual	CDListMgr*	GetObjectList(){return &m_ObjectList;};
	virtual	int			GetObjectCount(){return m_ObjectList.GetCount();};
	virtual UINT 		GetActiveObjectNo(){return m_nActiveObjectNo;};
	virtual void		SetActiveObjectNo(UINT nRow){m_nActiveObjectNo = nRow;};
	virtual	int			GetActiveObjectIndex(){return m_nActiveObjectIndex;};
	virtual	void		SetActiveObjectIndex(int nIndex){ m_nActiveObjectIndex = nIndex;};
	virtual int 		GetActiveObjectType(){return m_nActiveObjectType;};
	virtual void		SetActiveObjectType(int nType){m_nActiveObjectType = nType;};
	///////////////////////////////////////////////////////////////////////// object
	
// Helper functions
	void 	Do_Object_Dialog();
	void 	Do_Object_DataView(CDC* PtrDC,int y,int nRowIndex);
	void	Do_Object_DrawView(CDC*PtrDC,BOOL bPenChange,
	        						int nObjectIndex,int nViewNumber);
	int 	GetObjectIndexfromKey(int nObjectType,CString KeyID,UINT KeyNo);
	int		IsObjectHit(int nObjectType,CClientDC* ptrDC,POINT point,
					RECT* pRect,int nViewNumber);
//	virtual UINT	GetLength(LPOINT3 WIC_I,LPOINT3 WIC_J);
	///////////////////////////////////////////////////// RowView/Data
	void	ChangeSelectionNextObjectIndex(BOOL bNext);
	void	ChangeSelectionToObjectIndex(UINT nNewActiveObjectIndex);
	void	UpdateAllViewsWithActiveIndex(CView* pSourceView,
											UINT nActiveIndex);
	///////////////////////////////////////////////////////////// Helper
//	POINT 	GetOrigin(LPOINT3 WIC,int nViewNumber);
//	void 	ScalebyZoomFactor(POINT* pt,UINT nMaxPt,UINT nViewNumber);
	///////////////////////////////////////////////////////////// helper/cardpack
	void 	SetFormatParam(UINT DecPlaces,long lWorldBase);
	virtual CString GetFormat(){return m_strFormat;};
	///////////////////////////////////////////////////// Specials
	CDrObject* GetSpecObject(int nObjectType);
	/////////////////////////////////////////////////
	virtual void 	SetMapFactorInfo();
	///////////////////////////////////////////////////// Helper
	virtual void 	SCtoDS(double* dpt);    // SCale to DeScale
	virtual void 	DStoSC(double* dpt);    // DeScale to SCale
	virtual void 	SCtoDS(int* npt);
	virtual void 	DStoSC(int* npt);
	virtual void 	SCtoDS(long* npt);
	virtual void 	DStoSC(long* npt);
	virtual void 	SCtoDS(POINT* pt);
	virtual void 	DStoSC(POINT* pt);
	virtual void 	SCtoDS(LPOINT3* pt);
	virtual void 	DStoSC(LPOINT3* pt);
	virtual void 	SCtoDS(LPOINT* pt);
	virtual void 	DStoSC(LPOINT* pt);
	virtual void 	SCtoDS(RECT* rect);
	virtual void 	DStoSC(RECT* rect);
	virtual void 	SCtoDS(LRECT* rect);
	virtual void 	DStoSC(LRECT* rect);
	////////////////////////////////////
	virtual BOOL	IsMeshGenOn(){return m_bMeshGenOn;};
	virtual void	SetMeshGenOn(BOOL bGenOn){m_bMeshGenOn = bGenOn;};
	virtual UINT	GetMeshType(){return m_nMeshType;};
	virtual void	SetMeshType(UINT nType){m_nMeshType = nType;};
	virtual int 	GetCurrentTopLevel(){return m_nCurrentTopLevel;};
	virtual void	SetCurrentTopLevel(int nTL){m_nCurrentTopLevel = nTL;};
	

protected:

	
//	void 	InitXForm();
	//////////////////////////
	void 	InitBooleans();
	void 	InitDataWindow();
	void 	InitDrFont();
	void 	InitDrPen();
	void 	InitHitNet();
	void 	InitLayer();
	void 	InitMapFactor();
	void 	InitPrecision();
	void 	InitScaleFactor();
	void 	InitUnit();
	void 	InitObj3DMnu();
	void 	InitPatchMnu();
										
		   
protected:
    
	////////////////////////////////////// C3D classes
//	CXForm		m_XForm;
	///////////////////////////
	BOOL		m_bMeshGenOn; 
	UINT		m_nMeshType;
	BOOL		m_bSceneChanged;       	// new TransformScene
	BOOL		m_bViewChanged;        	// new TransformView
	///////////////////////////
	CSize 		m_sizeDoc;
    /////////////////////////
	CEBoxMgr 	m_EBoxMgr;
	CDBoxMgr	m_DBoxMgr;
	////////////////////////////////////// DROBJECT
	CDListMgr	m_Obj3DList;
	CDListMgr	m_ObjectList;
	long		m_nLastObjectNo;		// Master Object Number:to be assigned to: 
						  				// All Elements & Non-Elements
	int  		m_nActiveObjectNo;      // Selected Object No
	int 		m_nActiveObjectIndex;   // Selected Object Index in List
	int			m_nActiveObjectType;	// Selected ObjectType;
	int			m_nCurrentTo    ޥ ,�T.�   !                  ޥ$ ��       � �� 0�   !              p�� �  ��        � �b 2�   !                   �  ��       � �b 4�   !              �@�  0�       � ��� 6�   !                  �$ d�       5�  �4 8�   !              �  5� �� � L� ��     0x0112 D�� _� ��     0xF000 D��l� �     0xF010 D�{ y� $�     0xF020 D�O �� <�     0xF030 D�� �� T�     0xF040 Dx