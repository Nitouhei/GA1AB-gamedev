#pragma once

//�I�u�W�F�N�g�l�[��------------------------------
enum OBJ_NAME
{
	OBJ_NO_NAME,	//�I�u�W�F�N�g������(�֎~)
	//�Q�[���Ŏg���I�u�W�F�N�g�̖��O
	//OBJ_�����ƕ\�L
	OBJ_TITLE,
	OBJ_HERO,
	OBJ_HEROATTACK,
	OBJ_ENEMY,
	OBJ_BLOCK,
	OBJ_BATORU,
	OBJ_SCENE_MAP,
	OBJ_SHOP_ITEM,
	OBJ_SHOP_SOUBI,
	OBJ_SHOP_SOUBI2,
	OBJ_JUMPENEMY,
	OBJ_TIME,
	OBJ_SCENECLEAR,
	OBJ_SCENEGAMEOVER

};
//------------------------------------------------

//�����蔻�葮��----------------------------------
enum HIT_ELEMENTS
{
	ELEMENT_NULL,//�������� �S�Ă̑����Ɠ����蔻�肪���s�����
	//�ȉ��@�����������m�ł͓����蔻��͎��s����Ȃ�
	//�����͒ǉ��\�����A�f�o�b�N���̐F�͏����ݒ蕪��������
	ELEMENT_PLAYER,
	ELEMENT_ENEMY,
	ELEMENT_ITEM,
	ELEMENT_MAGIC,
	ELEMENT_FIELD,
	ELEMENT_RED,
	ELEMENT_GREEN,
	ELEMENT_BLUE,
	ELEMENT_BLACK,
	ELEMENT_WHITE,
};
//------------------------------------------------

//------------------------------------------------
//�Z�[�u�����[�h�ƃV�[���Ԃ̂���肷��f�[�^
struct UserData
{
	int mSeveData;	//�T���v���Z�[�u�f�[�^
	
};
//------------------------------------------------


//�Q�[�����Ŏg�p�����O���[�o���ϐ��E�萔�E��--



//------------------------------------------------
//�Q�[�����Ŏg�p����N���X�w�b�_------------------


//------------------------------------------------

//�Q�[���V�[���I�u�W�F�N�g�w�b�_------------------
#include "ObjHero.h"
#include "ObjBatoru.h"
#include "ObjBlock.h"
#include "ObjEnemy.h"
#include "ObjTime.h"
#include "CObjheroattack.h"
#include "ObjJunpEnemy.h"



//------------------------------------------------

//�Q�[���V�[���N���X�w�b�_------------------------
#include "SceneTitle.h"
#include "SceneBattle.h"
#include "SceneItem.h"
#include "SceneItem2.h"
#include "SceneMap.h"
#include "ShopSoubi.h"
#include "ShopSoubi2.h"
#include "SceneGameOver.h"
#include "SceneClear.h"
#include "SceneBattle2.h"

//-----------------------------------------------

//�V�[���X�^�[�g�N���X---------------------------
//�Q�[���J�n���̃V�[���N���X�o�^
#define SET_GAME_START  CSceneTitle
//-----------------------------------------------