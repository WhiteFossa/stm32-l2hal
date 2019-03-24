#include <l2hal_aux.h>

void AUX_Mem_SafeFree(void* ptr)
{
	free(ptr);
	ptr = NULL;
}

char* AUX_Str_Substring(char* string, uint16_t start, uint16_t length)
{
	char* result = malloc(length + 1);
	memcpy(result, string + start, length);
	result[length] = '\0';

	return result;
}

char* AUX_Str_MergeStrings(char* str1, char* str2)
{
	size_t needToAllocate = strlen(str1) + strlen(str2) + 1; /* +1 because of null-termination */
	char* result = malloc(needToAllocate);
	strcpy(result, str1);
	strcat(result, str2);

	return result;
}
