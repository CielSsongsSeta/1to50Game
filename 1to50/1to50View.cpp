
// 1to50View.cpp : CMy1to50View Ŭ������ ����
//

#include "stdafx.h"
#include "1to50.h"

#include "1to50Doc.h"
#include "1to50View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMy1to50View

IMPLEMENT_DYNCREATE(CMy1to50View, CView)

BEGIN_MESSAGE_MAP(CMy1to50View, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMy1to50View::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CMy1to50View ����/�Ҹ�

CMy1to50View::CMy1to50View()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.	
	m_GameState = GAME_READY;//ó�� ���۽� ���� �غ� ���·�
	m_Bitmap.LoadBitmap(MAKEINTRESOURCE(IDB_BITMAP1));//�̹��� �ε�
}

CMy1to50View::~CMy1to50View()
{
}

BOOL CMy1to50View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CMy1to50View �׸���

void CMy1to50View::OnDraw(CDC* pDC)
{
	CMy1to50Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	CDC MemDC;
	CBitmap *oldBitmap;

	switch(m_GameState)
	{
	case GAME_READY://���� �غ� ������ ��� ���� ���
		pDC->TextOut(0,0, CString("Click To Game Start!!!"));
		break;
	case GAME_RUN:
		//�׸��� �����ϱ� ���� �޸� �����
		MemDC.CreateCompatibleDC(pDC);

		//�׸��� ���� �޸𸮿� ����
		oldBitmap = MemDC.SelectObject(&m_Bitmap);

		for(int i=0;i < 5;i++)
		{
			for(int j=0;j < 10;j++)
			{
				//�׸� ���°� ���������� ���
				if(m_ptBitmap[i][j].isVisible)
				{
					//�׸� �׸���(�簢��)
					pDC->BitBlt(m_ptBitmap[i][j].ptBitmap.x, m_ptBitmap[i][j].ptBitmap.y,
						50, 50, &MemDC, 0, 0, SRCCOPY);
					//���ڸ� ���ڿ��� �����
					CString str;
					str.Format(L"%d", m_ptBitmap[i][j].number);

					//���� ���
					pDC->TextOut(m_ptBitmap[i][j].ptBitmap.x+15, m_ptBitmap[i][j].ptBitmap.y+15, 
						str);
				}
			}
		}
		//����� �޸� �����ֱ�
		MemDC.SelectObject(oldBitmap);		
		MemDC.DeleteDC();

		break;
	case GAME_RESULT://������ ������ ���� ���
		pDC->TextOut(0,0, CString("Game OVER!!!"));
		break;
	}
}


// CMy1to50View �μ�

void CMy1to50View::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CMy1to50View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMy1to50View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMy1to50View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

void CMy1to50View::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMy1to50View::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CMy1to50View ����

#ifdef _DEBUG
void CMy1to50View::AssertValid() const
{
	CView::AssertValid();
}

void CMy1to50View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy1to50Doc* CMy1to50View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy1to50Doc)));
	return (CMy1to50Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy1to50View �޽��� ó����
//���� �ʱ�ȭ �ϱ�
void CMy1to50View::InitGame(void)
{
	m_currentPosition = 1;
	//�����͸� �ʱ�ȭ �ϱ�
	for(int i=0;i < 5;i++)
	{
		for(int j=0;j < 10;j++)
		{		
			m_ptBitmap[i][j].isVisible = TRUE;
			m_ptBitmap[i][j].number = m_currentPosition;
			
			//���� ��� ��ġ �־��ֱ�
			m_ptBitmap[i][j].ptBitmap.x = j * 50 + 50;
			m_ptBitmap[i][j].ptBitmap.y = i * 50 + 50;
			
			//�־��� ���ڸ� ����
			m_currentPosition++;
		}
	}

	//���� ����� ����ؾ� �ϱ� ������ 1���� ����
	m_currentPosition = 1;

	//���ڸ� �����ֱ�
	for(int i=0;i < 100;i++)
	{
		int a = rand() % 5;
		int b = rand() % 10;

		int c = rand() % 5;
		int d = rand() % 10;

		int temp = m_ptBitmap[a][b].number;
		m_ptBitmap[a][b].number = m_ptBitmap[c][d].number;
		m_ptBitmap[c][d].number = temp;
	}
}

void CMy1to50View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	switch(m_GameState)
	{
	case GAME_READY://�عٻ��¿��� ���콺 ����� ���ӽ��� ���·�
		m_GameState = GAME_RUN;
		InitGame();//���� �ʱ�ȭ �ϰ�

		InvalidateRect(NULL);//ȭ�� ����
		break;
	case GAME_RUN:
		int x, y;

		x = (point.x - 50) / 50;
		y = (point.y - 50) / 50;//���콺 ��ġ ������
		
		//���콺 ��ġ�� ��ȿ�� ��ġ���� �˻���
		if((x >= 0 && x < 10) && (y >= 0 && y < 5))
		{
			//������� ���ڸ� �����
			if(m_ptBitmap[y][x].number == m_currentPosition)
			{
				//������ �׸� �ʺ��̰�
				m_ptBitmap[y][x].isVisible = FALSE;
				m_currentPosition++;//���� ���ڷ�

				//������ ���������˻��ؼ� ������ ���� ���·�
				if(m_currentPosition == 51)
					m_GameState = GAME_RESULT;

				InvalidateRect(NULL);
			}
		}

		break;
	case GAME_RESULT:
		m_GameState = GAME_READY;//�ٽ� �غ� ���·� ����
		break;
	}
	CView::OnLButtonDown(nFlags, point);
}