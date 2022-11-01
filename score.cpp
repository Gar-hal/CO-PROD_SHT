//=============================================================================
//
// スコア処理 [score.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "score.h"
#include "sprite.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_WIDTH				(16)	// キャラサイズ
#define TEXTURE_HEIGHT				(32)	// 
#define TEXTURE_MAX					(2)		// テクスチャの数


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11Buffer				*g_VertexBuffer = NULL;		// 頂点情報
static ID3D11ShaderResourceView	*g_Texture[TEXTURE_MAX] = { NULL };	// テクスチャ情報

static char *g_TexturName[] = {
	"data/TEXTURE/number16x32.png",
	"data/TEXTURE/number16x32.png",
};


static bool						g_Use;						// true:使っている  false:未使用
static float					g_w, g_h;					// 幅と高さ
static XMFLOAT3					g_Pos0;						// ポリゴンの座標
static XMFLOAT3					g_Pos1;						// ポリゴンの座標
static int						g_TexNo;					// テクスチャ番号


static int						g_Score;						// スコア
static int						g_KillScore;					// 撃破スコア
static int						g_KillassScore;					// 撃破補助スコア
static int						g_ShootScore;					// 発射スコア
static int						g_HitScore;						// 命中スコア

//static SCORE	g_Score[SCORE_MAX];	// スコア構造体



//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitScore(void)
{
	ID3D11Device *pDevice = GetDevice();

	//テクスチャ生成
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		g_Texture[i] = NULL;
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			g_TexturName[i],
			NULL,
			NULL,
			&g_Texture[i],
			NULL);
	}


	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);


	// プレイヤーの初期化
	g_Use   = true;
	g_w     = TEXTURE_WIDTH;
	g_h     = TEXTURE_HEIGHT;
	g_Pos0  = { 900.0f, 60.0f, 0.0f };
	g_Pos1  = { 900.0f, 100.0f, 0.0f };
	g_TexNo = 0;




	// スコアの初期化
	g_Score = 0;
	g_KillScore = 0;
	g_KillassScore = 0;
	g_ShootScore = 0;
	g_HitScore = 0;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitScore(void)
{
	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}

	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		if (g_Texture[i])
		{
			g_Texture[i]->Release();
			g_Texture[i] = NULL;
		}
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateScore(void)
{


#ifdef _DEBUG	// デバッグ情報を表示する
	//char *str = GetDebugStr();
	//sprintf(&str[strlen(str)], " PX:%.2f PY:%.2f", g_Pos.x, g_Pos.y);
	
#endif

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawScore(void)
{
	{
		// 頂点バッファ設定
		UINT stride0 = sizeof(VERTEX_3D);
		UINT offset0 = 0;
		GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride0, &offset0);

		// マトリクス設定
		SetWorldViewProjection2D();

		// プリミティブトポロジ設定
		GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		// マテリアル設定
		MATERIAL material;
		ZeroMemory(&material, sizeof(material));
		material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		SetMaterial(material);

		// スコア表示
		{
			// テクスチャ設定
			GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[0]);

			// 桁数分処理する
			int number0 = g_Score;
			for (int i = 0; i < SCORE_DIGIT; i++)
			{
				// 今回表示する桁の数字
				float x = (float)(number0 % 10);

				// スコアの位置やテクスチャー座標を反映
				float px = g_Pos0.x - g_w * i;	// スコアの表示位置X
				float py = g_Pos0.y;			// スコアの表示位置Y
				float pw = g_w;				// スコアの表示幅
				float ph = g_h;				// スコアの表示高さ

				float tw = 1.0f / 10;		// テクスチャの幅
				float th = 1.0f / 1;		// テクスチャの高さ
				float tx = x * tw;			// テクスチャの左上X座標
				float ty = 0.0f;			// テクスチャの左上Y座標

				// １枚のポリゴンの頂点とテクスチャ座標を設定
				SetSpriteColor(g_VertexBuffer, px, py, pw, ph, tx, ty, tw, th,
					XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

				// ポリゴン描画
				GetDeviceContext()->Draw(4, 0);

				// 次の桁へ
				number0 /= 10;
			}
		}

		// キル数表示
		{
			// テクスチャ設定
			GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[1]);

			// 桁数分処理する
			int number1 = g_KillScore;
			for (int i = 0; i < SCORE_DIGIT; i++)
			{
				// 今回表示する桁の数字
				float x = (float)(number1 % 10);

				// スコアの位置やテクスチャー座標を反映
				float px = g_Pos1.x - g_w * i;	// スコアの表示位置X
				float py = g_Pos1.y;			// スコアの表示位置Y
				float pw = g_w;				// スコアの表示幅
				float ph = g_h;				// スコアの表示高さ

				float tw = 1.0f / 10;		// テクスチャの幅
				float th = 1.0f / 1;		// テクスチャの高さ
				float tx = x * tw;			// テクスチャの左上X座標
				float ty = 0.0f;			// テクスチャの左上Y座標

				// １枚のポリゴンの頂点とテクスチャ座標を設定
				SetSpriteColor(g_VertexBuffer, px, py, pw, ph, tx, ty, tw, th,
					XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

				// ポリゴン描画
				GetDeviceContext()->Draw(4, 0);

				// 次の桁へ
				number1 /= 10;
			}
		}

	}

}


//=============================================================================
// スコアを加算する
// 引数:add :追加する点数。マイナスも可能
//=============================================================================
void AddScore(int add)
{
	g_Score += add;
	if (g_Score > SCORE_NUM_MAX)
	{
		g_Score = SCORE_NUM_MAX;
	}

}

void KillScore(int addkill)
{
	g_KillScore += addkill;
	if (g_KillScore > SCORE_NUM_MAX)
	{
		g_KillScore = SCORE_NUM_MAX;
	}

}

void KillassScore(int addkillass)
{
	g_KillassScore += addkillass;
	if (g_KillassScore > SCORE_NUM_MAX)
	{
		g_KillassScore = SCORE_NUM_MAX;
	}

}

void ShootScore(int addshoot)
{
	g_ShootScore += addshoot;
	if (g_ShootScore > SCORE_NUM_MAX)
	{
		g_ShootScore = SCORE_NUM_MAX;
	}

}

void HitScore(int addhit)
{
	g_HitScore += addhit;
	if (g_HitScore > SCORE_NUM_MAX)
	{
		g_HitScore = SCORE_NUM_MAX;
	}

}





int GetScore(void)
{
	return g_Score;
}


void SetScore(int score)
{
	g_Score = score;
}


