//=============================================================================
//
// 当たり判定処理 [ bounding_area.h ]
// Author : Keisuke Haga
//
//=============================================================================
#pragma once


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

BOOL AxisAlignedBoundingBox(XMFLOAT3 pos1, float w1, float h1,
							XMFLOAT3 pos2, float w2, float h2);

BOOL BoundingCircle(XMFLOAT3 pos1, float r1,
					XMFLOAT3 pos2, float r2);

BOOL BoundingTriangle(XMFLOAT3 pos1, float len1,
					  XMFLOAT3 pos2, float len2);

BOOL BoundingCircleAndBox(XMFLOAT3 pos1, float r1,
						  XMFLOAT3 pos2, float w2, float h2);
