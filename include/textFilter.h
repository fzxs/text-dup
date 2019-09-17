
#ifndef __STU_TEXT_FILTER_H_
#define __STU_TEXT_FILTER_H_

/* �ı�����ģ�� */

#include <string>
#include <vector>

namespace student
{
    class textFilter
    {
        static const std::string kTitlePattern;    //��������
        static const std::string kHeadPattern;    //����ͷ����
    public:
        //���캯��
        textFilter();

        //��������
        ~textFilter();

    public:
        //��ʼ��
        int open(const std::string &configFile);

        //�ж��Ƿ�����Ŀ
        bool isTitle(const std::string &text, std::string &fmt);

    private:
        //��ϴ�ı�
        void clearText(std::string &text);

    private:
        void *_titleReg;
        void *_headReg;
        std::vector<void *> _regexp;
    };
}

#endif  //  __STU_TEXT_FILTER_H_
