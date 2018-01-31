//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjBlock.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjBlock::CObjBlock(int map[10][100])
{
	float Volume = Audio::VolumeMaster(0);
//�}�b�v�f�[�^���R�s�[
	memcpy(m_map, map, sizeof(int)*(10 * 100));
	Audio::LoadAudio(0, L"BGM Action.wav", SOUND_TYPE::BACK_MUSIC);
//	 Volume  =Audio::VolumeMaster(-0.7);
	Audio::Start(0);
}
//�C�j�V�����C�Y
void CObjBlock::Init()
{
	m_scroll = 0.0f;
}
//�A�N�V����
void CObjBlock::Action()
{

	//��l���̈ʒu���擾
	CObjHero*hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();

	//����X�N���[�����C��
	if (hx < 80)
	{
		hero->SetX(80);					//��l���̓��C���𒴂��Ȃ��悤�ɂ���
		m_scroll -= hero->GetVX();		//��l�����{�������ׂ����̒l��m_scroll�ɉ�����
	}

	//�O���X�N���[�����C��
	if (hx > 300)
	{
		hero->SetX(300);
		m_scroll -= hero->GetVX();
	}


	//�G�o�����C��
	//��l���̈ʒu+500��G�o�����C���ɂ���
	float Line = hx + (-m_scroll) + 500;

	//�G�o�����C����v�f�ԍ���
	int ex = ((int)Line) / 64;
	for (int i = 0; i < 10; i++)
	{
		if (m_map[i][ex] == 4)
		{
			//4������΁A�G���o��
			CObjEnemy*objs = new CObjEnemy(ex*64.0f, i*64.0f);
			Objs::InsertObj(objs, OBJ_ENEMY, 10);
			//�G�o���ꏊ�̒l��0�ɂ���
			m_map[i][ex] = 0;
		}
		if (m_map[i][ex] == 5)
		{
			//5������΁A�W�����v����G���o��
			CObjJumpEnemy*objs = new CObjJumpEnemy(ex*64.0f, i*64.0f);
			Objs::InsertObj(objs, OBJ_JUMPENEMY, 10);
			//�G�o���ꏊ�̒l��0�ɂ���
			m_map[i][ex] = 0;
		}
	}
}
//�h���[
void CObjBlock::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu

	//�w�i�\��
	src.m_top = 320.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 1024.0f;
	dst.m_bottom = 640.0f;
	Draw::Draw(0, &src, &dst, c, 0.0f);
	//�}�b�v�`�b�v�ɂ��block
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (m_map[i][j] > 0)
			{
			//�\���ʒu�̐ݒ�
			dst.m_top = i*64.0f;
			dst.m_left = j*64.0f+m_scroll;
			dst.m_right = dst.m_left+64.0f;
			dst.m_bottom = dst.m_top+64.0f;
			if (m_map[i][j] == 2)
			{
				//�X�^�[�g�u���b�N
				BlockDraw(320.0f + 64.0f, 0.0f, &dst, c);
			}
			else if (m_map[i][j] == 3)
			{
				//�S�[���u���b�N
				BlockDraw(320.0f + 64.0f, 64.0f, &dst, c);
			}
			else if (m_map[i][j] == 4)
			{
				;//�G�z�u�p�̔ԍ��̂��߉������Ȃ�
			}
			/*
			else if (m_map[i][j] == 5)
			{
				Obstacle(320.0f + 0.0f, 64.0f, &dst, c);
			}
			*/
			else
			{
				BlockDraw(320.0f, 0.0f, &dst, c);
			}
			
			}
		}
	}
}
/*
BlockDrawMethod�֐�
����1 float	   x 	:���\�[�X�؂���ʒuX
����2 float    Y    :���\�[�X�؂���ʒuY
����3 RECT_F*  dst  :�`�ʈʒu
����4 float    c[]/ :�J���[���
�u���b�N��64*64����`��p�B���\�[�X�؂���ʒu�݂̂�x,y��
�ݒ�ł���
*/
void CObjBlock::BlockDraw(float x, float y, RECT_F*dst, float c[])
{
	RECT_F src;
	src.m_top = y;
	src.m_left = x;
	src.m_right = src.m_left + 64.0f;
	src.m_bottom = src.m_top + 64.0f;
	//�`��
	Draw::Draw(0, &src, dst, c, 0.0f);
}

//Block�֐�
//����1	 float* x			:�s��object��X�ʒu
//����2	 float* y			:������s��object��Y�ʒu
//����3  bool	scrolll_on	:������s��object�̓X�N���[���̉e���^���邩�ǂ���(true=�^���� false=�^���Ȃ�)
//����4�@bool*	up			:�㉺���E����̏㕔���ɓ������Ă��邩�ǂ�����Ԃ�
//����5  bool*	down		:�㉺���E����̉������ɓ������Ă��邩�ǂ�����Ԃ�
//����6  bool*	left		:�㉺���E����̉������ɓ������Ă��邩�ǂ�����Ԃ�
//����7  bool*	right		:�㉺���E����̉������ɓ������Ă��邩�ǂ�����Ԃ�
//����8	 float* vx			:���E���莞�̔����ɂ��ړ������E�͂̒l��ς��ĕԂ�
//����9  float* vy			:�㉺���莞�ɂ�鎩�R�����^���̈ړ������E�͂̒l��ς��ĕԂ�
//����10 int*   bt			:���������莞�A����ȃu���b�N�̃^�C�v��Ԃ�
//������s��object�ƃu���b�N64�~64����ŁA�����蔻��Ə㉺���E������s��
//���̌��ʂ͈���4�`10�ɕԂ�

void CObjBlock::BlockHit(
	float* x, float* y, bool scroll_on,
	bool* up, bool* down, bool* left, bool* right,
	float* vx, float* vy, int* bt
)
{
	//��l���̏Փˏ�Ԋm�F�p�t���O�̏�����
	*up = false;
	*down = false;
	*left = false;
	*right = false;

	//����ł���block�̎�ނ̏�����
	*bt=0;

	//m_map�̑S�v�f�ɃA�N�Z�X
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (m_map[i][j] > 0&&m_map[i][j]!=4)
			{
				//�v�f�ԍ������W�ɕύX
				float bx = j*64.0f;
				float by = i*64.0f;

				//�X�N���[���̉e��
				float scroll = scroll_on ? m_scroll : 0;

				//��l���ƃu���b�N�̓����蔻��
				if ((*x + (-scroll) + 42.0f>bx) && (*x + (-scroll)<bx + 64.0f) && (*y + 64.0f>by) && (*y<by + 64.0f))
				{
					//�㉺���E����

					//vector�̍쐬
					float rvx = (*x + (-scroll)) - bx;
					float rvy = *y - by;

					//���������߂�
					float len = sqrt(rvx*rvx + rvy*rvy);

					//�p�x�����߂�
					float r = atan2(rvy, rvx);
					r = r*180.0f / 3.14f;

					if (r <= 0.0f)
						r = abs(r);
					else
						r = 360.0f - abs(r);
					//len��������̒����̂��Z���ꍇ����ɓ���
					if (len < 88.0f)
					{
						//�p�x�ŏ㉺���E�𔻒�
						if ((r < 45 && r>0) || r > 315)
						{
							//�E
							*right=true;//��l�����猩�āA���̕������Փ˂��Ă���
							*x =bx + 64.0f + (scroll);//�u���b�N�̈ʒu-��l���̕�
							*vx=-(*vx)*0.1f;
						}
						if (r > 45 && r < 135)
						{
							//��
							*down=true;//��l�����猩�āA���̕������Փ˂��Ă���
							*y=by - 64.0f;//�u���b�N�̈ʒu-��l���̕�
						    //��ނ�n���̃X�^�[�g�ƃS�[���̂ݕύX����
							if (m_map[i][j] >= 2)
								*bt=m_map[i][j];//�u���b�N�̗v�f�itype�j����l���ɓn��
							*vy=0.0f;
						}
						if (r > 135 && r < 225)
						{
							//��
							*left=true;//��l�����猩�āA�E�̕������Փ˂��Ă���
							*x =bx - 42.5f + (scroll);//�u���b�N�̈ʒu-��l���̕�
							*vx= -(*vx)*0.1f;
						}
						if (r > 225 && r < 315)
						{
							//��
							*up=true;//��l�����猩�āA��̕������Փ˂��Ă���
							*y=by + 64.0f;//�u���b�N�̈ʒu-��l���̕�
							if (*vy < 0)
							{
								*vy=0.0f;
							}
						}
					}
				}
			}
		}
	}
}
/*
���ϊ֐�
����1,2 float ax,ay:A�x�N�g��
����3,4 float bx,by:B�x�N�g��
�߂�l�@float :�ˉe
���e�@A�x�N�g����B�x�N�g���œ��ς��s���ˉe�����߂�
*/
	float CObjBlock::Dot(float ax, float ay, float bx, float by)
	{
		float t = 0.0f;

		t = ax*bx + ay*by;

		return t;
}
	/*
	�O�ϊ֐�
	����1,2 float ax,ay:A�x�N�g��
	����3,4 float bx,by:B�x�N�g��
	�߂�l�@float :�ˉe
	���e�@A�x�N�g����B�x�N�g���ŊO�ς��s���ˉe�����߂�
	*/
	float CObjBlock::Cross(float ax, float ay, float bx, float by)
	{
		float t = 0.0f;

		t = ax*bx - ay*by;

		return t;
	}

	//���������߂�}�N��
#define SGN(x) 1 - (x <= 0 ) - (x < 0 )
	/*
	���Ɛ��ƌ������ʊ֐�
	���� float 1, 2	 a1x , a1y		:���x�N�g��A�̎n�_
	���� float 3, 4  a2x , a2y		;���x�N�g��B�̎n�_
	���� float 5, 6  b1x , b1y		:�x�N�g��B�̎n�_
	���� float 7, 8  b2x , b2y		:�x�N�g��B�̏I�_
	���� float 9,10  out_px,out_py	:��������x�N�g���̌�_�ʒu
	�߂�l�@bool	:true=��_�L��@false=��_����
	���e : ������A�EB�x�N�g���̌�_�������Aout_px��out_py�ɕԂ�*/
	//�����Ɛ��ƌ�������
	bool CObjBlock::LineCrossPoint(
		float a1x, float a1y, float a2x, float a2y,
		float b1x, float b1y, float b2x, float b2y,
		float* out_px, float *out_py
	)
	{
		//�G���[�R�[�h
		*out_px = -99999.0f;	*out_py = -99999.0f;

		//A�x�N�g���쐬(a2��a1)
		float ax = a2x - a1x;	float ay = a2y - a1y;
		//B�x�N�g���쐬(b2��b1)
		float bx = b2x - b1x;	float by = b2y - b1y;
		//C�x�N�g���쐬(b1��a1)
		float cx = b1x - a1x;	float cy = b1y - a1y;
		//D�x�N�g���쐬(b2��a1)
		float dx = b2x - a1x;	float dy = b2y - a1y;

		//A�~C�̎ˉe�����߂�
		float t1 = Cross(ax, ay, cx, cy);
		float t2 = Cross(ax, ay, dx, dy);

		//���������������ɂȂ��Ă���̂��ǂ������`�F�b�N
		if (SGN(t1) == SGN(t2))
			return false;//���_����

		//�ˉe���Βl��
		t1 = abs(t1);	t2 = abs(t2);
		//��_�����߂�
		float px = bx * (t1 / (t1 + t2)) + b1x;
		float py = by * (t1 / (t1 + t2)) + b1y;

		//AP�x�N�g��(p��a1)
		float apx = px - a1x;		float apy = py - a1y;

		//BP�x�N�g��(p��a2)
		float bpx = px - a2x;		float bpy = py - a2y;

		//A�EAP�̎ˉe��A�EBP�̎ˉe�����߂�
		float w1 = Dot(ax, ay, apx, apy);
		float w2 = Dot(ax, ay, bpx, bpy);

		//��_��Ԃ�
		*out_px = px; *out_py = py;

		return true;
	}
	/*
	��l���ƕǂ̌�������֐�
	����1,2 float  x , y			:��l���̈ʒu
	����3,4 float  vx,vy			:��l���̈ړ��x�N�g��
	����5,6 float  out_px,out_py	:Block�Ƃ̌�_
	����7   float  out				:�ʒu�����_�܂ł̋���
	��l���̈ʒu+�ړ��x�N�g���Ƃ����u���b�N�̕ӂŌ�_������s��
	�ł��߂���_�̈ʒu�Ƌ�����Ԃ�*/
	bool CObjBlock::HeroBlockCrossPint(
		float x, float y, float vx, float vy,
		float* out_px, float* out_py, float* out_len
	)
	{
		bool pb = false;		  //��_�m�F�p
		float len = 99999.0f; //��_�Ƃ̋���
		//�u���b�N�̕ӈʒu
		float edge[4][4] =
		{
			{  0,  0, 64,  0},//��
			{ 64,  0, 64, 64},//��
			{ 64, 64,  0, 64},//��
			{  0, 64,  0,  0},//��
		};

		//m_map�̑S�v�f�ɃA�N�Z�X
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 100; j++)
			{
				if (m_map[i][j] > 0 && m_map[i][j] != 4)
				{
					//�u���b�N��4�ӂ����_��T��
					for (int k = 0; k < 4; k++)
					{
						//��_��T��
						float px, py;
						bool b;
						float l = 0.0f;
						b = LineCrossPoint(x, y, x + vx, y + vy,
							j * 64+edge[k][0], i * 64+edge[k][1], j * 63 + edge[k][2], i * 64 + edge[k][3],
							&px, &py);

						//��_�`�F�b�N
						if (b == true)
						{
							//��_�Ƃ̋��������߂�
							l = sqrt((px - x)*(px - x) + (py - y)*(py - y));

							//��������_�̒��ōł��������Z�����̂�T��
							if (len < l)
							{
								len = l;
								*out_px = px;
								*out_py = py;
								pb = true;
							}
						}
					}
				}
			}
		}
		*out_len = len;
		return pb;
	}