#include "Imagine_Log/SingletonLogger.h"

namespace Imagine_Tool
{

Logger* SingletonLogger::logger_;

Logger* SingletonLogger::GetInstance()
{
    if (logger_ == nullptr) {
        std::unique_lock<std::mutex> lock(lock_);
        if (logger_ == nullptr) {
            logger_ = new Logger();
        }
    }

    return logger_;
}

bool SingletonLogger::DestroyInstance()
{
    std::unique_lock<std::mutex> lock(lock_);
    if (logger_ != nullptr) {
        delete logger_;
        logger_ = nullptr;

        return true;
    }

    return false;
}

bool SingletonLogger::Init(std::string profile_path)
{
    static bool is_init = false;
    if (is_init) {
        return true;
    }
    is_init = true;
    YAML::Node config = YAML::LoadFile(profile_path);
    Init(config);

    return true;
}

} // namesapce Imagine_Tool