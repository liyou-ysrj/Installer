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
CX_INT32 CPackage::CX_CreateDirectory(std::string dirname)
{
  CX_Dir_File::iterator ret=dir_file.find(dirname);
  if(ret!=dir_file.end())
    return CX_DIRALREADYEXIST;

  dir_file.insert(CX_Dir_Pair(dirname,CX_File()));
  dir_file[dirname].insert(CX_File_Pair(".",std::vector<std::string>()));
  CX_UINT32 tmp=FILE_DIR;
  std::string tmp_str;
  tmp_str.assign((char*)&tmp,sizeof(CX_UINT32));
  dir_file[dirname]["."].push_back(tmp_str);
  dir_file[dirname]["."].push_back(dirname);
  tmp_str.assign((char*)&default_dk_property,sizeof(CX_UINT32));
  dir_file[dirname]["."].push_back(tmp_str);
  tmp=0;
  tmp_str.assign((char*)&tmp,sizeof(CX_UINT32));
  dir_file[dirname]["."].push_back(tmp_str);
					   
  return CX_OK;

}

CX_INT32 CPackage::CX_CreateFile(std::string dirname,std::string filename)
{
  CX_Dir_File::iterator dir_ret=dir_file.find(dirname);
  if(dir_ret==dir_file.end())
    {
      dir_file.insert(CX_Dir_Pair(dirname,CX_File()));
      dir_file[dirname].insert(CX_File_Pair(".",std::vector<std::string>()));
    }
  CX_File::iterator file_ret=dir_file[dirname].find(filename);
  if(file_ret!=dir_file[dirname].end())
    return CX_FILEALREADYEXIST;

  dir_file[dirname].insert(CX_File_Pair(filename,std::vector<std::string>()));
  CX_UINT32 tmp=FILE_FILE;
  std::string tmp_str;
  tmp_str.assign((char*)&tmp,sizeof(CX_UINT32));
  dir_file[dirname][filename].push_back(tmp_str);
  dir_file[dirname][filename].push_back(filename);
  tmp=0;
  tmp_str.assign((char*)&default_fk_prorerty,sizeof(CX_UINT32));
  dir_file[dirname][filename].push_back(tmp_str);
  tmp_str.assign((char*)&default_fk_compresstype,sizeof(CX_UINT32));
  dir_file[dirname][filename].push_back(tmp_str);
  return CX_OK;


}

CX_INT32 CPackage::CX_SetDirectoryOption(std::string dirname, CX_UINT32 key, void *value, CX_INT32 *value_size)
{
  CX_UINT32 tmp_value;
  switch(key)
    {
    case DK_NAME:
      dir_file[dirname]["."][DK_NAME].assign((char*)value,*value_size);
      return CX_OK;
      break;

    case DK_PROPERTY:
    case DK_FILENUM:
      tmp_value=(*(CX_UINT32*)value);
      dir_file[dirname]["."][key].assign((char*)&tmp_value,sizeof(CX_UINT32));
      break;

    default:
      return CX_WRONGKEY;
      break;

    }
  return CX_OK;
  
}

CX_INT32 CPackage::CX_SetFileOption(std::string dirname,std::string filename,CX_UINT32 key,void* value,CX_INT32* value_size)
{
  CX_UINT32 tmp_value;
  switch(key)
    {
    case FK_SRCNAME:
      dir_file[dirname][filename][key].assign((char*)value,*value_size);
      break;

    case FK_PROPERTY:
    case FK_COMPRESSTYPE:
      tmp_value=(*(CX_UINT32*)value);
      dir_file[dirname][filename][key].assign((char*)&tmp_value,sizeof(CX_UINT32));
      break;
    default:
      return CX_WRONGKEY;
      break;
    }

  return CX_OK;
}

CX_INT32 CPackage::CX_GetDirectoryOption(std::string dirname,CX_UINT32 key,void* value,CX_INT32* value_size)
{
  switch(key)
    {
    case DK_NAME:
      {
	std::string::size_type tmp_size=dir_file[dirname]["."][key].size();
	(*value_size)=tmp_size>(*value_size)?(*value_size):tmp_size;
	memcpy(value,dir_file[dirname]["."][key].c_str(),*value_size);
      }
      break;

    case DK_PROPERTY:
    case DK_FILENUM:
      if(*value_size!=sizeof(CX_UINT32))
	{
	  *value_size=sizeof(CX_UINT32);
	  return CX_WRONGVALUESIZE;
	}
      memcpy(value,dir_file[dirname]["."][key].c_str(),*value_size);
      break;

    default:
      return CX_WRONGKEY;
      break;

    }

  return CX_OK;
}


CX_INT32 CPackage::CX_GetFileOption(std::string dirname, std::string filename, CX_UINT32 key, void *value, CX_INT32 *value_size)
{
  std::string::size_type tmp_size;

  switch(key)
    {
    case FK_SRCNAME:
      tmp_size=dir_file[dirname][filename][key].size();
      (*value_size)=tmp_size>(*value_size)?(*value_size):tmp_size;
      memcpy(value,dir_file[dirname][filename][key].c_str(),*value_size);
      break;

    case FK_PROPERTY:
    case FK_COMPRESSTYPE:
      memcpy(value,dir_file[dirname][filename][key].c_str(),sizeof(CX_UINT32));
      break;
    }


  return CX_OK;
}



std::vector<std::string> CPackage::CX_GetAllDirectoryName()
{
  std::vector<std::string> ret;
  CX_Dir_File::iterator it;
  for(it=dir_file.begin();it!=dir_file.end();it++)
    {
      ret.push_back(it->first);
    }
  return ret;
}

std::vector<std::string> CPackage::CX_GetAllFileInDirectoryName(std::string dirname)
{
  std::vector<std::string> ret;
  CX_File files=dir_file[dirname];
  CX_File::iterator it;
  for(it=files.begin();it!=files.end();it++)
    {
      ret.push_back(it->first);
    }
  return ret;
}



















