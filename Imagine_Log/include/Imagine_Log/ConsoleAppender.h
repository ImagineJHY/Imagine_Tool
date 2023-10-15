#ifndef IMAGINE_TOOL_CONSOLEAPPENDER_H
#define IMAGINE_TOOL_CONSOLEAPPENDER_H

#include "LogAppender.h"

namespace Imagine_Tool
{

class ConsoleAppender : public LogAppender
{
 public:
    bool WriteLog(std::string str)
    {
        std::unique_lock<std::mutex> lock(lock_);
        printf("%s\n", str.c_str());

        return true;
    }
};

} // namespace Imagine_Tool

#endif