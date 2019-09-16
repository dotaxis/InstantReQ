#include "InstantReQ.h"
#include "Windows.h"
#include <sstream>
#include <bakkesmod\plugin\bakkesmodplugin.h>


class InputHandler final {
public:

	/*
    int CalculateAbsoluteCoordinateX(int x)
    {
      return (x * 65535) / GetSystemMetrics(SM_CXSCREEN);
    }

    int CalculateAbsoluteCoordinateY(int y)
    {
      return (y * 65535) / GetSystemMetrics(SM_CYSCREEN);
    }

     void leftClick(int x, int y)
    {
	  INPUT mouseInput = { 0 };
	  mouseInput.type = INPUT_MOUSE;
      mouseInput.mi.dx = CalculateAbsoluteCoordinateX(x);
      mouseInput.mi.dy = CalculateAbsoluteCoordinateY(y);
	  mouseInput.mi.time = GetTickCount();


      mouseInput.mi.dwFlags = (MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE);
	  SendInput(1, &mouseInput, sizeof(INPUT));
	  //Sleep(1000);

      mouseInput.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
      SendInput(1, &mouseInput, sizeof(INPUT));
	  //Sleep(1000);

      mouseInput.mi.dwFlags = MOUSEEVENTF_LEFTUP;
      SendInput(1, &mouseInput, sizeof(INPUT));
	  //Sleep(1000);
    }

	 std::stringstream leftClick2(int x, int y) {

		 INPUT input[3];
		 for (int i = 0; i < 3; i++)
		 {
			 memset(&input[i], 0, sizeof(INPUT));
			 input[i].type = INPUT_MOUSE;
		 }

		 input[0].mi.dx = (x * 0xFFFF) / (GetSystemMetrics(SM_CXSCREEN) - 1);
		 input[0].mi.dy = (y * 0xFFFF) / (GetSystemMetrics(SM_CYSCREEN) - 1);
		 input[0].mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
		 input[1].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		 input[2].mi.dwFlags = MOUSEEVENTF_LEFTUP;

		 SendInput(3, input, sizeof(INPUT));
		 std::stringstream str;
		 str << "Absolute X: " << input[0].mi.dx << " Width: " << GetSystemMetrics(SM_CXSCREEN);
		 return str;
	 }
	 */

	 void pressKey(int KEY) {
		 INPUT k = { 0 };

		 k.type = INPUT_KEYBOARD;
		 k.ki.time = 0;
		 k.ki.wVk = 0;
		 k.ki.dwExtraInfo = 0;
		 k.ki.dwFlags = KEYEVENTF_SCANCODE;
		 k.ki.wScan = KEY;

		 SendInput(1, &k, sizeof(INPUT));
		 Sleep(50);
		 k.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
		 SendInput(1, &k, sizeof(INPUT));
		 k.ki.dwFlags = KEYEVENTF_SCANCODE;
		 return;
	 }

};
