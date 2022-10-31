//=============================================================================
//
// 入力処理 [input.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

// プログラム分けするときに使う
#define	USE_KEYBOARD				// 宣言するとキーボードで操作可能になる
#define	USE_MOUSE					// 宣言するとマウスで操作可能になる
#define	USE_PAD						// 宣言するとパッドで操作可能になる


/* game pad情報 */
#define BUTTON_L_UP			0x00000001l	// 左方向キー上		(.IY<0)
#define BUTTON_L_DOWN		0x00000002l	// 左方向キー下		(.IY>0)
#define BUTTON_L_LEFT		0x00000004l	// 左方向キー左		(.IX<0)
#define BUTTON_L_RIGHT		0x00000008l	// 左方向キー右		(.IX>0)

#define BUTTON_R_UP			0x00100000l	// 右方向キー上		(.lRz < 25000)
#define BUTTON_R_DOWN		0x00200000l	// 右方向キー下		(.lRz > 40000)
#define BUTTON_R_LEFT		0x00400000l	// 右方向キー左		(.lZ  < 20000)
#define BUTTON_R_RIGHT		0x00800000l	// 右方向キー右		(.lZ  > 45000)

#define BUTTON_POV_UP		0x00010000l	// 十字キー上		(.rgdwPOV[0] == 0)
#define BUTTON_POV_DOWN		0x00020000l	// 十字キー下		(.rgdwPOV[0] == 18000)
#define BUTTON_POV_LEFT		0x00040000l	// 十字キー左		(.rgdwPOV[0] == 27000)
#define BUTTON_POV_RIGHT	0x00080000l	// 十字キー右		(.rgdwPOV[0] == 9000)

#define BUTTON_X			0x00000010l	// Ｘボタン			(.rgbButtons[0]&0x80)
#define BUTTON_A			0x00000020l	// Ａボタン			(.rgbButtons[1]&0x80)
#define BUTTON_B			0x00000040l	// Ｂボタン			(.rgbButtons[2]&0x80)
#define BUTTON_Y			0x00000080l	// Ｙボタン			(.rgbButtons[3]&0x80)

#define BUTTON_L			0x00000100l	// Ｌボタン			(.rgbButtons[4]&0x80)
#define BUTTON_R			0x00000200l	// Ｒボタン			(.rgbButtons[5]&0x80)
#define BUTTON_L2			0x00000400l	// Ｌボタン			(.rgbButtons[6]&0x80)
#define BUTTON_R2			0x00000800l	// Ｒボタン			(.rgbButtons[7]&0x80)

#define BUTTON_SHARE		0x00001000l	// SHAREボタン		(.rgbButtons[8]&0x80)
#define BUTTON_OPTIONS		0x00002000l	// OPTIONSボタン	(.rgbButtons[9]&0x80)

#define BUTTON_L3			0x00004000l	// Ｌ３ボタン		(.rgbButtons[10]&0x80)
#define BUTTON_R3			0x00008000l	// Ｒ３ボタン		(.rgbButtons[11]&0x80)
#define BUTTON_PS			0x01000000l	// ＰＳボタン		(.rgbButtons[12]&0x80)
#define BUTTON_PAD			0x02000000l	// トラックパッド	(.rgbButtons[13]&0x80)

#define GAMEPADMAX			4			// 同時に接続するジョイパッドの最大数をセット

enum {	// ボタンに対するrgbButtons[?]配列の配列番号(DirectInput上でのXYABボタン位置に合わせた)
	rgbButtons_X,
	rgbButtons_A,
	rgbButtons_B,
	rgbButtons_Y,
	rgbButtons_L,
	rgbButtons_R,
	rgbButtons_L2,
	rgbButtons_R2,
	rgbButtons_SELECT,
	rgbButtons_START,
	rgbButtons_L3,
	rgbButtons_R3,
	rgbButtons_PS,
	rgbButtons_PAD,
};



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitInput(HINSTANCE hInst, HWND hWnd);
void UninitInput(void);
void UpdateInput(void);

//---------------------------- keyboard
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
bool GetKeyboardRepeat(int nKey);
bool GetKeyboardRelease(int nKey);

//---------------------------- mouse
BOOL IsMouseLeftPressed(void);      // 左クリックした状態
BOOL IsMouseLeftTriggered(void);    // 左クリックした瞬間
BOOL IsMouseRightPressed(void);     // 右クリックした状態
BOOL IsMouseRightTriggered(void);   // 右クリックした瞬間
BOOL IsMouseCenterPressed(void);    // 中クリックした状態
BOOL IsMouseCenterTriggered(void);  // 中クリックした瞬間
long GetMouseX(void);               // マウスがX方向に動いた相対値
long GetMouseY(void);               // マウスがY方向に動いた相対値
long GetMouseZ(void);               // マウスホイールが動いた相対値

//---------------------------- game pad
BOOL IsButtonPressed(int padNo, DWORD button);
BOOL IsButtonTriggered(int padNo, DWORD button);


