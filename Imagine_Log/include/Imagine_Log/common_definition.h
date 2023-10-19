#ifndef IMAGINE_TOOL_LOG_COMMON_DEFINITION_H
#define IMAGINE_TOOL_LOG_COMMON_DEFINITION_H

namespace Imagine_Tool
{

#define LOG_DEBUG(LOG_MESSAGE...) Imagine_Tool::SingletonLogger::GetInstance()->Log(Imagine_Tool::Logger::LogLevel::Debug, LOG_MESSAGE)
#define LOG_WARN(LOG_MESSAGE...) Imagine_Tool::SingletonLogger::GetInstance()->Log(Imagine_Tool::Logger::LogLevel::Warn, LOG_MESSAGE)
#define LOG_INFO(LOG_MESSAGE...) Imagine_Tool::SingletonLogger::GetInstance()->Log(Imagine_Tool::Logger::LogLevel::Info, LOG_MESSAGE)
#define LOG_ERROR(LOG_MESSAGE...) Imagine_Tool::SingletonLogger::GetInstance()->Log(Imagine_Tool::Logger::LogLevel::Error, LOG_MESSAGE)
#define LOG_fATAL(LOG_MESSAGE...) Imagine_Tool::SingletonLogger::GetInstance()->Log(Imagine_Tool::Logger::LogLevel::Fatal, LOG_MESSAGE)
// #define LOG_#NAME(LOG_MESSAGE) Logger::GetInstance()->Log(Logger::LogLevel::##NAME, LOG_MESSAGE)

} // namespace Imagine_Tool

#endif