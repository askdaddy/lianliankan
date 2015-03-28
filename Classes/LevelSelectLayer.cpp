#include "LevelSelectLayer.h"
#include "GameUtils.h"
#include "GameData.h"
#include "MenuScene.h"

LevelSelectLayer::LevelSelectLayer() :_currentPage(0){//��ʼ��
	float maxPage = g_maxLevel / g_EachPageCount;// �ܵĹؿ���  ÿһҳ�Ĺؿ���   float
	_maxPage = g_maxLevel / g_EachPageCount;//int����
	log("yeshu =%f, =%d",maxPage,_maxPage);
	if (maxPage > _maxPage){//�Ƚϴ�С
		_maxPage = _maxPage + 1;
	}
	
}
LevelSelectLayer::~LevelSelectLayer(){

}

Scene* LevelSelectLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = LevelSelectLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool LevelSelectLayer::init(){
	if (!Layer::init()){
		return false;
	}


	auto gameBg = Sprite::create("bg.png");
	//float wBg = gameBg->getContentSize().width;
	//Rect rect;
	//if (VISIBLE_WIDTH >= size_width) {
	//	rect = Rect((wBg - VISIBLE_WIDTH)/2, 1, VISIBLE_WIDTH, VISIBLE_HEIGHT);   //ͼƬ�Ĵ�С
	//}else {
	//	rect = Rect((wBg - size_width)/2, 1, size_width, size_height);   //ͼƬ�Ĵ�С
	//	
	//}

	//gameBg->setTextureRect(rect);
	gameBg->setScaleX(GetXScaleRate);
	gameBg->setScaleY(GetYScaleRate);
	gameBg->setPosition(Vec2(VISIBLE_WIDTH / 2, VISIBLE_HEIGHT / 2));
	this->addChild(gameBg, -1);

	//����
	pBack = MenuItemImage::create("btn_back.png", "btn_back.png",CC_CALLBACK_0(LevelSelectLayer::menuBackMainMenu, this));
	pBack->setScaleX(GetXScaleRate);
	pBack->setScaleY(GetYScaleRate);
	pBack->setPosition(Vec2(pBack->boundingBox().size.width / 2 + 10 , VISIBLE_HEIGHT - pBack->boundingBox().size.height / 2 - 10));
	pMenu = Menu::create(pBack, NULL);
	pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu);


	initAllLevels();
	initNavigation();

	return true;
}


//��ʼ������  
void LevelSelectLayer::initNavigation(){
	float alreadyUseH = pBack->boundingBox().size.height + level_space*2  + (g_EachPageCount/g_EachLineCount)*(GameData::getInstance()->getlevelSpriteW() +level_space*2);

	leftMenuSpritePre = MenuItemImage::create("page_pre.png", "page_pre.png", CC_CALLBACK_0(LevelSelectLayer::prePageBack, this));
	log("changdu %f,%f",leftMenuSpritePre->getContentSize().width,leftMenuSpritePre->getContentSize().height);
	leftMenuSpritePre->setScaleX(GetXScaleRate);
	leftMenuSpritePre->setScaleY(GetYScaleRate);
	float leftW = leftMenuSpritePre->boundingBox().size.width;
	float leftH = leftMenuSpritePre->boundingBox().size.height;
	leftMenuSpritePre->setPosition(VISIBLE_WIDTH*0.5 - leftW ,VISIBLE_HEIGHT -(alreadyUseH+leftH/2));

	rightMenuSpritePre = MenuItemImage::create("page_next.png", "page_next.png", CC_CALLBACK_0(LevelSelectLayer::nextPageBack, this));
	rightMenuSpritePre->setScaleX(GetXScaleRate);
	rightMenuSpritePre->setScaleY(GetYScaleRate);
	float rightW = rightMenuSpritePre->boundingBox().size.width;
	float rightH = rightMenuSpritePre->boundingBox().size.height;
	rightMenuSpritePre->setPosition(VISIBLE_WIDTH*0.5 + rightW ,VISIBLE_HEIGHT -(alreadyUseH+leftH/2));

	pageMenu = Menu::create(leftMenuSpritePre,rightMenuSpritePre, NULL);
	pageMenu->setPosition(Vec2::ZERO);
	this->addChild(pageMenu);

	if (_currentPage == 0){
		leftMenuSpritePre->setVisible(false);
	}
	if (_currentPage == (_maxPage - 1)){
		rightMenuSpritePre->setVisible(false);
	}
}


void LevelSelectLayer::initAllLevels(){
	//UserDefault *save = UserDefault::getInstance();
	//g_passLevelCount = save->getIntegerForKey(PlayerPassLevelCountKey, 0);//��ȡ�û���ǰ�Ĺؿ��ȼ�
	//log("g_passLevelCount:%d", g_passLevelCount);

	//just for test, in real game, comment the below code
	//g_passLevelCount = 10;
	int g_passLevelCount = GameData::getInstance()->getCurLevel();
	log("g_passLevelCount:%d", g_passLevelCount);

	levelSelectContent = LevelSelectContent::create();//�ؿ��ȼ�ѡ��
	this->addChild(levelSelectContent);
	_currentPage = g_passLevelCount / g_EachPageCount;//�����û���ǰ�Ĺؿ��ȼ��������ǰҳ��
	if (_currentPage >= _maxPage){
		_currentPage = _maxPage - 1;
	}
	levelSelectContent->initAllLevels(_currentPage,pBack->boundingBox().size.height + level_space*2);//��ʼ����ҳ�Ĺؿ�
}

void LevelSelectLayer::menuBackMainMenu()
{
	Scene *pScene = Scene::create();
	pScene->addChild(MenuScene::create());
	Director::getInstance()->replaceScene(pScene);
}



void LevelSelectLayer::nextPageBack(){
	if (_currentPage < _maxPage - 1){
		_currentPage = _currentPage + 1;

		levelSelectContent->initAllLevels(_currentPage,pBack->boundingBox().size.height + level_space*2);

		if (_currentPage == (_maxPage - 1)){
			rightMenuSpritePre->setVisible(false);
		}
		leftMenuSpritePre->setVisible(true);
	}
}
void LevelSelectLayer::prePageBack(){
	if (_currentPage >= 1){
		_currentPage = _currentPage - 1;

		levelSelectContent->initAllLevels(_currentPage,pBack->boundingBox().size.height + level_space*2);

		if (_currentPage == 0){
			leftMenuSpritePre->setVisible(false);
		}
		rightMenuSpritePre->setVisible(true);
	}
}

