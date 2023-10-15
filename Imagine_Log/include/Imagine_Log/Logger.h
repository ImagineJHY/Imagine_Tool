#ifndef IMAGINE_TOOL_LOGGER_H
#define IMAGINE_TOOL_LOGGER_H

#include "common_definition.h"
#include "ConsoleAppender.h"
#include "FileAppender.h"
#include "Imagine_Time/Timer.h"

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
   static Logger* GetInstance();

   static bool DestroyInstance();

 public:
   Logger* SetName(std::string& log_name)
   {
      log_name_ = log_name;

      return this;
   }

   Logger* SetPath(std::string& log_path)
   {
      log_path_ = log_path;

      return this;
   }

   Logger* SetAsyncWrite()
   {
      async_write_ = true;

      return this;
   }

   bool Init(std::string profile_path = "");

   Logger* Log(LogLevel level, const char* format, ...);

   std::string GenerateLogHeader();
 
 private:
   Logger(): async_write_(false) {};

   // Logger(std::string& log_name, std::string& log_path) : log_name_(log_name), log_path_(log_path) {};

   Logger(const Logger& logger){};

   Logger& operator=(const Logger& logger){}


 private:
   static Logger* logger_;
   static std::mutex lock_;

 private:
   
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