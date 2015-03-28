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
	MenuItemImage* leftMenuSpritePre;
	MenuItemImage* rightMenuSpritePre;
	Menu* pageMenu;
	MenuItemImage* pBack;
	Menu* pMenu;

	void initNavigation();//��ʼ������
	void initAllLevels();//��ʼ�����еȼ�
	void nextPageBack();//��һҳ
	void prePageBack();//ǰһҳ
	void menuBackMainMenu();
};


#endif