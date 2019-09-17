
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
 const std::string textFilter::kHeadPattern = "^[0-9]+(��){0,1}";

/********************************************************
   Func Name: textFilter
Date Created: 2019-9-16
 Description: ���캯��
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
 Description: ��������
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
 Description: ��ʼ��
       Input: 
      Output: 
      Return: error code
     Caution: 
*********************************************************/
int textFilter::open(const std::string &configFile)
{
    if (configFile.empty())
    {
        //����û�й���
        return 0;
    }

    int errCode = 0;
    std::ifstream infile;
    std::string line;
    void * pReg = NULL;

    //���ر�������
    this->_titleReg = compileRegular(textFilter::kTitlePattern.c_str());
    assert(this->_titleReg);

    //���ر���ͷ����
    this->_headReg = compileRegular(textFilter::kHeadPattern.c_str());
    assert(this->_headReg);
    
    infile.open(configFile);
    while (std::getline(infile, line))
    {
        if (line.empty())
        {
            continue;
        }
        //����������ʽ
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
 Description: �����ı�
       Input: 
      Output: 
      Return: error code
     Caution: 
*********************************************************/
void textFilter::clearText(std::string &text)
{
    char *pTmp = NULL;
    std::string newStr = text;

    //1.����У��
    if (text.empty())
    {
        return;
    }

    //2.�ı���ϴ
    for (auto it = this->_regexp.begin(); it != this->_regexp.end(); ++it)
    {
        //�滻�ı�
        pTmp = regularReplace(*it, newStr.c_str(), "");
        assert(pTmp);
        newStr = pTmp;
    }

    text = newStr;
}

/********************************************************
   Func Name: isTitle
Date Created: 2019-9-16
 Description: �ж��Ƿ�����Ŀ
       Input: 
      Output: 
      Return: ��Ŀ����true������Ŀ����false
     Caution: 
*********************************************************/
bool textFilter::isTitle(const std::string &text, std::string &fmt)
{
    assert(!text.empty());

    std::string newStr = text;
    int errCode = 0;
    char * pTmp = NULL;

    //1.�ı���ϴ
    this->clearText(newStr);

    //2.����Ƿ���ϱ����ж�
    if (!regularMatch(this->_titleReg, newStr.c_str()))
    {
        return false;
    }

    //3.��ϴͷ
    pTmp = regularReplace(this->_headReg, newStr.c_str(), "");
    assert(pTmp);
    newStr = pTmp;

    //4.��ȡMD5
    errCode = md5_calculate((char *)newStr.c_str(), newStr.length(), &pTmp);
    assert(!errCode);

    fmt = pTmp;

    return true;
}
