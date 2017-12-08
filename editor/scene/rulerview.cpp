#include "rulerview.hpp"
#include "rulerline.hpp"

#include <QDebug>

namespace ee {
using Self = RulerView;

Self* Self::create() {
    auto result = new Self();
    result->init();
    result->autorelease();
    return result;
}

bool Self::init() {
    if (not Super::init()) {
        return false;
    }
    dirty_ = true;
    setMinDisplayLength(1.0f);
    setMaxDisplayLength(1.0f);
    scheduleUpdate();
    return true;
}

void Self::onEnter() {
    Super::onEnter();
}

void Self::onExit() {
    Super::onExit();
}

void Self::update(float delta) {
    Q_UNUSED(delta);
    if (dirty_) {
        updateView();
        dirty_ = false;
    }
}

Self* Self::setLineWidth(float width) {
    if (std::abs(lineWidth_ - width) <= std::numeric_limits<float>::epsilon()) {
        return this;
    }
    lineWidth_ = width;
    dirty_ = true;
    return this;
}

Self* Self::setUnitLength(float length) {
    if (std::abs(unitLength_ - length) <=
        std::numeric_limits<float>::epsilon()) {
        return this;
    }
    unitLength_ = length;
    dirty_ = true;
    return this;
}

Self* Self::setMinDisplayLength(float length) {
    if (std::abs(minDisplayLength_ - length) <=
        std::numeric_limits<float>::epsilon()) {
        return this;
    }
    minDisplayLength_ = length;
    dirty_ = true;
    return this;
}

Self* Self::setMaxDisplayLength(float length) {
    if (std::abs(maxDisplayLength_ - length) <=
        std::numeric_limits<float>::epsilon()) {
        return this;
    }
    maxDisplayLength_ = length;
    dirty_ = true;
    return this;
}

Self* Self::setOrigin(const cocos2d::Point& position) {
    if (origin_ == position) {
        return this;
    }
    origin_ = position;
    dirty_ = true;
    return this;
}

Self* Self::setRegion(const cocos2d::Size& region) {
    if (region_.equals(region)) {
        return this;
    }
    region_ = region;
    dirty_ = true;
    return this;
}

void Self::updateViewBegin() {
    lineIndex_ = 0;
}

void Self::updateViewEnd() {
    while (lineIndex_ < rulerLines_.size()) {
        auto&& line = rulerLines_.at(lineIndex_++);
        line->setVisible(false);
    }
}

RulerLine* Self::createLine() {
    if (lineIndex_ >= rulerLines_.size()) {
        auto line = RulerLine::create();
        addChild(line);
        rulerLines_.push_back(line);
    }
    auto&& line = rulerLines_.at(lineIndex_++);
    line->setVisible(true);
    return line;
}

void Self::updateView() {
    updateViewBegin();
    auto minUnits = maxDisplayLength_ / unitLength_;

    constexpr auto maxUnits = 100000.0f;
    auto units = maxUnits;

    auto findUnits = [&units, minUnits](float base) {
        while (base < units) {
            if (minUnits <= base) {
                units = base;
                return true;
            }
            base *= 10;
        }
        return false;
    };
    auto base5 = findUnits(0.10f) && findUnits(0.05f);

    qDebug() << "Update ruler: units = " << units;
    auto length = units * unitLength_;
    auto subLength = length / (base5 ? 5 : 2);

    auto offsetX = std::fmod(origin_.x, length);
    auto offsetY = std::fmod(origin_.y, length);
    for (auto x = offsetX - length; x <= region_.width + length; x += length) {
        drawVerticalLine(x, 255, true);
        drawLines(base5, x, subLength, 255 / 15,
                  std::bind(&Self::drawVerticalLine, this,
                            std::placeholders::_1, std::placeholders::_2,
                            false));
    }
    for (auto y = offsetY - length; y <= region_.height + length; y += length) {
        drawHorizontalLine(y, 255, true);
        drawLines(base5, y, subLength, 255 / 15,
                  std::bind(&Self::drawHorizontalLine, this,
                            std::placeholders::_1, std::placeholders::_2,
                            false));
    }
    updateViewEnd();
}

void Self::drawLines(bool base5, float from, float length, int opacity,
                     const Drawer& drawer) {
    auto delta = length - minDisplayLength_;
    if (delta <= 0) {
        return;
    }
    if (base5) {
        for (int i = 0; i < 5; ++i) {
            auto next = from + length;
            if (i + 1 < 5) {
                drawer(next, opacity);
            }
            drawLines(false, from, length / 2, opacity / 3, drawer);
            from = next;
        }
    } else {
        for (int i = 0; i < 2; ++i) {
            auto next = from + length;
            if (i + 1 < 2) {
                drawer(next, opacity);
            }
            drawLines(true, from, length / 5, opacity / 3, drawer);
            from = next;
        }
    }
}

void Self::drawVerticalLine(float x, int opacity, bool showCoordinate) {
    auto layer = createLine();
    layer->setPosition(cocos2d::Point(x, 0));
    layer->setLineWidth(lineWidth_)
        ->alignVertical(region_.height)
        ->setLineOpacity(opacity);
    if (showCoordinate) {
        auto coordinate = (x - origin_.x) / unitLength_;
        layer->setCoordinate(coordinate);
    } else {
        layer->hideCoordinate();
    }
}

void Self::drawHorizontalLine(float y, int opacity, bool showCoordinate) {
    auto layer = createLine();
    layer->setPosition(cocos2d::Point(0, y));
    layer->setLineWidth(lineWidth_)
        ->alignHorizontal(region_.width)
        ->setLineOpacity(opacity);
    if (showCoordinate) {
        auto coordinate = (y - origin_.y) / unitLength_;
        layer->setCoordinate(coordinate);
    } else {
        layer->hideCoordinate();
    }
}
} // namespace ee
