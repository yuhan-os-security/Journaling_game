// Journaling_game.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//코딩하면서 생각나는대로 필터 없이 주석에 적어놓았음. 조금 어수선할 수 있음

#include "framework.h"
#include "Journaling_game.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
					 _In_opt_ HINSTANCE hPrevInstance,
					 _In_ LPWSTR    lpCmdLine,
					 _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 여기에 코드를 입력합니다.

	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_JOURNALINGGAME, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 애플리케이션 초기화를 수행합니다:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_JOURNALINGGAME));

	MSG msg;

	// 기본 메시지 루프입니다:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style          = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc    = WndProc;
	wcex.cbClsExtra     = 0;
	wcex.cbWndExtra     = 0;
	wcex.hInstance      = hInstance;
	wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_JOURNALINGGAME));
	wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_JOURNALINGGAME);
	wcex.lpszClassName  = szWindowClass;
	wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	  CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
	  return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// 현재 장면에 대한 정보이다
	// 해당 변수로 화면에 표시할 컴포넌트들을 조절한다.
	static int Page = page_main; //이 부분 직접 변경하면서 해보기. 원래는 page_main이었다.

	// 모든 라벨에 대한 모음이다.
	// 서브모듈을 활용한 객체이다.
	static vector<LABEL*> labels;

	// 페이지 버튼에 대한 모음이다.
	// 페이지를 바꾸는 버튼에 대한 변수이다.
	// 서브모듈을 활용한 객체이다.
	static vector<TEXTBUTTON*> page_buttons;
	
	// 에딧(텍스트 상자)에 대한 모음이다. push_back 적용이 안되서 임시방편.
	static HWND edit1;
	static HWND edit2;
	

	// 점프할 페이지 번호
	// 변수의 값을 0 이외의 값으로 설정 한 후 버튼이 눌리면 해당 페이지로 이동됨
	static int jump = 0;
	

	switch (message)
	{
	case WM_CREATE:
		// 1번 페이지에서 사용될 요소
		// 게임 초기화면
		labels.push_back(new LABEL(300, 200, L"누구나 꿈꿔본 암호 뚫기 게임", 30));		// 라벨0
		labels.push_back(new LABEL(580, 240, L"Feat.후킹", 20));						// 라벨1

		// 시작 버튼 등록
		page_buttons.push_back(new TEXTBUTTON(L"게임시작", 0, 430, 300, 150, 50, 20));	// 버튼0
		page_buttons[0]->setAction(NextPage);

		// 도움말 버튼 등록
		page_buttons.push_back(new TEXTBUTTON(L"도움말", 0, 430, 370, 150, 50, 20));	// 버튼1
		page_buttons[1]->setAction(HelpPage);		
		
		// 1번 버튼의 동작을 중지 시킨다.
		//page_buttons[1]->setEnabled(false);
		// 1번 버튼을 보이게 설정한다.
		

		// ------------------2번 페이지에서 사용될 요소----------------------
		// 이름 입력 페이지
		labels.push_back(new LABEL(410, 150, L"플레이어 등록", 30));	// 라벨2
		labels.push_back(new LABEL(280, 200, L"PLAYER 1", 30));			// 라벨3
		labels.push_back(new LABEL(280, 250, L"PLAYER 2", 30));			// 라벨4

		page_buttons.push_back(new TEXTBUTTON(L"시작", 0, 430, 320, 150, 50, 20));		// 버튼2
		page_buttons[2]->setAction(NextPage);
		page_buttons[2]->setVisible(false);
		page_buttons[2]->setEnabled(false);

		//edit1 = CreateWindow(L"EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 450, 200, 250, 40, hWnd, (HMENU)101, NULL, NULL);
		//edit2 = CreateWindow(L"EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 450, 270, 250, 40, hWnd, (HMENU)102, NULL, NULL);
		// 에딧은 몇 개가 필요하게 될 지 모르겠어서 배열 없이 따로 만들어봤다. 솔직히 인수 하나하나의 의미는 잘 모르겠고
		// 시간이 너무 늦어서 급한대로 인터넷에서 에딧 생성 코드를 찾아서 이 코드에 맞게 고쳐봤다
		// 어느 정도는 알겠는데.. 빠삭하게 알려면 맘먹고 찾아봐야 할 듯. (에딧=텍스트 상자)


		// ------------------3번 페이지에서 사용될 요소-----------------------
		// 계정 등록 페이지
		labels.push_back(new LABEL(420, 150, L"계정 생성", 30));		// 라벨5
		labels.push_back(new LABEL(280, 200, L"사용자 ID", 30));		// 라벨6
		labels.push_back(new LABEL(280, 250, L"사용자 PW", 30));		// 라벨7

		labels.push_back(new LABEL(50, 50, L"PLAYER 1", 20));			// 라벨8
		labels.push_back(new LABEL(180, 50, L"ROUND N", 20));			// 라벨9

		page_buttons.push_back(new TEXTBUTTON(L"초기화", 0, 350, 320, 100, 50, 20));	// 버튼3
		page_buttons.push_back(new TEXTBUTTON(L"회원가입", 0, 470, 320, 100, 50, 20));	// 버튼4

		page_buttons[3]->setAction(resetPage);
		page_buttons[3]->setVisible(false);
		page_buttons[3]->setEnabled(false);

		page_buttons[4]->setAction(NextPage);
		page_buttons[4]->setVisible(false);
		page_buttons[4]->setEnabled(false);


		// ------------------4번 페이지에서 사용될 요소-----------------------
		// 로그인 페이지
		labels.push_back(new LABEL(460, 150, L"로그인", 30));			// 라벨10
		labels.push_back(new LABEL(320, 200, L"ID : ", 30));			// 라벨11
		labels.push_back(new LABEL(320, 250, L"PW : ", 30));			// 라벨12
		
		labels.push_back(new LABEL(50, 50, L"PLAYER 1", 20));			// 라벨13
		labels.push_back(new LABEL(180, 50, L"ROUND N", 20));			// 라벨14

		page_buttons.push_back(new TEXTBUTTON(L"로그인", 0, 600, 200, 100, 90, 30)); // 버튼5
		page_buttons[5]->setAction(NextPage);
		page_buttons[5]->setVisible(false);
		page_buttons[5]->setEnabled(false);

		page_buttons.push_back(new TEXTBUTTON(L"<-", 0, 600, 50, 50, 50, 30)); // 버튼6
		page_buttons[6]->setAction(JumpPage);		
		page_buttons[6]->setVisible(false);			
		page_buttons[6]->setEnabled(false);			

		// ------------------5번 페이지에서 사용될 요소-----------------------
		// 공격자 로그인 페이지
		labels.push_back(new LABEL(170, 150, L"로그인", 30));		// 라벨15
		labels.push_back(new LABEL(80, 200, L"ID : ", 30));			// 라벨16
		labels.push_back(new LABEL(80, 250, L"PW : ", 30));			// 라벨17

		labels.push_back(new LABEL(50, 50, L"PLAYER 2", 20));		// 라벨18
		labels.push_back(new LABEL(180, 50, L"ROUND N", 20));		// 라벨19

		page_buttons.push_back(new TEXTBUTTON(L"로그인", 0, 360, 200, 100, 90, 30)); // 버튼7
		page_buttons[7]->setAction(NextPage);
		page_buttons[7]->setVisible(false);
		page_buttons[7]->setEnabled(false);


		// ------------------6번 페이지에서 사용될 요소-----------------------
		// 결과 페이지
		labels.push_back(new LABEL(410, 200, L"N", 50));			// 라벨20
		labels.push_back(new LABEL(480, 200, L":", 50));			// 라벨21
		labels.push_back(new LABEL(550, 200, L"N", 50));			// 라벨22
		labels.push_back(new LABEL(310, 250, L"플레이어1", 30));	// 라벨23
		labels.push_back(new LABEL(550, 250, L"플레이어2", 30));	// 라벨24
		labels.push_back(new LABEL(350, 300, L"승", 30));			// 라벨25
		labels.push_back(new LABEL(590, 300, L"패", 30));			// 라벨26
		

		page_buttons.push_back(new TEXTBUTTON(L"처음으로", 0, 410, 350, 150, 50, 20)); // 버튼8
		page_buttons[8]->setAction(NextPage);		
		page_buttons[8]->setVisible(false);
		page_buttons[8]->setEnabled(false);

		// ------------------7번 페이지에서 사용될 요소-----------------------
		// 도움말 페이지
		page_buttons.push_back(new TEXTBUTTON(L"뒤로가기", 0, 450, 170, 150, 50, 20)); // 버튼9
		page_buttons[9]->setAction(HelpPage);		// HelpPage -> 페이지 번호를 반환하는 함수임.
		page_buttons[9]->setVisible(false);
		page_buttons[9]->setEnabled(false);

		// 버튼과 라벨의 생성이 완료되면 페이지 변경 메시지를 보내 화면을 보여주기 시작한다.
		PostMessage(hWnd, WM_page_change, wParam, lParam);
		break;

	case WM_LBUTTONDOWN : 
	{
		// 버튼이 눌렸을 때 액션을 한다.
		int t = 0;
		for (const auto& i : page_buttons)
		{
			// 눌린 버튼을 추적하여 t 변수에 임시 저장한다.
			t = i->press_Action(hWnd, jump, Page, lParam);

			// t 변수의 값이 0이 아니라면 페이지 번호를 변경한다.
			// 페이지의 이동이 발생하였는지 확인하여 버튼의 상태를 설정한다.
			if (t != 0)
			{
				// Page 값을 변경한다.
				Page = t;

				// 페이지 변경 메시지를 호출한다.
				PostMessage(hWnd, WM_page_change, wParam, lParam);

				// 화면이 변경되었으므로 jump값을 0으로 변경
				jump = 0;
				break;
			}
		}
		// 화면 리다이랙션
		InvalidateRect(hWnd, NULL, true);
	}
		break;
	// 페이지 변경 메시지
	case WM_page_change:
	{
		// 모든 버튼을 비활성화
		for (const auto& i : page_buttons) {
			i->setEnabled(false);
			i->setVisible(false);
		}

		// 에딧 텍스트에 대해 비활성화 상태로 만든다.
		if (edit1 != NULL) {
			DestroyWindow(edit1);
			edit1 = NULL;
		}
		if (edit2 != NULL) {
			DestroyWindow(edit2);
			edit2 = NULL;
		}

		// Page값 에 따라 버튼의 출력 및 동작 여부를 설정함
		// 페이지가 변경될 때 가장 먼저 실행되는 코드들
		// 버튼의 활성화를 할 때 쓰인다.
		switch (Page)
		{
		case page_main:
			// 게임 초기화면
			for (int i = 0; i <= 1; i++)
			{
				page_buttons[i]->setEnabled(true);
				page_buttons[i]->setVisible(true);
			}
			break;

		case page_name:
			// 이름 입력 페이지
			edit1 = CreateWindow(L"EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 450, 200, 250, 40, hWnd, (HMENU)101, NULL, NULL);
			edit2 = CreateWindow(L"EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 450, 250, 250, 40, hWnd, (HMENU)102, NULL, NULL);
			for (int i = 2; i <= 2; i++)
			{
				page_buttons[i]->setEnabled(true);
				page_buttons[i]->setVisible(true);
			}
			break;

		case page_signin:
			// 계정 등록 페이지
			edit1 = CreateWindow(L"EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 450, 200, 200, 40, hWnd, (HMENU)101, NULL, NULL);
			edit2 = CreateWindow(L"EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 450, 250, 200, 40, hWnd, (HMENU)102, NULL, NULL);
			for (int i = 3; i <= 4; i++)
			{
				page_buttons[i]->setEnabled(true);
				page_buttons[i]->setVisible(true);
			}
			break;

		case page_login:
			// 로그인 페이지
			edit1 = CreateWindow(L"EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 390, 200, 200, 40, hWnd, (HMENU)101, NULL, NULL);
			edit2 = CreateWindow(L"EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 390, 250, 200, 40, hWnd, (HMENU)102, NULL, NULL);
			for (int i = 5; i <= 6; i++)
			{
				page_buttons[i]->setEnabled(true);
				page_buttons[i]->setVisible(true);
			}
			jump = page_signin;
			break;

		case page_attack_login:
			// 공격자 로그인 페이지
			edit1 = CreateWindow(L"EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 200, 200, 40, hWnd, (HMENU)101, NULL, NULL);
			edit2 = CreateWindow(L"EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 250, 200, 40, hWnd, (HMENU)102, NULL, NULL);
			for (int i = 7; i <= 7; i++)
			{
				page_buttons[i]->setEnabled(true);
				page_buttons[i]->setVisible(true);
			}
			break;

		case page_result:
			// 결과 페이지
			for (int i = 8; i <= 8; i++)
			{
				page_buttons[i]->setEnabled(true);
				page_buttons[i]->setVisible(true);
			}
			break;

		case page_help:
			// 도움말 페이지
			for (int i = 9; i <= 9; i++)
			{
				page_buttons[i]->setEnabled(true);
				page_buttons[i]->setVisible(true);
			}
			break;
		}
	}
		break;
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);

			// Page값 에 따라 화면을 출력한다.
			switch (Page)
			{
			case page_main:
				// 게임 초기화면
				
				for (int i = 0; i <= 1; i++)
					labels[i]->paint(hdc);

				for (int i = 0; i <= 1; i++)
					page_buttons[i]->paint(hdc);

				break;
			case page_name:	
				// 이름 입력 페이지
				// 마찬가지로 이 아래에 이름 입력 페이지를 구성해보겠음.
				
				for (int i = 2; i <= 4; i++)
					labels[i]->paint(hdc);

				for (int i = 2; i <= 2; i++)
					page_buttons[i]->paint(hdc);

				break;
			case page_signin:
				// 계정 등록 페이지
				
				for (int i = 5; i <= 9; i++)
					labels[i]->paint(hdc);

				for (int i = 3; i <= 4; i++)
					page_buttons[i]->paint(hdc);

				break;
			case page_login:
				// 로그인 페이지
				
				for (int i = 10; i <= 14; i++)
					labels[i]->paint(hdc);

				for (int i = 5; i <= 6; i++)
					page_buttons[i]->paint(hdc);

				break;
			case page_attack_login:
				// 공격자 로그인 페이지
				
				for (int i = 15; i <= 19; i++)
					labels[i]->paint(hdc);

				for (int i = 7; i <= 7; i++)
					page_buttons[i]->paint(hdc);

				break;
			case page_result:
				// 결과 페이지

				for (int i = 20; i <= 26; i++)
					labels[i]->paint(hdc);

				for (int i = 8; i <= 8; i++)
					page_buttons[i]->paint(hdc);

				break;
			case page_help:
				// 도움말 페이지
				for (int i = 9; i <= 9; i++)
					page_buttons[i]->paint(hdc);
				break;

			default:
				break;
			}
			EndPaint(hWnd, &ps);
		}
		break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}