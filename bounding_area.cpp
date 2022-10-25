//=============================================================================
//
// �Փ˔��菈�� [ bounding_area.cpp ]
// Author : Keisuke Haga
//
//=============================================================================
#include "main.h"
#include "bounding_area.h"


//=============================================================================
// AABB�ɂ��Փ˔��菈��
// �Q�������W�n�Ɉˑ����A��]���͍l�����Ȃ�
// �߂�l�F�Փˎ���TRUE
//=============================================================================
BOOL AxisAlignedBoundingBox(XMFLOAT3 pos1, float w1, float h1,
							XMFLOAT3 pos2, float w2, float h2)
{
	BOOL ans = FALSE;	// �����l��FALSE

	// ��`���S�_����e�ӂւ̋���
	w1 *= 0.5f;
	h1 *= 0.5f;
	w2 *= 0.5f;
	h2 *= 0.5f;

	// �Փ˔��菈��
	if ((pos1.x + w1 > pos2.x - w2) &&
		(pos1.x - w1 < pos2.x + w2) &&
		(pos1.y + h1 > pos2.y - h2) &&
		(pos1.y - h1 < pos2.y + h2))
		ans = TRUE;	// �Փˎ�����

	return ans;
}


//=============================================================================
// BC�ɂ��Փ˔��菈��
// �e�~�̑傫���͔C�ӂ̊e���a
// �߂�l�F�Փˎ���TRUE
//=============================================================================
BOOL BoundingCircle(XMFLOAT3 pos1, float r1,
					XMFLOAT3 pos2, float r2)
{
	BOOL ans = FALSE;	// �����l��FALSE

	float len = (r1 + r2) * (r1 + r2);		// ���a�̂Q��
	XMVECTOR temp = XMLoadFloat3(&pos1) - XMLoadFloat3(&pos2);
	temp = XMVector3LengthSq(temp);			// �Q�_�Ԃ̋����i�Q��j
	float lenSq = 0.0f;
	XMStoreFloat(&lenSq, temp);

	// ���a�̂Q���苗�����Z��
	if (len > lenSq) ans = TRUE;	// �Փˎ�����

	return ans;
}


//=============================================================================
// AABT�ɂ��Փ˔��菈��
// ���O�p�`�݂̂ŁA�傫���͒��S�_����e�_�ւ̒���
// ��ӂ��Q�������W�n�Ɉˑ����A��]���͍l�����Ȃ�
// �߂�l�F�Փˎ���TRUE
//=============================================================================
BOOL BoundingTriangle(XMFLOAT3 pos1, float len1,
					  XMFLOAT3 pos2, float len2)
{
	BOOL ans = FALSE;	// �����l��FALSE

	// �e�O�p�`�̊e���_
	XMFLOAT3 pos1up, pos1lt, pos1rt, pos2up, pos2lt, pos2rt;

	// �e�O�p�`�̊e���_�܂ł̋����ɕK�v�Ȓ���
	float y1 = (len1 * 0.5f);
	float x1 = sqrtf(y1 * 3);

	float y2 = (len2 * 0.5f);
	float x2 = sqrtf(y2 * 3);

	// �e�O�p�`�̊e���_���W�v�Z
	// pos = position
	// up  = upper
	// lt  = left
	// rt  = right
	pos1up.x = pos1.x;
	pos1up.y = pos1.y - len1;
	pos1lt.y = pos1.y + y1;
	pos1lt.x = pos1.x - x1;
	pos1rt.y = pos1.y + y1;
	pos1rt.x = pos1.x + x1;

	pos2up.x = pos2.x;
	pos2up.y = pos2.y - len2;
	pos2lt.y = pos2.y + y1;
	pos2lt.x = pos2.x - x1;
	pos2rt.y = pos2.y + y1;
	pos2rt.x = pos2.x + x1;


	// �O�όv�Z
	// Vec = Vector
	// up  = upper
	// lr  = lower
	// lt  = left
	// rt  = right

	// �O�p�`�Q�̏�_
	float Vec1rt_pos2up = ((pos1rt.x - pos1up.x) * (pos2up.y - pos1up.y)) - ((pos2up.x - pos1up.x) * (pos1rt.y - pos1up.y));	// �O�p�`�P�E�Ε�
	float Vec1lt_pos2up = ((pos1lt.x - pos1rt.x) * (pos2up.y - pos1rt.y)) - ((pos2up.x - pos1rt.x) * (pos1lt.y - pos1rt.y));	// �O�p�`�P���Ε�
	float Vec1lr_pos2up = ((pos1up.x - pos1lt.x) * (pos2up.y - pos1lt.y)) - ((pos2up.x - pos1lt.x) * (pos1up.y - pos1lt.y));	// �O�p�`�P����

	// �O�p�`�Q�̍��_
	float Vec1rt_pos2lt = ((pos1rt.x - pos1up.x) * (pos2lt.y - pos1up.y)) - ((pos2lt.x - pos1up.x) * (pos1rt.y - pos1up.y));	// �O�p�`�P�E�Ε�
	float Vec1lt_pos2lt = ((pos1lt.x - pos1rt.x) * (pos2lt.y - pos1rt.y)) - ((pos2lt.x - pos1rt.x) * (pos1lt.y - pos1rt.y));	// �O�p�`�P���Ε�
	float Vec1lr_pos2lt = ((pos1up.x - pos1lt.x) * (pos2lt.y - pos1lt.y)) - ((pos2lt.x - pos1lt.x) * (pos1up.y - pos1lt.y));	// �O�p�`�P����

	// �O�p�`�Q�̉E�_
	float Vec1rt_pos2rt = ((pos1rt.x - pos1up.x) * (pos2rt.y - pos1up.y)) - ((pos2rt.x - pos1up.x) * (pos1rt.y - pos1up.y));	// �O�p�`�P�E�Ε�
	float Vec1lt_pos2rt = ((pos1lt.x - pos1rt.x) * (pos2rt.y - pos1rt.y)) - ((pos2rt.x - pos1rt.x) * (pos1lt.y - pos1rt.y));	// �O�p�`�P���Ε�
	float Vec1lr_pos2rt = ((pos1up.x - pos1lt.x) * (pos2rt.y - pos1lt.y)) - ((pos2rt.x - pos1lt.x) * (pos1up.y - pos1lt.y));	// �O�p�`�P����

	// �O�p�`�P�̏�_
	float Vec2rt_pos1up = ((pos2rt.x - pos2up.x) * (pos1up.y - pos2up.y)) - ((pos1up.x - pos2up.x) * (pos2rt.y - pos2up.y));	// �O�p�`�Q�E�Ε�
	float Vec2lt_pos1up = ((pos2lt.x - pos2rt.x) * (pos1up.y - pos2rt.y)) - ((pos1up.x - pos2rt.x) * (pos2lt.y - pos2rt.y));	// �O�p�`�Q���Ε�
	float Vec2lr_pos1up = ((pos2up.x - pos2lt.x) * (pos1up.y - pos2lt.y)) - ((pos1up.x - pos2lt.x) * (pos2up.y - pos2lt.y));	// �O�p�`�Q����

	// �O�p�`�P�̍��_
	float Vec2rt_pos1lt = ((pos2rt.x - pos2up.x) * (pos1lt.y - pos2up.y)) - ((pos1lt.x - pos2up.x) * (pos2rt.y - pos2up.y));	// �O�p�`�Q�E�Ε�
	float Vec2lt_pos1lt = ((pos2lt.x - pos2rt.x) * (pos1lt.y - pos2rt.y)) - ((pos1lt.x - pos2rt.x) * (pos2lt.y - pos2rt.y));	// �O�p�`�Q���Ε�
	float Vec2lr_pos1lt = ((pos2up.x - pos2lt.x) * (pos1lt.y - pos2lt.y)) - ((pos1lt.x - pos2lt.x) * (pos2up.y - pos2lt.y));	// �O�p�`�Q����

	// �O�p�`�P�̉E�_
	float Vec2rt_pos1rt = ((pos2rt.x - pos2up.x) * (pos1rt.y - pos2up.y)) - ((pos1rt.x - pos2up.x) * (pos2rt.y - pos2up.y));	// �O�p�`�Q�E�Ε�
	float Vec2lt_pos1rt = ((pos2lt.x - pos2rt.x) * (pos1rt.y - pos2rt.y)) - ((pos1rt.x - pos2rt.x) * (pos2lt.y - pos2rt.y));	// �O�p�`�Q���Ε�
	float Vec2lr_pos1rt = ((pos2up.x - pos2lt.x) * (pos1rt.y - pos2lt.y)) - ((pos1rt.x - pos2lt.x) * (pos2up.y - pos2lt.y));	// �O�p�`�Q����


	// �C�ӂ̎O�p�`�̒��_���P�ł������̎O�p�`�̂R�̕ӑS�Ă��E�ɂ���ꍇ�A�Փ�
	if ((((Vec1rt_pos2up) < 0.0f) && ((Vec1lt_pos2up) < 0.0f) && ((Vec1lr_pos2up) < 0.0f)) ||
		(((Vec1rt_pos2lt) < 0.0f) && ((Vec1lt_pos2lt) < 0.0f) && ((Vec1lr_pos2lt) < 0.0f)) ||
		(((Vec1rt_pos2rt) < 0.0f) && ((Vec1lt_pos2rt) < 0.0f) && ((Vec1lr_pos2rt) < 0.0f)) ||
		(((Vec2rt_pos1up) < 0.0f) && ((Vec2lt_pos1up) < 0.0f) && ((Vec2lr_pos1up) < 0.0f)) ||
		(((Vec2rt_pos1lt) < 0.0f) && ((Vec2lt_pos1lt) < 0.0f) && ((Vec2lr_pos1lt) < 0.0f)) ||
		(((Vec2rt_pos1rt) < 0.0f) && ((Vec2lt_pos1rt) < 0.0f) && ((Vec2lr_pos1rt) < 0.0f)))
		ans = TRUE;	// �Փˎ�����


	return ans;
}


//=============================================================================
// AABB��BC�ɂ��Փ˔��菈��
// �Q�������W�n�Ɉˑ����A��]���͍l�����Ȃ�
// �߂�l�F�Փˎ���TRUE
//=============================================================================
BOOL BoundingCircleAndBox(XMFLOAT3 pos1, float r1,
						  XMFLOAT3 pos2, float w2, float h2)
{
	// ��`���S�_����e�ӂւ̋���
	w2 *= 0.5f;
	h2 *= 0.5f;

	// �Փ˔��菈��, �c��
	if ((pos1.y < (pos2.y - h2 - r1)) &&
		(pos1.y > (pos2.y + h2 + r1)) &&
		(pos1.x > (pos2.x - w2)) &&
		(pos1.x < (pos2.x + w2)))
		return TRUE;

	// �Փ˔��菈��, ����
	if ((pos1.y < (pos2.y - h2)) &&
		(pos1.y > (pos2.y + h2)) &&
		(pos1.x > (pos2.x - w2 - r1)) &&
		(pos1.x < (pos2.x + w2 + r1)))
		return TRUE;

	// ��`�̊e���_
	XMFLOAT3 UL, UR, LL, LR;

	// ��`�̊e���_�̌v�Z
	UL.x = pos2.x - w2;
	UL.y = pos2.y - h2;

	UR.x = pos2.x + w2;
	UR.y = pos2.y - h2;

	LL.x = pos2.x - w2;
	LL.y = pos2.y + h2;

	LR.x = pos2.x + w2;
	LR.y = pos2.y + h2;


	//�e���_�̎��͂ɉ~�����邩�ǂ����̔���
	{
		XMVECTOR temp = XMLoadFloat3(&pos1) - XMLoadFloat3(&UL);
		temp = XMVector3LengthSq(temp);			// �Q�_�Ԃ̋����i�Q��j
		float lenSq = 0.0f;
		XMStoreFloat(&lenSq, temp);
		// ���a�̂Q���苗�����Z��
		if (r1 > lenSq) return TRUE;	// �Փˎ�����

		temp = XMLoadFloat3(&pos1) - XMLoadFloat3(&UR);
		temp = XMVector3LengthSq(temp);			// �Q�_�Ԃ̋����i�Q��j
		lenSq = 0.0f;
		XMStoreFloat(&lenSq, temp);
		// ���a�̂Q���苗�����Z��
		if (r1 > lenSq) return TRUE;	// �Փˎ�����
	
		temp = XMLoadFloat3(&pos1) - XMLoadFloat3(&LL);
		temp = XMVector3LengthSq(temp);			// �Q�_�Ԃ̋����i�Q��j
		lenSq = 0.0f;
		XMStoreFloat(&lenSq, temp);
		// ���a�̂Q���苗�����Z��
		if (r1 > lenSq) return TRUE;	// �Փˎ�����

		temp = XMLoadFloat3(&pos1) - XMLoadFloat3(&LR);
		temp = XMVector3LengthSq(temp);			// �Q�_�Ԃ̋����i�Q��j
		lenSq = 0.0f;
		XMStoreFloat(&lenSq, temp);
		// ���a�̂Q���苗�����Z��
		if (r1 > lenSq) return TRUE;	// �Փˎ�����

	}

	return FALSE;	// �Ō�܂ŏ��������Ζ��Փ�
}
