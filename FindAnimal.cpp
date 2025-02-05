// FindAnimal.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "FindAnimal.h"
#include "Repository.h"
#include "MeRepository.h"
#include "AnimalFilter.h"

#include <string>
#include <windows.h>

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

Repository* rep = new MeRepository;


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。
    // Repository* rep = new MeRepository();

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_FINDANIMAL, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FINDANIMAL));

    MSG msg;

    // 主消息循环:
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
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FINDANIMAL));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_FINDANIMAL);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

void CreateChineseCheckBox(HWND hWnd, HINSTANCE hInstance, int i, const std::wstring& wKey) {
    // 创建字体
    HFONT hFont = CreateFont(
        20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS,
        CLEARTYPE_QUALITY, VARIABLE_PITCH, L"SimSun" // 中文字体
    );

    // Position
    int wid = (i % 3) * 150 + 30;                // 宽
    int lng = (i == 0 ? 0 : i / 3) * 50 + 30;    // 长

    // 创建复选框窗口
    HWND hCheckBox = CreateWindow(
        L"BUTTON",                                          // 控件类名
        wKey.c_str(),                                       // 复选框文本
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_CHECKBOX,   // 样式
        wid, lng, 100, 30,                                  // 位置和大小
        hWnd,                                               // 父窗口
        (HMENU)i,                                           // 控件ID
        hInstance,                                          // 当前实例句柄
        nullptr                                             // 空指针
    );

    // 设置字体
    SendMessage(hCheckBox, WM_SETFONT, (WPARAM)hFont, TRUE);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 将实例句柄存储在全局变量中

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 
        470,         // 宽
        330,         // 长
        nullptr, nullptr, hInstance, nullptr);

    if (!hWnd) return FALSE;

    int i = 0;
    for (auto& entry : rep->getMap()) {
        // 创建复选框控件
        std::wstring key = entry.first;
        // 将 std::string 转换为 std::wstring
        std::wstring wKey(key.begin(), key.end());
        
        CreateChineseCheckBox(hWnd, hInstance, i, wKey);

        i++;
    }

    // 创建按钮控件
    HWND hButton = CreateWindow(
        L"BUTTON",
        L"展示已选",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        150, 55 * (i + 1) / 3, 150, 30,
        hWnd,
        (HMENU)100,
        hInstance,
        nullptr
    );

    /*
    std::string k = std::to_string(rep.getMap().size());
    std::wstring wKey(k.begin(), k.end());
    MessageBox(hWnd, wKey.c_str(), L"Selection", MB_OK);
    */

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}



//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 如果按钮被点击
        if (wmId == 100)  // 这是按钮ID
        {
            std::vector<std::wstring> targets;
            std::wstring message = L"";
            int i = 0;
            for (auto& entry : rep->getMap()) {
                if (SendMessage(GetDlgItem(hWnd, i), BM_GETCHECK, 0, 0) == BST_CHECKED) 
                    targets.push_back(entry.first);

                i++;
            }
            auto result = Filter(targets, rep);

            i = 0;
            for (auto& val : result) {
                message += (L"  " + std::to_wstring(++i) + L"、");
                message += val;
                if (i % 4 == 0) message += L"\n";
            }

            message += (message.size() == 0 ? L"当前无可用" : L"");
            // 显示选择的动物
            MessageBox(hWnd, message.c_str(), L"你可以使用的动物如下", MB_OK);
        }
        // 检查是否是那些按钮
        bool over = false;
        int i = 0;
        for (auto& entry : rep->getMap()) {
            if (i == wmId) {
                HWND hCheckBox = GetDlgItem(hWnd, wmId);
                SendMessage(hCheckBox, BM_SETCHECK,
                SendMessage(hCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED ? BST_UNCHECKED : BST_CHECKED,
                0);
                over = true;
                break;
            }
            i++;
        }
        if (over) break;

        // 分析菜单选择:
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

    // 如果您需要改变复选框的勾选状态（例如，程序初始化时勾选某些框）
    case WM_INITDIALOG:
        // 设置复选框状态（例如，勾选“Cat”和“Bird”）
        SendMessage(GetDlgItem(hWnd, 1), BM_SETCHECK, BST_CHECKED, 0);

        SendMessage(GetDlgItem(hWnd, 3), BM_SETCHECK, BST_CHECKED, 0);
        break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 在此处添加使用 hdc 的任何绘图代码...
        EndPaint(hWnd, &ps);
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

// “关于”框的消息处理程序。
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
