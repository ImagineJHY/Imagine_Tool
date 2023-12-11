#include "Imagine_Log/FileAppender.h"

#include "Imagine_Time/Imagine_Time.h"
#include "Imagine_Log/common_definition.h"

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

namespace Imagine_Tool
{

namespace Imagine_Log
{

FileAppender::FileAppender(const std::string& file_name, const std::string& file_path, size_t max_file_size)
            : LogAppender(), file_name_(file_name), file_path_(file_path), max_file_size_(max_file_size), is_open_(false) 
{
}

FileAppender::~FileAppender()
{
    if (is_open_) {
        close(open_file_fd_);
    }
}

LogAppender* FileAppender::WriteLog(const std::string& str)
{
    std::unique_lock<std::mutex> lock(lock_);
    if (!is_open_) {
        open_file_ = file_name_ + "." + ::Imagine_Tool::Imagine_Time::TimeUtil::ToDate(NOW_MS);
        open_file_fd_ = open((file_path_ + open_file_).c_str(), O_CREAT | O_RDWR, 0777);
        if (open_file_fd_ < 0) {
            throw std::exception();
        }
        is_open_ = true;
    }
    if (GetFileSize(file_path_ + open_file_) >= max_file_size_) {
        close(open_file_fd_);
        open_file_ = file_name_ + "." + ::Imagine_Tool::Imagine_Time::TimeUtil::ToDate(NOW_MS);
        open_file_fd_ = open((file_path_ + open_file_).c_str(), O_CREAT | O_RDWR, 0777);
        if (open_file_fd_ < 0) {
            throw std::exception();
        }
    }
    write(open_file_fd_, (str + LOG_ENDDING_TAG).c_str(), str.size() + 1);

    return this;
}

size_t FileAppender::GetFileSize(const std::string& file_name) const
{
    struct stat statbuf;
    stat(file_name.c_str(), &statbuf);

    return statbuf.st_size;
}

} // namespace Imagine_Log

} // namespace Imagine_Tool
