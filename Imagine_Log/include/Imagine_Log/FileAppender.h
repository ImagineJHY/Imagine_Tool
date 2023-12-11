#ifndef IMAGINE_TOOL_FILEAPPENDER_H
#define IMAGINE_TOOL_FILEAPPENDER_H

#include "LogAppender.h"

namespace Imagine_Tool
{

namespace Imagine_Log
{

class LogAppender;

class FileAppender : public LogAppender
{
 public:
    FileAppender(const std::string& file_name, const std::string& file_path, size_t max_file_size);

    ~FileAppender();

    LogAppender* WriteLog(const std::string& str);

    size_t GetFileSize(const std::string& file_name) const;

 private:
    std::string file_name_;     //文件名(真实文件名会跟上时间后缀)
    std::string file_path_;
    size_t max_file_size_;
    bool is_open_;
    int open_file_fd_;
    std::string open_file_;
};

} // namespace Imagine_Log

} // namespace Imagine_Tool

#endif