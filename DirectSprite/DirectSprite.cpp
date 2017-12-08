/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox 
*     All rights reserved.
*
* @file		DirectSprite.cpp
* @brief	This File is DirectSprite DLL Project Header.
* @author	Alopex/Helium
* @version	v1.10a
* @date		2017-11-28	v1.00a	alopex	Create This Project
* @date		2017-12-8	v1.10a	alopex	Code Do Not Rely On MSVCR Library
*/
#include "DirectCommon.h"
#include "DirectSprite.h"

//D3DXSprite精灵(一般用于2D场景渲染)

//------------------------------------------------------------------
// @Function:	 DirectSprite()
// @Purpose: DirectSprite构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectSprite::DirectSprite()
{
	m_pD3D9Device = NULL;		//IDirect3DDevice9接口指针初始化(NULL)
	m_pSpriteTexture = NULL;	//ID3DXSprite表面纹理接口指针初始化(NULL)
	m_pSprite = NULL;			//ID3DXSprite点精灵接口指针初始化(NULL)
}

//------------------------------------------------------------------
// @Function:	 ~DirectSprite()
// @Purpose: DirectSprite析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectSprite::~DirectSprite()
{
	SAFE_RELEASE(m_pSpriteTexture);	//释放m_pSpriteTexture
	SAFE_RELEASE(m_pSprite);		//释放m_pSprite
}

//------------------------------------------------------------------
// @Function:	 DirectSprite(LPDIRECT3DDEVICE9 pD3D9Device)
// @Purpose: DirectSprite构造函数
// @Since: v1.00a
// @Para: LPDIRECT3DDEVICE9 pD3D9Device		//Direct3D接口指针
// @Return: None
//------------------------------------------------------------------
DirectSprite::DirectSprite(LPDIRECT3DDEVICE9 pD3D9Device)
{
	m_pD3D9Device = pD3D9Device;//IDirect3DDevice9接口指针初始化(传入D3D9设备指针)
	m_pSpriteTexture = NULL;	//ID3DXSprite表面纹理接口指针初始化(NULL)
	m_pSprite = NULL;			//ID3DXSprite点精灵接口指针初始化(NULL)
}

//------------------------------------------------------------------
// @Function:	 DirectSpriteInit(LPCWSTR lpszStr)
// @Purpose: DirectSprite初始化函数
// @Since: v1.00a
// @Para: LPCWSTR lpszStr		//精灵纹理路径
// @Return: None
//------------------------------------------------------------------
HRESULT WINAPI DirectSprite::DirectSpriteInit(LPCWSTR lpszStr)
{
	VERIFY(D3DXCreateTextureFromFile(m_pD3D9Device, lpszStr, &m_pSpriteTexture));//D3DXSprite精灵加载纹理
	VERIFY(D3DXCreateSprite(m_pD3D9Device, &m_pSprite));//D3DXSprite精灵创建

	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 DirectSpriteReload(LPCWSTR lpszStr)
// @Purpose: DirectSprite重新加载纹理
// @Since: v1.00a
// @Para: LPCWSTR lpszStr		//精灵纹理路径
// @Return: None
//------------------------------------------------------------------
HRESULT WINAPI DirectSprite::DirectSpriteReload(LPCWSTR lpszStr)
{
	SAFE_RELEASE(m_pSpriteTexture);	//释放m_pSpriteTexture
	SAFE_RELEASE(m_pSprite);		//释放m_pSprite
	VERIFY(D3DXCreateTextureFromFile(m_pD3D9Device, lpszStr, &m_pSpriteTexture));//D3DXSprite精灵加载纹理
	VERIFY(D3DXCreateSprite(m_pD3D9Device, &m_pSprite));//D3DXSprite精灵创建

	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 DirectSpriteBegin(void)
// @Purpose: DirectSprite开始渲染
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT WINAPI DirectSprite::DirectSpriteBegin(void)
{
	VERIFY(m_pSprite->Begin(D3DXSPRITE_ALPHABLEND));
	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 DirectSpriteEnd(void)
// @Purpose: DirectSprite结束渲染
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT WINAPI DirectSprite::DirectSpriteEnd(void)
{
	VERIFY(m_pSprite->End());
	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 DirectSpriteGetTransform(D3DXMATRIX* pMatrix)
// @Purpose: DirectSprite获取当前变换矩阵
// @Since: v1.00a
// @Para: D3DXMATRIX* pMatrix
// @Return: None
//------------------------------------------------------------------
void WINAPI DirectSprite::DirectSpriteGetTransform(D3DXMATRIX* pMatrix)
{
	m_pSprite->GetTransform(pMatrix);
}

//------------------------------------------------------------------
// @Function:	 DirectSpriteSetTransform(D3DXMATRIX* pMatrix)
// @Purpose: DirectSprite设置当前变换矩阵
// @Since: v1.00a
// @Para: D3DXMATRIX* pMatrix
// @Return: None
//------------------------------------------------------------------
void WINAPI DirectSprite::DirectSpriteSetTransform(D3DXMATRIX* pMatrix)
{
	m_pSprite->SetTransform(pMatrix);
}

//----------------------------------------------------------------------
// @Function:	 DirectSpriteDraw(DirectSpriteDrawPara* sSpriteDrawPara)
// @Purpose: DirectSprite设置当前变换矩阵
// @Since: v1.00a
// @Para: DirectSpriteDrawPara* sSpriteDrawPara
// @Return: None
//----------------------------------------------------------------------
void WINAPI DirectSprite::DirectSpriteDraw(DirectSpriteDrawPara* sSpriteDrawPara)
{
	m_pSprite->Draw(m_pSpriteTexture, &(sSpriteDrawPara->SpriteRect), &(sSpriteDrawPara->SpriteCenter), &(sSpriteDrawPara->SpritePosition), sSpriteDrawPara->SpriteColor);
}

//----------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectSpriteDraw(RECT* pSpriteRect, D3DXVECTOR3* pSpriteCenter, D3DXVECTOR3* pSpritePosition, D3DCOLOR SpriteColor)
// @Purpose: DirectSprite绘制精灵
// @Since: v1.00a
// @Para: RECT* pSpriteRect				//绘制矩形区域
// @Para: D3DXVECTOR3* pSpriteCenter	//绘制中心向量
// @Para: D3DXVECTOR3* pSpritePosition	//绘制位置向量
// @Para: D3DCOLOR SpriteColor			//绘制颜色
// @Return: None
//----------------------------------------------------------------------------------------------------------------------------------
void WINAPI DirectSprite::DirectSpriteDraw(RECT* pSpriteRect, D3DXVECTOR3* pSpriteCenter, D3DXVECTOR3* pSpritePosition, D3DCOLOR SpriteColor)
{
	m_pSprite->Draw(m_pSpriteTexture, pSpriteRect, pSpriteCenter, pSpritePosition, SpriteColor);
}

//---------------------------------------------------------------------------------------------------------
// @Function:	 DirectSpriteDrawScale(DirectSpriteDrawPara* sSpriteDrawPara, float fScaleX, float fScaleY)
// @Purpose: DirectSprite绘制拉伸变换
// @Since: v1.00a
// @Para: D3DXMATRIX* pMatrix
// @Return: None
//---------------------------------------------------------------------------------------------------------
void WINAPI DirectSprite::DirectSpriteDrawScale(DirectSpriteDrawPara* sSpriteDrawPara, float fScaleX, float fScaleY)
{
	D3DXMATRIX Matrix;
	D3DXMATRIX MatrixNative;
	D3DXMATRIX MatrixScale;

	m_pSprite->GetTransform(&MatrixNative);
	Matrix = MatrixNative;
	D3DXMatrixScaling(&MatrixScale, fScaleX, fScaleY, 1.0f);
	Matrix = Matrix * MatrixScale;
	m_pSprite->SetTransform(&Matrix);
	m_pSprite->Draw(m_pSpriteTexture, &(sSpriteDrawPara->SpriteRect), &(sSpriteDrawPara->SpriteCenter), &(sSpriteDrawPara->SpritePosition), sSpriteDrawPara->SpriteColor);
	m_pSprite->SetTransform(&MatrixNative);
}

//-----------------------------------------------------------------------------------------------------------------
// @Function:	 DirectSpriteDrawScale(DirectSpriteDrawPara* sSpriteDrawPara, DirectSpriteTransformPara sScalePara)
// @Purpose: DirectSprite绘制拉伸变换
// @Since: v1.00a
// @Para: D3DXMATRIX* pMatrix
// @Return: None
//-----------------------------------------------------------------------------------------------------------------
void WINAPI DirectSprite::DirectSpriteDrawScale(DirectSpriteDrawPara* sSpriteDrawPara, DirectSpriteScale sScalePara)
{
	D3DXMATRIX Matrix;
	D3DXMATRIX MatrixNative;
	D3DXMATRIX MatrixScale;

	m_pSprite->GetTransform(&MatrixNative);
	Matrix = MatrixNative;
	D3DXMatrixScaling(&MatrixScale, sScalePara.fScaleX, sScalePara.fScaleY, 1.0f);
	Matrix = Matrix * MatrixScale;
	m_pSprite->SetTransform(&Matrix);
	m_pSprite->Draw(m_pSpriteTexture, &(sSpriteDrawPara->SpriteRect), &(sSpriteDrawPara->SpriteCenter), &(sSpriteDrawPara->SpritePosition), sSpriteDrawPara->SpriteColor);
	m_pSprite->SetTransform(&MatrixNative);
}

//-----------------------------------------------------------------------------------------------------------------
// @Function:	 DirectSpriteDrawRotate(DirectSpriteDrawPara* sSpriteDrawPara, float fRotateZ)
// @Purpose: DirectSprite绘制旋转变换
// @Since: v1.00a
// @Para: D3DXMATRIX* pMatrix
// @Return: None
//-----------------------------------------------------------------------------------------------------------------
void WINAPI DirectSprite::DirectSpriteDrawRotate(DirectSpriteDrawPara* sSpriteDrawPara, float fRotateZ)
{
	D3DXMATRIX Matrix;
	D3DXMATRIX MatrixNative;
	D3DXMATRIX MatrixRotate;

	m_pSprite->GetTransform(&MatrixNative);
	Matrix = MatrixNative;
	D3DXMatrixRotationZ(&MatrixRotate, fRotateZ);
	Matrix = Matrix * MatrixRotate;
	m_pSprite->SetTransform(&Matrix);
	m_pSprite->Draw(m_pSpriteTexture, &(sSpriteDrawPara->SpriteRect), &(sSpriteDrawPara->SpriteCenter), &(sSpriteDrawPara->SpritePosition), sSpriteDrawPara->SpriteColor);
	m_pSprite->SetTransform(&MatrixNative);
}

//-----------------------------------------------------------------------------------------------------------------
// @Function:	 DirectSpriteDrawRotate(DirectSpriteDrawPara* sSpriteDrawPara, DirectSpriteRotate sRotatePara)
// @Purpose: DirectSprite绘制旋转变换
// @Since: v1.00a
// @Para: D3DXMATRIX* pMatrix
// @Return: None
//-----------------------------------------------------------------------------------------------------------------
void WINAPI DirectSprite::DirectSpriteDrawRotate(DirectSpriteDrawPara* sSpriteDrawPara, DirectSpriteRotate sRotatePara)
{
	D3DXMATRIX Matrix;
	D3DXMATRIX MatrixNative;
	D3DXMATRIX MatrixRotate;

	m_pSprite->GetTransform(&MatrixNative);
	Matrix = MatrixNative;
	D3DXMatrixRotationZ(&MatrixRotate, sRotatePara.fRotateZ);
	Matrix = Matrix * MatrixRotate;
	m_pSprite->SetTransform(&Matrix);
	m_pSprite->Draw(m_pSpriteTexture, &(sSpriteDrawPara->SpriteRect), &(sSpriteDrawPara->SpriteCenter), &(sSpriteDrawPara->SpritePosition), sSpriteDrawPara->SpriteColor);
	m_pSprite->SetTransform(&MatrixNative);
}

//---------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectSpriteDrawTranslate(DirectSpriteDrawPara* sSpriteDrawPara, float fTranslateX, float fTranslateY)
// @Purpose: DirectSprite绘制平移变换
// @Since: v1.00a
// @Para: D3DXMATRIX* pMatrix
// @Return: None
//---------------------------------------------------------------------------------------------------------------------
void WINAPI DirectSprite::DirectSpriteDrawTranslate(DirectSpriteDrawPara* sSpriteDrawPara, float fTranslateX, float fTranslateY)
{
	D3DXMATRIX Matrix;
	D3DXMATRIX MatrixNative;
	D3DXMATRIX MatrixTranslate;
	D3DXMATRIX MatrixInvrsT;

	m_pSprite->GetTransform(&MatrixNative);
	Matrix = MatrixNative;
	D3DXMatrixTranslation(&MatrixTranslate, fTranslateX, fTranslateY, 0.0f);
	D3DXMatrixInverse(&MatrixInvrsT, NULL, &MatrixTranslate);
	Matrix = Matrix * MatrixInvrsT * MatrixTranslate;
	m_pSprite->SetTransform(&Matrix);
	m_pSprite->Draw(m_pSpriteTexture, &(sSpriteDrawPara->SpriteRect), &(sSpriteDrawPara->SpriteCenter), &(sSpriteDrawPara->SpritePosition), sSpriteDrawPara->SpriteColor);
	m_pSprite->SetTransform(&MatrixNative);
}

//-------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectSpriteDrawTranslate(DirectSpriteDrawPara* sSpriteDrawPara, DirectSpriteTransformPara sTransformPara)
// @Purpose: DirectSprite绘制平移变换
// @Since: v1.00a
// @Para: D3DXMATRIX* pMatrix
// @Return: None
//-------------------------------------------------------------------------------------------------------------------------
void WINAPI DirectSprite::DirectSpriteDrawTranslate(DirectSpriteDrawPara* sSpriteDrawPara, DirectSpriteTranslate sTranslatePara)
{
	D3DXMATRIX Matrix;
	D3DXMATRIX MatrixNative;
	D3DXMATRIX MatrixTranslate;
	D3DXMATRIX MatrixInvrsT;

	m_pSprite->GetTransform(&MatrixNative);
	Matrix = MatrixNative;
	D3DXMatrixTranslation(&MatrixTranslate, sTranslatePara.fTranslateX, sTranslatePara.fTranslateY, 0.0f);
	D3DXMatrixInverse(&MatrixInvrsT, NULL, &MatrixTranslate);
	Matrix = Matrix * MatrixInvrsT * MatrixTranslate;
	m_pSprite->SetTransform(&Matrix);
	m_pSprite->Draw(m_pSpriteTexture, &(sSpriteDrawPara->SpriteRect), &(sSpriteDrawPara->SpriteCenter), &(sSpriteDrawPara->SpritePosition), sSpriteDrawPara->SpriteColor);
	m_pSprite->SetTransform(&MatrixNative);
}

//-------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectSpriteDrawTransform(DirectSpriteDrawPara* sSpriteDrawPara, DirectSpriteTransformPara sTransformPara)
// @Purpose: DirectSprite绘制变换矩阵
// @Since: v1.00a
// @Para: D3DXMATRIX* pMatrix
// @Return: None
//-------------------------------------------------------------------------------------------------------------------------
void WINAPI DirectSprite::DirectSpriteDrawTransform(DirectSpriteDrawPara* sSpriteDrawPara, DirectSpriteTransformPara sTransformPara)
{
	D3DXMATRIX Matrix;
	D3DXMATRIX MatrixNative;
	D3DXMATRIX MatrixScale;
	D3DXMATRIX MatrixRotate;
	D3DXMATRIX MatrixTranslate;
	D3DXMATRIX MatrixInvrsT;

	m_pSprite->GetTransform(&MatrixNative);
	Matrix = MatrixNative;
	D3DXMatrixScaling(&MatrixScale, sTransformPara.sScalePara.fScaleX, sTransformPara.sScalePara.fScaleY, 1.0f);
	D3DXMatrixRotationZ(&MatrixRotate, sTransformPara.sRotatePara.fRotateZ);
	D3DXMatrixTranslation(&MatrixTranslate, sTransformPara.sTranslatePara.fTranslateX, sTransformPara.sTranslatePara.fTranslateY, 0.0f);
	D3DXMatrixInverse(&MatrixInvrsT, NULL, &MatrixTranslate);
	Matrix = Matrix * MatrixInvrsT * MatrixScale * MatrixRotate * MatrixTranslate;
	m_pSprite->SetTransform(&Matrix);
	m_pSprite->Draw(m_pSpriteTexture, &(sSpriteDrawPara->SpriteRect), &(sSpriteDrawPara->SpriteCenter), &(sSpriteDrawPara->SpritePosition), sSpriteDrawPara->SpriteColor);
	m_pSprite->SetTransform(&MatrixNative);
}