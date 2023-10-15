#ifndef IMAGINE_TOOL_SINGLETONLOGGER_H
#define IMAGINE_TOOL_SINGLETONLOGGER_H

#include "Imagine_Log/Logger.h"

namespace Imagine_Tool
{

class SingletonLogger : public Logger
{
 public:
    static Logger* GetInstance();

    static bool DestroyInstance();

 public:
    SingletonLogger();

    ~SingletonLogger() {};
 
 private:
  static Logger* logger_;
};

} // namespace Imagine_Tool

#endif