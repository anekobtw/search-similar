#include <Geode/Geode.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include "popup.h"

using namespace geode::prelude;


class $modify(CustomLevelInfoLayer, LevelInfoLayer) {
	bool init(GJGameLevel* level, bool challenge) {
		if (!LevelInfoLayer::init(level, challenge)) return false;
		
		CCMenuItemSpriteExtra* searchSimilarButton = CCMenuItemSpriteExtra::create(CCSprite::create("searchBtn.png"_spr), this, menu_selector(CustomLevelInfoLayer::onSearchSimilar));
		searchSimilarButton->setScale(0.125f);  // because it's too big
		searchSimilarButton->setID("search-similar-button"_spr);
		
		CCNode* leftSideMenu = this->getChildByID("left-side-menu");
		leftSideMenu->addChild(searchSimilarButton);
		leftSideMenu->updateLayout();

		return true;
	}

	void onSearchSimilar(CCObject*) {
		searchSimilarPopup* popup = searchSimilarPopup::create("search similar", this->m_level);
		this->addChild(popup, 1000);
	}
};