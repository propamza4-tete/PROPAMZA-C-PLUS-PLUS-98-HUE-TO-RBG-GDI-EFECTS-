#include <windows.h>
#include <stdlib.h>
#include <math.h>

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
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);

    int signX = 1;
    int signY = 1;
    int incrementor = 10;
    int x = 10;
    int y = 10;
    double hue = 0.0;

    while(1) {
        HDC hdc = GetDC(0);

        x += incrementor * signX;
        y += incrementor * signY;

        int top_x = x;
        int top_y = y;
        int bottom_x = x + 100;
        int bottom_y = y + 100;

        hue += 1.0;
        if(hue > 360.0) hue = 0.0;

        HBRUSH brush = CreateSolidBrush(HueToRGB(hue));
        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);

        Ellipse(hdc, top_x, top_y, bottom_x, bottom_y);

        SelectObject(hdc, oldBrush);
        DeleteObject(brush);
        ReleaseDC(0, hdc);

        if (y >= h) signY = -1;
        if (x >= w) signX = -1;
        if (y <= 0) signY = 1;
        if (x <= 0) signX = 1;

        Sleep(10);
    }
    return 0;
}

