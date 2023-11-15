#include <windows.h>
#include <stdio.h>
#include <math.h>
// USE: gcc -o prueba prueba.c -lgdi32 -mwindows

// Funciones para el manejo de la ventana
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Crear la ventana
    HWND hwnd;
    MSG msg;
    WNDCLASS wc;

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "GDIExample";

    RegisterClass(&wc);

    hwnd = CreateWindow("GDIExample", "GDI Example", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Bucle de mensajes de la ventana
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hdc;

    switch (msg) {
        case WM_PAINT: {

            // RECT clientRect;
            // GetClientRect(hwnd, &clientRect);

            // int canvasWidth = clientRect.right - clientRect.left;
            // int canvasHeight = clientRect.bottom - clientRect.top;

            // // Inicializar GDI en el contexto del dispositivo
            // hdc = BeginPaint(hwnd, &ps);

            // // Crear un pincel y un bolígrafo
            // // HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0)); // Rojo
            // // HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0)); // Rojo

            // // Crear un pincel y un bolígrafo
            // HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255)); // Blanco
            // HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255)); // Azul

            // // Seleccionar el pincel y el bolígrafo en el contexto del dispositivo
            // SelectObject(hdc, hBrush);
            // SelectObject(hdc, hPen);

            // Rectangle(hdc, 10, 10, canvasWidth - 10, canvasHeight - 10);

            // // Liberar los recursos
            // DeleteObject(hBrush);
            // DeleteObject(hPen);

            // // Crear un pincel y un bolígrafo
            // hBrush = CreateSolidBrush(RGB(0, 255, 0)); // Verde
            // hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0)); // Rojo

            // // Seleccionar el pincel y el bolígrafo en el contexto del dispositivo
            // SelectObject(hdc, hBrush);
            // SelectObject(hdc, hPen);

            // // Dibujar un círculo en las coordenadas (50, 50) con ancho y alto de 100
            // Ellipse(hdc, 50, 50, 150, 150);

            // // Dibujar una línea desde (200, 50) hasta (300, 150)
            // MoveToEx(hdc, 200, 50, NULL);
            // LineTo(hdc, 300, 150);

            // // Dibujar un rectángulo desde (350, 50) hasta (450, 150)
            // Rectangle(hdc, 350, 50, 450, 150);

            // // Liberar los recursos
            // DeleteObject(hBrush);
            // DeleteObject(hPen);

            hdc = BeginPaint(hwnd, &ps);

            // Mapear las coordenadas del mundo real a las coordenadas de la ventana
            int canvasWidth, canvasHeight;
            RECT clientRect;
            GetClientRect(hwnd, &clientRect);
            canvasWidth = clientRect.right - clientRect.left;
            canvasHeight = clientRect.bottom - clientRect.top;

            // Dibujar los ejes
            MoveToEx(hdc, 0, canvasHeight / 2, NULL);
            LineTo(hdc, canvasWidth, canvasHeight / 2);
            MoveToEx(hdc, canvasWidth / 2, 0, NULL);
            LineTo(hdc, canvasWidth / 2, canvasHeight);

            HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0)); // Blanco
            SelectObject(hdc, hBrush);

            // Dibujar la gráfica de la función y = sin(x)
            double scaleX = 20.0;
            double scaleY = 50.0;
            double offsetX = canvasWidth / 2;
            double offsetY = canvasHeight / 2;

            // MATH
            double unitX = 20;
            double unitY = 20;
            double steps = 1;
            double numberSpacing = 5;
            
            // SET UNITS
            for (int x = (int)(canvasWidth / 2); x > (int)(-canvasWidth / 2); x -= unitX){
                // Mapear las coordenadas reales a las coordenadas de la ventana
                int mappedX = (int)(x * scaleX + offsetX);
                // int mappedY = (int)(-y * scaleY / 3 + offsetY);

                // Escribir texto en el canvas
                char num_text[20] = "";
                int algo = snprintf(num_text, sizeof(num_text), "%d", x);
                // printf(num_text);
                
                if (x % (int)unitX * numberSpacing == 0) TextOutA(hdc, x, (int)(canvasHeight / 2 - unitX) - 20, num_text, sizeof(num_text) - 1); // -1 para excluir el carácter nulo

                // Dibujar linea
                MoveToEx(hdc, x, (int)(canvasHeight / 2 - 10), NULL);
                LineTo(hdc, x, (int)(canvasHeight / 2 + 10));
            }
            for (int x = (int)(canvasWidth / 2); x < canvasWidth; x += unitX){
                // Mapear las coordenadas reales a las coordenadas de la ventana
                int mappedX = (int)(x * scaleX + offsetX);
                // int mappedY = (int)(-y * scaleY / 3 + offsetY);

                MoveToEx(hdc, x, (int)(canvasHeight / 2 - 10), NULL);
                LineTo(hdc, x, (int)(canvasHeight / 2 + 10));
            }
            for (int y = (int)(canvasHeight / 2); y > 0; y -= unitY){
                // Mapear las coordenadas reales a las coordenadas de la ventana
                int mappedY = (int)(y * scaleY + offsetY);

                MoveToEx(hdc, (int)(canvasWidth / 2 - 10), y, NULL);
                LineTo(hdc, (int)(canvasWidth / 2 + 10), y);
            }
            for (int y = (int)(canvasHeight / 2); y < canvasHeight; y += unitY){
                // Mapear las coordenadas reales a las coordenadas de la ventana
                int mappedY = (int)(y * scaleY + offsetY);

                MoveToEx(hdc, (int)(canvasWidth / 2 - 10), y, NULL);
                LineTo(hdc, (int)(canvasWidth / 2 + 10), y);
            }

            for (int x = -canvasWidth; x < canvasWidth; x++) {
                if (x % (int)steps == 0){
                    // double y = sin(x / scaleX) * scaleY; // Funcion 1
                    double y = 1/10.0 * x * x; // Funcion 2
                    // double y = pow((x-5), 2) + 5; // Funcion 2
                    // double y = sqrt(exp(x - 5)) + 5;
                    // double y = x; // Funcion 2
                    // Arreglar eje Y invertido
                    y = -y;
                    // Mapear las coordenadas reales a las coordenadas de la ventana
                    int mappedX = (int)(x * scaleX + offsetX);
                    int mappedY = (int)(-y * scaleY + offsetY);
                    SetPixel(hdc, mappedX, mappedY, RGB(0, 0, 255));  // Pintar el punto en azul
                    // Ellipse(hdc, mappedX - 2, mappedY - 2, mappedX + 2, mappedY + 2);
                    Ellipse(hdc, x + offsetX - 2, y + offsetY - 2, x + offsetX + 2, y + offsetY + 2);
                }
            }

            // Escribir texto en el canvas
            const char text[] = "Ejemplo de texto";
            TextOutA(hdc, 10, 10, text, sizeof(text) - 1); // -1 para excluir el carácter nulo
            Rectangle(hdc, 350, 50, 351, 51);
            // Escribir texto en el canvas
            // char num_text[20] = "";
            // int algo = snprintf(num_text, sizeof(num_text), "%d", 8694);
            // printf(num_text);
            // TextOutA(hdc, 10, (int)(canvasHeight / 2 - unitX) - 20, num_text, sizeof(num_text) - 1); // -1 para excluir el carácter nulo

            // Finalizar la pintura
            EndPaint(hwnd, &ps);
            break;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
