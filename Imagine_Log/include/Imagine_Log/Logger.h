#ifndef IMAGINE_TOOL_LOGGER_H
#define IMAGINE_TOOL_LOGGER_H

#include <string>
#include <mutex>
#include <stdarg.h>

namespace YAML
{

class Node;

} // namespace YAML

namespace Imagine_Tool
{

namespace Imagine_Log
{

class LogAppender;

class Logger
{
 public:
   enum LogLevel
   {
      Debug,
      Warn,
      Info,
      Error,
      Fatal
   };

 public:
  static Logger*& GetInstance();

  static Logger*& SetInstance(Logger*& logger_instance);

 public:
   Logger();

   Logger(const Logger& logger);

   virtual ~Logger();

   virtual Logger* Init(const std::string& profile_path = "");

   virtual Logger* Init(const YAML::Node& config);

   Logger* Log(LogLevel level, const char* format, ...);

   std::string GenerateLogHeader() const;

 protected:
  static std::mutex lock_;

 protected:
   
  std::string log_name_;    //日志文件名
  std::string log_path_;    //日志保存路径
  size_t max_log_size_;     //单个日志文件最大大小
  bool async_write_;        //异步日志
  std::string log_title_;   //日志标签
  bool time_stamp_;         //开启时间戳
   
  LogAppender* appender_;
  char buffer_[1024 * 1024];
};

} // namespace Imagine_Log

} // namespace Imagine_Tool

#endif