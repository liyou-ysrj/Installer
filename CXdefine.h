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


//FILETYPE
#define FILE_DIR 0X1
#define FILE_FILE 0x2

//设置directoryoption时可用的key，可以用|操作符同时赋予多个属性
#define FILE_TYPE 0x0
#define DK_NAME 0X1
#define DK_PROPERTY 0X2 
#define DK_FILENUM 0X3

//DK_NAME对应的value是char类型

//DK_PRORERTY对应的value可取的值
#define DP_NONE 0
#define DP_HIDDEN 0X1
#define DP_READONLY 0X2
#define DP_SYSTEM 0X4

//DK_FILENUM可以取的值为CX_UINT32类型


//设置fileoption可用的key
#define FILE_TYPE 0x0
#define FK_SRCNAME 0x1
#define FK_PROPERTY 0x3
#define FK_COMPRESSTYPE 0x4

//FK_SRCNAME和FK_TARGETNAME对应的value类型应该是char类型的

//FK_PROPERTY对应的value,可以用|操作符同时赋予多个属性
#define FP_NONE 0
#define FP_READONLY 0X1
#define FP_HIDDEN 0X2
#define FP_SYSTEM 0X4
#define FP_DESKTOP 0X8
#define FP_STARTMENU 0X10
#define FP_TASKBAR 0X20


//file_compress_type对应的value可取的值
#define FCT_NONE 0X0
#define FCT_GZIP 0X1
#define FCT_DEFLATE 0x2



#endif












