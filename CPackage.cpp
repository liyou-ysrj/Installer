#include "CPackage.h"
#include <string.h>

CPackage::CPackage()
{
 
}

CPackage::CPackage(std::string package_name)
{
  m_package.open(package_name.c_str());
}

CX_INT32 CPackage::CX_CreateDirectory(std::string dirname)
{
  CX_Dir_File::iterator ret=dir_file.find(dirname);
  if(ret!=dir_file.end())
    return CX_DIRALREADYEXIST;

  dir_file.insert(CX_Dir_Pair(dirname,CX_File()));
  dir_file[dirname].insert(CX_File_Pair(".",std::vector<std::string>()));
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
  return CX_OK;


}

CX_INT32 CPackage::CX_SetDirectoryOption(std::string dirname, directory_key key, void *value, CX_INT32 *value_size)
{
 
  switch(key)
    {
    case DK_NAME:
      dir_file[dirname]["."][DK_NAME].assign((char*)value,*value_size);
      return CX_OK;
      break;
    case DK_PROPERTY:
      if(*value_size!=sizeof(directory_property))
	{
	  *value_size=sizeof(directory_property);
	  return CX_WRONGVALUESIZE;
	}
      dir_file[dirname]["."][DK_PROPERTY].assign((char*)value,*value_size);
      break;

    case DK_FILENUM:
      dir_file[dirname]["."][DK_FILENUM].assign((char*)value,*value_size);
      break;

    default:
      return CX_WRONGKEY;
      break;

    }
  return CX_OK;
  
}

CX_INT32 CPackage::CX_SetFileOption(std::string dirname,std::string filename,file_key key,void* value,CX_INT32* value_size)
{
  switch(key)
    {
    case FK_SRCNAME:
      dir_file[dirname][filename][FK_SRCNAME].assign((char*)value,*value_size);
      break;

    case FK_TARGETNAME:
      dir_file[dirname][filename][FK_TARGETNAME].assign((char*)value,*value_size);
      break;

    case FK_PROPERTY:
      if(*value_size!=sizeof(file_property))
	return CX_WRONGVALUESIZE;
      dir_file[dirname][filename][FK_PROPERTY].assign((char*)value,*value_size);
      break;

    case FK_COMPRESSTYPE:
      if(*value_size!=sizeof(file_compress_type))
	return CX_WRONGVALUESIZE;
      dir_file[dirname][filename][FK_COMPRESSTYPE].assign((char*)value,*value_size);
      break;
    default:
      return CX_WRONGKEY;
      break;
    }

  return CX_OK;
}

CX_INT32 CPackage::CX_GetDirectoryOption(std::string dirname,std::string filename,directory_key key,void* value,CX_INT32* value_size)
{


  return CX_OK;
}


CX_INT32 CPackage::CX_GetFileOption(std::string dirname, std::string filename, file_key key, void *value, CX_INT32 *value_size)
{
  switch(key)
    {
    case DK_NAME:
      {
	std::string::size_type tmp_size=dir_file[dirname][filename][DK_NAME].size();
	std::string::size_type* tmp_value_size=(std::string::size_type*)value_size;
       	memcpy(value,dir_file[dirname][filename][DK_NAME].c_str(),(tmp_size>*tmp_value_size)?(*tmp_value_size):tmp_size);
  
      }
      break;
      
    case DK_PROPERTY:

      break;




    }


  return CX_OK;
}



std::vector<std::string> CPackage::CX_GetAllDirectoryName()
{

}

std::vector<std::string> CPackage::CX_GetAllFileInDirectoryName()
{

}














