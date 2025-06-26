#pragma once
#include <Geode/ui/Popup.hpp>
#include <Geode/Geode.hpp>

using namespace geode::prelude;

CCMenuItemToggler* createToggle(CCObject* target, CCPoint pos, const std::string& text, CCLayer* layer);


class searchSimilarPopup : public geode::Popup<std::string const&> {
public:
    bool setup(std::string const& value) override;
    void onSearch(CCObject* sender);
    static searchSimilarPopup* create(std::string const& text, GJGameLevel* level);

private:
    GJGameLevel* currentLevel = nullptr;
    
    CCMenuItemToggler* difficultyToggler = nullptr;
    CCMenuItemToggler* featureToggler = nullptr;
    CCMenuItemToggler* lengthToggler = nullptr;
    CCMenuItemToggler* songToggler = nullptr;
    
    CCMenuItemToggler* ratedOnlyToggler = nullptr;
    CCMenuItemToggler* noStarsToggler = nullptr;
};
