#include "pch.h"
#include "Plugin_AudioHook/Plugin_AudioHook.h"
/********************************************************************
//    Created:     2026/08/02  15:52:56
//    File Name:   D:\XEngine_AVCodecApp\AVCodec_PluginExample\PluginModule_AudioHook\pch.cpp
//    File Path:   D:\XEngine_AVCodecApp\AVCodec_PluginExample\PluginModule_AudioHook
//    File Base:   pch
//    File Ext:    cpp
//    Project:     AVCodec_PluginExample
//    Author:      qyt
//    Purpose:     导出实现
//    History:
*********************************************************************/
bool AudioHook_IsErrorOccur = false;
XLONG AudioHook_dwErrorCode = 0;
//////////////////////////////////////////////////////////////////////////
CPlugin_AudioHook m_PluginAudioHook;
//////////////////////////////////////////////////////////////////////////
//                       导出函数定义
//////////////////////////////////////////////////////////////////////////
extern "C" XLONG PluginCore_GetLastError()
{
	return AudioHook_dwErrorCode;
}
/*********************************************************************************
*                                导出函数定义                                    *
*********************************************************************************/
extern "C" bool PluginCore_Init(XENGINE_PLUGINPARAM* pSt_PluginParameter)
{
	return m_PluginAudioHook.PluginCore_Init(pSt_PluginParameter);
}
extern "C" void PluginCore_UnInit()
{
	m_PluginAudioHook.PluginCore_UnInit();
}
extern "C" int PluginCore_RegisterType()
{
	return m_PluginAudioHook.PluginCore_RegisterType();
}
extern "C" void PluginCore_GetInfo(XCHAR* ptszPluginName, XCHAR* ptszPluginVersion, XCHAR* ptszPluginAuthor, XCHAR* ptszPluginDesc)
{
	return m_PluginAudioHook.PluginCore_GetInfo(ptszPluginName, ptszPluginVersion, ptszPluginAuthor, ptszPluginDesc);
}
extern "C" bool PluginCore_Call(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, LPCXSTR lpszMsgBufer, int nMsgLen, XCHAR*** pppInputParameters, int nInputPCount, XCHAR*** pppOutputParameters, int* pInt_OutputPCount)
{
	return m_PluginAudioHook.PluginCore_Call(ptszMsgBuffer, pInt_MsgLen, lpszMsgBufer, nMsgLen, pppInputParameters, nInputPCount, pppOutputParameters, pInt_OutputPCount);
}
extern "C" bool PluginCore_Call2(XHANDLE*** ppphBuffer)
{
	return m_PluginAudioHook.PluginCore_Call2(ppphBuffer);
}