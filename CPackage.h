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
  ~CPackage();
 public:
  CX_INT32 CX_CreatePackage(std::string package_name);
  CX_INT32 CX_CreateDirectory(std::string dirname);

  CX_INT32 CX_CreateFile(std::string dirname,std::string filename);

  CX_INT32 CX_SetDirectoryOption(std::string dirname,CX_UINT32 key,void* value,CX_INT32* value_size);

  CX_INT32 CX_SetFileOption(std::string dirname,std::string filename,CX_UINT32 key,void* value,CX_INT32* value_size); 


  CX_INT32 CX_GetDirectoryOption(std::string dirname,CX_UINT32 key,void* value,CX_INT32* value_size);

  CX_INT32 CX_GetFileOption(std::string dirname,std::string filename,CX_UINT32 key,void* value,CX_INT32* value_size);

  std::vector<std::string> CX_GetAllDirectoryName();

  std::vector<std::string> CX_GetAllFileInDirectoryName(std::string dirname);
 private:
  CX_Dir_File dir_file;
  std::ofstream m_package;
  std::ifstream m_srcfile;
  CX_UINT32 default_dk_property,default_fk_prorerty,default_fk_compresstype;
};



#endif
















