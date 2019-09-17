

#ifndef __CRYPTO_BASE_H_
#define __CRYPTO_BASE_H_

/* ʮ�����Ʊ��� */

/*
���������п��ܴ���/0 /r /n ��Щ�����ַ��������������������н��д���
���Խ������е�ÿһ���ַ�ת��������ʮ���������֡�
ʮ���������ֵķ�Χ��[0-9A-Z]��û��0������֣�ֻ��0����ַ�
*/

#ifdef __cplusplus
extern "C"
{
#endif
	/********************************************************
	   Func Name: string_to_hex
	Date Created: 2018-10-10
	 Description: �ַ���תʮ�������ַ�
		   Input: 
		  Output:
		  Return:
		 Caution: ���ص�pcDst���ַ���
	*********************************************************/
	int hex_encode(unsigned char *pcSrc, int inLen, char **pcDst);

	/********************************************************
	   Func Name: hex_to_string
	Date Created: 2018-10-10
	 Description: ʮ�������ַ���ת�ַ���
		   Input: 
		  Output:
		  Return:
		 Caution: ���ص�pcDst���ַ����飬�����ַ���
	*********************************************************/
	int hex_decode(unsigned char *pcSrc, unsigned char **pcDst, int *outLen);
	
#ifdef __cplusplus
}
#endif

#endif







