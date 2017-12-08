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

//D3DXSprite����(һ������2D������Ⱦ)

//------------------------------------------------------------------
// @Function:	 DirectSprite()
// @Purpose: DirectSprite���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectSprite::DirectSprite()
{
	m_pD3D9Device = NULL;		//IDirect3DDevice9�ӿ�ָ���ʼ��(NULL)
	m_pSpriteTexture = NULL;	//ID3DXSprite��������ӿ�ָ���ʼ��(NULL)
	m_pSprite = NULL;			//ID3DXSprite�㾫��ӿ�ָ���ʼ��(NULL)
}

//------------------------------------------------------------------
// @Function:	 ~DirectSprite()
// @Purpose: DirectSprite��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectSprite::~DirectSprite()
{
	SAFE_RELEASE(m_pSpriteTexture);	//�ͷ�m_pSpriteTexture
	SAFE_RELEASE(m_pSprite);		//�ͷ�m_pSprite
}

//------------------------------------------------------------------
// @Function:	 DirectSprite(LPDIRECT3DDEVICE9 pD3D9Device)
// @Purpose: DirectSprite���캯��
// @Since: v1.00a
// @Para: LPDIRECT3DDEVICE9 pD3D9Device		//Direct3D�ӿ�ָ��
// @Return: None
//------------------------------------------------------------------
DirectSprite::DirectSprite(LPDIRECT3DDEVICE9 pD3D9Device)
{
	m_pD3D9Device = pD3D9Device;//IDirect3DDevice9�ӿ�ָ���ʼ��(����D3D9�豸ָ��)
	m_pSpriteTexture = NULL;	//ID3DXSprite��������ӿ�ָ���ʼ��(NULL)
	m_pSprite = NULL;			//ID3DXSprite�㾫��ӿ�ָ���ʼ��(NULL)
}

//------------------------------------------------------------------
// @Function:	 DirectSpriteInit(LPCWSTR lpszStr)
// @Purpose: DirectSprite��ʼ������
// @Since: v1.00a
// @Para: LPCWSTR lpszStr		//��������·��
// @Return: None
//------------------------------------------------------------------
HRESULT WINAPI DirectSprite::DirectSpriteInit(LPCWSTR lpszStr)
{
	VERIFY(D3DXCreateTextureFromFile(m_pD3D9Device, lpszStr, &m_pSpriteTexture));//D3DXSprite�����������
	VERIFY(D3DXCreateSprite(m_pD3D9Device, &m_pSprite));//D3DXSprite���鴴��

	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 DirectSpriteReload(LPCWSTR lpszStr)
// @Purpose: DirectSprite���¼�������
// @Since: v1.00a
// @Para: LPCWSTR lpszStr		//��������·��
// @Return: None
//------------------------------------------------------------------
HRESULT WINAPI DirectSprite::DirectSpriteReload(LPCWSTR lpszStr)
{
	SAFE_RELEASE(m_pSpriteTexture);	//�ͷ�m_pSpriteTexture
	SAFE_RELEASE(m_pSprite);		//�ͷ�m_pSprite
	VERIFY(D3DXCreateTextureFromFile(m_pD3D9Device, lpszStr, &m_pSpriteTexture));//D3DXSprite�����������
	VERIFY(D3DXCreateSprite(m_pD3D9Device, &m_pSprite));//D3DXSprite���鴴��

	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 DirectSpriteBegin(void)
// @Purpose: DirectSprite��ʼ��Ⱦ
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
// @Purpose: DirectSprite������Ⱦ
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
// @Purpose: DirectSprite��ȡ��ǰ�任����
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
// @Purpose: DirectSprite���õ�ǰ�任����
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
// @Purpose: DirectSprite���õ�ǰ�任����
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
// @Purpose: DirectSprite���ƾ���
// @Since: v1.00a
// @Para: RECT* pSpriteRect				//���ƾ�������
// @Para: D3DXVECTOR3* pSpriteCenter	//������������
// @Para: D3DXVECTOR3* pSpritePosition	//����λ������
// @Para: D3DCOLOR SpriteColor			//������ɫ
// @Return: None
//----------------------------------------------------------------------------------------------------------------------------------
void WINAPI DirectSprite::DirectSpriteDraw(RECT* pSpriteRect, D3DXVECTOR3* pSpriteCenter, D3DXVECTOR3* pSpritePosition, D3DCOLOR SpriteColor)
{
	m_pSprite->Draw(m_pSpriteTexture, pSpriteRect, pSpriteCenter, pSpritePosition, SpriteColor);
}

//---------------------------------------------------------------------------------------------------------
// @Function:	 DirectSpriteDrawScale(DirectSpriteDrawPara* sSpriteDrawPara, float fScaleX, float fScaleY)
// @Purpose: DirectSprite��������任
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
// @Purpose: DirectSprite��������任
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
// @Purpose: DirectSprite������ת�任
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
// @Purpose: DirectSprite������ת�任
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
// @Purpose: DirectSprite����ƽ�Ʊ任
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
// @Purpose: DirectSprite����ƽ�Ʊ任
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
// @Purpose: DirectSprite���Ʊ任����
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