//=============================================================================
//
// �X�R�A���� [score.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "score.h"
#include "sprite.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_WIDTH				(16)	// �L�����T�C�Y
#define TEXTURE_HEIGHT				(32)	// 
#define TEXTURE_MAX					(2)		// �e�N�X�`���̐�


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer				*g_VertexBuffer = NULL;		// ���_���
static ID3D11ShaderResourceView	*g_Texture[TEXTURE_MAX] = { NULL };	// �e�N�X�`�����

static char *g_TexturName[] = {
	"data/TEXTURE/number16x32.png",
	"data/TEXTURE/number16x32.png",
};


static bool						g_Use;						// true:�g���Ă���  false:���g�p
static float					g_w, g_h;					// ���ƍ���
static XMFLOAT3					g_Pos0;						// �|���S���̍��W
static XMFLOAT3					g_Pos1;						// �|���S���̍��W
static int						g_TexNo;					// �e�N�X�`���ԍ�


static int						g_Score;						// �X�R�A
static int						g_KillScore;					// ���j�X�R�A
static int						g_KillassScore;					// ���j�⏕�X�R�A
static int						g_ShootScore;					// ���˃X�R�A
static int						g_HitScore;						// �����X�R�A

//static SCORE	g_Score[SCORE_MAX];	// �X�R�A�\����



//=============================================================================
// ����������
//=============================================================================
HRESULT InitScore(void)
{
	ID3D11Device *pDevice = GetDevice();

	//�e�N�X�`������
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


	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);


	// �v���C���[�̏�����
	g_Use   = true;
	g_w     = TEXTURE_WIDTH;
	g_h     = TEXTURE_HEIGHT;
	g_Pos0  = { 900.0f, 60.0f, 0.0f };
	g_Pos1  = { 900.0f, 100.0f, 0.0f };
	g_TexNo = 0;




	// �X�R�A�̏�����
	g_Score = 0;
	g_KillScore = 0;
	g_KillassScore = 0;
	g_ShootScore = 0;
	g_HitScore = 0;

	return S_OK;
}

//=============================================================================
// �I������
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
// �X�V����
//=============================================================================
void UpdateScore(void)
{


#ifdef _DEBUG	// �f�o�b�O����\������
	//char *str = GetDebugStr();
	//sprintf(&str[strlen(str)], " PX:%.2f PY:%.2f", g_Pos.x, g_Pos.y);
	
#endif

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawScore(void)
{
	{
		// ���_�o�b�t�@�ݒ�
		UINT stride0 = sizeof(VERTEX_3D);
		UINT offset0 = 0;
		GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride0, &offset0);

		// �}�g���N�X�ݒ�
		SetWorldViewProjection2D();

		// �v���~�e�B�u�g�|���W�ݒ�
		GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		// �}�e���A���ݒ�
		MATERIAL material;
		ZeroMemory(&material, sizeof(material));
		material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		SetMaterial(material);

		// �X�R�A�\��
		{
			// �e�N�X�`���ݒ�
			GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[0]);

			// ��������������
			int number0 = g_Score;
			for (int i = 0; i < SCORE_DIGIT; i++)
			{
				// ����\�����錅�̐���
				float x = (float)(number0 % 10);

				// �X�R�A�̈ʒu��e�N�X�`���[���W�𔽉f
				float px = g_Pos0.x - g_w * i;	// �X�R�A�̕\���ʒuX
				float py = g_Pos0.y;			// �X�R�A�̕\���ʒuY
				float pw = g_w;				// �X�R�A�̕\����
				float ph = g_h;				// �X�R�A�̕\������

				float tw = 1.0f / 10;		// �e�N�X�`���̕�
				float th = 1.0f / 1;		// �e�N�X�`���̍���
				float tx = x * tw;			// �e�N�X�`���̍���X���W
				float ty = 0.0f;			// �e�N�X�`���̍���Y���W

				// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
				SetSpriteColor(g_VertexBuffer, px, py, pw, ph, tx, ty, tw, th,
					XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

				// �|���S���`��
				GetDeviceContext()->Draw(4, 0);

				// ���̌���
				number0 /= 10;
			}
		}

		// �L�����\��
		{
			// �e�N�X�`���ݒ�
			GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[1]);

			// ��������������
			int number1 = g_KillScore;
			for (int i = 0; i < SCORE_DIGIT; i++)
			{
				// ����\�����錅�̐���
				float x = (float)(number1 % 10);

				// �X�R�A�̈ʒu��e�N�X�`���[���W�𔽉f
				float px = g_Pos1.x - g_w * i;	// �X�R�A�̕\���ʒuX
				float py = g_Pos1.y;			// �X�R�A�̕\���ʒuY
				float pw = g_w;				// �X�R�A�̕\����
				float ph = g_h;				// �X�R�A�̕\������

				float tw = 1.0f / 10;		// �e�N�X�`���̕�
				float th = 1.0f / 1;		// �e�N�X�`���̍���
				float tx = x * tw;			// �e�N�X�`���̍���X���W
				float ty = 0.0f;			// �e�N�X�`���̍���Y���W

				// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
				SetSpriteColor(g_VertexBuffer, px, py, pw, ph, tx, ty, tw, th,
					XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

				// �|���S���`��
				GetDeviceContext()->Draw(4, 0);

				// ���̌���
				number1 /= 10;
			}
		}

	}

}


//=============================================================================
// �X�R�A�����Z����
// ����:add :�ǉ�����_���B�}�C�i�X���\
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


