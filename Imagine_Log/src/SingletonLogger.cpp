#include "Imagine_Log/SingletonLogger.h"

#include "yaml-cpp/yaml.h"

namespace Imagine_Tool
{

namespace Imagine_Log
{

Logger* SingletonLogger::logger_;

Logger*& SingletonLogger::GetInstance()
{
    // 懒汉单例
    if (logger_ == nullptr) {
        std::unique_lock<std::mutex> lock(lock_);
        if (logger_ == nullptr) {
            logger_ = new SingletonLogger();
        }
    }

    return logger_;
}

Logger*& SingletonLogger::GetInstance(const std::string& profile_path)
{
    // 懒汉单例
    if (logger_ == nullptr) {
        std::unique_lock<std::mutex> lock(lock_);
        if (logger_ == nullptr) {
            logger_ = new SingletonLogger(profile_path);
        }
    }

    return logger_;
}

Logger*& SingletonLogger::GetInstance(const YAML::Node& config)
{
    // 懒汉单例
    if (logger_ == nullptr) {
        std::unique_lock<std::mutex> lock(lock_);
        if (logger_ == nullptr) {
            logger_ = new SingletonLogger(config);
        }
    }

    return logger_;
}

Logger*& SingletonLogger::SetInstance(Logger*& logger)
{
    return logger;
}

Logger* SingletonLogger::DestroyInstance()
{
    std::unique_lock<std::mutex> lock(lock_);
    if (logger_ != nullptr) {
        delete logger_;
        logger_ = nullptr;
    }

    return logger_;
}

SingletonLogger::SingletonLogger() : Logger()
{
}

SingletonLogger::SingletonLogger(const std::string& profile_path) : Logger()
{
    Init(profile_path);
}

SingletonLogger::SingletonLogger(const YAML::Node& config) : Logger()
{
    Init(config);
}

SingletonLogger::~SingletonLogger()
{
}

Logger* SingletonLogger::Init(const std::string& profile_path)
{
    static bool is_init = false;
    if (is_init) {
        return this;
    }
    is_init = true;
    YAML::Node config = YAML::LoadFile(profile_path);
    
    return Init(config);
}

Logger* SingletonLogger::Init(const YAML::Node& config)
{
    static bool is_init = false;
    if (is_init) {
        return this;
    }
    is_init = true;
    Logger::Init(config);

    return this;
}

} // namespace Imagine_Log

} // namesapce Imagine_Tool