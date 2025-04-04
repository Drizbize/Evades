#include "Tween.h"

std::function<float(float)> getFunctionFormulaFromStyle(tweenStyle style)
{
    switch (style)
    {
    case tweenStyle::Linear:
        return [](float value) -> float { return value; };
    case tweenStyle::Square:
        return [](float value) -> float { return value * value; };
    case tweenStyle::Cube:
        return [](float value) -> float { return value * value * value; };
    default:
        return [](float value) -> float { return value; };
    }
}

TweenService::TweenBase::TweenBase()
{
}

TweenService::TweenBase::~TweenBase()
{
}

TweenService::TweenService(float duraction, bool isReversed,
    std::function<void()> eventFunc_Step, std::function<void()> eventFunc_EndTween)
    : m_duration(duraction),
    m_isReverse(isReversed), m_isActualReversed(isReversed),
    m_eventFunc_Step(eventFunc_Step), m_eventFunc_EndTween(eventFunc_EndTween)
{
}

TweenService::~TweenService()
{
    for (TweenBase* tweenModule : m_tweens)
    {
        delete tweenModule;
    }
}

inline bool TweenService::removeLastTween()
{
    if (m_tweens.empty()) return false;

    m_tweens.pop_back();
    return true;
}

void TweenService::setEventFunc_Step(std::function<void()> func)
{
    m_eventFunc_Step = func;
}

void TweenService::setEventFunc_EndTween(std::function<void()> func)
{
    m_eventFunc_EndTween = func;
}

void TweenService::start()
{
    m_isRunning = true;
}

void TweenService::stop()
{
    m_isRunning = false;
}

void TweenService::reset()
{
    m_time = 0;
    m_isRunning = false;
    m_isActualReversed = m_isReverse;
    m_tweensReset();
}

bool TweenService::play(float dt)
{
    if (!m_isRunning) return false;

    m_time += dt;

    if (m_time >= m_duration)
    {
        m_tweensFinish();
    }
    else
    {
        m_tweensContinue();
    }

    return true;
}

bool TweenService::isPlaying()
{
    return m_isRunning;
}

float TweenService::getCurrentDuration()
{
    return m_time;
}

void TweenService::m_tweensFinish()
{
    m_time = 0;
    if (!m_isActualReversed)
    {
        m_isRunning = false;
        if (m_isReverse)
        {
            for (TweenBase* tweenModule : m_tweens) {
                tweenModule->tweenFinish();
            }
            m_isActualReversed = true;
        }
    }
    else
    {
        for (TweenBase* tweenModule : m_tweens) {
            tweenModule->tweenFinish();
        }
        m_isActualReversed = false;
    }

    if (m_eventFunc_Step)
    {
        m_eventFunc_Step();
    }
    if (m_eventFunc_EndTween)
    {
        m_eventFunc_EndTween();
    }
}

void TweenService::m_tweensContinue()
{
    for (TweenBase* tweenModule : m_tweens) {
        tweenModule->tweenContinue(m_time);
    }
    if (m_eventFunc_Step)
    {
        m_eventFunc_Step();
    }
}

void TweenService::m_tweensReset()
{
    for (TweenBase* tweenModule : m_tweens) {
        tweenModule->reset();
    }
    if (m_eventFunc_Step)
    {
        m_eventFunc_Step();
    }
}
