//
// Created by natha on 05/09/2025.
//

#include "Time.h"
#include <iostream>
#include <sstream>
#include <iomanip>

Time::Time() : m_deltaTime(0.0f), m_fixedDeltaTime(0.016f), m_currentTime(0.0f), m_timeScale(1.0f), m_fps(0), m_frameCount(0), m_fpsUpdateTime(0.0f), m_paused(false)
{
    m_startTime = Clock::now();
    m_lastFrameTime = m_startTime;
    m_currentFrameTime = m_startTime;
}

void Time::Update()
{
    if (m_paused)
    {
        m_deltaTime = 0.0f;
        return;
    }

    m_currentFrameTime = Clock::now();

    std::chrono::duration<float> realChronoDelta = m_currentFrameTime - m_lastFrameTime;
    float realDeltaTime = realChronoDelta.count();

    m_deltaTime = realDeltaTime * m_timeScale;
    m_currentTime += m_deltaTime;

    m_frameCount++;
    m_fpsUpdateTime += realDeltaTime;

    if (m_fpsUpdateTime >= 1.0f)
    { 
        m_fps = m_frameCount;
        m_frameCount = 0;
        m_fpsUpdateTime = 0.0f;
    }

    m_lastFrameTime = m_currentFrameTime;
}

void Time::TogglePause()
{
    m_paused = !m_paused;
}

std::string Time::GetFormattedTime() const
{
    int totalSeconds = static_cast<int>(m_currentTime);
    int hours = totalSeconds / 3600;
    int minutes = (totalSeconds % 3600) / 60;
    int seconds = totalSeconds % 60;
    int milliseconds = static_cast<int>((m_currentTime - totalSeconds) * 1000);
    
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << hours << ":"
       << std::setfill('0') << std::setw(2) << minutes << ":"
       << std::setfill('0') << std::setw(2) << seconds << "."
       << std::setfill('0') << std::setw(3) << milliseconds;
    
    return ss.str();
}




