#include "PauseLayer.h"
#include "SimpleAudioEngine.h"

#include "Audio.h"
#include "MenuLayer.h"
#include "GameUtils.h"
#include "LevelSelectLayer.h"
#include "GameScene.h"

USING_NS_CC;

PauseLayer::~PauseLayer() {

}

//传入一个CCrenderTexture   
//相当于一个正在运行的游戏的截图作为这个暂停对话框的背景   
//这样就看起来像是对话框在游戏界面之上，一般游戏当中都是这样子写的。  
CCScene* PauseLayer::scene(CCRenderTexture* sqr)
{
	CCScene *scene = CCScene::create();
	PauseLayer *layer = PauseLayer::create();
	scene->addChild(layer, 1); 

	//增加部分：使用Game界面中截图的sqr纹理图片创建Sprite  
    //并将Sprite添加到GamePause场景层中  
    //得到窗口的大小  
	CCSprite *back_spr = CCSprite::createWithTexture(sqr->getSprite()->getTexture());
	back_spr->setPosition(Vec2(VISIBLE_WIDTH / 2, VISIBLE_HEIGHT / 2)); //放置位置,这个相对于中心位置。  
	back_spr->setFlipY(true);           //翻转，因为UI坐标和OpenGL坐标不同  
	back_spr->setColor(Color3B::GRAY); //图片颜色变灰色  
	scene->addChild(back_spr);


	CCSprite *back_small_spr = CCSprite::create("pause_bg.png");
	back_small_spr->setScaleX(GetXScaleRate);
	back_small_spr->setScaleX(GetYScaleRate);
	back_small_spr->setPosition(ccp(VISIBLE_WIDTH /2 , VISIBLE_HEIGHT / 2)); 
	scene->addChild(back_small_spr);


	return scene;
}

bool PauseLayer::init()
{

	if (!CCLayer::init())
	{
		return false;
	}
	
	CCPoint origin = CCDirector::getInstance()->getVisibleOrigin();

		
	CCMenuItemImage *pRestartItem = CCMenuItemImage::create(
		"pause_again.png",
		"pause_again.png",
		CC_CALLBACK_0(PauseLayer::menuRestart, this));
	pRestartItem->setScaleX(GetXScaleRate);
	pRestartItem->setScaleX(GetYScaleRate);
	pRestartItem->setPosition(Vec2(VISIBLE_WIDTH / 2, VISIBLE_HEIGHT / 2));
	

	CCMenuItemImage *pContinueItem = CCMenuItemImage::create(
		"pause_play.png",
		"pause_play.png",
		CC_CALLBACK_0(PauseLayer::menuContinueCallback,this));
	pContinueItem->setScaleX(GetXScaleRate);
	pContinueItem->setScaleX(GetYScaleRate);
	pContinueItem->setPosition(Vec2(VISIBLE_WIDTH / 2, VISIBLE_HEIGHT / 2 + pRestartItem->boundingBox().size.height + level_space));



	CCMenuItemImage *pLoginItem = CCMenuItemImage::create(
		"pause_level.png",
		"pause_level.png",
		CC_CALLBACK_0(PauseLayer::menuLogin, this));
	pLoginItem->setScaleX(GetXScaleRate);
	pLoginItem->setScaleX(GetYScaleRate);
	pLoginItem->setPosition(Vec2(VISIBLE_WIDTH / 2, VISIBLE_HEIGHT / 2 - pRestartItem->boundingBox().size.height - level_space));


	// create menu, it's an autorelease object  
	CCMenu* pMenu = CCMenu::create(pContinueItem, pRestartItem, pLoginItem, NULL);
	pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu, 1000);

	CCDirector::sharedDirector()->pause();

	return true;
}
void PauseLayer::menuContinueCallback()
{
	
	Audio::getInstance()->playButtonClick();
	CCDirector::sharedDirector()->popScene();
	removeFromParentAndCleanup(true);
	CCDirector::sharedDirector()->resume();

}


void  PauseLayer::menuRestart()
{
	Audio::getInstance()->playButtonClick();
	CCDirector::sharedDirector()->popScene();
	removeFromParentAndCleanup(true);
	CCDirector::sharedDirector()->resume();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, GameScene::create()));
}

void  PauseLayer::menuLogin()
{
	Audio::getInstance()->playButtonClick();
	CCDirector::sharedDirector()->popScene();
	removeFromParentAndCleanup(true);
	Director::sharedDirector()->resume();
	Director::getInstance()->replaceScene(LevelSelectLayer::createScene());
}
