
// 1to50View.cpp : CMy1to50View 클래스의 구현
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
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMy1to50View::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CMy1to50View 생성/소멸

CMy1to50View::CMy1to50View()
{
	// TODO: 여기에 생성 코드를 추가합니다.	
	m_GameState = GAME_READY;//처음 시작시 게임 준비 상태로
	m_Bitmap.LoadBitmap(MAKEINTRESOURCE(IDB_BITMAP1));//이미지 로딩
}

CMy1to50View::~CMy1to50View()
{
}

BOOL CMy1to50View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMy1to50View 그리기

void CMy1to50View::OnDraw(CDC* pDC)
{
	CMy1to50Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CDC MemDC;
	CBitmap *oldBitmap;

	switch(m_GameState)
	{
	case GAME_READY://게임 준비 상태일 경우 글자 출력
		pDC->TextOut(0,0, CString("Click To Game Start!!!"));
		break;
	case GAME_RUN:
		//그림을 조작하기 위한 메모리 만들기
		MemDC.CreateCompatibleDC(pDC);

		//그림을 조작 메모리에 연결
		oldBitmap = MemDC.SelectObject(&m_Bitmap);

		for(int i=0;i < 5;i++)
		{
			for(int j=0;j < 10;j++)
			{
				//그림 상태가 보여질때만 출력
				if(m_ptBitmap[i][j].isVisible)
				{
					//그림 그리기(사각형)
					pDC->BitBlt(m_ptBitmap[i][j].ptBitmap.x, m_ptBitmap[i][j].ptBitmap.y,
						50, 50, &MemDC, 0, 0, SRCCOPY);
					//숫자를 문자열로 만들기
					CString str;
					str.Format(L"%d", m_ptBitmap[i][j].number);

					//숫자 출력
					pDC->TextOut(m_ptBitmap[i][j].ptBitmap.x+15, m_ptBitmap[i][j].ptBitmap.y+15, 
						str);
				}
			}
		}
		//사용한 메모리 돌려주기
		MemDC.SelectObject(oldBitmap);		
		MemDC.DeleteDC();

		break;
	case GAME_RESULT://게임이 끝나면 글자 출력
		pDC->TextOut(0,0, CString("Game OVER!!!"));
		break;
	}
}


// CMy1to50View 인쇄

void CMy1to50View::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CMy1to50View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMy1to50View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMy1to50View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
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


// CMy1to50View 진단

#ifdef _DEBUG
void CMy1to50View::AssertValid() const
{
	CView::AssertValid();
}

void CMy1to50View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy1to50Doc* CMy1to50View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy1to50Doc)));
	return (CMy1to50Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy1to50View 메시지 처리기
//게임 초기화 하기
void CMy1to50View::InitGame(void)
{
	m_currentPosition = 1;
	//데이터를 초기화 하기
	for(int i=0;i < 5;i++)
	{
		for(int j=0;j < 10;j++)
		{		
			m_ptBitmap[i][j].isVisible = TRUE;
			m_ptBitmap[i][j].number = m_currentPosition;
			
			//순서 대로 위치 넣어주기
			m_ptBitmap[i][j].ptBitmap.x = j * 50 + 50;
			m_ptBitmap[i][j].ptBitmap.y = i * 50 + 50;
			
			//넣어줄 숫자를 증가
			m_currentPosition++;
		}
	}

	//게임 실행시 사용해야 하기 때문에 1부터 시작
	m_currentPosition = 1;

	//숫자를 섞어주기
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch(m_GameState)
	{
	case GAME_READY://준바상태에서 마우스 누루면 게임실행 상태로
		m_GameState = GAME_RUN;
		InitGame();//게임 초기화 하고

		InvalidateRect(NULL);//화면 갱신
		break;
	case GAME_RUN:
		int x, y;

		x = (point.x - 50) / 50;
		y = (point.y - 50) / 50;//마우스 위치 얻어오기
		
		//마우스 위치가 유효한 위치인지 검사후
		if((x >= 0 && x < 10) && (y >= 0 && y < 5))
		{
			//순서대로 숫자를 누루면
			if(m_ptBitmap[y][x].number == m_currentPosition)
			{
				//눌러진 그림 않보이게
				m_ptBitmap[y][x].isVisible = FALSE;
				m_currentPosition++;//다음 숫자로

				//게임이 끝났는지검사해서 끝나면 다음 상태로
				if(m_currentPosition == 51)
					m_GameState = GAME_RESULT;

				InvalidateRect(NULL);
			}
		}

		break;
	case GAME_RESULT:
		m_GameState = GAME_READY;//다시 준비 상태로 가기
		break;
	}
	CView::OnLButtonDown(nFlags, point);
}