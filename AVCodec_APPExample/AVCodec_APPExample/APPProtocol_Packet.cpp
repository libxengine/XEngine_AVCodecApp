#include "APPCommHdr.h"
#include "APPProtocol_Packet.h"
CAPPProtocol_Packet::CAPPProtocol_Packet()
{
}
CAPPProtocol_Packet::~CAPPProtocol_Packet()
{

}
//////////////////////////////////////////////////////////////////////////
//                             公有函数
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：APPProtocol_Packet_ToolCreate
函数功能：转码工具创建函数
 参数.一：ptszMSGBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出封包数据
 参数.二：pInt_MSGLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出封包大小
 参数.三：lpszDestFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入转码到的目标为止
 参数.四：lpszDestType
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入转码的媒体格式
 参数.五：nHLSTime
  In/Out：In
  类型：整数型
  可空：Y
  意思：输入HLS切片时间
 参数.六：nTotalRate
  In/Out：In
  类型：整数型
  可空：Y
  意思：输入总码率
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CAPPProtocol_Packet::APPProtocol_Packet_ToolCreate(XCHAR* ptszMSGBuffer, int* pInt_MSGLen, LPCXSTR lpszDestFile, LPCXSTR lpszDestType, int nHLSTime /* = 0 */, int nTotalRate /* = 0 */)
{
	if ((NULL == ptszMSGBuffer) || (NULL == pInt_MSGLen))
	{
		return false;
	}
	Json::Value st_JsonRoot;
	Json::StreamWriterBuilder st_JsonWBuilder;

#ifdef _MSC_BUILD
	XCHAR tszUTFBuffer[XPATH_MAX] = {};
	BaseLib_Charset_AnsiToUTF(lpszDestFile, tszUTFBuffer);
	st_JsonRoot["streamaddr"] = tszUTFBuffer;
#else
	st_JsonRoot["streamaddr"] = lpszDestFile;
#endif

	if (0 == _tcsxncmp(lpszDestType, "ts", 2))
	{
		st_JsonRoot["streamtype"] = "mpegts";
	}
	else
	{
		st_JsonRoot["streamtype"] = lpszDestType;
	}
	st_JsonRoot["nHLSTime"] = nHLSTime;
	st_JsonRoot["nTotalRate"] = nTotalRate;

	st_JsonWBuilder["emitUTF8"] = true;
	*pInt_MSGLen = (int)Json::writeString(st_JsonWBuilder, st_JsonRoot).length();
	memcpy(ptszMSGBuffer, Json::writeString(st_JsonWBuilder, st_JsonRoot).c_str(), *pInt_MSGLen);

	return true;
}
/********************************************************************
函数名称：APPProtocol_Packet_ToolCodec
函数功能：转码工具编解码函数封装
 参数.一：ptszMSGBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出封包数据
 参数.二：pInt_MSGLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出封包大小
 参数.三：pSt_AVProtocol
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入音视频转码信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CAPPProtocol_Packet::APPProtocol_Packet_ToolCodec(XCHAR* ptszMSGBuffer, int* pInt_MSGLen, XENGINE_AVCONFIGINFO *pSt_AVProtocol)
{
	if ((NULL == ptszMSGBuffer) || (NULL == pInt_MSGLen))
	{
		return false;
	}
	Json::Value st_JsonRoot;
	Json::Value st_JsonVideo;
	Json::Value st_JsonAudio;
	Json::StreamWriterBuilder st_JsonWBuilder;

	st_JsonVideo["bEnable"] = pSt_AVProtocol->st_AVVideo.bEnable;
	st_JsonVideo["nBitRate"] = (Json::Value::UInt64)pSt_AVProtocol->st_AVVideo.nBitRate;
	st_JsonVideo["enAVCodec"] = pSt_AVProtocol->st_AVVideo.enAVCodec;
	st_JsonVideo["nGOPSize"] = pSt_AVProtocol->st_AVVideo.nGOPSize;
	st_JsonVideo["nWidth"] = pSt_AVProtocol->st_AVVideo.nWidth;
	st_JsonVideo["nHeight"] = pSt_AVProtocol->st_AVVideo.nHeight;
	st_JsonVideo["nFormat"] = pSt_AVProtocol->st_AVVideo.nFormat;
	st_JsonVideo["nFrameBase"] = pSt_AVProtocol->st_AVVideo.nFrameBase;
	st_JsonVideo["nFrameRate"] = pSt_AVProtocol->st_AVVideo.nFrameRate;
	Json::Value st_JsonVCodec;
	st_JsonVCodec["tszENCodecGPU"] = pSt_AVProtocol->st_VideoCodec.tszENCodecGPU;
	st_JsonVCodec["tszDECodecGPU"] = pSt_AVProtocol->st_VideoCodec.tszDECodecGPU;
	st_JsonVCodec["tszRateControl"] = pSt_AVProtocol->st_VideoCodec.tszRateControl;
	st_JsonVCodec["tszProfileID"] = pSt_AVProtocol->st_VideoCodec.tszProfileID;
	st_JsonVCodec["tszCodecLevel"] = pSt_AVProtocol->st_VideoCodec.tszCodecLevel;
	st_JsonVCodec["tszCodecPreset"] = pSt_AVProtocol->st_VideoCodec.tszCodecPreset;
	st_JsonVCodec["tszCodecTune"] = pSt_AVProtocol->st_VideoCodec.tszCodecTune;
	st_JsonVCodec["nBitRateMin"] = pSt_AVProtocol->st_VideoCodec.nBitRateMin;
	st_JsonVCodec["nBitRateMax"] = pSt_AVProtocol->st_VideoCodec.nBitRateMax;
	st_JsonVCodec["nBitRateSize"] = pSt_AVProtocol->st_VideoCodec.nBitRateSize;
	st_JsonVCodec["nColor"] = pSt_AVProtocol->st_VideoCodec.nColor;
	st_JsonVCodec["nFrameRef"] = pSt_AVProtocol->st_VideoCodec.nFrameRef;
	st_JsonVCodec["bGOPForce"] = pSt_AVProtocol->st_VideoCodec.bGOPForce;

	Json::Value st_JsonVFilter;
	Json::Value st_JsonFilterSubtitle;
	st_JsonFilterSubtitle["bEnableSubtitle"] = pSt_AVProtocol->st_VideoFilter.st_FilterSubtitle.bEnableSubtitle;
	st_JsonFilterSubtitle["nSTTextAlpha"] = pSt_AVProtocol->st_VideoFilter.st_FilterSubtitle.nSTTextAlpha;
	st_JsonFilterSubtitle["nSTTextOutline"] = pSt_AVProtocol->st_VideoFilter.st_FilterSubtitle.nSTTextOutline;
	st_JsonFilterSubtitle["nSTTextPos"] = pSt_AVProtocol->st_VideoFilter.st_FilterSubtitle.nSTTextPos;
	st_JsonFilterSubtitle["nSTTextSize"] = pSt_AVProtocol->st_VideoFilter.st_FilterSubtitle.nSTTextSize;
	st_JsonFilterSubtitle["nSTTextPos"] = pSt_AVProtocol->st_VideoFilter.st_FilterSubtitle.nSTTextXPos;
	st_JsonFilterSubtitle["nSTTextPos"] = pSt_AVProtocol->st_VideoFilter.st_FilterSubtitle.nSTTextYPos;
	st_JsonFilterSubtitle["tszSTTextColor"] = pSt_AVProtocol->st_VideoFilter.st_FilterSubtitle.tszSTTextColor;
	XCHAR tszFontStr[XPATH_MAX] = {};
	_xstprintf(tszFontStr, _X("./XEngine_Config/Fonts/%s.otf"), pSt_AVProtocol->st_VideoFilter.st_FilterSubtitle.tszSTTextFont);
	st_JsonFilterSubtitle["tszSTTextFont"] = tszFontStr;

	st_JsonVFilter["st_FilterSubtitle"] = st_JsonFilterSubtitle;
	st_JsonVideo["st_VideoFilter"] = st_JsonVFilter;
	//音频
	st_JsonAudio["bEnable"] = pSt_AVProtocol->st_AVAudio.bEnable;
	st_JsonAudio["nBitRate"] = (Json::Value::UInt64)pSt_AVProtocol->st_AVAudio.nBitRate;
	st_JsonAudio["enAVCodec"] = pSt_AVProtocol->st_AVAudio.enAVCodec;
	st_JsonAudio["nChannel"] = pSt_AVProtocol->st_AVAudio.nChannel;
	st_JsonAudio["nSampleFmt"] = pSt_AVProtocol->st_AVAudio.nSampleFmt;
	st_JsonAudio["nSampleRate"] = pSt_AVProtocol->st_AVAudio.nSampleRate;
	Json::Value st_JsonACodec;
	st_JsonACodec["tszRateControl"] = pSt_AVProtocol->st_AudioCodec.tszRateControl;
	st_JsonACodec["nBitRateMin"] = pSt_AVProtocol->st_AudioCodec.nBitRateMin;
	st_JsonACodec["nBitRateMax"] = pSt_AVProtocol->st_AudioCodec.nBitRateMax;

	Json::Value st_JsonAFilter;
	st_JsonAFilter["bEBUR128"] = pSt_AVProtocol->st_AudioFilter.bEBUR128;
	st_JsonAFilter["bResampleChannel"] = pSt_AVProtocol->st_AudioFilter.bResampleChannel;
	st_JsonAudio["st_AudioFilter"] = st_JsonAFilter;

	st_JsonVideo["st_CodecConfigure"] = st_JsonVCodec;
	st_JsonAudio["st_CodecConfigure"] = st_JsonACodec;
	st_JsonRoot["st_VideoInfo"] = st_JsonVideo;
	st_JsonRoot["st_AudioInfo"] = st_JsonAudio;

	st_JsonWBuilder["emitUTF8"] = true;
	*pInt_MSGLen = (int)Json::writeString(st_JsonWBuilder, st_JsonRoot).length();
	memcpy(ptszMSGBuffer, Json::writeString(st_JsonWBuilder, st_JsonRoot).c_str(), *pInt_MSGLen);

	return true;
}
/********************************************************************
函数名称：APPProtocol_Packet_ToolPlayer
函数功能：转码工具播放函数封装
 参数.一：ptszMSGBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出封包数据
 参数.二：pInt_MSGLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出封包大小
 参数.三：lpszSourceFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入原始文件地址
 参数.四：lpszPlayerTime
  In/Out：In
  类型：常量字符指针
  可空：Y
  意思：输入切换时间
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CAPPProtocol_Packet::APPProtocol_Packet_ToolPlayer(XCHAR* ptszMSGBuffer, int* pInt_MSGLen, LPCXSTR lpszSourceFile, LPCXSTR lpszPlayerTime /* = _X("1") */)
{
	if ((NULL == ptszMSGBuffer) || (NULL == pInt_MSGLen))
	{
		return false;
	}
	Json::Value st_JsonRoot;
	Json::StreamWriterBuilder st_JsonWBuilder;

	XCHAR tszUTFBuffer[XPATH_MAX] = {};
	BaseLib_Charset_AnsiToUTF(lpszSourceFile, tszUTFBuffer);
	st_JsonRoot["filename"] = tszUTFBuffer;
	st_JsonRoot["sysstartime"] = lpszPlayerTime;
	st_JsonRoot["avstarttime"];
	st_JsonRoot["show"] = false;

	st_JsonWBuilder["emitUTF8"] = true;
	*pInt_MSGLen = (int)Json::writeString(st_JsonWBuilder, st_JsonRoot).length();
	memcpy(ptszMSGBuffer, Json::writeString(st_JsonWBuilder, st_JsonRoot).c_str(), *pInt_MSGLen);

	return true;
}
/********************************************************************
函数名称：APPProtocol_Packet_ToolFilter
函数功能：转码工具滤镜函数封装
 参数.一：ptszMSGBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出封包数据
 参数.二：pInt_MSGLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出封包大小
 参数.三：pSt_CVProtocol
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入滤镜处理信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CAPPProtocol_Packet::APPProtocol_Packet_ToolFilter(XCHAR* ptszMSGBuffer, int* pInt_MSGLen, XENGINE_CVCONFIGURE* pSt_CVProtocol)
{
	if ((NULL == ptszMSGBuffer) || (NULL == pInt_MSGLen))
	{
		return false;
	}
	Json::Value st_JsonRoot;
	Json::Value st_JsonVideo;
	Json::StreamWriterBuilder st_JsonWBuilder;

	Json::Value st_JsonVideoWaterMaker;
	if (pSt_CVProtocol->st_VideoFilter.st_FilterWaterMaker.bEnableWaterMaker)
	{
		st_JsonVideoWaterMaker["bEnable"] = pSt_CVProtocol->st_VideoFilter.st_FilterWaterMaker.bEnableWaterMaker;
		st_JsonVideoWaterMaker["nTime"] = pSt_CVProtocol->st_VideoFilter.st_FilterWaterMaker.nWMTime;
		st_JsonVideoWaterMaker["dlSize"] = pSt_CVProtocol->st_VideoFilter.st_FilterWaterMaker.dlWMSize;
		st_JsonVideoWaterMaker["nXPoint"] = pSt_CVProtocol->st_VideoFilter.st_FilterWaterMaker.nWMXPoint;
		st_JsonVideoWaterMaker["nYPoint"] = pSt_CVProtocol->st_VideoFilter.st_FilterWaterMaker.nWMYPoint;
		st_JsonVideoWaterMaker["tszImageFile"] = pSt_CVProtocol->st_VideoFilter.st_FilterWaterMaker.tszWMImage;
	}
	Json::Value st_JsonVideoText;
	if (pSt_CVProtocol->st_VideoFilter.st_FilterText.bEnableText)
	{
		st_JsonVideoText["bEnable"] = pSt_CVProtocol->st_VideoFilter.st_FilterText.bEnableText;
		st_JsonVideoText["nBorder"] = pSt_CVProtocol->st_VideoFilter.st_FilterText.nBorder;
		st_JsonVideoText["nTime"] = pSt_CVProtocol->st_VideoFilter.st_FilterText.nTextTime;
		st_JsonVideoText["nSize"] = pSt_CVProtocol->st_VideoFilter.st_FilterText.nTextSize;
		st_JsonVideoText["nAlpha"] = pSt_CVProtocol->st_VideoFilter.st_FilterText.nTextAlpha;
		XCHAR tszUTFBuffer[XPATH_MIN] = {};
		BaseLib_Charset_AnsiToUTF(pSt_CVProtocol->st_VideoFilter.st_FilterText.tszTextStr, tszUTFBuffer);
		st_JsonVideoText["tszText"] = tszUTFBuffer;
		st_JsonVideoText["tszColor"] = pSt_CVProtocol->st_VideoFilter.st_FilterText.tszTextColor;
		st_JsonVideoText["nXPoint"] = pSt_CVProtocol->st_VideoFilter.st_FilterText.nTextXPoint;
		st_JsonVideoText["nYPoint"] = pSt_CVProtocol->st_VideoFilter.st_FilterText.nTextYPoint;
		st_JsonVideoText["nSpeed"] = pSt_CVProtocol->st_VideoFilter.st_FilterText.nSpeed;
		XCHAR tszFontStr[XPATH_MAX] = {};
		_xstprintf(tszFontStr, _X("./XEngine_Config/Fonts/%s.otf"), pSt_CVProtocol->st_VideoFilter.st_FilterText.tszTextFont);
		st_JsonVideoText["tszFont"] = tszFontStr;
	}
	Json::Value st_JsonVideoDelogo;
	if (pSt_CVProtocol->st_VideoFilter.st_FilterDelogo.bEnable)
	{
		st_JsonVideoDelogo["bEnable"] = pSt_CVProtocol->st_VideoFilter.st_FilterDelogo.bEnable;
		st_JsonVideoDelogo["nDeLogoX"] = pSt_CVProtocol->st_VideoFilter.st_FilterDelogo.nDeLogoX;
		st_JsonVideoDelogo["nDeLogoY"] = pSt_CVProtocol->st_VideoFilter.st_FilterDelogo.nDeLogoY;
		st_JsonVideoDelogo["nDeLogoW"] = pSt_CVProtocol->st_VideoFilter.st_FilterDelogo.nDeLogoW;
		st_JsonVideoDelogo["nDeLogoH"] = pSt_CVProtocol->st_VideoFilter.st_FilterDelogo.nDeLogoH;
	}
	Json::Value st_JsonVideBGImage;
	if (pSt_CVProtocol->st_VideoFilter.st_FilterBGImage.bEnableBGImage)
	{
		st_JsonVideBGImage["bEnable"] = pSt_CVProtocol->st_VideoFilter.st_FilterBGImage.bEnableBGImage;
		st_JsonVideBGImage["tszImageFile"] = pSt_CVProtocol->st_VideoFilter.st_FilterBGImage.tszBGImageFile;
		st_JsonVideBGImage["nHeight"] = pSt_CVProtocol->st_VideoFilter.st_FilterBGImage.nHeight;
		st_JsonVideBGImage["nWidth"] = pSt_CVProtocol->st_VideoFilter.st_FilterBGImage.nWidth;
	}

	st_JsonVideo["WaterMaker"] = st_JsonVideoWaterMaker;
	st_JsonVideo["Text"] = st_JsonVideoText;
	st_JsonVideo["Delogo"] = st_JsonVideoDelogo;
	st_JsonVideo["BGImage"] = st_JsonVideBGImage;
	st_JsonRoot["FilterVideo"] = st_JsonVideo;

	st_JsonWBuilder["emitUTF8"] = true;
	*pInt_MSGLen = (int)Json::writeString(st_JsonWBuilder, st_JsonRoot).length();
	memcpy(ptszMSGBuffer, Json::writeString(st_JsonWBuilder, st_JsonRoot).c_str(), *pInt_MSGLen);

	return true;
}
/********************************************************************
函数名称：APPProtocol_Packet_ToolAi
函数功能：AI配置协议封装
 参数.一：ptszMSGBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出封包数据
 参数.二：pInt_MSGLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出封包大小
 参数.三：pSt_AIProtocol
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入滤镜处理信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CAPPProtocol_Packet::APPProtocol_Packet_ToolAi(XCHAR* ptszMSGBuffer, int* pInt_MSGLen, XENGINE_AICONFIGURE* pSt_AIProtocol)
{
	if ((NULL == ptszMSGBuffer) || (NULL == pInt_MSGLen))
	{
		return false;
	}
	Json::Value st_JsonRoot;
	Json::StreamWriterBuilder st_JsonWBuilder;

	Json::Value st_JsonVideo;
	st_JsonVideo["bEnableTimeLimit"] = pSt_AIProtocol->st_AIVideo.bEnableTimeLimit;
	Json::Value st_JsonAudio;
	st_JsonAudio["bEnableTimeLimit"] = pSt_AIProtocol->st_AIAudio.bEnableTimeLimit;

	Json::Value st_JsonCrypto;
	st_JsonCrypto["nCryptionVideoType"] = pSt_AIProtocol->st_AVCryption.nCryptionVideoType;
	st_JsonCrypto["nCryptionAudioType"] = pSt_AIProtocol->st_AVCryption.nCryptionAudioType;
	st_JsonCrypto["nCryptionLevel"] = pSt_AIProtocol->st_AVCryption.nCryptionLevel;
	st_JsonCrypto["tszCryptionPass"] = pSt_AIProtocol->st_AVCryption.tszCryptionPass;

	st_JsonRoot["bEnableAI"] = pSt_AIProtocol->bEnableAI;
	st_JsonRoot["st_AIVideo"] = st_JsonVideo;
	st_JsonRoot["st_AIAudio"] = st_JsonAudio;
	st_JsonRoot["st_AVCrypto"] = st_JsonCrypto;

	st_JsonWBuilder["emitUTF8"] = true;
	*pInt_MSGLen = (int)Json::writeString(st_JsonWBuilder, st_JsonRoot).length();
	memcpy(ptszMSGBuffer, Json::writeString(st_JsonWBuilder, st_JsonRoot).c_str(), *pInt_MSGLen);

	return true;
}
/********************************************************************
函数名称：APPProtocol_Packet_ToolCloud
函数功能：云转码协议打包函数
 参数.一：ptszMSGBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出打好包的数据信息
 参数.二：pInt_MSGLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出打包大小
 参数.三：lpszFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入文件
 参数.四：pSt_CloudConfig
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要传递的信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CAPPProtocol_Packet::APPProtocol_Packet_ToolCloud(XCHAR* ptszMSGBuffer, int* pInt_MSGLen, LPCXSTR lpszFile, XENGINE_CLOUDCONFIG* pSt_CloudConfig)
{
	if ((NULL == ptszMSGBuffer) || (NULL == pInt_MSGLen))
	{
		return false;
	}
	Json::Value st_JsonRoot;
	Json::StreamWriterBuilder st_JsonWBuilder;

	XCHAR tszUTFFile[XPATH_MAX] = {};
	BaseLib_Charset_AnsiToUTF(lpszFile, tszUTFFile);

	st_JsonRoot["filename"] = tszUTFFile;
	st_JsonRoot["bucketname"] = pSt_CloudConfig->st_BucketInfo.tszBucketName;
	st_JsonRoot["outputname"] = pSt_CloudConfig->st_BucketInfo.tszBucketPath;
	st_JsonRoot["regionname"] = pSt_CloudConfig->st_BucketInfo.tszBucketRegion;
	st_JsonRoot["srclanauage"] = pSt_CloudConfig->st_AIDubbing.tszSrcLanauage;
	st_JsonRoot["dstlanauage"] = pSt_CloudConfig->st_AIDubbing.tszDstLanauage;
	st_JsonRoot["bSubTitles"] = pSt_CloudConfig->st_AIDubbing.bSubTitles;
	st_JsonRoot["bCOSDelete"] = pSt_CloudConfig->st_AIDubbing.bCOSDelete;

	st_JsonWBuilder["emitUTF8"] = true;
	*pInt_MSGLen = (int)Json::writeString(st_JsonWBuilder, st_JsonRoot).length();
	memcpy(ptszMSGBuffer, Json::writeString(st_JsonWBuilder, st_JsonRoot).c_str(), *pInt_MSGLen);

	return true;
}