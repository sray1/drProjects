// CLayer.h : header file
//
#ifndef _LAYEROBJECT
#define _LAYEROBJECT

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "DrObject.h"
#define MAX_LAYER	500
/////////////////////////////////////////////////////////////////////////////
// CLayer
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CLayer : public CDrObject
{
// Construction
public:  
	CLayer();

	DECLARE_SERIAL(CLayer)


protected: 
public:
// Implementation
public:
	
	///////////////////////////////////////////////////// EXPORTS needed for DLL
	virtual void	DoDataView(CDC* PtrDC, int y);
	virtual int 	GetObjectType(){return m_nObjectType;};
	virtual void 	SetObjectType(int nType){m_nObjectType = nType;};
	virtual int 	GetElemType(){return m_nElemType;};
	virtual void	SetElemType(int nType){m_nElemType = nType;};
	virtual long 	GetObjectNo(){return m_nObjectNo;}; 
	virtual void	SetObjectNo(long nNo){ m_nObjectNo = nNo;};
	virtual void	Pack_drPipe(CString* pstrCard);
	virtual void 	GetObjectInfo(CDrObject* pObject);
	virtual void 	SetObjectInfo(CDrObject* pObject);
	///////////////////////////////////////////////////// Layer
	virtual UINT 	GetCurrentLayer(){return m_nCurrentLayer;};
	virtual void	SetCurrentLayer(UINT nCurrentLayer)
						{m_nCurrentLayer = nCurrentLayer;};	
	virtual UINT 	GetCurrentLayerOld(){return m_nCurrentLayerOld;};
	virtual void	SetCurrentLayerOld(UINT nCurrentLayer)
						{m_nCurrentLayerOld = nCurrentLayer;};	
	virtual UINT 	GetCurrentLayerDefault(){return m_nCurrentLayerDefault;};
	virtual void	SetCurrentLayerDefault(UINT nCurrentLayer)
						{m_nCurrentLayerDefault = nCurrentLayer;};
				//////////////////////////////////////////////		
    virtual CString GetLayerInfo(UINT i);
    virtual void	SetLayerInfo(UINT i,UINT nType);
    			//////////////////////////////// 
	virtual void 	GetLayerArray(UINT nLayer[][2]);
	virtual void 	SetLayerArray(UINT nLayer[][2]);
	virtual void 	GetLayerOldArray(UINT nLayer[][2]);
	virtual void 	SetLayerOldArray(UINT nLayer[][2]);
	virtual void 	GetLayerDefaultArray(UINT nLayer[][2]);
	virtual void 	SetLayerDefaultArray(UINT nLayer[][2]); 
	////////////////////////
	virtual	void 		ReadDefaultLayer();
	virtual	void 		InitLayer();

protected: 

	int		m_nElemType;	
	int		m_nObjectType;
	long	m_nObjectNo;
    /////////////////////////////////////////// Layer
    UINT	m_nLayer[MAX_LAYER][2];       // Working
    UINT	m_nLayerOld[MAX_LAYER][2];    // Old For Edit 
    UINT	m_nLayerDefault[MAX_LAYER][2];    // Default Setting from/to INI
	UINT	m_nCurrentLayer;
    UINT	m_nCurrentLayerOld;
    UINT	m_nCurrentLayerDefault;

protected: 

public:
	virtual ~CLayer(){};
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CLayer)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif
