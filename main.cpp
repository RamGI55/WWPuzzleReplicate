
#include <Windows.h>
#include <complex>
#include <sstream>

#include "GameLogic.h"

#pragma comment (lib, "gdiplus.lib")

using namespace Gdiplus;

const wchar_t gClassName[]= L"MyWindowsClass";


LRESULT CALLBACK WindowProc(
    HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
Puzzle::GameLogic gLogic;
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;

    Gdiplus::GdiplusStartup (&gdiplusToken, &gdiplusStartupInput, nullptr);


    HWND hWnd;
    WNDCLASSEX wc;


    // register the window class
    ZeroMemory (&wc, sizeof (WNDCLASSEX)); // intialise the memory as 0.

    // initialising the windows.
    wc.style = CS_HREDRAW | CS_VREDRAW; // redraw when the window is moved.
    wc.lpszClassName = reinterpret_cast<LPCSTR>(gClassName);
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpfnWndProc = WindowProc;
    wc.cbSize = sizeof (WNDCLASSEX);

    if (!RegisterClassEx (&wc))
    {
        // if windows has been failed to be loaded, send the error message
        MessageBox (
            nullptr, reinterpret_cast<LPCSTR>(L"Failed to register the window class.\n"),reinterpret_cast<LPCSTR>(L"Error"),
            MB_ICONEXCLAMATION | MB_OK
    );
        return 0;
    }

    RECT wr = { 0, 0, 1500, 850}; // set the size, and the position of the window.

    // Generate the windows
    hWnd = CreateWindowEx(
        WS_EX_COMPOSITED,
        reinterpret_cast<LPCSTR>(gClassName),
        reinterpret_cast<LPCSTR>(L"Wuthering Waves Puzzle"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        1920,
        1080,
        NULL,
        NULL,
        hInstance,
        NULL);

    if (hWnd == nullptr)
    {
        MessageBox (
            nullptr, reinterpret_cast<LPCSTR>(L"Failed to create the window class.\n"),reinterpret_cast<LPCSTR>(L"Error"),
            MB_ICONEXCLAMATION | MB_OK
            );
        return 0;
    }
    gLogic.Init(hWnd);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // message handles
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    gLogic.Release();
    Gdiplus::GdiplusShutdown(gdiplusToken);
    return 0;
}

// get the text with the font in the window.
void OnPaint (HWND hwnd)
{
    HDC hdc;
    PAINTSTRUCT ps;
    hdc = BeginPaint(hwnd, &ps);

    Gdiplus::Graphics graphics (hdc);
    gLogic.Draw(graphics);

    EndPaint(hwnd, &ps);
}


    // Write the Window procesure
    LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lparam)
    {
        switch (message)
        {

        case WM_LBUTTONDOWN:
            {
                break;
            }
        case WM_PAINT: // using window message to draw permernent regtangles.
            {
                OnPaint(hWnd);
                break;
            }
        case WM_LBUTTONUP:
            gLogic.OnClick(LOWORD(lparam), HIWORD(lparam));
            break;
        case WM_CLOSE:
            DestroyWindow(hWnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lparam);
        }
    return 0;
    }