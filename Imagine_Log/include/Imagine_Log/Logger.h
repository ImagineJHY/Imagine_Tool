#ifndef IMAGINE_TOOL_LOGGER_H
#define IMAGINE_TOOL_LOGGER_H

#include "common_definition.h"
#include "ConsoleAppender.h"
#include "FileAppender.h"
#include "Imagine_Time/Timer.h"
#include "yaml-cpp/yaml.h"

#include <string>
#include <mutex>
#include <stdarg.h>

namespace Imagine_Tool
{

class Logger
{
 public:
   enum LogLevel{
      Debug,
      Warn,
      Info,
      Error,
      Fatal
   };

 public:
  static Logger*& GetInstance();

  static void SetInstance(Logger* logger);

 public:
   Logger(): async_write_(false){};

   Logger(const Logger& logger){};

   virtual ~Logger(){};

   bool Init(std::string profile_path = "");

   Logger* Log(LogLevel level, const char* format, ...);

   std::string GenerateLogHeader();

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

} // Imagine_Tool

#endif