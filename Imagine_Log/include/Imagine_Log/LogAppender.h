#ifndef IMAGINE_LOG_LOGAPPENDER_H
#define IMAGINE_LOG_LOGAPPENDER_H

#include <string>
#include <mutex>

namespace Imagine_Tool
{

namespace Imagine_Log
{

class LogAppender
{
 public:
    LogAppender();

    virtual ~LogAppender();

    virtual LogAppender* WriteLog(const std::string& str) = 0;

 protected:
    std::mutex lock_;
};

} // namespace Imagine_Log

} // namespace Imagine_Tool

#endif