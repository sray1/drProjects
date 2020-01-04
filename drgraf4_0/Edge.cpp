class AFX_EXT_CLASS CEdge : public CObject
{
// Construction
public:  
	CEdge(){};
	virtual ~CEdge(){};
	//////////////////////////////////////
	DECLARE_DYNAMIC(CEdge)
	////////////////////////////////////////////////
	virtual CDListMgr*	GetNodeList(){return &m_NodeList;};
protected:
	CDListMgr	m_NodeList;	
};
///////////////////
