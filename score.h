//=============================================================================
//
// スコア処理 [score.h]
// Author : 
//
//=============================================================================
#pragma once


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCORE_MAX			(3)		// スコアの個数
#define SCORE_DIGIT			(5)			// 桁数
#define SCORE_NUM_MAX			(99999)		// スコアの最大値



//*****************************************************************************
// 構造体定義
//*****************************************************************************

//struct SCORE
//{
//	bool						g_Use;						// true:使っている  false:未使用
//	float					g_w, g_h;					// 幅と高さ
//	XMFLOAT3					g_Pos;						// ポリゴンの座標
//	int						g_TexNo;					// テクスチャ番号
//
//
//	int						g_Score;					// スコア
//
//	int						g_KillScore;					// 撃破スコア
//	int						g_KillassScore;					// 撃破補助スコア
//	int						g_ShootScore;					// 発射スコア
//	int						g_HitScore;						// 命中スコア
//
//
//
//};


//*****************************************************************************
// プロトタイプ宣言
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


