#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：バトル
class CObjBatoru :public CObj
{
public:
	CObjBatoru() {};
	~CObjBatoru() {};
	void Init();	 //イニシャライズ
	void Action();	 //アクション
	void Draw();	 //ドロー

	
private:
	int batorumap[6][10];
};