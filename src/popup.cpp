#include "popup.h"


CCMenuItemToggler* createToggler(CCObject* target, CCPoint pos, const std::string& text, CCLayer* layer) {
    CCSprite* onSpr = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
    CCSprite* offSpr = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");

    std::string id = text;
    std::replace(id.begin(), id.end(), ' ', '-');

    CCMenuItemToggler* toggler = CCMenuItemToggler::create(offSpr, onSpr, target, nullptr);
    toggler->setScale(0.63f);
    toggler->setPosition(pos);
    toggler->setID(id + "-toggler");

    CCLabelBMFont* label = CCLabelBMFont::create(text.c_str(), "bigFont.fnt");
    label->setScale(0.45f);
    label->setAnchorPoint({ 0.f, 0.5f });
    label->setPosition(pos.x + 20.f, pos.y + 2.f);

    layer->addChild(toggler);
    layer->addChild(label);
    layer->updateLayout();

    return toggler;
}


bool searchSimilarPopup::setup(std::string const& value) {
    this->setTitle(value.c_str());
 
    CCMenu* buttonsMenu = CCMenu::create();
    buttonsMenu->setPosition(0.f, 0.f);
    buttonsMenu->setID("buttons-menu");
    m_mainLayer->addChild(buttonsMenu);
 
    difficultyToggler = createToggler(this, { 40.f, 205.f }, "same difficulty", buttonsMenu);
    featureToggler = createToggler(this, { 40.f, 165.f }, "same feature", buttonsMenu);
    lengthToggler = createToggler(this, { 40.f, 125.f }, "same length", buttonsMenu);
    songToggler = createToggler(this, { 40.f, 85.f }, "same song", buttonsMenu);
    ratedOnlyToggler = createToggler(this, { 340.f, 205.f }, "rated only", buttonsMenu);
    noStarsToggler = createToggler(this, { 340.f, 165.f }, "no stars", buttonsMenu);

    CCMenuItemSpriteExtra* searchButton = CCMenuItemSpriteExtra::create(ButtonSprite::create("Search"), this, menu_selector(searchSimilarPopup::onSearch));
    searchButton->setPosition({240.f, 35.f});
    
    buttonsMenu->addChild(searchButton);
    buttonsMenu->updateLayout();

    return true;
}


searchSimilarPopup* searchSimilarPopup::create(std::string const& text, GJGameLevel* level) {
    auto ret = new searchSimilarPopup();
    
    if (ret->initAnchored(480.f, 280.f, text)) {
        ret->currentLevel = level;
        ret->autorelease();
        return ret;
    }
    
    delete ret;
    return nullptr;
}


void searchSimilarPopup::onSearch(CCObject* sender) {
    // featured 
    bool featuredFilter = false;
    bool epicFilter = false;
    bool mythicFilter = false;
    bool legendaryFilter = false;
    
    if (this->featureToggler->isOn()) {
        featuredFilter = currentLevel->m_featured != 0 && currentLevel->m_isEpic == 0;
        epicFilter = currentLevel->m_isEpic == 1;
        mythicFilter = currentLevel->m_isEpic == 2;
        legendaryFilter = currentLevel->m_isEpic == 3;
    }


    // difficulty
    std::string difficulty = "-1,-2,-3,1,2,3,4,5";
    if (this->difficultyToggler->isOn()) {
        difficulty = std::to_string(currentLevel->getAverageDifficulty());
        
        if (this->currentLevel->m_autoLevel) {
            difficulty = "-3";
        }

        if (this->currentLevel->m_demon.value() == 1) {
            int demonDiff = this->currentLevel->m_demonDifficulty;

            switch (demonDiff) {
                case 3: difficulty = "6"; break;
                case 4: difficulty = "7"; break;
                case 0: difficulty = "8"; break;
                case 5: difficulty = "9"; break;
                case 6: difficulty = "10"; break;
            }
        }
    }


    // length
    std::string length = "0,1,2,3,4,5";
    if (this->lengthToggler->isOn()) {
        length = std::to_string(this->currentLevel->m_levelLength);
    }


    // song
    bool songFilter = false;
    bool customSongFilter = false;
    int songID = 0;
    if (this->songToggler->isOn()) {
        songFilter = true;

        // Stereo Madness's track ID is 0. That's the game bug
        if (this->currentLevel->m_audioTrack != 0) {
            songID = this->currentLevel->m_audioTrack;
        }

        if (this->currentLevel->m_songID != 0) {
            customSongFilter = true;
            songID = this->currentLevel->m_songID;
        }
    }


    // search object
    GJSearchObject* searchObject = GJSearchObject::create(SearchType::Search);
    
    searchObject->m_difficulty = difficulty;
    searchObject->m_length = length;
    
    searchObject->m_starFilter = this->ratedOnlyToggler->isOn();
    searchObject->m_noStarFilter = this->noStarsToggler->isOn();
    
    searchObject->m_featuredFilter = featuredFilter;
    searchObject->m_epicFilter = epicFilter;
    searchObject->m_legendaryFilter = legendaryFilter;
    searchObject->m_mythicFilter = mythicFilter;

    searchObject->m_songID = songID;
    searchObject->m_customSongFilter = customSongFilter;
    searchObject->m_songFilter = songFilter;

    CCDirector::get()->pushScene(CCTransitionFade::create(.5f, LevelBrowserLayer::scene(searchObject)));
}
