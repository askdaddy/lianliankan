#ifndef __LIANLIANKANX__LevelSelectItem__
#define __LIANLIANKANX__LevelSelectItem__

#include "cocos2d.h"
#include "GameData.h"
#include <string>
USING_NS_CC;


class LevelSelectItem : public MenuItemSprite{
	CC_SYNTHESIZE(int, _level, Level);//������get set //varType, varName, funName ���Խ��i�ĵȼ�
	CC_SYNTHESIZE(LevelItemType, _type, Type);
public:
	LevelSelectItem(int level);//���캯��
	static LevelSelectItem* create(int level); //��������
private:
	void selectCallBack(Ref* sender);
	void extraInit();
	std::string getFrameNameByType(const LevelItemType& type);
};

#endif