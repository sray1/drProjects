// DBoxMgr.h : header file
//
#ifndef _DBOXMGR_H
#define _DBOXMGR_H

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


/////////////////////////////////////////////////////////////////////////////
// CDBoxMgr
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CDBoxMgr : public CObject
{
// Construction
public:  
	CDBoxMgr();

	DECLARE_SERIAL(CDBoxMgr)


protected: 
public:
// Implementation
public: 

	////////////////////////////////////////////////////////////////////// DrawBox
	virtual BOOL	IsDrawBoxActive(){return m_bDrawBox;};
	virtual void	SetDrawBoxStatus(BOOL bStatus){m_bDrawBox = bStatus;};
	virtual int		GetActiveObjectType(){return m_nObjectType;};
	virtual void	SetActiveObjectType(int nObjectType){m_nObjectType = nObjectType;};
	virtual int		GetActiveToolType(){return m_nToolType;};
	virtual void	SetActiveToolType(int nToolType){m_nToolType = nToolType;};
	virtual COLORREF	GetActiveForeColor(){return m_crFore;};
	virtual void	SetActiveForeColor(COLORREF nColor){m_crFore = nColor;};
	virtual COLORREF	GetActiveBackColor(){return m_crBack;};
	virtual void	SetActiveBackColor(COLORREF nColor){m_crBack = nColor;};
	/////////////////////////////////////////////////////	

protected:
	
	///////////////////////////////////////// DrawBox
    BOOL		m_bDrawBox;
    int			m_nObjectType;
	int			m_nToolType;
	COLORREF	m_crFore;
	COLORREF	m_crBack;
	////////////////////////
    
protected: 

public:
	virtual ~CDBoxMgr(){};
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
};

#undef AFX_DATA
#define AFX_DATA
/////////////////
#endif           

