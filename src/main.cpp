#include <Geode/Geode.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include "popup.h"

using namespace geode::prelude;


class $modify(CustomLevelInfoLayer, LevelInfoLayer) {
	bool init(GJGameLevel* level, bool challenge) {
		if (!LevelInfoLayer::init(level, challenge)) return false;
		
		auto searchSimilarButton = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("gj_findBtn_001.png"), this, menu_selector(CustomLevelInfoLayer::onSearchSimilar));
		searchSimilarButton->setID("search-similar-button"_spr);
		
		auto leftSideMenu = this->getChildByID("left-side-menu");
		leftSideMenu->addChild(searchSimilarButton);
		leftSideMenu->updateLayout();

		return true;
	}

	void onSearchSimilar(CCObject*) {
		auto popup = searchSimilarPopup::create("search similar", this->m_level);
		this->addChild(popup, 1000);
	}
};