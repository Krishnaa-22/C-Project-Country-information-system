#include <windows.h>
#include <string>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void AddControls(HWND);
void ShowInfoOptions();
void ShowSelectedInfo(int infoType);
void DrawFlag(HDC hdc, RECT rect, int countryIndex);
#define BTN_USA 1
#define BTN_INDIA 2
#define BTN_AUSTRALIA 3
#define BTN_UAE 4
#define BTN_RUSSIA 5
#define BTN_NAME 10
#define BTN_CAPITAL 11
#define BTN_CURRENCY 12
#define BTN_LANGUAGE 13
#define BTN_FLAG 14
#define BTN_POPULATION 15
#define BTN_ALL 16
HWND hButtonUSA, hButtonIndia, hButtonAustralia, hButtonUAE, hButtonRussia;
HWND hButtonName, hButtonCapital, hButtonCurrency, hButtonLanguage, hButtonFlag, hButtonPopulation, hButtonAll;
HWND hLabelInstruction, hLabelResult, hFlagArea;
int selectedCountry = -1;
bool showingOptions = false;
struct Country {
    wchar_t name[100];
    wchar_t currency[100];
    wchar_t languages[150];
    wchar_t capital[50];
    wchar_t population[50];
    wchar_t area[50];
};
Country countries[5] = {
    {L"United States of America", L"US Dollar (USD)", L"English", L"Washington, D.C.",L"331 million", L"9.8 million sqkm"},
    {L"India", L"Indian Rupee (INR)", L"Hindi, English, and 21 other languages", L"New Delhi",L"1.4 billion", L"3.3 million sqkm"},
    {L"Australia", L"Australian Dollar (AUD)", L"English", L"Canberra",L"26 million", L"7.7 million sqkm"},
    {L"United Arab Emirates", L"UAE Dirham (AED)", L"Arabic (English widely spoken)", L"Abu Dhabi",L"10 million", L"83,600 sqkm"},
    {L"Russia", L"Russian Ruble (RUB)", L"Russian", L"Moscow",L"144 million", L"17.1 million sqkm"}
};
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
    WNDCLASSW wc = {0};
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"CountryInfoClass";
    wc.lpfnWndProc = WndProc;
    if (!RegisterClassW(&wc))
        return -1;
    CreateWindowW(L"CountryInfoClass", L"Country Information System",
                  WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                  100, 100, 700, 600,
                  NULL, NULL, hInst, NULL);
    MSG msg = {0};
    while(GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch(msg) {
        case WM_CREATE:
            AddControls(hwnd);
            break;
        case WM_COMMAND:
            switch(LOWORD(wp)) {
                case BTN_USA:
                    selectedCountry = 0;
                    ShowInfoOptions();
                    break;
                case BTN_INDIA:
                    selectedCountry = 1;
                    ShowInfoOptions();
                    break;
                case BTN_AUSTRALIA:
                    selectedCountry = 2;
                    ShowInfoOptions();
                    break;
                case BTN_UAE:
                    selectedCountry = 3;
                    ShowInfoOptions();
                    break;
                case BTN_RUSSIA:
                    selectedCountry = 4;
                    ShowInfoOptions();
                    break;
                case BTN_NAME:
                    ShowSelectedInfo(0);
                    break;
                case BTN_CAPITAL:
                    ShowSelectedInfo(1);
                    break;
                case BTN_CURRENCY:
                    ShowSelectedInfo(2);
                    break;
                case BTN_LANGUAGE:
                    ShowSelectedInfo(3);
                    break;
                case BTN_FLAG:
                    ShowSelectedInfo(4);
                    break;
                case BTN_POPULATION:
                    ShowSelectedInfo(5);
                    break;
                case BTN_ALL:
                    ShowSelectedInfo(6);
                    break;
            }
            break;
        case WM_PAINT:
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hwnd, &ps);
                if (selectedCountry >= 0 && IsWindowVisible(hFlagArea)) {
                    RECT flagRect;
                    GetClientRect(hFlagArea, &flagRect);
                    MapWindowPoints(hFlagArea, hwnd, (POINT*)&flagRect, 2);
                    DrawFlag(hdc, flagRect, selectedCountry);
                }
                EndPaint(hwnd, &ps);
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProcW(hwnd, msg, wp, lp);
    }
    return 0;
}
void AddControls(HWND hwnd) {
    hLabelInstruction = CreateWindowW(L"Static", L"STEP 1: Select a Country",
                  WS_VISIBLE | WS_CHILD | SS_CENTER,
                  200, 20, 300, 30,
                  hwnd, NULL, NULL, NULL);
    hButtonUSA = CreateWindowW(L"Button", L"USA",
                              WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                              50, 60, 120, 40,
                              hwnd, (HMENU)BTN_USA, NULL, NULL);
    hButtonIndia = CreateWindowW(L"Button", L"India",
                                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                                190, 60, 120, 40,
                                hwnd, (HMENU)BTN_INDIA, NULL, NULL);
    hButtonAustralia = CreateWindowW(L"Button", L"Australia",
                                    WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                                    330, 60, 120, 40,
                                    hwnd, (HMENU)BTN_AUSTRALIA, NULL, NULL);
    hButtonUAE = CreateWindowW(L"Button", L"UAE",
                              WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                              470, 60, 120, 40,
                              hwnd, (HMENU)BTN_UAE, NULL, NULL);
    hButtonRussia = CreateWindowW(L"Button", L"Russia",
                                 WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                                 260, 110, 120, 40,
                                 hwnd, (HMENU)BTN_RUSSIA, NULL, NULL);
    CreateWindowW(L"Static", L"STEP 2: What information do you want to see?",
                  WS_CHILD | SS_CENTER,
                  150, 170, 400, 30,
                  hwnd, (HMENU)100, NULL, NULL);
    hButtonName = CreateWindowW(L"Button", L"Country Name",
                               WS_CHILD | BS_PUSHBUTTON,
                               50, 210, 150, 35,
                               hwnd, (HMENU)BTN_NAME, NULL, NULL);
    hButtonCapital = CreateWindowW(L"Button", L"Capital City",
                                  WS_CHILD | BS_PUSHBUTTON,
                                  220, 210, 150, 35,
                                  hwnd, (HMENU)BTN_CAPITAL, NULL, NULL);

    hButtonCurrency = CreateWindowW(L"Button", L"Currency",
                                   WS_CHILD | BS_PUSHBUTTON,
                                   390, 210, 150, 35,
                                   hwnd, (HMENU)BTN_CURRENCY, NULL, NULL);
    hButtonLanguage = CreateWindowW(L"Button", L"Languages",
                                   WS_CHILD | BS_PUSHBUTTON,
                                   50, 260, 150, 35,
                                   hwnd, (HMENU)BTN_LANGUAGE, NULL, NULL);
    hButtonFlag = CreateWindowW(L"Button", L"Flag",
                               WS_CHILD | BS_PUSHBUTTON,
                               220, 260, 150, 35,
                               hwnd, (HMENU)BTN_FLAG, NULL, NULL);
    hButtonPopulation = CreateWindowW(L"Button", L"Population & Area",
                                     WS_CHILD | BS_PUSHBUTTON,
                                     390, 260, 150, 35,
                                     hwnd, (HMENU)BTN_POPULATION, NULL, NULL);
    hButtonAll = CreateWindowW(L"Button", L"Show All Information",
                              WS_CHILD | BS_PUSHBUTTON,
                              220, 310, 150, 35,
                              hwnd, (HMENU)BTN_ALL, NULL, NULL);
    CreateWindowW(L"Static", L"Information Display:",
                  WS_CHILD,
                  50, 370, 200, 25,
                  hwnd, (HMENU)101, NULL, NULL);
    hLabelResult = CreateWindowW(L"Static", L"",
                                WS_CHILD | SS_LEFT,
                                50, 400, 600, 120,
                                hwnd, NULL, NULL, NULL);
    hFlagArea = CreateWindowW(L"Static", L"",
                             WS_CHILD | SS_BLACKFRAME,
                             50, 400, 300, 80,
                             hwnd, NULL, NULL, NULL);
}
void ShowInfoOptions() {
    SetWindowTextW(hLabelInstruction, L"STEP 2: What information do you want to see?");
    ShowWindow(GetDlgItem(GetParent(hButtonName), 100), SW_SHOW);
    ShowWindow(hButtonName, SW_SHOW);
    ShowWindow(hButtonCapital, SW_SHOW);
    ShowWindow(hButtonCurrency, SW_SHOW);
    ShowWindow(hButtonLanguage, SW_SHOW);
    ShowWindow(hButtonFlag, SW_SHOW);
    ShowWindow(hButtonPopulation, SW_SHOW);
    ShowWindow(hButtonAll, SW_SHOW);
    ShowWindow(GetDlgItem(GetParent(hLabelResult), 101), SW_HIDE);
    ShowWindow(hLabelResult, SW_HIDE);
    ShowWindow(hFlagArea, SW_HIDE);
    SetWindowTextW(hLabelResult, L"");
    showingOptions = true;
}
void ShowSelectedInfo(int infoType) {
    if (selectedCountry < 0) return;
    wchar_t result[500] = L"";
    bool showFlag = false;
    switch(infoType) {
        case 0:
            {
                wcscat(result, L"Country Name:\n");
                wcscat(result, countries[selectedCountry].name);
            }
            break;
        case 1:
            {
                wcscat(result, L"Capital City:\n");
                wcscat(result, countries[selectedCountry].capital);
            }
            break;
        case 2:
            {
                wcscat(result, L"Currency:\n");
                wcscat(result, countries[selectedCountry].currency);
            }
            break;
        case 3:
            {
                wcscat(result, L"Languages Spoken:\n");
                wcscat(result, countries[selectedCountry].languages);
            }
            break;
        case 4:
            {
                wcscat(result, L"Flag of ");
                wcscat(result, countries[selectedCountry].name);
                wcscat(result, L":");
                showFlag = true;
            }
            break;
        case 5:
            {
                wcscat(result, L"Population: ");
                wcscat(result, countries[selectedCountry].population);
                wcscat(result, L"\nArea: ");
                wcscat(result, countries[selectedCountry].area);
            }
            break;
        case 6:
            {
                wcscat(result, L"Country: ");
                wcscat(result, countries[selectedCountry].name);
                wcscat(result, L"\n\nCapital: ");
                wcscat(result, countries[selectedCountry].capital);
                wcscat(result, L"\n\nCurrency: ");
                wcscat(result, countries[selectedCountry].currency);
                wcscat(result, L"\n\nLanguages: ");
                wcscat(result, countries[selectedCountry].languages);
                wcscat(result, L"\n\nPopulation: ");
                wcscat(result, countries[selectedCountry].population);
                wcscat(result, L"\nArea: ");
                wcscat(result, countries[selectedCountry].area);
                showFlag = true;
            }
            break;
    }
    ShowWindow(GetDlgItem(GetParent(hLabelResult), 101), SW_SHOW);
    ShowWindow(hLabelResult, SW_SHOW);
    SetWindowTextW(hLabelResult, result);
    if (showFlag) {
        ShowWindow(hFlagArea, SW_SHOW);
        InvalidateRect(hFlagArea, NULL, TRUE);
        InvalidateRect(GetParent(hFlagArea), NULL, TRUE);
    } else {
        ShowWindow(hFlagArea, SW_HIDE);
    }
}
void DrawFlag(HDC hdc, RECT rect, int countryIndex) {
    HBRUSH brush;
    RECT stripe;
    int i, cx, cy;
    switch(countryIndex) {
        case 0:
            {
                for(i = 0; i < 6; i++) {
                    stripe = rect;
                    stripe.top = rect.top + (i * (rect.bottom - rect.top) / 6);
                    stripe.bottom = stripe.top + (rect.bottom - rect.top) / 6;
                    brush = CreateSolidBrush(i % 2 == 0 ? RGB(178, 34, 52) : RGB(255, 255, 255));
                    FillRect(hdc, &stripe, brush);
                    DeleteObject(brush);
                }
                stripe = rect;
                stripe.right = rect.left + (rect.right - rect.left) / 3;
                stripe.bottom = rect.top + (rect.bottom - rect.top) / 2;
                brush = CreateSolidBrush(RGB(60, 59, 110));
                FillRect(hdc, &stripe, brush);
                DeleteObject(brush);
            }
            break;
        case 1:
            {
                stripe = rect;
                stripe.bottom = rect.top + (rect.bottom - rect.top) / 3;
                brush = CreateSolidBrush(RGB(255, 153, 51));
                FillRect(hdc, &stripe, brush);
                DeleteObject(brush);
                stripe.top = stripe.bottom;
                stripe.bottom = stripe.top + (rect.bottom - rect.top) / 3;
                brush = CreateSolidBrush(RGB(255, 255, 255));
                FillRect(hdc, &stripe, brush);
                DeleteObject(brush);
                stripe.top = stripe.bottom;
                stripe.bottom = rect.bottom;
                brush = CreateSolidBrush(RGB(19, 136, 8));
                FillRect(hdc, &stripe, brush);
                DeleteObject(brush);
                brush = CreateSolidBrush(RGB(0, 0, 128));
                cx = (rect.left + rect.right) / 2;
                cy = (rect.top + rect.bottom) / 2;
                Ellipse(hdc, cx - 15, cy - 15, cx + 15, cy + 15);
                DeleteObject(brush);
            }
            break;
        case 2:
            {
                brush = CreateSolidBrush(RGB(0, 0, 139));
                FillRect(hdc, &rect, brush);
                DeleteObject(brush);
                brush = CreateSolidBrush(RGB(255, 255, 255));
                for(i = 0; i < 5; i++) {
                    RECT star = {rect.left + 30 + i*50, rect.top + 30,
                                rect.left + 40 + i*50, rect.top + 40};
                    Ellipse(hdc, star.left, star.top, star.right, star.bottom);
                }
                DeleteObject(brush);
            }
            break;
        case 3:
            {
                stripe = rect;
                stripe.bottom = rect.top + (rect.bottom - rect.top) / 3;
                brush = CreateSolidBrush(RGB(0, 122, 61));
                FillRect(hdc, &stripe, brush);
                DeleteObject(brush);
                stripe.top = stripe.bottom;
                stripe.bottom = stripe.top + (rect.bottom - rect.top) / 3;
                brush = CreateSolidBrush(RGB(255, 255, 255));
                FillRect(hdc, &stripe, brush);
                DeleteObject(brush);
                stripe.top = stripe.bottom;
                stripe.bottom = rect.bottom;
                brush = CreateSolidBrush(RGB(0, 0, 0));
                FillRect(hdc, &stripe, brush);
                DeleteObject(brush);
                stripe = rect;
                stripe.right = rect.left + (rect.right - rect.left) / 4;
                brush = CreateSolidBrush(RGB(206, 17, 38));
                FillRect(hdc, &stripe, brush);
                DeleteObject(brush);
            }
            break;
        case 4:
            {
                stripe = rect;
                stripe.bottom = rect.top + (rect.bottom - rect.top) / 3;
                brush = CreateSolidBrush(RGB(255, 255, 255));
                FillRect(hdc, &stripe, brush);
                DeleteObject(brush);
                stripe.top = stripe.bottom;
                stripe.bottom = stripe.top + (rect.bottom - rect.top) / 3;
                brush = CreateSolidBrush(RGB(0, 57, 166));
                FillRect(hdc, &stripe, brush);
                DeleteObject(brush);
                stripe.top = stripe.bottom;
                stripe.bottom = rect.bottom;
                brush = CreateSolidBrush(RGB(213, 43, 30));
                FillRect(hdc, &stripe, brush);
                DeleteObject(brush);
            }
            break;
    }
}
