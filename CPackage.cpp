#include "CPackage.h"


CPackage::CPackage()
{
  
}

CPackage::CPackage(std::string package_name)
{
  m_package.open(package_name);
}
CX_INT32 CPackage::AddFile(int filefullname)
{
  
  CXDirAndFile::iterator dir=m_file_dir.find(m_current_dir);
  if(dir!=m_file_dir.end())
    dir->second.append(std::vector<std::string>().append(filefullname));
  else
    m_file_dir.insert(pair<std::string,std::vector<std::vector<std::string>>(m_current_dir,std::vector<std::vector<std::std::string>>().append(std::vector<std::string>().append(filefullname))));
  return CX_OK;
}

CX_INT32 CPackage::SetCurrentDir(std::string dir)
{
  m_current_dir=dir;
  return CX_OK;
}

CX_INT32  CPackage::StartPackage()
{
  

}

CX_INT64 CPackage::GetFileSize(std::string filefullname)
{
  std::ifstream t_if(filefullname);
  t_if.seekg(std::ifstream::end);
  CX_INT64 size=t_if.tellg();
  return size;
}

CX_INT64 CPackage::SetLnkEnable(std::string &filefullname)
{
  filefullname.append(ADD_LNK);
  return CX_OK;
}

CX_INT32 CPackage::WriteDataBlock(DataInfo di)
{
  m_package.write(&di.dataname_size,sizeof(di.dataname_size));
  m_package.write(di.dataname,di.dataname_size);
  m_package.write(&di.data_compress_type,sizeof(data_compress_type));
  m_package.write(&di.data_size,sizeof(di.data_size));
  m_package.write(di.data,di.data_size);
  return CX_OK;
}

CX_INT32 CPackage::WriteDataDir(DataDirInfo ddi)
{
  m_package.write(&ddi.data_dir_name_size,sizeof(ddi.data_dir_name_size));
  m_package.write(ddi.data_dir_name,ddi.data_dir_name_size);
  m_package.write(&ddi.data_dir_file_num,sizeof(ddi.data_dir_file_num));
  return CX_OK;
}




















