#include "GameData.h"
#include "Audio.h"
#include "GameUtils.h"

USING_NS_CC;

GameData* GameData::_instance = 0;
GameData::GameData() {
	this->init();
}

GameData* GameData::getInstance() {
	if (_instance == 0) {
		_instance = new GameData();
	}
	return _instance;
}

void GameData::init() {
	//��ȡ�û���ǰ�ȼ�
	this->initUserPassLevel();
	//��ȡ�ȼ���������
	this->initLevelData();
	is_pause = false;
	//��ʼ���ȼ��ؿ�һЩ����
	this->initLevelScale();
}

void GameData::initLevelScale() {
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("startUI.plist", "startUI.png");
	//auto leftMenuSpriteNor = Sprite::create("page_pre.png");
	auto locte = Sprite::create("lockLevel.png");
	//locte->autorelease();
	//page_scale = GameUtils::getPageScale(leftMenuSpriteNor,normalSprite);
	level_scale = GameUtils::getLevelScale(locte);
	level_sprite_w = locte->getContentSize().width*level_scale;
	//level_space = GameUtils::getSpaceSizeRate(2+g_EachLineCount);
	//log("init level Data =%f,=%f,=%f",page_scale,level_scale,level_space);

}

void GameData::initUserPassLevel() {
	if (!UserDefault::getInstance()->getBoolForKey(PlayerPassLevelCountKey))
	{
		UserDefault::getInstance()->setBoolForKey(PlayerPassLevelCountKey, true);
		UserDefault::getInstance()->setIntegerForKey("curlevel", 1);
		UserDefault::getInstance()->flush();
	}
	this->setCurLevel(UserDefault::getInstance()->getIntegerForKey("curlevel"));
	this->setChooseLevel(this->getCurLevel());
}

void GameData::saveUserPassLevel() {
	if (!UserDefault::getInstance()->getBoolForKey(PlayerPassLevelCountKey))
	{
		UserDefault::getInstance()->setBoolForKey(PlayerPassLevelCountKey, true);
	}
	UserDefault::getInstance()->setIntegerForKey("curlevel", this->getCurLevel());
	UserDefault::getInstance()->flush();
}

void GameData::passCurrentUserLevel() {
	if (this->getChooseLevel() > this->getCurLevel()) {
		if (this->getCurLevel() >= level_data.size()) {
			return;
		}
		this->setCurLevel(this->getCurLevel() + 1);
		this->saveUserPassLevel();
	}
}

/*
auto find_sp = sp_map.find("10");//ͨ��find()����keyΪ��10����pair���͡�
auto sp3 = find_sp->second;//����Ӧ�Ķ���
std::string find_str = find_sp->first;//��
CCLOG("sp6 key value is %s",find_str.c_str());//��ӡ����

auto sp2=sp_map.at("sp1");//ͨ��keyȡ��sp1
sp_map.insert("11",sp2);//�ٽ�sp1������keyֵ�ķ�ʽ����map
sp_map.insert("22",sp2);
sp_map.insert("33",sp2);
auto _key=sp_map.keys(sp1);//���sp1��Ӧ��keyֵ
for(const auto&e : _key)
{
CCLOG("_key is %s",e.c_str());//���sp1��Ӧ��keyֵ�����ĸ����ֱ��ǣ�sp1,11,22,33��
}

*/
//��ʼ����Ϸ��������
void GameData::initLevelData() {
	//��ȡplist�����ļ�
	std::string plistPath = FileUtils::sharedFileUtils()->fullPathFromRelativeFile("levelinfo.plist", "levelinfo.plist");
	level_data.clear();
	xy_data.clear();
	auto allkeys = Array::create();
	//level_data = dynamic_cast<Array *>(Dictionary::createWithContentsOfFile(plistPath.c_str()));
	auto plistDic = Dictionary::createWithContentsOfFile(plistPath.c_str());
	allkeys = dynamic_cast<Array *> (plistDic->allKeys());
	for (unsigned i = 0; i < allkeys->count(); i++) {
		auto key = (String *)allkeys->objectAtIndex(i);
		log("idKey=%s", key->getCString());
		auto levelDic = dynamic_cast<Dictionary *> (plistDic->objectForKey(key->getCString()));
		//Array* imgArr = Array::create();
		Array* xyArr = Array::create();
		//xyArr->retain();
		xyArr->addObject(dynamic_cast<String *>(levelDic->objectForKey("total_x")));
		xyArr->addObject(dynamic_cast<String *>(levelDic->objectForKey("total_y")));
		xyArr->addObject(dynamic_cast<String *>(levelDic->objectForKey("score")));
		auto xString = (String *)xyArr->objectAtIndex(0);
		log("xyArr x=%s", xString->getCString());
		xy_data.insert(key->intValue(), xyArr);
		auto imgArr = dynamic_cast<Array *>(levelDic->objectForKey("imageidarr"));
		level_data.insert(key->intValue(), imgArr);
		for (unsigned imgCount = 0; imgCount < imgArr->count(); imgCount++) {
			auto idString = (String *)(imgArr->objectAtIndex(imgCount));
			log("idString imgid=%d", idString->intValue());
		}
	}
	auto xie = xy_data.at(1);
	auto xString = (String *)xie->objectAtIndex(0);
	log("xie x=%s", xString->getCString());

}


void GameData::getLevelXY(int &x, int &y,int &score,int level) {
	if (level == 0) {
		level = this->getChooseLevel();
	}
	log("getLevelXY %d", level);
	auto xyArr = (Array* )xy_data.at(level);
	x = ((String *)xyArr->objectAtIndex(0))->intValue();
	y = ((String *)xyArr->objectAtIndex(1))->intValue();
	score = ((String *)xyArr->objectAtIndex(2))->intValue();
}

Array* GameData::getLevelData(int level) {
	if (level > this->getLevelCount()) {
		return NULL;
	}
	if (level == 0) {
		level = this->getChooseLevel();
	}
	return (Array*)level_data.at(level);
}

int GameData::getLevelCount() {
	return level_data.size();
}

void GameData::playOrStopMusic() {
	if( is_pause==false )
    {
		Audio::getInstance()->pauseAllEffects();
    }
    else
    {
		Audio::getInstance()->resumeAllEffects();
    }
}