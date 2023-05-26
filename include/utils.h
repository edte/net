#ifndef UTILS_H
#define UTILS_H

#include <string.h>
#include <stdio.h>

static int _utils_month, _utils_day, _utils_year; 
static char _utils_buff[16]; 
static const char _utils_month_names[] = "JanFebMarAprMayJunJulAugSepOctNovDec";\

// 正在开发，就打开这个宏，那么输出时就会答应调试信息，正式发行就注释掉
#define DEV_DEBUG 1

#if DEV_DEBUG 
#define DEBUG(str, ...)                       \
    sscanf(__DATE__, "%s %d %d", _utils_buff, &_utils_day, &_utils_year);\
    _utils_month = (strstr(_utils_month_names, _utils_buff)-_utils_month_names)/3+1;\
    sprintf(_utils_buff, "%d-%02d-%02d", _utils_year, _utils_month, _utils_day);\
    printf("[DEBUG] %s %s [%s:%u %s] - "str"\n",_utils_buff,__TIME__, __FILE__, __LINE__, __FUNCTION__,##__VA_ARGS__);
#else
#define DEBUG(str, ...)                       
#endif

#define ERROR(str, ...)                     \
    sscanf(__DATE__, "%s %d %d", _utils_buff, &_utils_day, &_utils_year);\
    _utils_month = (strstr(_utils_month_names, _utils_buff)-_utils_month_names)/3+1;\
    sprintf(_utils_buff, "%d-%02d-%02d", _utils_year, _utils_month, _utils_day);\
    fprintf(stderr,"[ERROR] %s %s [%s:%u %s] - "str"\n", _utils_buff,__TIME__, __FILE__, __LINE__, __FUNCTION__,##__VA_ARGS__);

#define PANIC(str, ...) \
    sscanf(__DATE__, "%s %d %d", _utils_buff, &_utils_day, &_utils_year);\
    _utils_month = (strstr(_utils_month_names, _utils_buff)-_utils_month_names)/3+1;\
    sprintf(_utils_buff, "%d-%02d-%02d", _utils_year, _utils_month, _utils_day);\
    fprintf(stderr,"[PANIC] %s %s [%s:%u %s] - "str"\n",_utils_buff,__TIME__, __FILE__, __LINE__, __FUNCTION__,##__VA_ARGS__);


#define FATAL(str, ...) \
    sscanf(__DATE__, "%s %d %d", _utils_buff, &_utils_day, &_utils_year);\
    _utils_month = (strstr(_utils_month_names, _utils_buff)-_utils_month_names)/3+1;\
    sprintf(_utils_buff, "%d-%02d-%02d", _utils_year, _utils_month, _utils_day);\
    fprintf(stderr,"[FATAL] %s %s [%s:%u %s] - "str"\n",_utils_buff,__TIME__, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__); \
    exit(-1);

#endif
