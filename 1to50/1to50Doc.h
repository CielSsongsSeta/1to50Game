
// 1to50Doc.h : CMy1to50Doc Ŭ������ �������̽�
//


#pragma once


class CMy1to50Doc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CMy1to50Doc();
	DECLARE_DYNCREATE(CMy1to50Doc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// �����Դϴ�.
public:
	virtual ~CMy1to50Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};


