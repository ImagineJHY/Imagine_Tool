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

} // namesapce Imagine_Tool