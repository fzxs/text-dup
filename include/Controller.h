
#ifndef __STU_CONTROLLER_H_
#define __STU_CONTROLLER_H_

/* 控制器模块 */

#include "textFilter.h"

#include <stdio.h>
#include <string>
#include <map>

namespace student
{
    struct ReportForm
    {
        std::string srcText;    //原始文本
        std::string fileName;    //文件名称
        unsigned int lineNo;    //行号
    public:
        //构造函数
        ReportForm(const std::string &text, const std::string &name, unsigned int no) :srcText(text), fileName(name), lineNo(no)
        {
        }
    };

    class Controller
    {
    public:
        //构造函数
        Controller();

        //析构函数
        ~Controller();

    public:
        //初始化
        int open(const std::string &matchFile);

        //启动
        int run(const std::string &pathName);

    private:
        //轮询文件
        int loopFile(const std::string &fileName);

        //处理标题
        void handleTitle(const ReportForm & form);

    private:
        textFilter _filter;    //过滤器
        FILE *_fp;
        std::map<std::string, ReportForm> _reportForm;    //报表内容
    };
}

#endif  //  __STU_CONTROLLER_H_
