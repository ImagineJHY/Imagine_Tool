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

private:
    static void SetInstance(Logger* logger){};

 public:
    SingletonLogger();

    ~SingletonLogger() {};

   using Logger::Init;
    bool Init(std::string profile_path);
 
 private:
  static Logger* logger_;
};

} // namespace Imagine_Tool

#endif