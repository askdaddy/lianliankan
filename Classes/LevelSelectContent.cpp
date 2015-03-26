#include "LevelSelectContent.h"
#include "GameUtils.h"

LevelSelectContent::LevelSelectContent(){

}
LevelSelectContent::~LevelSelectContent(){

}

bool LevelSelectContent::init(){
	if (!Layer::init()){
		return false;
	}

	//initAllLevels();
	return true;
}

void LevelSelectContent::contentFadeOut(){//���ݽ�����ʧ
	auto fadeAction = FadeOut::create(0.2);
	this->runAction(fadeAction);
}

void LevelSelectContent::initAllLevels(int page){//��ʼ����ǰpage �Ĺؿ�
	this->removeAllChildren();


	const int eachPageItemCount = g_EachPageCount;

	_levelMenu = Menu::create();//�����ؿ��˵�
	this->addChild(_levelMenu);

	//float p = (VISIBLE_WIDTH - levelMarginX*GameUtils::getLevelScale() * 7) /2;

	float constStartPositionX = VISIBLE_WIDTH * 0.5 - levelMarginX*GameUtils::getLevelScale() * (g_EachLineCount / 2 -0.1);
	float startPositionX = constStartPositionX;
	float topStartPositionY = VISIBLE_HEIGHT * 0.5 + levelMarginY*GameUtils::getLevelScale() * (g_EachPageCount / g_EachLineCount / 2);

	for (int i = 0 + page * eachPageItemCount; i < eachPageItemCount + page * eachPageItemCount; i++){
		if (i < g_maxLevel){
			int lineCount = g_EachLineCount;
			if (i != (0 + page * eachPageItemCount) && i % lineCount == 0){
				startPositionX = constStartPositionX;
				topStartPositionY = topStartPositionY - levelMarginY*GameUtils::getLevelScale();
			}

			int levelCount = i + 1;
			auto oneLevelItem = LevelSelectItem::create(levelCount);
			_levelMenu->addChild(oneLevelItem);
			oneLevelItem->setPosition(startPositionX, topStartPositionY);
			startPositionX += levelMarginX*GameUtils::getLevelScale();
		}
	}

	_levelMenu->setPosition(0, 0);
	_levelMenu->setOpacity(0);
	auto fadeAction = FadeIn::create(0.5);
	_levelMenu->runAction(fadeAction);
}