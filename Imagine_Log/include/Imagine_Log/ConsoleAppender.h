#ifndef IMAGINE_LOG_CONSOLEAPPENDER_H
#define IMAGINE_LOG_CONSOLEAPPENDER_H

#include "LogAppender.h"

#include <string>

namespace Imagine_Tool
{

namespace Imagine_Log
{

class LogAppender;

class ConsoleAppender : public LogAppender
{
 public:
    ConsoleAppender();

    ~ConsoleAppender();
    
    LogAppender* WriteLog(const std::string& str);
};

} // namespace Imagine_Log

} // namespace Imagine_Tool

#endif