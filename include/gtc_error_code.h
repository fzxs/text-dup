
#ifndef __GTC_ERROR_CODE_H_
#define __GTC_ERROR_CODE_H_

typedef enum tag_error_code
{
    /* 常用错误 */
    SUCCESSFUL,    //成功
    FAILED,    //失败
    PARAM_NULL,    //参数为空
    PARAM_NOLEGAL,    //参数不合法
    MALLOC_FAILED,    //内存分配失败
    FILE_READ_FAILED,    //读取文件失败
    DATA_ERROR,    //数据错误
    TIMEOUT,    //超时
    SOCKET_READ_ERROR,    //网络读错误
    SERVER_ERROR,    //服务器错误
    REGULAR_COMPILE_FAILED,    //正则编译错误
    OPEN_FILE_FAILED,    //打开文件失败

}error_code_t;

#endif
