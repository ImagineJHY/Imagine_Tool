#include "Imagine_Log/Logger.h"

#include "yaml-cpp/yaml.h"
#include "Imagine_Time/Imagine_Time.h"
#include "Imagine_Log/FileAppender.h"
#include "Imagine_Log/common_definition.h"

#include <fcntl.h>

namespace Imagine_Tool
{

namespace Imagine_Log
{

std::mutex Logger::lock_;

Logger*& Logger::GetInstance()
{
    static Logger* logger = nullptr;
    
    return logger;
}

Logger*& Logger::SetInstance(Logger*& logger_instance)
{
    Logger*& logger = GetInstance();
    logger = logger_instance;

    return logger;
}

Logger::Logger(): async_write_(false)
{
}

Logger::Logger(const Logger& logger)
{
}

Logger::~Logger()
{
}

Logger* Logger::Init(const std::string& profile_path)
{
    if (profile_path == "") {
        throw std::exception();
    }

    YAML::Node config = YAML::LoadFile(profile_path);

    return Init(config);
}

Logger* Logger::Init(const YAML::Node& config)
{
    log_name_ = config[YAML_KEYWORDS_LOG_NAME].as<std::string>();
    log_path_ = config[YAML_KEYWORDS_LOG_PATH].as<std::string>();
    async_write_ = config[YAML_KEYWORDS_ASYNC_LOG].as<bool>();
    log_title_ = config[YAML_KEYWORDS_LOG_TITLE].as<std::string>();
    time_stamp_ = config[YAML_KEYWORDS_LOG_WITH_TIMESTAMP].as<bool>();
    max_log_size_ = config[YAML_KEYWORDS_MAX_LOG_FILE_SIZE].as<size_t>();

    if (async_write_) {

    } else {
        appender_ = new FileAppender(log_name_, log_path_, max_log_size_);
    }

    return this;
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

std::string Logger::GenerateLogHeader() const
{
    std::string header;
    if (time_stamp_) {
        header += LOG_KEYWORDS_LEFT_TAG + std::to_string(NOW_MS) + LOG_KEYWORDS_RIGHT_TAG;
    }
    if (log_title_ != "") {
        header += LOG_KEYWORDS_LEFT_TAG + log_title_ + LOG_KEYWORDS_RIGHT_TAG;
    }
    header += LOG_KEYWORDS_AND_CONTENT_DIVIDER;

    return header;
}

} // namespace Imagine_Log

} // namespace Imagine_Tool