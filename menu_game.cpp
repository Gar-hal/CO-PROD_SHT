//=============================================================================
//
// GameMenu処理 [menu_game.cpp]
// Author : 
//
//=============================================================================
#include "menu_game.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MENU_GAME_WIDTH				(SCREEN_WIDTH)	// 背景サイズ
#define MENU_GAME_HEIGHT			(SCREEN_HEIGHT)	// 背景サイズ
#define MENU_GAME_MAX				(3)				// テクスチャの数

#define MENU_GAME_WIDTH_LOGO		(480)			// ロゴサイズ
#define MENU_GAME_HEIGHT_LOGO		(80)			// ロゴサイズ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11Buffer* g_VertexBuffer = NULL;		// 頂点情報
static ID3D11ShaderResourceView* g_Texture[MENU_GAME_MAX] = { NULL };	// テクスチャ情報

static char* g_TexturName[MENU_GAME_MAX] = {
	"data/TEXTURE/menu_game.png",
	"data/TEXTURE/fade_black.png",
};


static BOOL	g_Menu_Load = FALSE;		// 初期化を行ったかのフラグ
static MENU_GAME	g_MenuG;


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitMenuGame(void)
{
	ID3D11Device* pDevice = GetDevice();

	//テクスチャ生成
	for (int i = 0; i < MENU_GAME_MAX; i++)
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


	// 変数の初期化
	g_MenuG.w = MENU_GAME_WIDTH;
	g_MenuG.h = MENU_GAME_HEIGHT;
	g_MenuG.pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_MenuG.texNo = 0;

	g_MenuG.flag = false;

	g_Menu_Load = TRUE;
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitMenuGame(void)
{
	if (g_Menu_Load == FALSE) return;

	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}

	for (int i = 0; i < MENU_GAME_MAX; i++)
	{
		if (g_Texture[i])
		{
			g_Texture[i]->Release();
			g_Texture[i] = NULL;
		}
	}

	g_Menu_Load = FALSE;
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMenuGame(void)
{
	if (GetKeyboardTrigger(DIK_E)) {
		if (g_MenuG.flag == false)	g_MenuG.flag = true;
		else						g_MenuG.flag = false;
	}
	
	if (g_MenuG.flag == false)	ShowCursor(FALSE);	// カーソルの非表示
	else						ShowCursor(TRUE);	// カーソルの表示

#ifdef _DEBUG	// デバッグ情報を表示する


#endif
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMenuGame(void)
{
	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// マトリクス設定
	SetWorldViewProjection2D();

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);
	
	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[1]);

	// １枚のポリゴンの頂点とテクスチャ座標を設定
	SetSpriteLTColor(g_VertexBuffer,
		0.0f, 0.0f, g_MenuG.w, g_MenuG.h,
		0.0f, 0.0f, 1.0f, 1.0f,
		XMFLOAT4(1.0f, 1.0f, 1.0f, 0.8f));

	// ポリゴン描画
	GetDeviceContext()->Draw(4, 0);

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[g_MenuG.texNo]);

	// １枚のポリゴンの頂点とテクスチャ座標を設定
	SetSpriteLTColor(g_VertexBuffer,
		0.0f, 0.0f, g_MenuG.w, g_MenuG.h,
		0.0f, 0.0f, 1.0f, 1.0f,
		XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	// ポリゴン描画
	GetDeviceContext()->Draw(4, 0);
}


//=============================================================================
// BG構造体の先頭アドレスを取得
//=============================================================================
MENU_GAME* GetMenuGame(void)
{
	return &g_MenuG;
}





