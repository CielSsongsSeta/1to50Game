
// 1to50View.h : CMy1to50View Ŭ������ �������̽�
//


#pragma once
#include "atltypes.h"
#include "afxwin.h"

//�Ѱ��� ���� ��Ÿ���� ����ü
struct MyRect
{
	CPoint ptBitmap;//��ġ
	int number;//����
	BOOL isVisible;//����������
};

//���� ���·� 3����(���� �غ�-> ���� ���� -> ���ӳ� -> ���� �غ�....)
enum GAMETYPE{GAME_READY, GAME_RUN, GAME_RESULT};

class CMy1to50View : public CView
{
protected: // serialization������ ��������ϴ�.
	CMy1to50View();
	DECLARE_DYNCREATE(CMy1to50View)

// Ư���Դϴ�.
public:
	CMy1to50Doc* GetDocument() const;

// �۾��Դϴ�.
public:
	MyRect m_ptBitmap[5][10];//50�� �����
	int m_currentPosition;//�° ���ڸ� ����� �ִ���
	GAMETYPE m_GameState;//���� ����
	CBitmap m_Bitmap;//�׸� �ε��� ����

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CMy1to50View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
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

#ifndef _DEBUG  // 1to50View.cpp�� ����� ����
inline CMy1to50Doc* CMy1to50View::GetDocument() const
   { return reinterpret_cast<CMy1to50Doc*>(m_pDocument); }
#endif

