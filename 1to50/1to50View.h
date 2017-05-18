
// 1to50View.h : CMy1to50View 클래스의 인터페이스
//


#pragma once
#include "atltypes.h"
#include "afxwin.h"

//한개의 블럭을 나타내는 구조체
struct MyRect
{
	CPoint ptBitmap;//위치
	int number;//숫자
	BOOL isVisible;//보여지는지
};

//게임 상태로 3가지(게임 준비-> 게임 실행 -> 게임끝 -> 게임 준비....)
enum GAMETYPE{GAME_READY, GAME_RUN, GAME_RESULT};

class CMy1to50View : public CView
{
protected: // serialization에서만 만들어집니다.
	CMy1to50View();
	DECLARE_DYNCREATE(CMy1to50View)

// 특성입니다.
public:
	CMy1to50Doc* GetDocument() const;

// 작업입니다.
public:
	MyRect m_ptBitmap[5][10];//50개 만들기
	int m_currentPosition;//몇개째 상자를 누루고 있는지
	GAMETYPE m_GameState;//게임 상태
	CBitmap m_Bitmap;//그림 로딩할 변수

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMy1to50View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	void InitGame(void);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	CRect ComRect[7][4];
	CRect MyRect[7][4];
	CDC *CardDC;
};

#ifndef _DEBUG  // 1to50View.cpp의 디버그 버전
inline CMy1to50Doc* CMy1to50View::GetDocument() const
   { return reinterpret_cast<CMy1to50Doc*>(m_pDocument); }
#endif

