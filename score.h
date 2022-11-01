//=============================================================================
//
// �X�R�A���� [score.h]
// Author : 
//
//=============================================================================
#pragma once


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCORE_MAX			(3)		// �X�R�A�̌�
#define SCORE_DIGIT			(5)			// ����
#define SCORE_NUM_MAX			(99999)		// �X�R�A�̍ő�l



//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//struct SCORE
//{
//	bool						g_Use;						// true:�g���Ă���  false:���g�p
//	float					g_w, g_h;					// ���ƍ���
//	XMFLOAT3					g_Pos;						// �|���S���̍��W
//	int						g_TexNo;					// �e�N�X�`���ԍ�
//
//
//	int						g_Score;					// �X�R�A
//
//	int						g_KillScore;					// ���j�X�R�A
//	int						g_KillassScore;					// ���j�⏕�X�R�A
//	int						g_ShootScore;					// ���˃X�R�A
//	int						g_HitScore;						// �����X�R�A
//
//
//
//};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);

void AddScore(int add);
void KillScore(int addkill);
void KillassScore(int addkillass);
void ShootScore(int addshoot);
void HitScore(int addhit);




int GetScore(void);
void SetScore(int score);


