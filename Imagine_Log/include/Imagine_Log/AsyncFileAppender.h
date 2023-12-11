#ifndef IMAGINE_TOOL_ASYNCFILEAPPENDER_H
#define IMAGINE_TOOL_ASYNCFILEAPPENDER_H

#include "LogAppender.h"

namespace Imagine_Tool
{

namespace Imagine_Log
{

class AsyncFileAppender : public LogAppender
{
 public:
    AsyncFileAppender();

    ~AsyncFileAppender();

    LogAppender* WriteLog(const std::string& str) = 0;
};

} // namespace Imagine_Log

} // namespace Imagine_Tool

#endif