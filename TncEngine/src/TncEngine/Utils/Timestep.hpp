#pragma once

#include <chrono>

namespace TncEngine {

    class Timestep
    {
    public:
        Timestep(float time = 0.0f)
            : m_Time(time)
        {
        }

        operator float() { return m_Time; }

        float GetSeconds() { return m_Time; }
        float GetMiliseconds() { return m_Time * 1000.0f; }

    public:
        static float Now()
        {
            return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count() / 1000.0f;
        }
    
    private:
        float m_Time;
    };

    template<typename Fn>
    class Timer
    {
    public:
        Timer(const char* name, Fn&& func)
            : m_Name(name), m_Stopped(false), m_Func(func)
        {
            m_StartTimePoint = std::chrono::steady_clock::now();
        }

        ~Timer()
        {
            if (!m_Stopped)
                Stop();
        }

        void Stop()
        {
            auto endTimePoint = std::chrono::steady_clock::now();

            auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(endTimePoint - m_StartTimePoint).count();

            m_Stopped = true;

            float duration = elapsed / 1000.0f;

            m_Func(m_Name, duration);
        }

    private:
        const char* m_Name;
        std::chrono::time_point<std::chrono::steady_clock> m_StartTimePoint;
        bool m_Stopped;
        Fn m_Func;
    };

}