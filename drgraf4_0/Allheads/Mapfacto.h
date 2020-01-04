// CMapFactor.h : header file
//
#ifndef _MAPFACTOROBJECT
#define _MAPFACTOROBJECT

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "DrObject.h" 
/////////////////////////////////////////////////////////////////////////////
// CMapFactor
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CMapFactor : public CDrObject
{
// Construction
public:  
	CMapFactor();

	DECLARE_SERIAL(CMapFactor)


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
	///////////////////////////////////////////////////// MapFactor
    virtual double 	GetMapFactor(){return m_dMapFactor;};
    virtual void 	SetMapFactor(double dmf){m_dMapFactor = dmf;};
	virtual int 	GetMapModeIndex(){return m_nMapIndex;}; 
	virtual void 	SetMapModeIndex(int index){m_nMapIndex = index;};      
	////////////////////////
	virtual	void 	ReadDefaultMapFactor();
	virtual	void 	InitMapFactor();


protected:

	int			m_nElemType;	
	int			m_nObjectType;
	long		m_nObjectNo;
	/////////////////////////////////////////// MapFactor
    UINT	m_nMapIndex;	        
    UINT	m_nMapIndexOld;	        
    UINT	m_nMapIndexDefault;	        
    double	m_dMapFactor;
    double	m_dMapFactorOld;
    double	m_dMapFactorDefault;

protected: 

public:
	virtual ~CMapFactor(){};
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CMapFactor)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif
