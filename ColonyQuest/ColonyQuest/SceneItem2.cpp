//シーン：アイテム屋２
//STLデバッグ機能をＯＦＦに
#define _SECURE_SCL	(0)
#define _HAS_ITERATOR_DEBUGGING (0)

#include "SceneItem2.h"

#include "GameHead.h"
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"

using namespace GameL;

void CSceneItem2::InitScene()
{
	CSceneItem2* objII = new CSceneItem2();
	Objs::InsertObj(objII, OBJ_SHOP_ITEM, 1);

	//グラフィック読み込み
	Draw::LoadImage(L"tekisuto1.png", 1, TEX_SIZE_512);
	Draw::LoadImage(L"tekisuto2.png", 2, TEX_SIZE_512);
	Draw::LoadImage(L"haikei3.png", 5, TEX_SIZE_512);
}
//------------------------------------------------------------------------------------------------------------------------------------
//初期化----------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------
void CSceneItem2::Scene()
{

}
//--------------------------------------------------------------------------------------------------------------------------------------------
//イニシャライズ---------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------
void CSceneItem2::Init()
{
	m_mou_x = 0.0f;   //マウスの位置
	m_mou_y = 0.0f;
	m_mou_r = false;  //マウスの状態　　false = 押してない　 true = 押してる
	m_mou_l = false;
}
//----------------------------------------------------------------------------------------------------------------------------------------------
//アクション-----------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------
void CSceneItem2::Action()
{
	//マウスの座標を取得
	m_mou_x = float(Input::GetPosX());
	m_mou_y = float(Input::GetPosY());
	//マウスの状態を取得
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	//戻る
	if (m_mou_x >= 700 && m_mou_x <= 1000 && m_mou_y >= 590 && m_mou_y <= 680)
	{
		if (m_mou_r == true)
		{
			Scene::SetScene(new CSceneItem());
		}
	}
}
//------------------------------------------------------------------------------------------------------------------------------------------
//ドロー--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------
void CSceneItem2::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	RECT_F src;
	RECT_F dst,dst2;

	//背景--------------------------------------------------------------
	//切り取り位置
	src.m_top    =   0.0f;
	src.m_left   =   0.0f;
	src.m_right  = 500.0f;
	src.m_bottom = 500.0f;
	//表示位置
	dst.m_top    =   0.0f;
	dst.m_left   =   0.0f;
	dst.m_right  = 525.0f + src.m_right;
	dst.m_bottom = 265.0f + src.m_bottom;
	Draw::Draw(5, &src, &dst, c, 0.0f);
	//テキスト-------------------------------------------アイテム屋
	//表示位置
	dst.m_top    =   0.0f;
	dst.m_left   =   0.0f;
	dst.m_right  = 380.0f;
	dst.m_bottom = 120.0f;
	Draw::Draw(1, &src, &dst, c, 0.0f);
	//テキスト------------------------------------------戻る
	//表示位置
	dst2.m_top = 550.0f;
	dst2.m_left = 700.0f;
	dst2.m_right = 1000.0f;
	dst2.m_bottom = 680.0f;
	Draw::Draw(2, &src, &dst, c, 0.0f);		  //テキスト３
	//文字表示------------------------------------------------------------------
	Font::StrDraw(L" ★アイテム屋★", 50,  45, 35, c);
	Font::StrDraw(L"    一覧", 50, 140, 50, c);
	Font::StrDraw(L"   戻る ", 700, 600, 60, c);
	//仮マウスの位置表示------------------------------------------------
	wchar_t str[256];
	swprintf_s(str, L"x = %f, y = %f", m_mou_x, m_mou_y);
	Font::StrDraw(str, 500, 20, 20, c);
}