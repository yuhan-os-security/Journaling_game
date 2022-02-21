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
		page_buttons.push_back(new TEXTBUTTON(L"게임시작", 0, 450, 300, 150, 50, 20));	// 버튼0
		page_buttons[0]->setAction(NextPage);		// 0 
													// setaction=액션리스너라고 보면 됨.
		// 도움말 버튼 등록
		page_buttons.push_back(new TEXTBUTTON(L"도움말", 0, 450, 370, 150, 50, 20));	// 버튼1
		page_buttons[1]->setAction(HelpPage);		
		
		// 1번 버튼의 동작을 중지 시킨다.
		//page_buttons[1]->setEnabled(false);
		// 1번 버튼을 보이게 설정한다.
		page_buttons[1]->setVisible(true);


		// ------------------2번 페이지에서 사용될 요소----------------------
		// 이름 입력 페이지
		labels.push_back(new LABEL(280, 200, L"PLAYER 1", 30));		// 라벨2
		labels.push_back(new LABEL(280, 270, L"PLAYER 2", 30));		// 라벨3

		page_buttons.push_back(new TEXTBUTTON(L"시작", 0, 450, 370, 150, 50, 20)); // 버튼2
		page_buttons[2]->setAction(NextPage);		// NextPage -> 페이지 번호를 반환하는 함수임.
		page_buttons[2]->setVisible(true);			// 2번 버튼을 보이게 설정한다.

		edit1 = CreateWindow(L"EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 450, 200, 250, 40, hWnd, (HMENU)101, NULL, NULL);
		edit2 = CreateWindow(L"EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 450, 270, 250, 40, hWnd, (HMENU)102, NULL, NULL);
		// 에딧은 몇 개가 필요하게 될 지 모르겠어서 배열 없이 따로 만들어봤다. 솔직히 인수 하나하나의 의미는 잘 모르겠고
		// 시간이 너무 늦어서 급한대로 인터넷에서 에딧 생성 코드를 찾아서 이 코드에 맞게 고쳐봤다
		// 어느 정도는 알겠는데.. 빠삭하게 알려면 맘먹고 찾아봐야 할 듯. (에딧=텍스트 상자)


		// ------------------3번 페이지에서 사용될 요소-----------------------
		// 계정 등록 페이지
		page_buttons.push_back(new TEXTBUTTON(L"등록", 0, 450, 370, 150, 50, 20)); // 버튼3
		page_buttons[3]->setAction(NextPage);		// NextPage -> 페이지 번호를 반환하는 함수임.
		page_buttons[3]->setVisible(true);			// 3번 버튼을 보이게 설정한다.


		// ------------------4번 페이지에서 사용될 요소-----------------------
		// 로그인 페이지
		labels.push_back(new LABEL(280, 200, L"사용자 ID", 30));		// 라벨4
		labels.push_back(new LABEL(280, 270, L"사용자 PW", 30));		// 라벨5
		

		page_buttons.push_back(new TEXTBUTTON(L"사용자 로그인", 0, 450, 370, 150, 50, 20)); // 버튼4
		page_buttons[4]->setAction(NextPage);		// NextPage -> 페이지 번호를 반환하는 함수임.
		page_buttons[4]->setVisible(true);			// 4번 버튼을 보이게 설정한다.


		// ------------------5번 페이지에서 사용될 요소-----------------------
		// 공격자 로그인 페이지
		labels.push_back(new LABEL(280, 200, L"공격자 ID", 30));		// 라벨6
		labels.push_back(new LABEL(280, 270, L"공격자 PW", 30));		// 라벨7

		page_buttons.push_back(new TEXTBUTTON(L"공격자 로그인", 0, 450, 370, 150, 50, 20)); // 버튼5
		page_buttons[5]->setAction(NextPage);		// NextPage -> 페이지 번호를 반환하는 함수임.
		page_buttons[5]->setVisible(true);			// 5번 버튼을 보이게 설정한다.


		// ------------------6번 페이지에서 사용될 요소-----------------------
		// 결과 페이지
		

		// ------------------7번 페이지에서 사용될 요소-----------------------
		// 도움말 페이지
		page_buttons.push_back(new TEXTBUTTON(L"뒤로가기", 0, 450, 170, 150, 50, 20)); // 버튼7
		page_buttons[6]->setAction(HelpPage);		// HelpPage -> 페이지 번호를 반환하는 함수임.
		page_buttons[6]->setVisible(true);	
		page_buttons[6]->setEnabled(false);		// 7번 버튼을 보이게 설정한다.
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

				

				// 모든 버튼을 비활성화 하는 코드를 삽입
				for (const auto& i : page_buttons) {
					i->setEnabled(false);
					i->setVisible(false);
				}

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
					page_buttons[0]->setEnabled(true);		// 게임시작 버튼 활성화
					page_buttons[0]->setVisible(true);		// 게임시작 버튼 활성화
					page_buttons[1]->setEnabled(true);		// 도움말 버튼 활성화
					page_buttons[1]->setVisible(true);		// 도움말 버튼 활성화
					break;

				case page_name:
					// 이름 입력 페이지
					
					break;

				case page_signin:
					// 계정 등록 페이지
					page_buttons[2]->setEnabled(true);		// 시작 버튼 활성화
					page_buttons[2]->setVisible(true);		// 시작 버튼 활성화
					break;

				case page_login:
					// 로그인 페이지
					page_buttons[3]->setEnabled(true);		// 등록 버튼 활성화
					page_buttons[3]->setVisible(true);		// 등록 버튼 활성화
					break;

				case page_attack_login:
					// 공격자 로그인 페이지
					page_buttons[4]->setEnabled(true);		// 사용자 로그인 버튼 활성화
					page_buttons[4]->setVisible(true);		// 사용자 로그인 버튼 활성화
					break;

				case page_result:
					// 결과 페이지
					page_buttons[5]->setEnabled(true);		// 공격자 로그인 버튼 활성화
					page_buttons[5]->setVisible(true);		// 공격자 로그인 버튼 활성화
					break;

				case page_help:
					// 도움말 페이지
					page_buttons[6]->setEnabled(true);
					page_buttons[6]->setVisible(true);		
					break;
				}
				break;
			}
		}
		// jump를 0으로 초기화 한 후 화면 리다이랙션
		jump = 0;
		InvalidateRect(hWnd, NULL, true);
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
				//아래는 게임 초기화면을 구성한 코드로 보임.
				labels[0]->paint(hdc);
				labels[1]->paint(hdc);
				page_buttons[0]->paint(hdc);
				page_buttons[1]->paint(hdc);
				break;
			case page_name:	
				// 이름 입력 페이지
				// 마찬가지로 이 아래에 이름 입력 페이지를 구성해보겠음.
				labels[2]->paint(hdc);
				labels[3]->paint(hdc);
				page_buttons[2]->paint(hdc);	// 아까 구성한 요소들을 차례대로 페이지에 삽입해 줌.
				break;
			case page_signin:
				// 계정 등록 페이지
				//DestroyWindow(edit1);
				//DestroyWindow(edit2);
				MessageBox(hWnd, _T("계정 등록페이지"), _T("미완성"), MB_OK);
				page_buttons[3]->paint(hdc);
				break;
			case page_login:
				// 로그인 페이지
				labels[4]->paint(hdc);
				labels[5]->paint(hdc);
				MessageBox(hWnd, _T("로그인페이지"), _T("미완성"), MB_OK);
				page_buttons[4]->paint(hdc);
				break;
			case page_attack_login:
				// 공격자 로그인 페이지
				labels[6]->paint(hdc);
				labels[7]->paint(hdc);
				MessageBox(hWnd, _T("공격자 로그인페이지"), _T("미완성"), MB_OK);
				page_buttons[5]->paint(hdc);
				break;
			case page_result:
				// 결과 페이지
				MessageBox(hWnd, _T("결과페이지"), _T("미완성"), MB_OK);
				break;
			case page_help:
				// 도움말 페이지
				MessageBox(hWnd, _T("도움말페이지"), _T("미완성"), MB_OK);
				page_buttons[6]->paint(hdc);
				break;
			default:
				break;
			}

			if (Page != 7)
			{
				page_buttons[6]->setEnabled(false);
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