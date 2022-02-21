#include"Journaling_game.h"


int NextPage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	WCHAR str[20];
	int x;
	x = (int)wParam;

	// 확인 메시지 출력
	//wsprintf(str,L"NextPage : %d", wParam);
	//MessageBox(hWnd, str, L"실행", MB_OK);
	
	// 다음 페이지 번호를 계산한다.
	// 0번은 페이지 변동 없음이므로 다음과 같은 형태의 연산이 올바른 연산이다.
	return (x % (max_page) + 1);
}

int JumpPage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return (int)message;
}

int HelpPage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static bool help_menu = false;
	static int Page = -1;

	// 도움말 보기를 누른 경우
	if (!help_menu)
	{
		// 플래그를 true로 만든 후 
		help_menu = true;
		// 페이지를 저장한다.
		Page = wParam;
		// 페이지 번호를 반환한다.
		return page_help;
	}
	else
	{
		// 플래그를 false로 만든 후
		help_menu = false;
		// wParam에 페이지 번호를 저장한다.
		wParam = Page;
		// 페이지 변수를 초기화 한다.
		Page = -1;
		// 이전 페이지를 반환한다.
		return wParam;
	}
	
}

int resetPage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return (int)wParam;
}


