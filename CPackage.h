#ifndef CPACKAGE_H
#define CPACKAGE_H

#define ADD_LNK "##LNK"
#define STR_END "##"


#include "CXtype.h"
#include <vector>
#include <map>
class CPackage
{
 public:
  typedef typename std::map<std::string,std::vector<std::vector<std::string>>> CXDirAndFile;
 public:
  CPackage();
  CPackage(std::string package_name);
 public:
  CX_INT32 AddFile(std::string filefullname);
  CX_INT32 SetCurrentDir(std::string dir);///>dir是指解包以后的dir，文件本来的dir包含在fielfullname里
  CX_INT32 StartPackage();
  CX_INT32 SetLnkEnable(std::string& filefullname);

 private:
  CX_INT32 MoveForward(CX_INT64 count);
  CX_INT32 MoveBackward(CX_INT64 count);
  CX_INT32 WriteDataBlock(DataInfo di);
  CX_INT32 WriteDataDir(DataDirInfo ddi);
  CX_INT64 GetFileSize(std::string filefullname);
 private:
  CXDirAndFile m_file_dir;
  std::string m_current_dir;
  std::ifstream m_file;
  std::ofstream m_package;
  
  

};



#endif
















