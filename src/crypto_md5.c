
#include "crypto_md5.h"
#include "openssl/md5.h"
#include "hex_code.h"

#include <stdlib.h>
#include <string.h>

/********************************************************
   Func Name: getEncryptKey
Date Created: 2018-9-5
 Description: ��ȡaes������Կ
	   Input: pcUserKey���û����� 
	             pstKey��AES��Կ
	  Output:
      Return: error code
     Caution: pstKey��Ҫ�ɵ��ú�������
*********************************************************/
int md5_calculate(char *plaintext, int plaintext_size, char **md5_str)
{
	int result = 0;
	MD5_CTX md5_ctx;
	unsigned char md5_buffer[MD5_LENTH] = { 0 };

	if (NULL == plaintext || 0 == plaintext_size || NULL == md5_str)
	{
		return -1;
	}

	//��ʼ��MD5�����Ľṹ
	MD5_Init(&md5_ctx);

	//ˢ��MD5�����ļ��������ݷ�Ƭ�������MD5ˢ�¡�
	MD5_Update(&md5_ctx, plaintext, plaintext_size);

	//����MD5����
	MD5_Final(md5_buffer, &md5_ctx);

	//ת��ʮ�������ַ���
	result = hex_encode(md5_buffer, MD5_LENTH, md5_str);
	if (result)
	{
		return -1;
	}

	return 0;
}


