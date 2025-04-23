
#ifndef UNICODE
#define UNICODE
#endif

#ifndef _UNICODE
#define _UNICODE
#endif

#include <Windows.h>
#include <complex>
#include <sstream>

#include "GameLogic.h"

#pragma comment (lib, "gdiplus.lib")

using namespace Gdiplus;

const wchar_t gClassName[]= L"MyWindowsClass";


LRESULT CALLBACK WindowProc(
    HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void OnPaint(HWND hwnd);

Puzzle::GameLogic gLogic;

void DebugMessage(const wchar_t* message) {
    OutputDebugStringW(message);
    OutputDebugStringW(L"\n");

}

void HandleError(const wchar_t* context, DWORD errorCode = GetLastError()) {
    wchar_t errorMsg[512];
    swprintf_s(errorMsg, 512, L"%s failed. Error code: %d", context, errorCode);
    MessageBoxW(NULL, errorMsg, L"Error", MB_ICONERROR | MB_OK);
    DebugMessage(errorMsg);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;

    Gdiplus::Status gdiStatus = Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
    if (gdiStatus != Gdiplus::Ok) {
        MessageBox(NULL, L"Failed to Initialise GDI+", L"Error", MB_OK);
        return 1;
    }

    DebugMessage (L"GDI+ initialised");
    HWND hWnd;
    WNDCLASSEX wc;


    // register the window class
    ZeroMemory (&wc, sizeof (WNDCLASSEX)); // intialise the memory as 0.

    // initialising the windows.
    wc.style = CS_HREDRAW | CS_VREDRAW; // redraw when the window is moved.
    wc.lpszClassName = gClassName;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpfnWndProc = WindowProc;
    wc.cbSize = sizeof (WNDCLASSEX);

    if (!RegisterClassEx (&wc))
    {
        // if windows has been failed to be loaded, send the error message
        MessageBox (
            nullptr, L"Failed to register the window class.\n",L"Error",
            MB_ICONEXCLAMATION | MB_OK
    );
        return 0;
    }

    RECT wr = { 0, 0, 1500, 850}; // set the size, and the position of the window.

    // Generate the windows
    hWnd = CreateWindowEx(
        WS_EX_COMPOSITED,
        gClassName,
        L"Wuthering Waves Puzzle",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        1250,
        950,
        NULL,
        NULL,
        hInstance,
        NULL);

    if (hWnd == nullptr)
    {
        DWORD error = GetLastError();
        wchar_t errorW[256];
        swprintf_s(errorW, 256, L"Failed to create window class.\nError: %ls", errorW);
        MessageBox (
            nullptr, L"Failed to create the window class.\n",L"Error",
            MB_ICONEXCLAMATION | MB_OK
            );
        Gdiplus::GdiplusShutdown(gdiplusToken);
        return 0;
    }
    DebugMessage(L"Window Created");

    gLogic.Init(hWnd);
    DebugMessage(L"Initialized");

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    DebugMessage(L"Window Updated");

    // message handles
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    gLogic.Release();
    Gdiplus::GdiplusShutdown(gdiplusToken);
    return (int)msg.wParam;
}

// get the text with the font in the window.
void OnPaint (HWND hwnd)
{
    HDC hdc;
    PAINTSTRUCT ps;
    hdc = BeginPaint(hwnd, &ps);

    Gdiplus::Graphics graphics (hdc);
    graphics.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
    graphics.Clear(Gdiplus::Color(255, 240, 240, 240));
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
