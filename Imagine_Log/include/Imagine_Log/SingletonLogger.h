#ifndef IMAGINE_LOG_SINGLETONLOGGER_H
#define IMAGINE_LOG_SINGLETONLOGGER_H

#include "Logger.h"

namespace Imagine_Tool
{

namespace Imagine_Log
{

class SingletonLogger : public Logger
{
 public:
    static Logger*& GetInstance();

    static Logger*& GetInstance(const std::string& profile_path);

    static Logger*& GetInstance(const YAML::Node& config);

    static Logger* DestroyInstance();

private:
    static Logger*& SetInstance(Logger*& logger);

 public:
    SingletonLogger();

    SingletonLogger(const std::string& profile_path);

    SingletonLogger(const YAML::Node& config);

    ~SingletonLogger();

    Logger* Init(const std::string& profile_path);

    Logger* Init(const YAML::Node& config);
 
 private:
  static Logger* logger_;
};

} // namespace Imagine_Log

} // namespace Imagine_Tool

#endif