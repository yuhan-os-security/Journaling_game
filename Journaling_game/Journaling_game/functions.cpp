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

	// ���� ���⸦ ���� ���
	if (help_menu)
	{
		// �÷��׸� true�� ���� �� 
		help_menu = true;
		// �������� �����Ѵ�.
		Page = wParam;
		// ������ ��ȣ�� ��ȯ�Ѵ�.
		return page_help;
	}
	else
	{
		// �÷��׸� false�� ���� ��
		help_menu = false;
		// wParam�� ������ ��ȣ�� �����Ѵ�.
		wParam = Page;
		// ������ ������ �ʱ�ȭ �Ѵ�.
		Page = -1;
		// ���� �������� ��ȯ�Ѵ�.
		return wParam;
	}
	
}


