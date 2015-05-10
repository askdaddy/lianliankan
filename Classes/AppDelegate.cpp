﻿#include "AppDelegate.h"

#include "Audio.h"
#include "HelloWorldScene.h"
#include "MenuScene.h"
#include "GameData.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("Lian Lian Kan");
        director->setOpenGLView(glview);
    }
	//auto screenSize = glview->getFrameSize();


	//if(screenSize.width > 640)
	//	glview->setDesignResolutionSize(768, 1024, ResolutionPolicy::SHOW_ALL);
	//else if (screenSize.height > 960)
	//	glview->setDesignResolutionSize(640, 1136, ResolutionPolicy::SHOW_ALL);
	//else 
	glview->setDesignResolutionSize(640, 960, ResolutionPolicy::FIXED_WIDTH);
	//static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(640, 960);
	//glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionShowAll);
    // turn on display FPS
    director->setDisplayStats(false);

	
	//auto designSize = Size(640, 960);
	//if(screenSize.width > 640) 
	//{
	//	auto resourceSize = Size(768, 1024);
	//	director->setContentScaleFactor(resourceSize.height/designSize.height);
	//}else if(screenSize.height > 960) 
	//{
	//	auto resourceSize = Size(640, 1136);
	//	director->setContentScaleFactor(resourceSize.height/designSize.height);
	//}

	//glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::FIXED_WIDTH);

    // set FPS. the default value is 1.0/60 if you don't call this
    //director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
	auto scene = MenuScene::create();

    // run
    director->runWithScene(scene);
	Audio::getInstance()->prepare();
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
