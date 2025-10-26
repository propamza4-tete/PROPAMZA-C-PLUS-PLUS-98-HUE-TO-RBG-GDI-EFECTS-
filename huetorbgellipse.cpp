#include <windows.h>
#include <stdlib.h>

COLORREF HueToRGB(double hue) {
    double H = hue / 60.0;
    int i = (int)H;
    double f = H - i;
    double p = 0;
    double q = 1 - f;
    double t = f;
    int r, g, b;

    switch(i) {
    case 0: r = 255; g = (int)(t*255); b = 0; break;
    case 1: r = (int)(q*255); g = 255; b = 0; break;
    case 2: r = 0; g = 255; b = (int)(t*255); break;
    case 3: r = 0; g = (int)(q*255); b = 255; break;
    case 4: r = (int)(t*255); g = 0; b = 255; break;
    default: r = 255; g = 0; b = (int)(q*255); break;
    }

    return RGB(r,g,b);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmdLine, int nShowCmd) {
    int screenWidth  = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    double hue = 0.0;

    while(1){
        hue += 1.0;
        if(hue > 360.0) hue = 0.0;

        HDC hdc = GetDC(0);

        HBRUSH brush = CreateSolidBrush(HueToRGB(hue));
        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);

        int x1 = rand() % screenWidth;
        int y1 = rand() % screenHeight;
        int x2 = rand() % screenWidth;
        int y2 = rand() % screenHeight;
        int x3 = rand() % screenWidth;
        int y3 = rand() % screenHeight;
        int x4 = rand() % screenWidth;
        int y4 = rand() % screenHeight;

        Pie(hdc, x1, y1, x2, y2, x3, y3, x4, y4);

        SelectObject(hdc, oldBrush);
        DeleteObject(brush);
        ReleaseDC(0, hdc);

        Sleep(10);
    }

    return 0;
}

