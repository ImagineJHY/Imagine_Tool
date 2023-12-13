#ifndef IMAGINE_LOG_LOG_MACRO_H
#define IMAGINE_LOG_LOG_MACRO_H

#include "SingletonLogger.h"

#define LOG_DEBUG(LOG_MESSAGE...)   ::Imagine_Tool::Imagine_Log::SingletonLogger::GetInstance()->Log(::Imagine_Tool::Imagine_Log::Logger::LogLevel::Debug, LOG_MESSAGE)
#define LOG_WARN(LOG_MESSAGE...)    ::Imagine_Tool::Imagine_Log::SingletonLogger::GetInstance()->Log(::Imagine_Tool::Imagine_Log::Logger::LogLevel::Warn, LOG_MESSAGE)
#define LOG_INFO(LOG_MESSAGE...)    ::Imagine_Tool::Imagine_Log::SingletonLogger::GetInstance()->Log(::Imagine_Tool::Imagine_Log::Logger::LogLevel::Info, LOG_MESSAGE)
#define LOG_ERROR(LOG_MESSAGE...)   ::Imagine_Tool::Imagine_Log::SingletonLogger::GetInstance()->Log(::Imagine_Tool::Imagine_Log::Logger::LogLevel::Error, LOG_MESSAGE)
#define LOG_fATAL(LOG_MESSAGE...)   ::Imagine_Tool::Imagine_Log::SingletonLogger::GetInstance()->Log(::Imagine_Tool::Imagine_Log::Logger::LogLevel::Fatal, LOG_MESSAGE)
// #define LOG_#NAME(LOG_MESSAGE) Logger::GetInstance()->Log(Logger::LogLevel::##NAME, LOG_MESSAGE)

#endif