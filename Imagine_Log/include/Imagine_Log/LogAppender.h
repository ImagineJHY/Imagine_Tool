#ifndef IMAGINE_TOOL_LOGAPPENDER_H
#define IMAGINE_TOOL_LOGAPPENDER_H

#include <string>
#include <mutex>

namespace Imagine_Tool
{

class LogAppender
{
 public:
    LogAppender(){};

    virtual ~LogAppender(){};

    virtual bool WriteLog(std::string str) = 0;

 protected:
    std::mutex lock_;
};


} // namespace Imagine_Tool

#endif