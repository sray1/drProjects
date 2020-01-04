// grafobj.h : header file
//
#ifndef _MSOBJMGR_H
#define _MSOBJMGR_H

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

#include <afxtempl.h>	// CList

#include "drobject.h"
#include "dListMgr.h"
///////////////////////////////////// ElemInfo Special
#include "ElemInfo.h"
//////////////////// 
#define MAX_MESH_ARRAY		75
//////////////////////////////////////////////// DeckRowHint Class
class AFX_EXT_CLASS CMeshRowHint : public CObject
{
public:
	CMeshRowHint();
	DECLARE_DYNAMIC(CMeshRowHint)
};
/////////////////////////////////////////////////////////////////////////////
// CMsObjMgr
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CMsObjMgr : public CObject
{
// Construction
public:
	CMsObjMgr();

	DECLARE_SERIAL(CMsObjMgr)


public:
 

	int			SetElemInfoID(CString& ObjID,UINT nObjType);
	///////////////////////////////////////////////////////////////////
	virtual	CDrObject*	AddToDataBase(CString& ObjID,int& nActiveIndex,int nObjType);
	virtual	CDrObject*	AddToDataBase(int& nActiveIndex, int nObjType);
	virtual	int			DeleteFromDataBase(int nObjIndex, int nObjType);
	//////////////////////
	virtual void Init();
	///////////////////////////////////////////////////////////////////////// object
	
// Helper functions

	void 			Do_Object_Dialog(int nActiveObjectType);
	void 			Do_Object_DataView(CDC* PtrDC,int y,int nRowIndex);
	void			Do_Object_DrawView(CDC*PtrDC,BOOL bPenChange,
	        						int nObjectIndex,int nViewNumber, int nActiveObjectType);
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
	virtual	int		ObjTypeToMeshIndex(int nObjectType);
	virtual	int		MeshIndexToObjType(int nIndex);
	virtual	UINT	GetLastMeshNo(int nObjectType);
	virtual	int		BumpLastMeshNo(int nObjectType);
	///////////////////////////////////////////////////// ElemInfo
	CDrObject*		GetSpecObject(int nObjectType);



protected:

	void 			InitElemInfo();
										
		   
protected:

	UINT				m_nLastMeshNo[MAX_MESH_ARRAY];
	///////////////////////////////////// ElemInfo Special
	CElemInfo 			m_ElemInfo;
	////////////////////////////////////////////////////////////////////////////// DataView
	int					m_nActiveRowIndex;
	CList<long,long>	m_RowList;		// RowList storing ObjType & ObjIndex
	////////////////////////
	
public:
// Implementation
public:
	virtual ~CMsObjMgr();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
protected: 
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////
#endif

