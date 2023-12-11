#ifndef IMAGINE_TOOL_LOG_COMMON_DEFINITION_H
#define IMAGINE_TOOL_LOG_COMMON_DEFINITION_H

namespace Imagine_Tool
{

namespace Imagine_Log
{

#define LOG_ENDDING_TAG                     "\r\n"
#define LOG_KEYWORDS_LEFT_TAG               "["
#define LOG_KEYWORDS_RIGHT_TAG              "]"
#define LOG_KEYWORDS_AND_CONTENT_DIVIDER    ": "

#define YAML_KEYWORDS_LOG_NAME              "log_name"
#define YAML_KEYWORDS_LOG_PATH              "log_path"
#define YAML_KEYWORDS_ASYNC_LOG             "async_log"
#define YAML_KEYWORDS_LOG_TITLE             "log_title"
#define YAML_KEYWORDS_LOG_WITH_TIMESTAMP    "log_with_timestamp"
#define YAML_KEYWORDS_MAX_LOG_FILE_SIZE     "max_log_file_size"

#define LOG_DEBUG(LOG_MESSAGE...)   ::Imagine_Tool::Imagine_Log::SingletonLogger::GetInstance()->Log(Imagine_Tool::Logger::LogLevel::Debug, LOG_MESSAGE)
#define LOG_WARN(LOG_MESSAGE...)    ::Imagine_Tool::Imagine_Log::SingletonLogger::GetInstance()->Log(Imagine_Tool::Logger::LogLevel::Warn, LOG_MESSAGE)
#define LOG_INFO(LOG_MESSAGE...)    ::Imagine_Tool::Imagine_Log::SingletonLogger::GetInstance()->Log(Imagine_Tool::Logger::LogLevel::Info, LOG_MESSAGE)
#define LOG_ERROR(LOG_MESSAGE...)   ::Imagine_Tool::Imagine_Log::SingletonLogger::GetInstance()->Log(Imagine_Tool::Logger::LogLevel::Error, LOG_MESSAGE)
#define LOG_fATAL(LOG_MESSAGE...)   ::Imagine_Tool::Imagine_Log::SingletonLogger::GetInstance()->Log(Imagine_Tool::Logger::LogLevel::Fatal, LOG_MESSAGE)
// #define LOG_#NAME(LOG_MESSAGE) Logger::GetInstance()->Log(Logger::LogLevel::##NAME, LOG_MESSAGE)

} // namespace Imagine_Log

} // namespace Imagine_Tool

#endif