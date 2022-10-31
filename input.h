//=============================================================================
//
// ���͏��� [input.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

// �v���O������������Ƃ��Ɏg��
#define	USE_KEYBOARD				// �錾����ƃL�[�{�[�h�ő���\�ɂȂ�
#define	USE_MOUSE					// �錾����ƃ}�E�X�ő���\�ɂȂ�
#define	USE_PAD						// �錾����ƃp�b�h�ő���\�ɂȂ�


/* game pad��� */
#define BUTTON_L_UP			0x00000001l	// �������L�[��		(.IY<0)
#define BUTTON_L_DOWN		0x00000002l	// �������L�[��		(.IY>0)
#define BUTTON_L_LEFT		0x00000004l	// �������L�[��		(.IX<0)
#define BUTTON_L_RIGHT		0x00000008l	// �������L�[�E		(.IX>0)

#define BUTTON_R_UP			0x00100000l	// �E�����L�[��		(.lRz < 25000)
#define BUTTON_R_DOWN		0x00200000l	// �E�����L�[��		(.lRz > 40000)
#define BUTTON_R_LEFT		0x00400000l	// �E�����L�[��		(.lZ  < 20000)
#define BUTTON_R_RIGHT		0x00800000l	// �E�����L�[�E		(.lZ  > 45000)

#define BUTTON_POV_UP		0x00010000l	// �\���L�[��		(.rgdwPOV[0] == 0)
#define BUTTON_POV_DOWN		0x00020000l	// �\���L�[��		(.rgdwPOV[0] == 18000)
#define BUTTON_POV_LEFT		0x00040000l	// �\���L�[��		(.rgdwPOV[0] == 27000)
#define BUTTON_POV_RIGHT	0x00080000l	// �\���L�[�E		(.rgdwPOV[0] == 9000)

#define BUTTON_X			0x00000010l	// �w�{�^��			(.rgbButtons[0]&0x80)
#define BUTTON_A			0x00000020l	// �`�{�^��			(.rgbButtons[1]&0x80)
#define BUTTON_B			0x00000040l	// �a�{�^��			(.rgbButtons[2]&0x80)
#define BUTTON_Y			0x00000080l	// �x�{�^��			(.rgbButtons[3]&0x80)

#define BUTTON_L			0x00000100l	// �k�{�^��			(.rgbButtons[4]&0x80)
#define BUTTON_R			0x00000200l	// �q�{�^��			(.rgbButtons[5]&0x80)
#define BUTTON_L2			0x00000400l	// �k�{�^��			(.rgbButtons[6]&0x80)
#define BUTTON_R2			0x00000800l	// �q�{�^��			(.rgbButtons[7]&0x80)

#define BUTTON_SHARE		0x00001000l	// SHARE�{�^��		(.rgbButtons[8]&0x80)
#define BUTTON_OPTIONS		0x00002000l	// OPTIONS�{�^��	(.rgbButtons[9]&0x80)

#define BUTTON_L3			0x00004000l	// �k�R�{�^��		(.rgbButtons[10]&0x80)
#define BUTTON_R3			0x00008000l	// �q�R�{�^��		(.rgbButtons[11]&0x80)
#define BUTTON_PS			0x01000000l	// �o�r�{�^��		(.rgbButtons[12]&0x80)
#define BUTTON_PAD			0x02000000l	// �g���b�N�p�b�h	(.rgbButtons[13]&0x80)

#define GAMEPADMAX			4			// �����ɐڑ�����W���C�p�b�h�̍ő吔���Z�b�g

enum {	// �{�^���ɑ΂���rgbButtons[?]�z��̔z��ԍ�(DirectInput��ł�XYAB�{�^���ʒu�ɍ��킹��)
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
// �v���g�^�C�v�錾
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
BOOL IsMouseLeftPressed(void);      // ���N���b�N�������
BOOL IsMouseLeftTriggered(void);    // ���N���b�N�����u��
BOOL IsMouseRightPressed(void);     // �E�N���b�N�������
BOOL IsMouseRightTriggered(void);   // �E�N���b�N�����u��
BOOL IsMouseCenterPressed(void);    // ���N���b�N�������
BOOL IsMouseCenterTriggered(void);  // ���N���b�N�����u��
long GetMouseX(void);               // �}�E�X��X�����ɓ��������Βl
long GetMouseY(void);               // �}�E�X��Y�����ɓ��������Βl
long GetMouseZ(void);               // �}�E�X�z�C�[�������������Βl

//---------------------------- game pad
BOOL IsButtonPressed(int padNo, DWORD button);
BOOL IsButtonTriggered(int padNo, DWORD button);


