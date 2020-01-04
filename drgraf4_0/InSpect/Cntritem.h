// cntritem.h : interface of the CDrGrafCntrItem class
//

#include <afxole.h>	//OLE
///////////////////
class CDrGrafDoc;
class CDrawView;

class CDrGrafCntrItem : public COleClientItem
{
	DECLARE_SERIAL(CDrGrafCntrItem)

// Constructors
public:
	CDrGrafCntrItem(CDrGrafDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	CDrGrafDoc* GetDocument()
		{ return (CDrGrafDoc*)COleClientItem::GetDocument(); }
	CDrawView* GetActiveView()
		{ return (CDrawView*)COleClientItem::GetActiveView(); }


	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrGrafCntrItem)
	public:
	virtual void OnChange(OLE_NOTIFICATION wNotification, DWORD dwParam);
	virtual void OnActivate();
	protected:
	virtual void OnGetItemPosition(CRect& rPosition);
	virtual void OnDeactivateUI(BOOL bUndoable);
	virtual BOOL OnChangeItemPosition(const CRect& rectPos);
	virtual BOOL CanActivate();
	//}}AFX_VIRTUAL

// Implementation
public:
	~CDrGrafCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	virtual void Serialize(CArchive& ar);

};

/////////////////////////////////////////////////////////////////////////////
