
// 1to50Doc.cpp : CMy1to50Doc 클래스의 구현
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


// CMy1to50Doc 생성/소멸

CMy1to50Doc::CMy1to50Doc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CMy1to50Doc::~CMy1to50Doc()
{
}

BOOL CMy1to50Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CMy1to50Doc serialization

void CMy1to50Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}


// CMy1to50Doc 진단

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


// CMy1to50Doc 명령
