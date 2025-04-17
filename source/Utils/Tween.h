#pragma once

#include <atomic>
#include <functional>
#include <list>
#include <thread>
#include <mutex>

enum class tweenStyle
{
    Linear = 0,
    Square,
    Cube
};
std::function<float(float)> getFunctionFormulaFromStyle(tweenStyle style);

class TweenService
{
public:
    TweenService(float duraction, bool isReversed = false,
        std::function<void()> eventFunc_Step = nullptr, std::function<void()> eventFunc_EndTween = nullptr);
    ~TweenService();

    template<typename T>
    void addTween(T& tweenValue, T end, tweenStyle style)
    {
        TweenModule<T>* newModule = new TweenModule<T>(tweenValue, end, style, m_duration);
        m_tweens.push_back(newModule);
    }

    bool removeLastTween();
    void setEventFunc_Step(std::function<void()> func);
    void setEventFunc_EndTween(std::function<void()> func);
    void play();
    void stop();
    void resetAll();
    bool isPlaying();
    float getCurrentDuration();
private:
    std::function<void()> m_eventFunc_Step;
    std::function<void()> m_eventFunc_EndTween;

    float m_duration;

    bool m_isReverse;
    bool m_isActualReversed;

    bool m_isRunning = false;
    float m_time = 0;

    std::mutex m_workerMutex;
    std::thread m_worker;
    void m_tweensFinish();
    void m_tweensContinue();
    void m_tweensReset();
    void m_workFunc();

    class TweenBase
    {
    public:
        TweenBase(); // float duration, tweenStyle style = tweenStyle::Linear, bool isReverse = false
        virtual ~TweenBase();
    protected:
        friend class TweenService;

        virtual void reset() = 0;
        virtual void resetAll() = 0;
        virtual void tweenFinish() = 0;
        virtual void tweenContinue(float time) = 0;
        virtual void updateValue() = 0;

        virtual void m_genDistanation() = 0;
    };

    template<typename T>
    class TweenModule : public TweenBase
    {
    public:
        friend class TweenService;
        ~TweenModule() {}
    private:
        TweenModule(T& tweenValue, T end, tweenStyle style, float duration)
            : m_value_ptr(tweenValue),
            m_origStart(tweenValue), m_origEnd(end),
            m_start(tweenValue), m_end(end),
            m_styleCalcFunc(getFunctionFormulaFromStyle(style))
        {
            m_styledDuration = m_styleCalcFunc(duration);
            m_genDistanation();
        }
    protected:
        T& m_value_ptr;
        T m_value;
        T m_origStart, m_origEnd;
        T m_start, m_end;
        T m_distanation;

        std::function<float(float)> m_styleCalcFunc;
        float m_styledDuration;

        virtual void resetAll() override
        {
            m_start = m_origStart;
            m_end = m_origEnd;
            m_value = m_origStart;
            m_value_ptr = m_value;
            m_genDistanation();
        }

        virtual void reset() override
        {
            m_start = m_value;
            m_end = m_origEnd;
            m_genDistanation();
        }

        virtual void tweenFinish()
        {
            T tempEnd = m_end;
            m_end = m_start;
            m_start = tempEnd;
            m_genDistanation();

            m_value = tempEnd;
        }

        virtual void tweenContinue(float time) override
        {
            m_value = m_distanation * (m_styleCalcFunc(time) / m_styledDuration) + m_start;
        }

        virtual void updateValue() override
        {
            m_value_ptr = m_value;
        }

        virtual void m_genDistanation() override
        {
            m_distanation = m_end - m_start;
        }
    };

    std::list<TweenBase*> m_tweens;
};

