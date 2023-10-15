#ifndef IMAGINE_TOOL_FILEAPPENDER_H
#define IMAGINE_TOOL_FILEAPPENDER_H

#include "LogAppender.h"
#include "Imagine_Time/TimeUtil.h"

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

namespace Imagine_Tool
{

class FileAppender : public LogAppender
{
 public:
    FileAppender(std::string file_name, std::string file_path, size_t max_file_size)
                : file_name_(file_name), file_path_(file_path), max_file_size_(max_file_size), is_open_(false) 
    {

    }
// open(&(spill_files_[i].back()[0]), O_CREAT | O_RDWR, 0777);
    ~FileAppender()
    {
        if (is_open_) {
            close(open_file_fd_);
        }
    }

    bool WriteLog(std::string str)
    {
        std::unique_lock<std::mutex> lock(lock_);
        if (!is_open_) {
            open_file_ = file_name_ + "." + TimeUtil::ToDate(NOW_MS);
            open_file_fd_ = open((file_path_ + open_file_).c_str(), O_CREAT | O_RDWR, 0777);
            if (open_file_fd_ < 0) {
                throw std::exception();
            }
            is_open_ = true;
        }
        if (GetFileSize(file_path_ + open_file_) >= max_file_size_) {
            close(open_file_fd_);
            open_file_ = file_name_ + "." + TimeUtil::ToDate(NOW_MS);
            open_file_fd_ = open((file_path_ + open_file_).c_str(), O_CREAT | O_RDWR, 0777);
            if (open_file_fd_ < 0) {
                throw std::exception();
            }
        }
        write(open_file_fd_, (str + "\n").c_str(), str.size() + 1);

        return true;
    }

    size_t GetFileSize(std::string file_name)
    {
        struct stat statbuf;
        stat(file_name.c_str(), &statbuf);

        return statbuf.st_size;
    }

 private:
    std::string file_name_;     //文件名(真实文件名会跟上时间后缀)
    std::string file_path_;
    size_t max_file_size_;
    bool is_open_;
    int open_file_fd_;
    std::string open_file_;
};

} // namespace Imagine_Tool

#endif