class AFX_EXT_CLASS CFace : public CObject
{
// Construction
public:  
	CFace(){};
	virtual ~CFace(){};
	//////////////////////////////////////
	DECLARE_DYNAMIC(CFace)
	////////////////////////////////////////////////
	virtual CDListMgr*	GetNodeList(){return &m_NodeList;};
protected:
	CDListMgr	m_NodeList;	
};
///////////////////
