
#ifndef __GTC_REGULAR_H_
#define __GTC_REGULAR_H_

#define PCRE_STATIC  //静态库编译选项 

#ifdef __cplusplus
extern "C"
{
#endif
    //编译正则表达式
    void * compileRegular(const char *pattern);

    //释放正则表达式对象
    void releaseRegular(void *pReg);

    //正则匹配
    int regularMatch(const void *pReg, const char *pSrc);

    //正则替换
    char * regularReplace(const void *pReg, const char *pSrc, const char *pReplace);

#ifdef __cplusplus
}
#endif

#endif
