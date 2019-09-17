
#include "Controller.h"
#include "gtc_error_code.h"
#include "StringBuilder.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <fstream>
#include <sstream>
#include <iterator>
#include <unistd.h>

using namespace student;

/************************************************************************
 Controller                                                         
************************************************************************/

/********************************************************
   Func Name: Controller
Date Created: 2019-9-16
 Description: ���캯��
       Input: 
      Output: 
      Return: 
     Caution: 
*********************************************************/
Controller::Controller() :_filter(), _fp(NULL)
{
}

/********************************************************
   Func Name: ~Controller
Date Created: 2019-9-16
 Description: ��������
       Input: 
      Output: 
      Return: 
     Caution: 
*********************************************************/
Controller::~Controller()
{
    if (this->_fp)
    {
        fclose(this->_fp);
        this->_fp = NULL;
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
int Controller::open(const std::string &matchFile)
{
    //����־�ļ�
    this->_fp = fopen("../log.md", "w");
    if (NULL == this->_fp)
    {
        return error_code_t::OPEN_FILE_FAILED;
    }

    return this->_filter.open(matchFile);
}

/********************************************************
   Func Name: run
Date Created: 2019-9-16
 Description: ����
       Input: 
      Output: 
      Return: error code
     Caution: 
*********************************************************/
int Controller::run(const std::string &pathName)
{
    assert(!pathName.empty());

    //����Ŀ¼�������ļ�
    DIR *dir = NULL;
    struct dirent *dir_file;
    char dirSrcFile[1024] = { 0 };

    dir = opendir(pathName.c_str());
    if (NULL == dir)
    {
        return error_code_t::OPEN_FILE_FAILED;
    }

    while (dir_file = readdir(dir), dir_file)
    {
        //����. ..
        if (0 == strcmp(dir_file->d_name, ".") || 0 == strcmp(dir_file->d_name, ".."))
        {
            continue;
        }

        memset(dirSrcFile, 0, 1024);
        sprintf(dirSrcFile, "%s/%s", pathName.c_str(), dir_file->d_name);

        this->loopFile(dirSrcFile);
    }

    ::closedir(dir);

    return 0;
}

/********************************************************
   Func Name: loopFile
Date Created: 2019-9-16
 Description: ��ѯ�ļ�
       Input: 
      Output: 
      Return: error code
     Caution: 
*********************************************************/
int Controller::loopFile(const std::string &fileName)
{
    assert(!fileName.empty());

    int errCode = 0;
    unsigned int lineNo = 0;
    std::ifstream infile;
    std::string line;

    infile.open(fileName);
    while (std::getline(infile, line))
    {
        lineNo++;
        if (line.empty())
        {
            //���ı�������
            continue;
        }

        //���⴦��
        this->handleTitle(ReportForm(line, fileName, lineNo));

    }
    infile.close();

    return errCode;
}

/********************************************************
   Func Name: handleTitle
Date Created: 2019-9-16
 Description: �������
       Input: 
      Output: 
      Return: error code
     Caution: 
*********************************************************/
void Controller::handleTitle(const ReportForm & form)
{
    std::string fmtStr;
    std::map<std::string, ReportForm>::iterator itFind;
    gtl::TLStringBuilder<char> builder;
    std::string strOut;

    if (!this->_filter.isTitle(form.srcText, fmtStr))
    {
        //������Ǳ���,�˳�
        return;
    }
    itFind = this->_reportForm.find(fmtStr);
    if (itFind == this->_reportForm.end())
    {
        //û���ҵ����洢
        this->_reportForm.insert(std::make_pair(fmtStr, form));
        return;
    }

    //�����ظ��ı�����ӡ��Ϣ
    //builder.Append("[%s:%u][%s]")
    builder.Append("taget:[");
    builder.Append(form.fileName);
    builder.Append(":");
    builder.Append(std::to_string(form.lineNo));
    builder.Append("]");
    builder.Append("[");
    builder.Append(form.srcText);
    builder.Append("]");

    builder.Append("\n");

    builder.Append("source:[");
    builder.Append(itFind->second.fileName);
    builder.Append(":");
    builder.Append(std::to_string(itFind->second.lineNo));
    builder.Append("]");
    builder.Append("[");
    builder.Append(itFind->second.srcText);
    builder.Append("]");

    builder.Append("\n");

    strOut = builder.ToString();

    fputs(strOut.c_str(), this->_fp);

}
