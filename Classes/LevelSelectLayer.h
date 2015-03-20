#ifndef __LIANLIANKANX__LEVELSELECTLAYER__
#define __LIANLIANKANX__LEVELSELECTLAYER__

#include "cocos2d.h"
#include "LevelSelectContent.h"

USING_NS_CC;

class LevelSelectLayer :public Layer{
public:
	LevelSelectLayer();
	~LevelSelectLayer();
	virtual bool init();
	CREATE_FUNC(LevelSelectLayer);
	static Scene* createScene();

private:
	LevelSelectContent* levelSelectContent;//�ȼ�����
	int _currentPage;//��ǰҳ
	int _maxPage;//���ҳ��
	Menu* _leftMenu;
	Menu* _rightMenu;

	void initNavigation();//��ʼ������
	void initAllLevels();//��ʼ�����еȼ�
	void nextPageBack(Ref* sender);//��һҳ
	void prePageBack(Ref* sender);//ǰһҳ
};


#endif