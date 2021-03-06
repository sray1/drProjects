// grafobj.h : header file
//
#ifndef _OBJMGR_H
#define _OBJMGR_H

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

#include <afxtempl.h>	// CList

#include "drobject.h"
#include "dListMgr.h"
///////////////////// Mesh 
#include "Def_Ms.h"
///////////////////// 
#include "Def_Spec.h"   // for initialization of the specials
#include "Booleans.h"
#include "DataWind.h"
#include "DrFont.h"
#include "DrPen.h"
#include "HitNet.h"
#include "Layer.h"
#include "patchMnu.h"
#include "Obj3DMnu.h"
///////////////////// 
#include "MapFacto.h"
#include "Precison.h"
#include "ScaleFac.h"
#include "Unit.h"
////////////////////
//#include "ElemInfo.h"
//////////////////// 
#define MAX_LABEL_DRAW_PT	1
#define MAX_LIST_ARRAY		50
#define MAX_INPUT_ARRAY		50
//////////////////////////////////////////////// DataRowHint Class
class AFX_EXT_CLASS CDataRowHint : public CObject
{
public:
	CDataRowHint();
	DECLARE_DYNAMIC(CDataRowHint)
};
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CObjectMgr
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CObjectMgr : public CObject
{
// Construction
public:
	CObjectMgr();

	DECLARE_SERIAL(CObjectMgr)


public:
 

	//////////////////////////////////////////////////////////////
	CDListMgr*	GetNodeList_OtherContext(BOOL bCNode,BOOL bMeshMode);		// OtherContext
	CDListMgr*	GetNodeList_NodeContext(UINT uType);						// NodeContext		
	int			SetNodeInfoID(CString& ObjID,BOOL bCNode,UINT uType);		
	int			SetNodeInfoID(CString& ObjID,BOOL bCNode,BOOL bMeshMode);		
	int			SetObjInfoID(CString& ObjID,UINT nObjType);
	/////////////////////////////////////////////////////////////////
	virtual CMapFactor* 	GetMapFactor(){return &m_MapFactor;};
	virtual CPrecision* 	GetPrecision(){return &m_Precision;};
	virtual CScaleFactor* 	GetScaleFactor(){return &m_ScaleFactor;};
	virtual CUnit*		 	GetUnit(){return &m_Unit;};
	/////////////////////////////////////////////////
	virtual void 			SetMapFactorInfo();
	///////////////////////////////////////////////////////////////////
	virtual	CDrObject*	AddToDataBase(CString& ObjID,int& nActiveIndex,int nObjType);
	virtual	CDrObject*	AddToDataBase(int& nActiveIndex, int nObjType);
	virtual	int			DeleteFromDataBase(int nObjIndex, int nObjType);
	virtual	CDListMgr*	GetObjectListFromIndex(int nIndex)
						{
							return (nIndex>=0 && nIndex<MAX_LIST_ARRAY)?
							&(m_ObjectList[nIndex]):(CDListMgr*)NULL;
						};
	virtual	int			ObjTypeToListIndex(int nObjectType);
	virtual	int			ListIndexToObjType(int nIndex);
	/////////////////////////////////////////////////
	virtual BOOL		IsSceneChanged(){return m_bSceneChanged;};
	virtual void		SetSceneChanged(BOOL bSC){m_bSceneChanged = bSC;};
	virtual BOOL		IsViewChanged(){return m_bViewChanged;};
	virtual void		SetViewChanged(BOOL bVC){m_bViewChanged = bVC;};
	//////////////////////
	virtual void Init();
	/////////////////////
//	CSize 		GetDocSize(LPOINT3 WinExtWIC,int nViewNumber);
	CSize 				GetDocSize();
	/////////////////////////////////////////////////////////////////////////////////// ListObjects
//	virtual	CDListMgr*	GetObj3DList(){return &m_Obj3DList;};
//	virtual	int			GetObj3DCount(){return m_Obj3DList.GetCount();};
	virtual	CDListMgr*	GetObjectList(int nObjectType);
	virtual	int			GetObjectCount(int nObjectType);
	virtual	UINT		GetLastObjectNo(int nObjectType);
	virtual	int			BumpLastObjectNo(int nObjectType);
	virtual UINT 		GetMasterLastObjectNo(){return m_nMasterLastObjectNo;};
	virtual void		SetMasterLastObjectNo(UINT nRow){m_nMasterLastObjectNo = nRow;};
	////////////
	virtual UINT 		GetActiveObjectNo(){return m_nActiveObjectNo;};
	virtual void		SetActiveObjectNo(UINT nRow){m_nActiveObjectNo = nRow;};
	virtual	int			GetActiveListIndex(){return m_nActiveListIndex;};
	virtual	void		SetActiveListIndex(int nIndex){ m_nActiveListIndex = nIndex;};
	virtual	int			GetActiveObjectIndex(){return m_nActiveObjectIndex;};
	virtual	void		SetActiveObjectIndex(int nIndex){ m_nActiveObjectIndex = nIndex;};
	virtual int 		GetActiveObjectType(){return m_nActiveObjectType;};
	virtual void		SetActiveObjectType(int nType){m_nActiveObjectType = nType;};
	///////////////////////////////////////////////////////////////////////// object
	
// Helper functions

	void 			Do_Object_Dialog(int nActiveObjectType);
	void 			Do_Object_DataView(CDC* PtrDC,int y,int nRowIndex);
	void			Do_Object_DrawView(CDC*PtrDC,BOOL bPenChange,
	        						int nObjectIndex,int nViewNumber, int nActiveObjectType);
	int 			GetObjectIndexfromKey(int nObjectType,CString KeyID,UINT KeyNo);
//	virtual UINT	GetLength(LPOINT3 WIC_I,LPOINT3 WIC_J);
	///////////////////////////////////////////////////// RowView/Data
	CList<long,long>* GetRowList(){return &m_RowList;};
	int				AddToRowList(int& nObjIndex, int& nObjType);
	int				DeleteFromRowList(int& nRowIndex);
	int				GetRowCount(){return m_RowList.GetCount();};
	int				GetActiveRowIndex(){return m_nActiveRowIndex;};
	void			SetActiveRowIndex(int n){m_nActiveRowIndex = n;};
	int				RowIndexToObjIndex(int nRowIndex, int& nObjIndex, int& nObjType);
	int				ObjIndexToRowIndex(int& nRowIndex, int& nObjIndex, int& nObjType);
	void			ChangeSelectionNextObjectIndex(BOOL bNext);
	void			ChangeSelectionToObjectIndex(UINT nNewActiveRowIndex);
	void			UpdateAllViewsWithActiveIndex(CView* pSourceView,
											UINT nActiveIndex, int nActiveObjType);
	///////////////////////////////////////////////////////////// Helper
//	POINT 	GetOrigin(LPOINT3 WIC,int nViewNumber);
//	void 	ScalebyZoomFactor(POINT* pt,UINT nMaxPt,UINT nViewNumber);
	///////////////////////////////////////////////////////////// helper/cardpack
	void 			SetFormatParam(UINT DecPlaces,long lWorldBase);
	virtual 		CString GetFormat(){return m_strFormat;};
	///////////////////////////////////////////////////// Specials
	CDrObject* 		GetSpecObject(int nObjectType);
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
	///////////////////////////////////////////////////////////////////////////////////InputObjects
	virtual	int		ObjTypeToInputIndex(int nObjectType);
	virtual	int		InputIndexToObjType(int nIndex);
	virtual	UINT	GetLastInputNo(int nObjectType);
	virtual	int		BumpLastInputNo(int nObjectType);
	/////////////////////////////////////////////////////////////////////////////////// Display
			int		ShowObject_On_Off(CDrObject* pObject,UINT GenObj,BOOL bOn);
			int		ShowLabel_On_Off(CDListMgr* pList,CString ID,BOOL bOn);




protected:


	
	
//	void 			InitElemInfo();
	//////////////////////////
	void 			InitBooleans();
	void 			InitDataWindow();
	void 			InitDrFont();
	void 			InitDrPen();
	void 			InitHitNet();
	void 			InitLayer();
	void 			InitObj3DMnu();
	void 			InitPatchMnu();
	////////////////////////////////////////////////////// Specials
	void 			InitMapFactor();
	void 			InitPrecision();
	void 			InitScaleFactor();
	void 			InitUnit();
										
		   
protected:

	UINT			m_nLastInputNo[MAX_INPUT_ARRAY];	// 
	//////////////////////////////////// Special Classes
	CBooleans 		m_Booleans;
	CDataWindow 	m_DataWindow;
	CDrFont 		m_DrFont;
	CDrPen 			m_DrPen;
	CHitNet 		m_HitNet;
	CLayer 			m_Layer;
	CObj3DMnu 		m_Obj3DMnu;
	CPatchMnu		m_PatchMnu;
	///////////////////////////////////// Specials
	CMapFactor 		m_MapFactor;
	CPrecision 		m_Precision;
	CScaleFactor 	m_ScaleFactor;
	CUnit 			m_Unit;
	///////////////////////////////////// ElemInfo Special
//	CElemInfo 		m_ElemInfo;
	///////////////////////////
	BOOL		m_bMeshGenOn; 
	UINT		m_nMeshType;
	BOOL		m_bSceneChanged;       	// new TransformScene
	BOOL		m_bViewChanged;        	// new TransformView
	///////////////////////////
	CSize 		m_sizeDoc;
	////////////////////////////////////////////////////////////////////////////// Lists:DataBase
//	CDListMgr	m_Obj3DList;
	CDListMgr	m_ObjectList[MAX_LIST_ARRAY];
	UINT		m_nLastObjectNo[MAX_LIST_ARRAY];
										// Object Number:to be assigned to: 
						  				//		Current m_ObjectList
	int			m_nActiveListIndex;		// Current m_ObjectList Array Index
	int 		m_nActiveObjectIndex;   // Selected Object Index in Current m_ObjectList
	int			m_nActiveObjectType;	// Selected ObjectType;
	long		m_nMasterLastObjectNo;	// Master Object Number:to be assigned to: 
						  						// All Elements & Non-Elements
	int  		m_nActiveObjectNo;      // Selected Object No
	int			m_nCurrentTopLevel;		// List Cut-off Level for draw etc.
	////////////////////////////////////////////////////////////////////////////// DataView
	int			m_nActiveRowIndex;
	CList<long,long>	m_RowList;		// RowList storing ObjType & ObjIndex
	/////////////////////////////////
	CString		m_strFormat;			// for Data Packing
	////////////////////////
	
public:
// Implementation
public:
	virtual ~CObjectMgr();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
protected: 
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////
#endif

