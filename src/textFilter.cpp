
#include "textFilter.h"
#include "regular.h"
#include "gtc_error_code.h"
#include "crypto_md5.h"

#include <fstream>
#include <sstream>
#include <iterator>
#include <assert.h>

using namespace student;

/************************************************************************
 textFilter                                                         
************************************************************************/
 const std::string textFilter::kTitlePattern = "^[0-9]+";
 const std::string textFilter::kHeadPattern = "^[0-9]+(、){0,1}";

/********************************************************
   Func Name: textFilter
Date Created: 2019-9-16
 Description: 构造函数
       Input: 
      Output: 
      Return: 
     Caution: 
*********************************************************/
 textFilter::textFilter() :_titleReg(NULL), _headReg(NULL)
{
}

/********************************************************
   Func Name: ~textFilter
Date Created: 2019-9-16
 Description: 析构函数
       Input: 
      Output: 
      Return: 
     Caution: 
*********************************************************/
textFilter::~textFilter()
{
    void *pReg = NULL;

    for (auto it = this->_regexp.begin(); it != this->_regexp.end(); ++it)
    {
        pReg = *it;
        releaseRegular(pReg);
    }
}

/********************************************************
   Func Name: open
Date Created: 2019-9-16
 Description: 初始化
       Input: 
      Output: 
      Return: error code
     Caution: 
*********************************************************/
int textFilter::open(const std::string &configFile)
{
    if (configFile.empty())
    {
        //允许没有规则
        return 0;
    }

    int errCode = 0;
    std::ifstream infile;
    std::string line;
    void * pReg = NULL;

    //加载标题正则
    this->_titleReg = compileRegular(textFilter::kTitlePattern.c_str());
    assert(this->_titleReg);

    //加载标题头正则
    this->_headReg = compileRegular(textFilter::kHeadPattern.c_str());
    assert(this->_headReg);
    
    infile.open(configFile);
    while (std::getline(infile, line))
    {
        if (line.empty())
        {
            continue;
        }
        //编译正则表达式
        pReg = compileRegular(line.c_str());
        if (NULL == pReg)
        {
            errCode = error_code_t::REGULAR_COMPILE_FAILED;
            break;
        }
        this->_regexp.emplace_back(pReg);
    }
    infile.close();
    
    return errCode;
}

/********************************************************
   Func Name: handleText
Date Created: 2019-9-16
 Description: 处理文本
       Input: 
      Output: 
      Return: error code
     Caution: 
*********************************************************/
void textFilter::clearText(std::string &text)
{
    char *pTmp = NULL;
    std::string newStr = text;

    //1.参数校验
    if (text.empty())
    {
        return;
    }

    //2.文本清洗
    for (auto it = this->_regexp.begin(); it != this->_regexp.end(); ++it)
    {
        //替换文本
        pTmp = regularReplace(*it, newStr.c_str(), "");
        assert(pTmp);
        newStr = pTmp;
    }

    text = newStr;
}

/********************************************************
   Func Name: isTitle
Date Created: 2019-9-16
 Description: 判断是否是题目
       Input: 
      Output: 
      Return: 题目返回true，非题目返回false
     Caution: 
*********************************************************/
bool textFilter::isTitle(const std::string &text, std::string &fmt)
{
    assert(!text.empty());

    std::string newStr = text;
    int errCode = 0;
    char * pTmp = NULL;

    //1.文本清洗
    this->clearText(newStr);

    //2.检测是否符合标题判断
    if (!regularMatch(this->_titleReg, newStr.c_str()))
    {
        return false;
    }

    //3.清洗头
    pTmp = regularReplace(this->_headReg, newStr.c_str(), "");
    assert(pTmp);
    newStr = pTmp;

    //4.提取MD5
    errCode = md5_calculate((char *)newStr.c_str(), newStr.length(), &pTmp);
    assert(!errCode);

    fmt = pTmp;

    return true;
}
