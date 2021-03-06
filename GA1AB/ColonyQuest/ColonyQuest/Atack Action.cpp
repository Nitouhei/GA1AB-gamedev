//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "Atack Action.h"
#include "ObjHero.h"

//使用するネームスペース
using namespace GameL;
//-----------------------------------------------------------------------------------------------------------------------------
//コンストラクタ---------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
CObjAtackAction::CObjAtackAction(float x, float y)
{
	m_x = x;
	m_y = y;
}
//----------------------------------------------------------------------------------------------------------------------------------
//イニシャライズ---------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------
void CObjAtackAction::Init()
{
	m_f = false;
	m_ani_time = 0;  //アニメ動作間隔
	m_ani_frame = 1.0f;//フレーム間隔
	m_ani_max_time = 2;  //アニメーション間隔最大値

	//当たり判定用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	//当たり判定用のHITBOX
	Hits::SetHitBox(this, m_x, m_y, 55, 55, ELEMENT_PLAYER, OBJ_ATACK_ACTION, 1);
}
//-----------------------------------------------------------------------------------------------------------------------------------
//アクション--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
void CObjAtackAction::Action()
{	//アニメーション間隔---------------------------------------------
	if (m_ani_time  >  m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}
	else if (m_ani_frame == 2)
	{
		m_ani_frame = 0;
	}

	//自身のHitBoxを更新
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_x, m_y);

	//当たっているか判定----------------------------------------------
	if (hit->CheckObjNameHit(OBJ_ENEMY) != nullptr)
	{
		//攻撃がどの角度で当たっているか
		HIT_DATA** hit_data;
		hit_data = hit->SearchObjNameHit(OBJ_ENEMY);

		for (int i = 0; i<hit->GetCount(); i++)
		{
			float r = hit_data[i]->r;
			if (r<45 && r >= 0 || r>315)
			{
				this->SetStatus(false);
				Hits::DeleteHitBox(this);//攻撃削除
			}
		}
	}
}
//------------------------------------------------------------------------------------------------------------------------------
//ドロー--------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------
void CObjAtackAction::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

	//切り取り位置
	src.m_top    =  70.0f + m_ani_frame * 170;
	src.m_left   =  20.0f;
	src.m_right  = 285.0f;
	src.m_bottom = 225.0f + m_ani_frame * 170;
	//表示位置
	dst.m_top    = 10.0f + m_y;      //y15
	dst.m_left   = 25.0f + m_x;		 //x30
	dst.m_right  = 55.0f + m_x;
	dst.m_bottom = 52.0f + m_y; 
	Draw::Draw(0, &src, &dst, c, 0.0f);
}