#ifndef IMAGINE_TOOL_NONSINGLETONLOGGER_H
#define IMAGINE_TOOL_NONSINGLETONLOGGER_H

#include "Imagine_Log/Logger.h"

namespace Imagine_Tool
{

class NonSingletonLogger : public Logger
{

 public:
    NonSingletonLogger(){};

    ~NonSingletonLogger(){};
};

} // namespace Imagine_Tool

#endif