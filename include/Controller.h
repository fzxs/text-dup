
#ifndef __STU_CONTROLLER_H_
#define __STU_CONTROLLER_H_

/* ������ģ�� */

#include "textFilter.h"

#include <stdio.h>
#include <string>
#include <map>

namespace student
{
    struct ReportForm
    {
        std::string srcText;    //ԭʼ�ı�
        std::string fileName;    //�ļ�����
        unsigned int lineNo;    //�к�
    public:
        //���캯��
        ReportForm(const std::string &text, const std::string &name, unsigned int no) :srcText(text), fileName(name), lineNo(no)
        {
        }
    };

    class Controller
    {
    public:
        //���캯��
        Controller();

        //��������
        ~Controller();

    public:
        //��ʼ��
        int open(const std::string &matchFile);

        //����
        int run(const std::string &pathName);

    private:
        //��ѯ�ļ�
        int loopFile(const std::string &fileName);

        //�������
        void handleTitle(const ReportForm & form);

    private:
        textFilter _filter;    //������
        FILE *_fp;
        std::map<std::string, ReportForm> _reportForm;    //��������
    };
}

#endif  //  __STU_CONTROLLER_H_
