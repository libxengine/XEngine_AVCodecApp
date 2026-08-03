#include "pch.h"
#include "Plugin_AudioHook.h"
/********************************************************************
//    Created:     2026/08/02  15:00:19
//    File Name:   D:\XEngine_AVCodecApp\AVCodec_PluginExample\PluginModule_AudioHook\Plugin_AudioHook\Plugin_AudioHook.cpp
//    File Path:   D:\XEngine_AVCodecApp\AVCodec_PluginExample\PluginModule_AudioHook\Plugin_AudioHook
//    File Base:   Plugin_AudioHook
//    File Ext:    cpp
//    Project:     XEngine_AVCodecApp (AV 编解码插件示例)
//    Author:      qyt
//    Purpose:     音频钩子插件实现
//    History:
*********************************************************************/
CPlugin_AudioHook::CPlugin_AudioHook()
{
}
CPlugin_AudioHook::~CPlugin_AudioHook()
{
}
//////////////////////////////////////////////////////////////////////////
//                       公有函数
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：PluginCore_Init
函数功能：初始化插件模块
 参数.一：pSt_PluginParameter
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入插件初始化信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CPlugin_AudioHook::PluginCore_Init(XENGINE_PLUGINPARAM *pSt_PluginParameter)
{
	AudioHook_IsErrorOccur = false;

	pSt_File = _xtfopen(_X("Audio.pcm"), _X("wb"));
    return true;
}
/********************************************************************
函数名称：PluginCore_UnInit
函数功能：卸载插件
返回值
  类型：无
  意思：
备注：
*********************************************************************/
void CPlugin_AudioHook::PluginCore_UnInit()
{
	AudioHook_IsErrorOccur = false;

	fclose(pSt_File);
}
/********************************************************************
函数名称：PluginCore_RegisterType
函数功能：注册插件类型
返回值
  类型：整数
  意思：插件类型,0无效,1视频,2音频
备注：
*********************************************************************/
int CPlugin_AudioHook::PluginCore_RegisterType()
{
	AudioHook_IsErrorOccur = false;

	return 2;
}
/********************************************************************
函数名称：PluginCore_GetInfo
函数功能：获取插件基础信息函数
 参数.一：ptszPluginName
  In/Out：Out
  类型：字符指针
  可空：N
  意思：处理名称
 参数.二：ptszPluginVersion
  In/Out：Out
  类型：字符指针
  可空：N
  意思：版本号.使用x.x.x.x 格式
 参数.三：ptszPluginAuthor
  In/Out：Out
  类型：字符指针
  可空：N
  意思：作者
 参数.四：ptszPluginDesc
  In/Out：Out
  类型：字符指针
  可空：N
  意思：插件描述
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
void CPlugin_AudioHook::PluginCore_GetInfo(XCHAR* ptszPluginName, XCHAR* ptszPluginVersion, XCHAR* ptszPluginAuthor, XCHAR* ptszPluginDesc)
{
	AudioHook_IsErrorOccur = false;
	
	_tcsxcpy(ptszPluginName, "audiohook");
	_tcsxcpy(ptszPluginVersion, "1.0.0.1001");
	_tcsxcpy(ptszPluginAuthor, "xengine");
	_tcsxcpy(ptszPluginDesc, "Audio Hook Plugin for XEngine API Service");
}
/********************************************************************
函数名称：PluginCore_Call
函数功能：调用插件
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CPlugin_AudioHook::PluginCore_Call(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, LPCXSTR lpszMsgBufer, int nMsgLen, XCHAR*** pppInputParameters, int nInputPCount, XCHAR*** pppOutputParameters, int* pInt_OutputPCount)
{
	AudioHook_IsErrorOccur = false;

	if ((NULL == ptszMsgBuffer) || (NULL == pInt_MsgLen))
	{
		AudioHook_IsErrorOccur = true;
		AudioHook_dwErrorCode = ERROR_AVCODEC_PLUGIN_MODULE_AUDIOHOOK_PARAMENT;
		return false;
	}
	return true;
}
bool CPlugin_AudioHook::PluginCore_Call2(XHANDLE*** ppphBuffer)
{
	AudioHook_IsErrorOccur = false;

	XENGINE_MSGBUFFER st_AVBuffer = {};
	AVHelp_Memory_GetAudioBuffer((*ppphBuffer)[0], &st_AVBuffer, false);
	fwrite(st_AVBuffer.unData.ptszMSGBuffer, 1, st_AVBuffer.nMSGLen[0], pSt_File);
	BaseLib_Memory_MSGFree(&st_AVBuffer);
	return true;
}
//////////////////////////////////////////////////////////////////////////
//                       保护函数
//////////////////////////////////////////////////////////////////////////