//
// Created by natha on 05/09/2025.
//

#pragma once

#include <chrono>
#include <string>

class Time {

public:

    Time();

    void Update();

    float GetDeltaTime() const { return m_deltaTime; }
    float GetFixedDeltaTime() const { return m_fixedDeltaTime; }
    float GetTime() const { return m_currentTime; }
    float GetTimeScale() const { return m_timeScale; }
    int GetFPS() const { return m_fps; }
    bool IsPaused() const { return m_paused; }

    void SetTimeScale(float scale) { m_timeScale = scale; }
    void SetPaused(bool paused) { m_paused = paused; }
    void SetFixedDeltaTime(float fixedDt) { m_fixedDeltaTime = fixedDt; }

    std::string GetFormattedTime() const;
    void TogglePause();

private:

    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = std::chrono::time_point<Clock>;

    TimePoint m_startTime;
    TimePoint m_lastFrameTime;
    TimePoint m_currentFrameTime;

    float m_deltaTime;
    float m_fixedDeltaTime;
    float m_currentTime;
    float m_timeScale;

    int m_fps;
    int m_frameCount;
    float m_fpsUpdateTime;

    bool m_paused;
};


