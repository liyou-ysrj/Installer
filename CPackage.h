#ifndef CPACKAGE_H
#define CPACKAGE_H


#include "CXinclude.h"
#include <vector>
#include <map>
#include <string>
#include <fstream>
class CPackage
{
 public:
  typedef std::map<std::string,std::map<std::string,std::vector<std::string> > > CX_Dir_File;
  typedef std::map<std::string,std::vector<std::string> > CX_File;
  typedef std::vector<std::string> CX_File_Option;
  typedef std::pair<std::string,CX_File> CX_Dir_Pair;
  typedef std::pair<std::string,CX_File_Option> CX_File_Pair;
 public:
  CPackage();
  CPackage(std::string package_name);//安装程序的名字
  
 public:
  CX_INT32 CX_CreateDirectory(std::string dirname);

  CX_INT32 CX_CreateFile(std::string dirname,std::string filename);

  CX_INT32 CX_SetDirectoryOption(std::string dirname,directory_key key,void* value,CX_INT32* value_size);//这种类型的函数输入的value_size在函数返回时都会被设置成对应的值的大小

  CX_INT32 CX_SetFileOption(std::string dirname,std::string filename,file_key key,void* value,CX_INT32* value_size); 


  CX_INT32 CX_GetDirectoryOption(std::string dirname,std::string filename,directory_key key,void* value,CX_INT32* value_size);

  CX_INT32 CX_GetFileOption(std::string dirname,std::string filename,file_key key,void* value,CX_INT32* value_size);

  std::vector<std::string> CX_GetAllDirectoryName();

  std::vector<std::string> CX_GetAllFileInDirectoryName();
 private:
  CX_Dir_File dir_file;
  std::ofstream m_package;
  std::ifstream m_srcfile;
};



#endif
















