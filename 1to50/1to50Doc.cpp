
// 1to50Doc.cpp : CMy1to50Doc Ŭ������ ����
//

#include "stdafx.h"
#include "1to50.h"

#include "1to50Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy1to50Doc

IMPLEMENT_DYNCREATE(CMy1to50Doc, CDocument)

BEGIN_MESSAGE_MAP(CMy1to50Doc, CDocument)
END_MESSAGE_MAP()


// CMy1to50Doc ����/�Ҹ�

CMy1to50Doc::CMy1to50Doc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

CMy1to50Doc::~CMy1to50Doc()
{
}

BOOL CMy1to50Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CMy1to50Doc serialization

void CMy1to50Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}


// CMy1to50Doc ����

#ifdef _DEBUG
void CMy1to50Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMy1to50Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMy1to50Doc ���
