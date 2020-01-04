// cntritem.h : interface of the CDrgrafCntrItem class
//

class CDrGrafDoc;
class CDrawView;

class CDrgrafCntrItem : public COleClientItem
{
	DECLARE_SERIAL(CDrgrafCntrItem)

// Constructors
public:
	CDrgrafCntrItem(CDrGrafDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	CDrGrafDoc* GetDocument()
		{ return (CDrGrafDoc*)COleClientItem::GetDocument(); }
	CDrGrafView* GetActiveView()
		{ return (CDrGrafView*)COleClientItem::GetActiveView(); }

// Implementation
public:
	~CDrgrafCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	virtual void Serialize(CArchive& ar);
	virtual void OnGetItemPosition(CRect& rPosition);
	virtual void OnDeactivateUI(BOOL bUndoable);

protected:
	virtual void OnChange(OLE_NOTIFICATION wNotification, DWORD dwParam);
	virtual BOOL OnChangeItemPosition(const CRect& rectPos);
};

/////////////////////////////////////////////////////////////////////////////
