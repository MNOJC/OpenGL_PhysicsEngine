//
// Created by natha on 10/09/2025.
//

#pragma once

#include <string>
#include <map>
#include <functional>

class CallbackRegistry {
public:

    static CallbackRegistry& Instance() {
        static CallbackRegistry instance; 
        return instance;
    }


    void RegisterCallback(const std::string& name, std::function<void()> callback) 
    {
        m_callbacks[name] = callback;
    }

    void ExecuteCallback(const std::string& name)
    {
        if (m_callbacks.contains(name)) {
            m_callbacks[name](); 
        }
    }

private:
    
    CallbackRegistry() = default; 
    std::map<std::string, std::function<void()>> m_callbacks;
};
