#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
//////////////////////////////////////////////////////////////////////////

int ReplaceString(char* _pDestStr, char _cReplaceChar, const char* _pszReplaceStr)
{
	int nReplaced = 0;
	size_t uStrLen = strlen(_pDestStr);
	size_t uReplaceLen = strlen(_pszReplaceStr);

	if(0 == uReplaceLen)
	{
		return 0;
	}

	for(size_t i = 0; i < uStrLen; ++i)
	{
		if(_cReplaceChar == _pDestStr[i])
		{
			++nReplaced;
		}
	}

	if(0 == nReplaced)
	{
		return 0;
	}

	char* pTailOfReplaced = _pDestStr + uStrLen + (uReplaceLen - sizeof(_cReplaceChar)) * nReplaced;
	char* pTailOfOriginal = _pDestStr + uStrLen;

	while(pTailOfOriginal != pTailOfReplaced)
	{
		if(*pTailOfOriginal == _cReplaceChar)
		{
			//	Skip the character needs to be replaced and full fill the destinate memory with the given string
			--pTailOfOriginal;
			pTailOfReplaced -= uReplaceLen;
			memcpy(pTailOfReplaced + 1, _pszReplaceStr, uReplaceLen);
		}
		else
		{
			//	Just copy the original characters to destinate position
			*pTailOfReplaced = *pTailOfOriginal;

			//	Move the pointer
			--pTailOfOriginal;
			--pTailOfReplaced;
		}
	}

	return nReplaced;
}

void Test_ReplaceString()
{
	char szStrBuf[1024] = {0};
	std::string xInput;

	printf("Test [ReplaceString]...Enter quit to quit\n");

	for(;;)
	{
		xInput.clear();
		getline(std::cin, xInput);
		strcpy(szStrBuf, xInput.c_str());
		if(0 == strcmp(szStrBuf, "quit"))
		{
			break;
		}

		int nRet = ReplaceString(szStrBuf, ' ', "%20");
		printf("Relaced %d characters, output[%s]\n",
			nRet, szStrBuf);
	}

	printf("Done...");
}