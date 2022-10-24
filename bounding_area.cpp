//=============================================================================
//
// 衝突判定処理 [ bounding_area.cpp ]
// Author : Keisuke Haga
//
//=============================================================================
#include "main.h"
#include "bounding_area.h"


//=============================================================================
// AABBによる衝突判定処理
// ２次元座標系に依存し、回転等は考慮しない
// 戻り値：衝突時にTRUE
//=============================================================================
BOOL AxisAlignedBoundingBox(XMFLOAT3 pos1, float w1, float h1,
							XMFLOAT3 pos2, float w2, float h2)
{
	BOOL ans = FALSE;	// 初期値はFALSE

	// 矩形中心点から各辺への距離
	w1 *= 0.5f;
	h1 *= 0.5f;
	w2 *= 0.5f;
	h2 *= 0.5f;

	// 衝突判定処理
	if ((pos1.x + w1 > pos2.x - w2) &&
		(pos1.x - w1 < pos2.x + w2) &&
		(pos1.y + h1 > pos2.y - h2) &&
		(pos1.y - h1 < pos2.y + h2))
		ans = TRUE;	// 衝突時処理

	return ans;
}


//=============================================================================
// BCによる衝突判定処理
// 各円の大きさは任意の各半径
// 戻り値：衝突時にTRUE
//=============================================================================
BOOL BoundingCircle(XMFLOAT3 pos1, float r1,
					XMFLOAT3 pos2, float r2)
{
	BOOL ans = FALSE;	// 初期値はFALSE

	float len = (r1 + r2) * (r1 + r2);		// 半径の２乗
	XMVECTOR temp = XMLoadFloat3(&pos1) - XMLoadFloat3(&pos2);
	temp = XMVector3LengthSq(temp);			// ２点間の距離（２乗）
	float lenSq = 0.0f;
	XMStoreFloat(&lenSq, temp);

	// 半径の２乗より距離が短い
	if (len > lenSq) ans = TRUE;	// 衝突時処理

	return ans;
}


//=============================================================================
// AABTによる衝突判定処理
// 正三角形のみで、大きさは中心点から各点への長さ
// 底辺が２次元座標系に依存し、回転等は考慮しない
// 戻り値：衝突時にTRUE
//=============================================================================
BOOL BoundingTriangle(XMFLOAT3 pos1, float len1,
					  XMFLOAT3 pos2, float len2)
{
	BOOL ans = FALSE;	// 初期値はFALSE

	// 各三角形の各頂点
	XMFLOAT3 pos1up, pos1lt, pos1rt, pos2up, pos2lt, pos2rt;

	// 各三角形の各頂点までの距離に必要な長さ
	float y1 = (len1 * 0.5f);
	float x1 = sqrtf(y1 * 3);

	float y2 = (len2 * 0.5f);
	float x2 = sqrtf(y2 * 3);

	// 各三角形の各頂点座標計算
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


	// 外積計算
	// Vec = Vector
	// up  = upper
	// lr  = lower
	// lt  = left
	// rt  = right

	// 三角形２の上点
	float Vec1rt_pos2up = ((pos1rt.x - pos1up.x) * (pos2up.y - pos1up.y)) - ((pos2up.x - pos1up.x) * (pos1rt.y - pos1up.y));	// 三角形１右斜辺
	float Vec1lt_pos2up = ((pos1lt.x - pos1rt.x) * (pos2up.y - pos1rt.y)) - ((pos2up.x - pos1rt.x) * (pos1lt.y - pos1rt.y));	// 三角形１左斜辺
	float Vec1lr_pos2up = ((pos1up.x - pos1lt.x) * (pos2up.y - pos1lt.y)) - ((pos2up.x - pos1lt.x) * (pos1up.y - pos1lt.y));	// 三角形１下辺

	// 三角形２の左点
	float Vec1rt_pos2lt = ((pos1rt.x - pos1up.x) * (pos2lt.y - pos1up.y)) - ((pos2lt.x - pos1up.x) * (pos1rt.y - pos1up.y));	// 三角形１右斜辺
	float Vec1lt_pos2lt = ((pos1lt.x - pos1rt.x) * (pos2lt.y - pos1rt.y)) - ((pos2lt.x - pos1rt.x) * (pos1lt.y - pos1rt.y));	// 三角形１左斜辺
	float Vec1lr_pos2lt = ((pos1up.x - pos1lt.x) * (pos2lt.y - pos1lt.y)) - ((pos2lt.x - pos1lt.x) * (pos1up.y - pos1lt.y));	// 三角形１下辺

	// 三角形２の右点
	float Vec1rt_pos2rt = ((pos1rt.x - pos1up.x) * (pos2rt.y - pos1up.y)) - ((pos2rt.x - pos1up.x) * (pos1rt.y - pos1up.y));	// 三角形１右斜辺
	float Vec1lt_pos2rt = ((pos1lt.x - pos1rt.x) * (pos2rt.y - pos1rt.y)) - ((pos2rt.x - pos1rt.x) * (pos1lt.y - pos1rt.y));	// 三角形１左斜辺
	float Vec1lr_pos2rt = ((pos1up.x - pos1lt.x) * (pos2rt.y - pos1lt.y)) - ((pos2rt.x - pos1lt.x) * (pos1up.y - pos1lt.y));	// 三角形１下辺

	// 三角形１の上点
	float Vec2rt_pos1up = ((pos2rt.x - pos2up.x) * (pos1up.y - pos2up.y)) - ((pos1up.x - pos2up.x) * (pos2rt.y - pos2up.y));	// 三角形２右斜辺
	float Vec2lt_pos1up = ((pos2lt.x - pos2rt.x) * (pos1up.y - pos2rt.y)) - ((pos1up.x - pos2rt.x) * (pos2lt.y - pos2rt.y));	// 三角形２左斜辺
	float Vec2lr_pos1up = ((pos2up.x - pos2lt.x) * (pos1up.y - pos2lt.y)) - ((pos1up.x - pos2lt.x) * (pos2up.y - pos2lt.y));	// 三角形２下辺

	// 三角形１の左点
	float Vec2rt_pos1lt = ((pos2rt.x - pos2up.x) * (pos1lt.y - pos2up.y)) - ((pos1lt.x - pos2up.x) * (pos2rt.y - pos2up.y));	// 三角形２右斜辺
	float Vec2lt_pos1lt = ((pos2lt.x - pos2rt.x) * (pos1lt.y - pos2rt.y)) - ((pos1lt.x - pos2rt.x) * (pos2lt.y - pos2rt.y));	// 三角形２左斜辺
	float Vec2lr_pos1lt = ((pos2up.x - pos2lt.x) * (pos1lt.y - pos2lt.y)) - ((pos1lt.x - pos2lt.x) * (pos2up.y - pos2lt.y));	// 三角形２下辺

	// 三角形１の右点
	float Vec2rt_pos1rt = ((pos2rt.x - pos2up.x) * (pos1rt.y - pos2up.y)) - ((pos1rt.x - pos2up.x) * (pos2rt.y - pos2up.y));	// 三角形２右斜辺
	float Vec2lt_pos1rt = ((pos2lt.x - pos2rt.x) * (pos1rt.y - pos2rt.y)) - ((pos1rt.x - pos2rt.x) * (pos2lt.y - pos2rt.y));	// 三角形２左斜辺
	float Vec2lr_pos1rt = ((pos2up.x - pos2lt.x) * (pos1rt.y - pos2lt.y)) - ((pos1rt.x - pos2lt.x) * (pos2up.y - pos2lt.y));	// 三角形２下辺


	// 任意の三角形の頂点が１つでも他方の三角形の３つの辺全てより右にある場合、衝突
	if ((((Vec1rt_pos2up) < 0.0f) && ((Vec1lt_pos2up) < 0.0f) && ((Vec1lr_pos2up) < 0.0f)) ||
		(((Vec1rt_pos2lt) < 0.0f) && ((Vec1lt_pos2lt) < 0.0f) && ((Vec1lr_pos2lt) < 0.0f)) ||
		(((Vec1rt_pos2rt) < 0.0f) && ((Vec1lt_pos2rt) < 0.0f) && ((Vec1lr_pos2rt) < 0.0f)) ||
		(((Vec2rt_pos1up) < 0.0f) && ((Vec2lt_pos1up) < 0.0f) && ((Vec2lr_pos1up) < 0.0f)) ||
		(((Vec2rt_pos1lt) < 0.0f) && ((Vec2lt_pos1lt) < 0.0f) && ((Vec2lr_pos1lt) < 0.0f)) ||
		(((Vec2rt_pos1rt) < 0.0f) && ((Vec2lt_pos1rt) < 0.0f) && ((Vec2lr_pos1rt) < 0.0f)))
		ans = TRUE;	// 衝突時処理


	return ans;
}


//=============================================================================
// AABBとBCによる衝突判定処理
// ２次元座標系に依存し、回転等は考慮しない
// 戻り値：衝突時にTRUE
//=============================================================================
BOOL BoundingCircleAndBox(XMFLOAT3 pos1, float r1,
						  XMFLOAT3 pos2, float w2, float h2)
{
	// 矩形中心点から各辺への距離
	w2 *= 0.5f;
	h2 *= 0.5f;

	// 衝突判定処理, 縦長
	if ((pos1.y < (pos2.y - h2 - r1)) &&
		(pos1.y > (pos2.y + h2 + r1)) &&
		(pos1.x > (pos2.x - w2)) &&
		(pos1.x < (pos2.x + w2)))
		return TRUE;

	// 衝突判定処理, 横長
	if ((pos1.y < (pos2.y - h2)) &&
		(pos1.y > (pos2.y + h2)) &&
		(pos1.x > (pos2.x - w2 - r1)) &&
		(pos1.x < (pos2.x + w2 + r1)))
		return TRUE;

	// 矩形の各頂点
	XMFLOAT3 UL, UR, LL, LR;

	// 矩形の各頂点の計算
	UL.x = pos2.x - w2;
	UL.y = pos2.y - h2;

	UR.x = pos2.x + w2;
	UR.y = pos2.y - h2;

	LL.x = pos2.x - w2;
	LL.y = pos2.y + h2;

	LR.x = pos2.x + w2;
	LR.y = pos2.y + h2;


	//各頂点の周囲に円があるかどうかの判定
	{
		XMVECTOR temp = XMLoadFloat3(&pos1) - XMLoadFloat3(&UL);
		temp = XMVector3LengthSq(temp);			// ２点間の距離（２乗）
		float lenSq = 0.0f;
		XMStoreFloat(&lenSq, temp);
		// 半径の２乗より距離が短い
		if (r1 > lenSq) return TRUE;	// 衝突時処理

		temp = XMLoadFloat3(&pos1) - XMLoadFloat3(&UR);
		temp = XMVector3LengthSq(temp);			// ２点間の距離（２乗）
		lenSq = 0.0f;
		XMStoreFloat(&lenSq, temp);
		// 半径の２乗より距離が短い
		if (r1 > lenSq) return TRUE;	// 衝突時処理
	
		temp = XMLoadFloat3(&pos1) - XMLoadFloat3(&LL);
		temp = XMVector3LengthSq(temp);			// ２点間の距離（２乗）
		lenSq = 0.0f;
		XMStoreFloat(&lenSq, temp);
		// 半径の２乗より距離が短い
		if (r1 > lenSq) return TRUE;	// 衝突時処理

		temp = XMLoadFloat3(&pos1) - XMLoadFloat3(&LR);
		temp = XMVector3LengthSq(temp);			// ２点間の距離（２乗）
		lenSq = 0.0f;
		XMStoreFloat(&lenSq, temp);
		// 半径の２乗より距離が短い
		if (r1 > lenSq) return TRUE;	// 衝突時処理

	}

	return FALSE;	// 最後まで処理されれば未衝突
}
