//=============================================================================
//
// GameMenu���� [menu_game.cpp]
// Author : 
//
//=============================================================================
#include "menu_game.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MENU_GAME_WIDTH				(SCREEN_WIDTH)	// �w�i�T�C�Y
#define MENU_GAME_HEIGHT			(SCREEN_HEIGHT)	// �w�i�T�C�Y
#define MENU_GAME_MAX				(3)				// �e�N�X�`���̐�

#define MENU_GAME_WIDTH_LOGO		(480)			// ���S�T�C�Y
#define MENU_GAME_HEIGHT_LOGO		(80)			// ���S�T�C�Y

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer* g_VertexBuffer = NULL;		// ���_���
static ID3D11ShaderResourceView* g_Texture[MENU_GAME_MAX] = { NULL };	// �e�N�X�`�����

static char* g_TexturName[MENU_GAME_MAX] = {
	"data/TEXTURE/menu_game.png",
	"data/TEXTURE/fade_black.png",
};


static BOOL	g_Menu_Load = FALSE;		// ���������s�������̃t���O
static MENU_GAME	g_MenuG;


//=============================================================================
// ����������
//=============================================================================
HRESULT InitMenuGame(void)
{
	ID3D11Device* pDevice = GetDevice();

	//�e�N�X�`������
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


	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);


	// �ϐ��̏�����
	g_MenuG.w = MENU_GAME_WIDTH;
	g_MenuG.h = MENU_GAME_HEIGHT;
	g_MenuG.pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_MenuG.texNo = 0;

	g_MenuG.flag = false;

	g_Menu_Load = TRUE;
	return S_OK;
}

//=============================================================================
// �I������
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
// �X�V����
//=============================================================================
void UpdateMenuGame(void)
{
	if (GetKeyboardTrigger(DIK_E)) {
		if (g_MenuG.flag == false)	g_MenuG.flag = true;
		else						g_MenuG.flag = false;
	}
	
	if (g_MenuG.flag == false)	ShowCursor(FALSE);	// �J�[�\���̔�\��
	else						ShowCursor(TRUE);	// �J�[�\���̕\��

#ifdef _DEBUG	// �f�o�b�O����\������


#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMenuGame(void)
{
	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �}�g���N�X�ݒ�
	SetWorldViewProjection2D();

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);
	
	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[1]);

	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetSpriteLTColor(g_VertexBuffer,
		0.0f, 0.0f, g_MenuG.w, g_MenuG.h,
		0.0f, 0.0f, 1.0f, 1.0f,
		XMFLOAT4(1.0f, 1.0f, 1.0f, 0.8f));

	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[g_MenuG.texNo]);

	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetSpriteLTColor(g_VertexBuffer,
		0.0f, 0.0f, g_MenuG.w, g_MenuG.h,
		0.0f, 0.0f, 1.0f, 1.0f,
		XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);
}


//=============================================================================
// BG�\���̂̐擪�A�h���X���擾
//=============================================================================
MENU_GAME* GetMenuGame(void)
{
	return &g_MenuG;
}





