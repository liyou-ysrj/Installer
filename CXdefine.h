#ifndef CX_DEFINE_H
#define CX_DEFINE_H




#define CX_OK 0
#define CX_FAILD 0x1
#define CX_DIRALREADYEXIST 0X2
#define CX_DIRNOTEXIST 0X3
#define CX_FILEALREADYEXIST 0x4
#define CX_FILENOTEXIST 0X5
#define CX_WRONGVALUESIZE 0X6
#define CX_WRONGKEY 0X7
#define CX_LAST 0XFFFFFFFF

/**********************************************************************
 *
 ********************CPackage类内部使用的宏定义不供调用者使用****************/

//定义Directory的各个key的位置
#define VALUE_TYPE 0x0
#define DK_TOPDIR 0x1
#define DK_PROPERTY 0X2 


//VALUE_TYPE 设置directory是否是TopDirectory,根据创建的目录是不是TopDirectory由函数自动取值
#define TYPE_DIR 0X1
#define TYPE_FILE 0x2


//DK_TOPDIR对应的value是UINT_32
#define DT_YES 0x0
#define DT_NO 0x1

//设置fileoption可用的key
#define VALUE_TYPE 0x0
#define FK_SRCNAME 0x1
#define FK_PROPERTY 0x3
#define FK_COMPRESSTYPE 0x4


/********************************************************************
********************调用者可以使用的宏定义常量**************************/

//设置DirectoryProperty时可用的value值
#define DP_NONE 0
#define DP_HIDDEN 0X1
#define DP_READONLY 0X2
#define DP_SYSTEM 0X4


//设置FileProperty时可用的value值
#define FP_NONE 0
#define FP_READONLY 0X1
#define FP_HIDDEN 0X2
#define FP_SYSTEM 0X4
#define FP_DESKTOP 0X8
#define FP_STARTMENU 0X10
#define FP_TASKBAR 0X20


//设置FileCompressType时可用的value值
#define FCT_NONE 0X0
#define FCT_GZIP 0X1
#define FCT_DEFLATE 0x2

/*******************************************************************/



#endif












