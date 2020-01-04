// SrvrItem.h : interface of the CDrGrafSrvrItem class
//

class CDrGrafSrvrItem : public COleServerItem
{
	DECLARE_DYNAMIC(CDrGrafSrvrItem)

// Constructors
public:
	CDrGrafSrvrItem(CDrGrafDoc* pContainerDoc);

// Attributes
	CDrGrafDoc* GetDocument() const
		{ return (CDrGrafDoc*)COleServerItem::GetDocument(); }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrGrafSrvrItem)
	public:
	virtual BOOL OnDraw(CDC* pDC, CSize& rSize);
	virtual BOOL OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize);
	//}}AFX_VIRTUAL

// Implementation
public:
	~CDrGrafSrvrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
};

/////////////////////////////////////////////////////////////////////////////
