#ifndef IMAGINE_LOG_NONSINGLETONLOGGER_H
#define IMAGINE_LOG_NONSINGLETONLOGGER_H

#include "Imagine_Log/Logger.h"

namespace Imagine_Tool
{

namespace Imagine_Log
{

class NonSingletonLogger : public Logger
{

 public:
    NonSingletonLogger();

    ~NonSingletonLogger();
};

} // namespace Imagine_Log

} // namespace Imagine_Tool

#endif