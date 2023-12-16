#include "Imagine_Log/ConsoleAppender.h"

namespace Imagine_Tool
{

namespace Imagine_Log
{

ConsoleAppender::ConsoleAppender() : LogAppender()
{
}

ConsoleAppender::~ConsoleAppender()
{
}

LogAppender* ConsoleAppender::WriteLog(const std::string& str)
{
    std::unique_lock<std::mutex> lock(lock_);
    printf("%s\n", str.c_str());

    return this;
}

} // namespace Imagine_Log

} // namespace Imagine_Tool
