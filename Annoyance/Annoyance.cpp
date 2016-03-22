#include "stdafx.h"
#include "Annoyance.h"

#define MAX_LOADSTRING 100
#define IDT_TIMER1 1

HINSTANCE g_hInstance = NULL;
HWND      g_hWnd      = NULL;
TCHAR     szTitle[ MAX_LOADSTRING ];
TCHAR     szWindowClass[ MAX_LOADSTRING ];

ATOM				      MyRegisterClass( HINSTANCE hInstance );
BOOL				      InitInstance( HINSTANCE, int );
LRESULT CALLBACK	WndProc( HWND, UINT, WPARAM, LPARAM );
INT_PTR CALLBACK	About( HWND, UINT, WPARAM, LPARAM );

int APIENTRY 
_tWinMain(
  HINSTANCE hInstance,
  HINSTANCE hPrevInstance,
  LPTSTR    lpCmdLine,
  int       nCmdShow
  ) {
  UNREFERENCED_PARAMETER( hPrevInstance );
  UNREFERENCED_PARAMETER( lpCmdLine );

  LoadString( hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING );
  LoadString( hInstance, IDC_ANNOYANCE, szWindowClass, MAX_LOADSTRING );
  MyRegisterClass( hInstance );

  // Perform application initialization:
  if( !InitInstance( hInstance, nCmdShow ) ) {
    return FALSE;
  }

  HACCEL hAccelTable = LoadAccelerators( hInstance, MAKEINTRESOURCE( IDC_ANNOYANCE ) );

  MSG msg;
  while( GetMessage( &msg, NULL, 0, 0 ) ) {
    if( !TranslateAccelerator( msg.hwnd, hAccelTable, &msg ) ) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }

  KillTimer( g_hWnd, IDT_TIMER1 );

  return (int)msg.wParam;
}

ATOM 
MyRegisterClass(
  HINSTANCE hInstance
  ) {
  WNDCLASSEX wcex;

  wcex.cbSize = sizeof( WNDCLASSEX );

  wcex.style			    = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc	  = WndProc;
  wcex.cbClsExtra		  = 0;
  wcex.cbWndExtra		  = 0;
  wcex.hInstance		  = hInstance;
  wcex.hIcon			    = LoadIcon( hInstance, MAKEINTRESOURCE( IDI_ANNOYANCE ) );
  wcex.hCursor		    = LoadCursor( NULL, IDC_ARROW );
  wcex.hbrBackground	= (HBRUSH)( COLOR_WINDOW + 1 );
  wcex.lpszMenuName	  = MAKEINTRESOURCE( IDC_ANNOYANCE );
  wcex.lpszClassName	= szWindowClass;
  wcex.hIconSm		    = LoadIcon( wcex.hInstance, MAKEINTRESOURCE( IDI_SMALL ) );

  return RegisterClassEx( &wcex );
}

BOOL
InitInstance(
  HINSTANCE hInstance, 
  int       nCmdShow
  ) {
  g_hInstance = hInstance;

  g_hWnd = CreateWindow(
    szWindowClass, 
    szTitle, 
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, 
    0, 
    CW_USEDEFAULT, 
    0, 
    NULL, 
    NULL, 
    hInstance, 
    NULL );

  if( !g_hWnd ) {
    return FALSE;
  }

  ShowWindow( g_hWnd, nCmdShow );
  UpdateWindow( g_hWnd );

  // Start being annoying
  SetTimer( g_hWnd, IDT_TIMER1, 1000, (TIMERPROC)NULL );

  return TRUE;
}

LRESULT CALLBACK 
WndProc(
  HWND   hWnd, 
  UINT   message, 
  WPARAM wParam, 
  LPARAM lParam
  ) {
  
  switch( message ) {
    case WM_TIMER:
      if( hWnd != NULL ) {
        // Start off easy
        // SetForegroundWindow will not move the window to the foreground,
        // but it will invoke FlashWindow internally and, thus, show the
        // taskbar.
        SetForegroundWindow( hWnd );

        // Our application is awesome! It must have your focus!
        SetActiveWindow( hWnd );

        // Flash that button!
        FlashWindow( hWnd, TRUE );
      }
      break;

    case WM_PAINT: {
      PAINTSTRUCT ps;
      HDC hdc;
      hdc = BeginPaint( hWnd, &ps );
      EndPaint( hWnd, &ps );
      break;
    }
    case WM_DESTROY:
      PostQuitMessage( 0 );
      break;
    default:
      return DefWindowProc(hWnd, message, wParam, lParam);
  }
  return 0;
}
