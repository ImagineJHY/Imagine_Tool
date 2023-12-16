#ifndef IMAGINE_LOG_COMMON_DEFINITION_H
#define IMAGINE_LOG_COMMON_DEFINITION_H

namespace Imagine_Tool
{

namespace Imagine_Log
{

#define LOG_ENDDING_TAG                     "\r\n"
#define LOG_KEYWORDS_LEFT_TAG               "["
#define LOG_KEYWORDS_RIGHT_TAG              "]"
#define LOG_KEYWORDS_AND_CONTENT_DIVIDER    ": "

#define YAML_KEYWORDS_LOG_NAME              "log_name"
#define YAML_KEYWORDS_LOG_PATH              "log_path"
#define YAML_KEYWORDS_ASYNC_LOG             "async_log"
#define YAML_KEYWORDS_LOG_TITLE             "log_title"
#define YAML_KEYWORDS_LOG_WITH_TIMESTAMP    "log_with_timestamp"
#define YAML_KEYWORDS_MAX_LOG_FILE_SIZE     "max_log_file_size"

} // namespace Imagine_Log

} // namespace Imagine_Tool

#endif