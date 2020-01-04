// CBooleans.h : header file
//
#ifndef _BOOLEANS_H
#define _BOOLEANS_H

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "DrObject.h" 
/////////////////////////////////////////////////////////////////////////////
// CBooleans
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CBooleans : public CDrObject
{
// Construction
public:  
	CBooleans();

	DECLARE_SERIAL(CBooleans)


	
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
	///////////////////////////////////////////////////// Booleans 
	virtual BOOL	IsSoundOn(){ return m_bSoundOn;};
	virtual void	ToggleSoundOn(){ m_bSoundOn = !m_bSoundOn;};
	virtual BOOL	IsCoonSocksOff(){ return m_bCoonSocksOff;};
	virtual void	ToggleCoonSocksOff(){ m_bCoonSocksOff = !m_bCoonSocksOff;};
	virtual BOOL	IsSnapOn(){return m_bSnapOn;};
	virtual void	ToggleSnapOn(){ m_bSnapOn = !m_bSnapOn;};
	virtual BOOL	IsHorSnapOn(){return m_bHorSnapOn;};
	virtual void	ToggleHorSnapOn(){ m_bHorSnapOn = !m_bHorSnapOn;};
	virtual BOOL	IsVerSnapOn(){return m_bVerSnapOn;};
	virtual void	ToggleVerSnapOn(){ m_bVerSnapOn = !m_bVerSnapOn;};
	virtual BOOL	IsSpawnOn(){return m_bSpawnOn;};
	virtual void	ToggleSpawnOn(){ m_bSpawnOn = !m_bSpawnOn;};
	virtual BOOL	IsBLineOn(){return m_bBLineOn;};
	virtual void	ToggleBLineOn(){ m_bBLineOn = !m_bBLineOn;};
	virtual BOOL	IsSingleSegOn(){return m_bSingleSegOn;};
	virtual void	ToggleSingleSegOn(){ m_bSingleSegOn = !m_bSingleSegOn;};
	virtual BOOL	IsAutoAcceptOn(){ return m_bAutoAcceptOn;};
	virtual void	ToggleAutoAcceptOn(){ m_bAutoAcceptOn = !m_bAutoAcceptOn;};
	virtual BOOL	IsDialogOn(){ return m_bDialogOn;};
	virtual void	ToggleDialogOn(){ m_bDialogOn = !m_bDialogOn;};
	virtual BOOL	IsElementOn(){ return m_bElementOn;};
	virtual void	ToggleElementOn(){ m_bElementOn = !m_bElementOn;};
	virtual BOOL	IsDragOn(){ return m_bDragOn;};
	virtual void	ToggleDragOn(){ m_bDragOn = !m_bDragOn;};
	virtual BOOL	IsRefreshOn(){ return m_bRefreshOn;};
	virtual void	ToggleRefreshOn(){ m_bRefreshOn = !m_bRefreshOn;};
	virtual BOOL	IsRubberBandOn(){ return m_bRubberBandOn;};
	virtual void	ToggleRubberBandOn(){ m_bRubberBandOn = !m_bRubberBandOn;};
    ///////////////////////////////////////// Views
	virtual BOOL	IsStViewActive(){ return m_bStViewActive;};	// static
	virtual void	ToggleStViewActive(){ m_bStViewActive = !m_bStViewActive;};
	virtual BOOL	IsSpViewActive(){ return m_bSpViewActive;};	// spectral
	virtual void	ToggleSpViewActive(){ m_bSpViewActive = !m_bSpViewActive;};
	virtual BOOL	IsHsViewActive(){ return m_bHsViewActive;};	// history
	virtual void	ToggleHsViewActive(){ m_bHsViewActive = !m_bHsViewActive;};
	//
	virtual BOOL	Is12ViewActive(){ return m_b12ViewActive;};
	virtual void	Toggle12ViewActive(){ m_b12ViewActive = !m_b12ViewActive;};
	virtual BOOL	Is23ViewActive(){ return m_b23ViewActive;};
	virtual void	Toggle23ViewActive(){ m_b23ViewActive = !m_b23ViewActive;};
	virtual BOOL	Is31ViewActive(){ return m_b31ViewActive;};
	virtual void	Toggle31ViewActive(){ m_b31ViewActive = !m_b31ViewActive;};
	virtual BOOL	IsIsoViewActive(){ return m_bIsoViewActive;};
	virtual void	ToggleIsoViewActive(){ m_bIsoViewActive = !m_bIsoViewActive;};
	virtual BOOL	IsDataViewActive(){ return m_bDataViewActive;};
	virtual void	ToggleDataViewActive(){ m_bDataViewActive = !m_bDataViewActive;};
	virtual BOOL	IsMeshDataViewActive(){ return m_bMeshDataViewActive;};
	virtual void	ToggleMeshDataViewActive(){ m_bMeshDataViewActive = !m_bMeshDataViewActive;};
	virtual BOOL	IsDeckViewActive(){ return m_bDeckViewActive;};
	virtual void	ToggleDeckViewActive(){ m_bDeckViewActive = !m_bDeckViewActive;};
	virtual BOOL	IsFormDataViewActive(){ return m_bFormDataViewActive;};
	virtual void	ToggleFormDataViewActive(){ m_bFormDataViewActive = !m_bFormDataViewActive;};
    /////////////////////////////////////////// Mode
	virtual BOOL	IsInputMode(){ return m_bInputMode;};
	virtual void	SetInputMode(BOOL bS){ m_bInputMode = bS;};
	virtual BOOL	IsOutputMode(){ return m_bOutputMode;};
	virtual void	SetOutputMode(BOOL bS){ m_bOutputMode = bS;};
	/////////////////////////////////////////////////////////// Zoom/MainView
	virtual	BOOL	IsZoomEnabled(int nViewNumber);
	virtual	void	SetZoomEnabled(int nViewNumber,BOOL bTF);
	virtual	BOOL	IsZoomOn(int nStatusType,int nViewNumber);
	virtual	BOOL	ToggleZoom(int nStatusType,int nViewNumber); 
	////////////////////////
	virtual	void 	ReadDefaultBooleans();
	virtual	void 	InitBooleans();
 
protected: 

	int		m_nElemType;	
	int		m_nObjectType;
	long	m_nObjectNo; 
	///////////////////////////////////////// Menu/Button
	BOOL	m_bSoundOn;
	BOOL	m_bDialogOn;
	BOOL	m_bElementOn;
	BOOL	m_bDragOn;
	BOOL	m_bRubberBandOn;
	BOOL	m_bRefreshOn;
	/////////////////////
	BOOL	m_bSnapOn;		// object level, ie., node,curve etc to Object Merge
	BOOL	m_bHorSnapOn;
	BOOL	m_bVerSnapOn;
	BOOL	m_bSpawnOn;		// Copy On
	BOOL	m_bBLineOn;
	BOOL	m_bSingleSegOn;
 	BOOL	m_bAutoAcceptOn;
 	BOOL	m_bCoonSocksOff;
 	///////////////////////////////////////// Views
    BOOL	m_bStViewActive;	// static
    BOOL	m_bSpViewActive;	// spectral
    BOOL	m_bHsViewActive;	// history
	//
    BOOL	m_b12ViewActive;
    BOOL	m_b23ViewActive;
    BOOL	m_b31ViewActive;
    BOOL	m_bIsoViewActive; 
    BOOL	m_bDataViewActive; 
    BOOL	m_bMeshDataViewActive; 
    BOOL	m_bDeckViewActive; 
    BOOL	m_bFormDataViewActive; 
    /////////////////////////////////////////// Mode
    BOOL	m_bInputMode;
    BOOL	m_bOutputMode;
	/////////////////////////////////////////// Zoom/MainView
	BOOL	m_bZoomEnable12;
	BOOL	m_bZoomEnable23;
	BOOL	m_bZoomEnable31;
	BOOL	m_bZoomEnableISO;
	BOOL	m_bZoomFit12;
	BOOL	m_bZoom12;
	BOOL	m_bZoomFit23;
	BOOL	m_bZoom23;
	BOOL	m_bZoomFit31;
	BOOL	m_bZoom31;
	BOOL	m_bZoomFitISO;
	BOOL	m_bZoomISO;

protected: 

public:
	virtual ~CBooleans(){};
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CBooleans)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif
