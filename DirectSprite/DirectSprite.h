/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox 
*     All rights reserved.
*
* @file		DirectSprite.h
* @brief	This File is DirectSprite DLL Project Header.
* @author	Alopex/Helium
* @version	v1.10a
* @date		2017-11-28	v1.00a	alopex	Create This Project
* @date		2017-12-8	v1.10a	alopex	Code Do Not Rely On MSVCR Library
*/
#pragma once

#ifndef __DIRECTSPRITE_H_
#define __DIRECTSPRITE_H_

//Macro Definition
#ifdef	DIRECTSPRITE_EXPORTS
#define DIRECTSPRITE_API __declspec(dllexport)
#else
#define DIRECTSPRITE_API __declspec(dllimport)
#endif

//Struct Definition
typedef struct
{
	float fScaleX;	//Scale变换X轴比例	//拉伸
	float fScaleY;	//Scale变换Y轴比例
} DirectSpriteScale;

typedef struct
{
	float fRotateZ;	//Rotate变换Z轴比例	//旋转
} DirectSpriteRotate;

typedef struct
{
	float fTranslateX;	//Translate变换X轴比例	//平移
	float fTranslateY;	//Translate变换Y轴比例
} DirectSpriteTranslate;

//变换参数
typedef struct
{
	DirectSpriteScale sScalePara;			//拉伸
	DirectSpriteRotate sRotatePara;			//旋转
	DirectSpriteTranslate sTranslatePara;	//平移
} DirectSpriteTransformPara;

//绘制参数
typedef struct
{
	RECT SpriteRect;						//Sprite矩形区域
	D3DXVECTOR3 SpriteCenter;				//Sprite中心向量
	D3DXVECTOR3 SpritePosition;				//Sprite位置向量
	D3DCOLOR SpriteColor;					//Sprite颜色
} DirectSpriteDrawPara;

//Class Definition
class DIRECTSPRITE_API DirectSprite
{
protected:
	LPDIRECT3DDEVICE9 m_pD3D9Device;		//The Direct3D 9 Render Device
	LPDIRECT3DTEXTURE9 m_pSpriteTexture;	//The Direct3D 9 Sprite Texture
	LPD3DXSPRITE m_pSprite;					//The Direct3D 9 Sprite

private:

public:
	DirectSprite();				//DirectSprite Constructor Function
	virtual ~DirectSprite();	//DirectSprite Destructor Function

	DirectSprite(LPDIRECT3DDEVICE9 pD3D9Device);					//DirectSprite Constructor Function(Use D3D Device)
	virtual HRESULT WINAPI DirectSpriteInit(LPCWSTR lpszStr);		//DirectSprite Initialize
	virtual HRESULT WINAPI DirectSpriteReload(LPCWSTR lpszStr);		//DirectSprite Reload(Texture Changed)
	HRESULT WINAPI DirectSpriteBegin(void);							//DirectSprite Begin Draw
	HRESULT WINAPI DirectSpriteEnd(void);							//DirectSprite End Draw
	void WINAPI DirectSpriteGetTransform(D3DXMATRIX* pMatrix);		//DirectSprite Get Transform
	void WINAPI DirectSpriteSetTransform(D3DXMATRIX* pMatrix);		//DirectSprite Set Transform
	void WINAPI DirectSpriteDraw(DirectSpriteDrawPara* sSpriteDrawPara);																//DirectSprite Draw
	void WINAPI DirectSpriteDraw(RECT* pSpriteRect, D3DXVECTOR3* pSpriteCenter, D3DXVECTOR3* pSpritePosition, D3DCOLOR SpriteColor);	//DirectSprite Draw
	void WINAPI DirectSpriteDrawScale(DirectSpriteDrawPara* sSpriteDrawPara, float fScaleX = 1.0f, float fScaleY = 1.0f);				//DirectSprite Draw Scale
	void WINAPI DirectSpriteDrawScale(DirectSpriteDrawPara* sSpriteDrawPara, DirectSpriteScale sScalePara); 							//DirectSprite Draw Scale
	void WINAPI DirectSpriteDrawRotate(DirectSpriteDrawPara* sSpriteDrawPara, float fRotateZ = 0.0f);									//DirectSprite Draw Rotate
	void WINAPI DirectSpriteDrawRotate(DirectSpriteDrawPara* sSpriteDrawPara, DirectSpriteRotate sRotatePara);							//DirectSprite Draw Rotate
	void WINAPI DirectSpriteDrawTranslate(DirectSpriteDrawPara* sSpriteDrawPara, float fTranslateX = 0.0f, float fTranslateY = 0.0f);	//DirectSprite Draw Translate
	void WINAPI DirectSpriteDrawTranslate(DirectSpriteDrawPara* sSpriteDrawPara, DirectSpriteTranslate sTranslatePara);					//DirectSprite Draw Translate
	void WINAPI DirectSpriteDrawTransform(DirectSpriteDrawPara* sSpriteDrawPara, DirectSpriteTransformPara sTransformPara);				//DirectSprite Draw Transform
};

#endif