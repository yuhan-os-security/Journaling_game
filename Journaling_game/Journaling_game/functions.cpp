#include"Journaling_game.h"


int NextPage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return ((int)wParam + 1) % (max_page + 1);
}

int JumpPage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return message;
}

int HelpPage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static bool help_menu = false;
	static int Page = -1;

	// 도움말 보기를 누른 경우
	if (help_menu)
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


