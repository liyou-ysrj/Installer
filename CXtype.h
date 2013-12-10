#ifndef CX_TYPE_H
#define CX_TYPE_H
#include "CXPrimitiveType.h"

enum directory_key
  {
    DK_NAME=0X1,
    DK_PROPERTY=0X2,
    DK_FILENUM=0X3,
    DK_NONE=0XFFFFFFFF
  };
enum directory_property
  {
    DP_HIDDEN=0X1,
    DP_READONLY=0X2,
    DP_SYSTEM=0X4,
    DP_NONE=0XFFFFFFFF
  };



enum file_key
  {
    FK_SRCNAME,
    FK_TARGETNAME,
    FK_PROPERTY,
    FK_COMPRESSTYPE,
    FK_NONE=0XFFFFFFFF
  };
enum file_property
  {
    FP_READONLY=0X1,
    FP_HIDDEN=0X2,
    FP_SYSTEM=0X4,
    FP_DESKTOP=0X8,
    FP_STARTMENU=0X10,
    FP_TASKBAR=0X20,
    FP_NONE=0XFFFFFFFF
  };
enum file_compress_type
  {
    FCT_GZIP=0X1,
    FCT_DEFLATE=0X2,
    FCT_NONE=0XFFFFFFFF
  };







#endif
















