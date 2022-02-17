#pragma once

#include "resource.h"
#include <windows.h>

#define page_main	1
#define page_name	2
#define page_signin	3
#define page_login	4
#define page_attack_login	5
#define page_result	6
#define page_help	7
#define max_page 6


/*!
* @brief		다음페이지 번호를 반환하는 함수
* @details		현재 페이지 번호를 받아와 다음 페이지 번호를 반환한다.
* @param		HWND	hWnd		사용하지 않음
* @param		UINT	message		사용하지 않음
* @param		WPARAM	wParam		현재 페이지 번호
* @param		LPARAM	lParam		사용하지 않음
*/
int NextPage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

/*!
* @brief		해당 페이지 번호를 반환하는 함수
* @details		이동할 페이지 번호를 받아와 반환한다.
* @param		HWND	hWnd		사용하지 않음
* @param		UINT	message		사용하지 않음
* @param		WPARAM	wParam		이동할 페이지 번호
* @param		LPARAM	lParam		사용하지 않음
*/
int JumpPage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

/*!
* @brief		도움말 페이지를 반환하는 함수
* @details		도움말 페이지 번호를 반환한다.
* @details		도움말 버튼을 다시 누른 경우 기존 페이지로 이동한다.
* @param		HWND	hWnd		사용하지 않음
* @param		UINT	message		사용하지 않음
* @param		WPARAM	wParam		사용하지 않음
* @param		LPARAM	lParam		사용하지 않음
*/
int HelpPage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);