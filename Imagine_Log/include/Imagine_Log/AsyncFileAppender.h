#ifndef IMAGINE_TOOL_ASYNCFILEAPPENDER_H
#define IMAGINE_TOOL_ASYNCFILEAPPENDER_H

#include "LogAppender.h"

namespace Imagine_Tool
{

class AsyncFileAppender : public LogAppender
{
 public:
    AsyncFileAppender();

    ~AsyncFileAppender();

    bool WriteLog(std::string str);
};

} // namespace Imagine_Tool

#endif