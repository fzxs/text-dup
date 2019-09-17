
#ifndef __STU_TEXT_FILTER_H_
#define __STU_TEXT_FILTER_H_

/* 文本过滤模块 */

#include <string>
#include <vector>

namespace student
{
    class textFilter
    {
        static const std::string kTitlePattern;    //标题正则
        static const std::string kHeadPattern;    //标题头正则
    public:
        //构造函数
        textFilter();

        //析构函数
        ~textFilter();

    public:
        //初始化
        int open(const std::string &configFile);

        //判断是否是题目
        bool isTitle(const std::string &text, std::string &fmt);

    private:
        //清洗文本
        void clearText(std::string &text);

    private:
        void *_titleReg;
        void *_headReg;
        std::vector<void *> _regexp;
    };
}

#endif  //  __STU_TEXT_FILTER_H_
