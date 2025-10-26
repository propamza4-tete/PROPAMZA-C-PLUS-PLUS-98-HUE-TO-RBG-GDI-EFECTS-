#include <windows.h>
#include <windowsx.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

COLORREF HueToRGB(double h) {
    double r, g, b;
    int i;
    double f, p, q, t;

    if (h < 0) h += 360;
    if (h >= 360) h -= 360;

    h /= 60;
    i = (int)h;
    f = h - i;
    p = 0;
    q = 1 - f;
    t = f;

    switch (i) {
    case 0: r = 1; g = t; b = 0; break;
    case 1: r = q; g = 1; b = 0; break;
    case 2: r = 0; g = 1; b = t; break;
    case 3: r = 0; g = q; b = 1; break;
    case 4: r = t; g = 0; b = 1; break;
    default: r = 1; g = 0; b = q; break;
    }

    return RGB((int)(r * 255), (int)(g * 255), (int)(b * 255));
}

int main() {
    srand((unsigned)time(0));

    double hue = 0.0;
    while (1) {
        int w = GetSystemMetrics(SM_CXSCREEN);
        int h = GetSystemMetrics(SM_CYSCREEN);
        HDC hdc = GetDC(0);

        hue += 1.0;
        if (hue > 360.0) hue = 0.0;

        COLORREF color = HueToRGB(hue);

        HPEN hPen = CreatePen(PS_SOLID, 2, color);
        HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

        HBRUSH hBrush = CreateSolidBrush(color);
        HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

        POINT vertices[3];
        vertices[0].x = rand() % w;
        vertices[0].y = rand() % h;
        vertices[1].x = rand() % w;
        vertices[1].y = rand() % h;
        vertices[2].x = rand() % w;
        vertices[2].y = rand() % h;

        Polygon(hdc, vertices, 3);

        SelectObject(hdc, hOldBrush);
        DeleteObject(hBrush);

        SelectObject(hdc, hOldPen);
        DeleteObject(hPen);

        ReleaseDC(0, hdc);
        Sleep(10);
    }

    return 0;
}

