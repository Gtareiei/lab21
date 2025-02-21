#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define ID_EDIT1 101
#define ID_EDIT2 102
#define ID_BUTTON_ADD 103
#define ID_BUTTON_SUB 104
#define ID_BUTTON_MUL 105
#define ID_BUTTON_DIV 106

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static HWND hEdit1, hEdit2, hAdd, hSub, hMul, hDiv;
    char num1[20], num2[20];
    double val1, val2, result;
    char buffer[50];

    switch (msg) {
        case WM_CREATE:
            CreateWindow("STATIC", "Please input two numbers", WS_VISIBLE | WS_CHILD,
                30, 10, 200, 20, hwnd, NULL, NULL, NULL);

            hEdit1 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER,
                30, 40, 180, 20, hwnd, (HMENU)ID_EDIT1, NULL, NULL);
            hEdit2 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER,
                30, 70, 180, 20, hwnd, (HMENU)ID_EDIT2, NULL, NULL);

            hAdd = CreateWindow("BUTTON", "+", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                30, 110, 40, 40, hwnd, (HMENU)ID_BUTTON_ADD, NULL, NULL);
            hSub = CreateWindow("BUTTON", "-", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                80, 110, 40, 40, hwnd, (HMENU)ID_BUTTON_SUB, NULL, NULL);
            hMul = CreateWindow("BUTTON", "*", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                130, 110, 40, 40, hwnd, (HMENU)ID_BUTTON_MUL, NULL, NULL);
            hDiv = CreateWindow("BUTTON", "/", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                180, 110, 40, 40, hwnd, (HMENU)ID_BUTTON_DIV, NULL, NULL);
            break;

        case WM_COMMAND:
            if (LOWORD(wParam) >= ID_BUTTON_ADD && LOWORD(wParam) <= ID_BUTTON_DIV) {
                GetWindowText(hEdit1, num1, 20);
                GetWindowText(hEdit2, num2, 20);

                // ตรวจสอบว่าสามารถแปลงเป็นตัวเลขได้
                if (sscanf(num1, "%lf", &val1) != 1 || sscanf(num2, "%lf", &val2) != 1) {
                    MessageBox(hwnd, "Invalid input! Please enter valid numbers.", "Error", MB_OK | MB_ICONERROR);
                    break;
                }

                switch (LOWORD(wParam)) {
                    case ID_BUTTON_ADD:
                        result = val1 + val2;
                        sprintf(buffer, "Result: %.6f", result);
                        MessageBox(hwnd, buffer, "Result", MB_OK);
                        break;
                    case ID_BUTTON_SUB:
                        result = val1 - val2;
                        sprintf(buffer, "Result: %.6f", result);
                        MessageBox(hwnd, buffer, "Result", MB_OK);
                        break;
                    case ID_BUTTON_MUL:
                        result = val1 * val2;
                        sprintf(buffer, "Result: %.6f", result);
                        MessageBox(hwnd, buffer, "Result", MB_OK);
                        break;
                    case ID_BUTTON_DIV:
                        if (val2 != 0) {
                            result = val1 / val2;
                            sprintf(buffer, "Result: %.6f", result);
                        } else {
                            sprintf(buffer, "Cannot divide by zero!");
                        }
                        MessageBox(hwnd, buffer, "Result", MB_OK);
                        break;
                }
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = {0};
    HWND hwnd;
    MSG msg;

    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hbrBackground = CreateSolidBrush(RGB(139, 0, 0)); 
    wc.lpszClassName = "MyCalculator";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    if (!RegisterClass(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindow("MyCalculator", "My Calculator", WS_OVERLAPPED | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, 250, 200,
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}
