#ifndef IMAGINE_TOOL_SINGLETONLOGGER_H
#define IMAGINE_TOOL_SINGLETONLOGGER_H

#include "Logger.h"

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
    SingletonLogger() {};

    ~SingletonLogger() {};

    bool Init(std::string profile_path);

    bool Init(YAML::Node config);
 
 private:
  static Logger* logger_;
};

} // namespace Imagine_Tool

#endif