#include "APPCommHdr.h"
#include "APPProtocol_Parse.h"
CAPPProtocol_Parse::CAPPProtocol_Parse()
{
}
CAPPProtocol_Parse::~CAPPProtocol_Parse()
{

}
//////////////////////////////////////////////////////////////////////////
//                             公有函数
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：APPProtocol_Parse_ToolReply
函数功能：转码工具通用响应解析
 参数.一：lpszMSGBuffer
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要解析的JSON缓冲区
 参数.二：nMSGLen
  In/Out：In
  类型：整数型
  可空：N
  意思：输入缓冲区大小
 参数.三：pInt_Code
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出解析到的状态
 参数.四：ptszMSGBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出解析到的内容
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CAPPProtocol_Parse::APPProtocol_Parse_ToolReply(LPCXSTR lpszMSGBuffer, int nMSGLen, int* pInt_Code /* = NULL */, XCHAR* ptszMSGBuffer /* = NULL */)
{
	if ((NULL == lpszMSGBuffer))
	{
		return false;
	}
	Json::Value st_JsonRoot;
	JSONCPP_STRING st_JsonError;
	Json::CharReaderBuilder st_JsonRBuilder;

	std::unique_ptr<Json::CharReader> const pSt_JsonReader(st_JsonRBuilder.newCharReader());
	if (!pSt_JsonReader->parse(lpszMSGBuffer, lpszMSGBuffer + nMSGLen, &st_JsonRoot, &st_JsonError))
	{
		return false;
	}

	if (NULL != pInt_Code)
	{
		*pInt_Code = st_JsonRoot["code"].asInt();
	}
	if (NULL != ptszMSGBuffer)
	{
		_tcsxcpy(ptszMSGBuffer, st_JsonRoot["msg"].asCString());
	}
	if (0 != st_JsonRoot["code"].asInt())
	{
		return false;
	}
	return true;
}
/********************************************************************
函数名称：APPProtocol_Parse_ToolCreate
函数功能：转码工具创建解析函数
 参数.一：lpszMSGBuffer
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要解析的JSON缓冲区
 参数.二：nMSGLen
  In/Out：In
  类型：整数型
  可空：N
  意思：输入缓冲区大小
 参数.三：pxhToken
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出解析到的句柄
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CAPPProtocol_Parse::APPProtocol_Parse_ToolCreate(LPCXSTR lpszMSGBuffer, int nMSGLen, XNETHANDLE* pxhToken)
{
	if ((NULL == lpszMSGBuffer))
	{
		return false;
	}
	Json::Value st_JsonRoot;
	JSONCPP_STRING st_JsonError;
	Json::CharReaderBuilder st_JsonRBuilder;

	std::unique_ptr<Json::CharReader> const pSt_JsonReader(st_JsonRBuilder.newCharReader());
	if (!pSt_JsonReader->parse(lpszMSGBuffer, lpszMSGBuffer + nMSGLen, &st_JsonRoot, &st_JsonError))
	{
		return false;
	}
	if (0 != st_JsonRoot["code"].asInt())
	{
		return false;
	}
	*pxhToken = st_JsonRoot["token"].asUInt64();
	return true;
}
/********************************************************************
函数名称：APPProtocol_Parse_ToolAi
函数功能：转码工具AI解析函数
 参数.一：lpszMSGBuffer
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要解析的JSON缓冲区
 参数.二：nMSGLen
  In/Out：In
  类型：整数型
  可空：N
  意思：输入缓冲区大小
 参数.三：pSt_AIConfigure
  In/Out：Out
  类型：数据结构指针
  可空：N
  意思：解析到的数据
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CAPPProtocol_Parse::APPProtocol_Parse_ToolAi(LPCXSTR lpszMSGBuffer, int nMSGLen, XENGINE_AICONFIGURE* pSt_AIConfigure)
{
	if ((NULL == lpszMSGBuffer))
	{
		return false;
	}
	Json::Value st_JsonRoot;
	JSONCPP_STRING st_JsonError;
	Json::CharReaderBuilder st_JsonRBuilder;

	std::unique_ptr<Json::CharReader> const pSt_JsonReader(st_JsonRBuilder.newCharReader());
	if (!pSt_JsonReader->parse(lpszMSGBuffer, lpszMSGBuffer + nMSGLen, &st_JsonRoot, &st_JsonError))
	{
		return false;
	}
	pSt_AIConfigure->bEnableAI = st_JsonRoot["bEnableAI"].asBool();
	
	Json::Value st_JsonVideo = st_JsonRoot["st_AIVideo"];
	Json::Value st_JsonAudio = st_JsonRoot["st_AIAudio"];

	if (!st_JsonVideo["bEnableTimeLimit"].isNull())
	{
		pSt_AIConfigure->st_AIVideo.bEnableTimeLimit = st_JsonVideo["bEnableTimeLimit"].asBool();
	}
	if (!st_JsonAudio["bEnableTimeLimit"].isNull())
	{
		pSt_AIConfigure->st_AIAudio.bEnableTimeLimit = st_JsonAudio["bEnableTimeLimit"].asBool();
	}

	if (!st_JsonRoot["st_AVCryption"].isNull())
	{
		Json::Value st_JsonCryption = st_JsonVideo["st_AVCryption"];
		pSt_AIConfigure->st_AVCryption.nCryptionAudioType = st_JsonCryption["nCryptionAudioType"].asInt();
		pSt_AIConfigure->st_AVCryption.nCryptionVideoType = st_JsonCryption["nCryptionVideoType"].asInt();
		pSt_AIConfigure->st_AVCryption.nCryptionLevel = st_JsonCryption["nCryptionLevel"].asInt();
		_tcsxcpy(pSt_AIConfigure->st_AVCryption.tszCryptionPass, st_JsonCryption["tszCryptionPass"].asCString());
	}

	if (!st_JsonVideo["st_CheckFrame"].isNull())
	{
		Json::Value st_JsonVCheckFrame = st_JsonVideo["st_CheckFrame"];
		if (!st_JsonVCheckFrame["bCheckFrame"].isNull())
		{
			pSt_AIConfigure->st_AIVideo.st_CheckFrame.bCheckFrame = st_JsonVCheckFrame["bCheckFrame"].asBool();
			pSt_AIConfigure->st_AIVideo.st_CheckFrame.dlThreshold = st_JsonVCheckFrame["dlThreshold"].asDouble();
			pSt_AIConfigure->st_AIVideo.st_CheckFrame.nCheckTime = st_JsonVCheckFrame["nCheckTime"].asInt();
			pSt_AIConfigure->st_AIVideo.st_CheckFrame.nCheckFrame = st_JsonVCheckFrame["nCheckFrame"].asInt();
		}
	}
	if (!st_JsonVideo["st_CheckBlack"].isNull())
	{
		Json::Value st_JsonVCheckBlack = st_JsonVideo["st_CheckBlack"];
		if (!st_JsonVCheckBlack["bCheckBlack"].isNull())
		{
			pSt_AIConfigure->st_AIVideo.st_CheckBlack.bCheckBlack = st_JsonVCheckBlack["bCheckBlack"].asBool();
			pSt_AIConfigure->st_AIVideo.st_CheckBlack.dlThreshold = st_JsonVCheckBlack["dlThreshold"].asDouble();
			pSt_AIConfigure->st_AIVideo.st_CheckBlack.nCheckTime = st_JsonVCheckBlack["nCheckTime"].asInt();
			pSt_AIConfigure->st_AIVideo.st_CheckBlack.nCheckFrame = st_JsonVCheckBlack["nCheckFrame"].asInt();
		}
	}
	if (!st_JsonAudio["st_CheckSilence"].isNull())
	{
		Json::Value st_JsonACheckSilence = st_JsonAudio["st_CheckSilence"];
		if (!st_JsonACheckSilence["bCheckSilence"].isNull())
		{
			pSt_AIConfigure->st_AIAudio.st_CheckSilence.bCheckSilence = st_JsonACheckSilence["bCheckSilence"].asBool();
			pSt_AIConfigure->st_AIAudio.st_CheckSilence.nCheckTime = st_JsonACheckSilence["nCheckTime"].asInt();
		}
	}
	
	return true;
}
/********************************************************************
函数名称：APPProtocol_Parse_ToolHeart
函数功能：转码工具心跳解析函数
 参数.一：lpszMSGBuffer
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要解析的JSON缓冲区
 参数.二：nMSGLen
  In/Out：In
  类型：整数型
  可空：N
  意思：输入缓冲区大小
 参数.三：pInt_Status
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出解析的状态
 参数.四：pInt_Status
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出解析的token
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CAPPProtocol_Parse::APPProtocol_Parse_ToolHeart(LPCXSTR lpszMSGBuffer, int nMSGLen, int* pInt_Status, XNETHANDLE* pInt_Token)
{
	if ((NULL == lpszMSGBuffer))
	{
		return false;
	}
	Json::Value st_JsonRoot;
	JSONCPP_STRING st_JsonError;
	Json::CharReaderBuilder st_JsonRBuilder;

	std::unique_ptr<Json::CharReader> const pSt_JsonReader(st_JsonRBuilder.newCharReader());
	if (!pSt_JsonReader->parse(lpszMSGBuffer, lpszMSGBuffer + nMSGLen, &st_JsonRoot, &st_JsonError))
	{
		return false;
	}
	
	if (!st_JsonRoot["data"].isNull())
	{
		return false;
	}
	Json::Value st_JsonData = st_JsonRoot["data"];
	if (!st_JsonData["nStatus"].isNull())
	{
		*pInt_Status = st_JsonData["nStatus"].asInt();
	}
	if (!st_JsonData["xhToken"].isNull())
	{
		*pInt_Token = st_JsonData["xhToken"].asUInt64();
	}

	return true;
}