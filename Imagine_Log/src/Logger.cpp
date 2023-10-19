#include "Imagine_Log/Logger.h"

#include <fcntl.h>
#include <stdarg.h>

namespace Imagine_Tool
{
    
std::mutex Logger::lock_;

Logger*& Logger::GetInstance()
{
    static Logger* logger;
    return logger;
}

void Logger::SetInstance(Logger* logger_instance)
{
    Logger*& logger = GetInstance();
    logger = logger_instance;
}

bool Logger::Init(std::string profile_path)
{
    if (profile_path == "") {
        throw std::exception();
    }

    YAML::Node config = YAML::LoadFile(profile_path);
    Init(config);

    return true;
}

bool Logger::Init(YAML::Node config)
{
    log_name_ = config["log_name"].as<std::string>();
    log_path_ = config["log_path"].as<std::string>();
    async_write_ = config["async_log"].as<bool>();
    log_title_ = config["log_title"].as<std::string>();
    time_stamp_ = config["log_with_timestamp"].as<bool>();
    max_log_size_ = config["max_log_file_size"].as<size_t>();

    if (async_write_) {

    } else {
        appender_ = new FileAppender(log_name_, log_path_, max_log_size_);
    }

    return true;
}

Logger* Logger::Log(LogLevel level, const char* format, ...)
{
    std::string str = GenerateLogHeader() + format;
    va_list args;
    va_start(args, format);
    ::vsnprintf(buffer_, sizeof(buffer_), str.c_str(), args);
    appender_->WriteLog(buffer_);
    va_end(args);

    return this;
}

std::string Logger::GenerateLogHeader()
{
    std::string header;
    if (time_stamp_) {
        header += "[" + std::to_string(NOW_MS) + "]";
    }
    if (log_title_ != "") {
        header += "[" + log_title_ + "]";
    }
    header += ": ";

    return header;
}

} // namespace Imagine_Tool