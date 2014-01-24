#ifndef INIREADER_H
#define INIREADER_H


char* IniReadString(char* szFileName, char* szKey, char* sDefault);
int IniReadInt(char* szFileName, char* szKey, int iDefault);
double IniReadDouble(char* szFileName, char* szKey, double dDefault);
bool IniReadBool(char* szFileName, char* szKey, bool bDefault);

#endif//INIREADER_H
