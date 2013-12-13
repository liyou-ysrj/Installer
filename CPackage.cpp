#include "CPackage.h"
#include <string.h>

CPackage::CPackage()
{
  default_dk_property=DP_NONE;
  default_fk_prorerty=FP_NONE;
  default_fk_compresstype=FCT_NONE;
}

CPackage::CPackage(std::string package_name)
{
  m_package.open(package_name.c_str());
  default_dk_property=DP_NONE;
  default_fk_prorerty=FP_NONE;
  default_fk_compresstype=FCT_NONE;
}
CPackage::~CPackage()
{
  m_package.close();

}
CX_INT32 CPackage::CX_CreatePackage(std::string package_name)
{
  m_package.open(package_name.c_str());

  return CX_OK;
}
CX_INT32 CPackage::CX_CreateTopDirectory(std::string dirname)
{
  CX_Dir_File::iterator ret=dir_file.find(dirname);
  if(ret!=dir_file.end())
    return CX_DIRALREADYEXIST;
  //在目录映射中增加一个目录，并且设置目录为Top目录
  dir_file.insert(CX_Dir_Pair(dirname,CX_File()));
  dir_file[dirname].insert(CX_File_Pair(".",std::vector<std::string>()));
  CX_UINT32 tmp=TYPE_DIR;
  std::string tmp_str;
  tmp_str.assign((char*)&tmp,sizeof(CX_UINT32));
  dir_file[dirname]["."].push_back(tmp_str);  //VALUE_TYPE
  tmp=DT_YES;
  tmp_str.assign((char*)&tmp,sizeof(CX_UINT32));//TopDirectory or not
  dir_file[dirname]["."].push_back(tmp_str);
  tmp_str.assign((char*)&default_dk_property,sizeof(CX_UINT32));  
  dir_file[dirname]["."].push_back(tmp_str);  //DK_PROPERTY

					   
  return CX_OK;

}
CX_INT32 CPackage::CX_CreateSubDirectory(std::string dirname,std::string subdir)
{
  
  CX_Dir_File::iterator ret=dir_file.find(dirname+subdir);
  if(ret!=dir_file.end())
    return CX_FILEALREADYEXIST;

  //给父目录增加一个类型为TYPE_DIR文件，让父目录知道增加了一个子目录
  CX_UINT32 tmp=TYPE_DIR;
  std::string tmp_str;
  tmp_str.assign((char*)&tmp,sizeof(CX_UINT32));
  dir_file[dirname][subdir].push_back(tmp_str);  //VALUE_TYPE
  tmp=DT_YES;
  tmp_str.assign((char*)&tmp,sizeof(CX_UINT32));
  dir_file[dirname][subdir].push_back(tmp_str);  //TopDirectory or not
  tmp_str.assign((char*)&default_dk_property,sizeof(CX_UINT32));  
  dir_file[dirname][subdir].push_back(tmp_str);  //DK_PROPERTY

  //在目录映射中增加一个新目录，并且标记为子目录
  dir_file[dirname].insert(CX_File_Pair(subdir,std::vector<std::string>()));
  dir_file[dirname].insert(CX_File_Pair(".",std::vector<std::string>()));
  tmp=TYPE_DIR;
  tmp_str.assign((char*)&tmp,sizeof(CX_UINT32));  
  dir_file[dirname]["."].push_back(tmp_str);  //VALUE_TYPE
  tmp=DT_NO;
  tmp_str.assign((char*)&tmp,sizeof(CX_UINT32));
  dir_file[dirname]["."].push_back(tmp_str);
  tmp_str.assign((char*)&default_dk_property,sizeof(CX_UINT32));  
  dir_file[dirname]["."].push_back(tmp_str);  //DK_PROPERTY

  return CX_OK;
}

CX_INT32 CPackage::CX_CreateFile(std::string dirname,std::string filename)
{

  CX_File::iterator file_ret=dir_file[dirname].find(filename);
  if(file_ret!=dir_file[dirname].end())
    return CX_FILEALREADYEXIST;

  dir_file[dirname].insert(CX_File_Pair(filename,std::vector<std::string>()));
  CX_UINT32 tmp=TYPE_FILE;
  std::string tmp_str;
  tmp_str.assign((char*)&tmp,sizeof(CX_UINT32));
  dir_file[dirname][filename].push_back(tmp_str);  //VALUE_TYPE
  dir_file[dirname][filename].push_back(filename);  //FK_SRCNAME
  tmp=0;
  tmp_str.assign((char*)&default_fk_prorerty,sizeof(CX_UINT32));
  dir_file[dirname][filename].push_back(tmp_str); //FK_PROPERTY
  tmp_str.assign((char*)&default_fk_compresstype,sizeof(CX_UINT32));
  dir_file[dirname][filename].push_back(tmp_str); //FK_COMPRESSTYPE
  return CX_OK;


}

CX_INT32 CPackage::CX_SetDirectoryProperty(std::string dirname,CX_UINT32 value)
{

  dir_file[dirname]["."][DK_PROPERTY].assign((char*)&value,sizeof(CX_UINT32));
  return CX_OK;
  
}


CX_INT32 CPackage::CX_SetFileInputFileName(std::string dirname,std::string filename,std::string inputfilename)
{
  dir_file[dirname][filename][FK_SRCNAME].assign(inputfilename.c_str(),inputfilename.size());
  return CX_OK;
}

CX_INT32 CPackage::CX_SetFileProperty(std::string dirname,std::string filename,CX_UINT32 value)
{

  dir_file[dirname][filename][FK_PROPERTY].assign((char*)&value,sizeof(CX_UINT32));
  return CX_OK;

}

CX_INT32 CPackage::CX_SetFileCompressType(std::string dirname,std::string filename,CX_UINT32 value)
{
  dir_file[dirname][filename][FK_COMPRESSTYPE].assign((char*)&value,sizeof(CX_UINT32));
  return CX_OK;

}


CX_INT32 CPackage::CX_GetDirectoryProperty(std::string dirname,CX_UINT32* value)
{

  memcpy(value,dir_file[dirname]["."][DK_PROPERTY].c_str(),sizeof(CX_UINT32));
  return CX_OK;
}

CX_INT32 CPackage::CX_GetFileInputFileName(std::string dirname, std::string filename,std::string& inputfilename)
{

  inputfilename.assign(dir_file[dirname][filename][FK_SRCNAME].c_str(),dir_file[dirname][filename][FK_SRCNAME].size());
  return CX_OK;
}

CX_INT32 CPackage::CX_GetFileProperty(std::string dirname,std::string filename,CX_UINT32* value)
{
  memcpy(value,dir_file[dirname][filename][FK_PROPERTY].c_str(),sizeof(CX_UINT32));
  return CX_OK;
}

CX_INT32 CPackage::CX_GetFileCompressType(std::string dirname,std::string filename,CX_UINT32* value)
{
  memcpy(value,dir_file[dirname][filename][FK_COMPRESSTYPE].c_str(),sizeof(CX_UINT32));
  return CX_OK;
}


std::vector<std::string> CPackage::CX_GetAllTopDirectoryName()
{
  std::vector<std::string> ret;
  CX_Dir_File::iterator it;
  CX_UINT32 dirtype;
  for(it=dir_file.begin();it!=dir_file.end();it++)
    {
      memcpy(&dirtype,dir_file[it->first]["."][DK_TOPDIR].c_str(),sizeof(CX_UINT32));
      if(dirtype==DT_YES)
	ret.push_back(it->first);
    }
  return ret;
}

std::vector<std::string> CPackage::CX_GetAllFileInDirectoryName(std::string dirname)
{
  std::vector<std::string> ret;
  CX_File files=dir_file[dirname];
  CX_File::iterator it;
  CX_UINT32 valuetype;
  for(it=files.begin();it!=files.end();it++)
    {
      memcpy(&valuetype,it->second[VALUE_TYPE].c_str(),sizeof(CX_UINT32));
      if(valuetype==TYPE_DIR)
	ret.push_back(std::string("Directory--")+it->first);
      else
	ret.push_back(std::string("File---")+it->first);
    }
  return ret;
}



















