#include "APPCommHdr.h"
#include "APPProtocol_Packet.h"
#include "APPProtocol_Parse.h"

void AVConfig_Packet(XENGINE_AVCONFIGINFO *pSt_AVProtocol)
{
	//视频参数
	pSt_AVProtocol->st_AVVideo.bEnable = true;
	pSt_AVProtocol->st_AVVideo.nBitRate = 4000;
	pSt_AVProtocol->st_AVVideo.enAVCodec = 27;  //H264
	pSt_AVProtocol->st_AVVideo.nBFrame = 0;
	pSt_AVProtocol->st_AVVideo.nGOPSize = 60;
	pSt_AVProtocol->st_AVVideo.nWidth = 1280;
	pSt_AVProtocol->st_AVVideo.nHeight = 720;
	pSt_AVProtocol->st_AVVideo.nFormat = 0;
	pSt_AVProtocol->st_AVVideo.nFrameBase = 1;
	pSt_AVProtocol->st_AVVideo.nFrameRate = 30;

	pSt_AVProtocol->st_VideoCodec.bGOPForce = true;
	pSt_AVProtocol->st_VideoCodec.nBitRateMax = 4000;
	pSt_AVProtocol->st_VideoCodec.nBitRateMin = 4000;
	pSt_AVProtocol->st_VideoCodec.nBitRateSize = 2000;
	_xstprintf(pSt_AVProtocol->st_VideoCodec.tszRateControl, _X("CBR"));

	_xstprintf(pSt_AVProtocol->st_VideoCodec.tszENCodecGPU, _X("NVIDIA"));
	_xstprintf(pSt_AVProtocol->st_VideoCodec.tszDECodecGPU, _X("NVIDIA"));
	_xstprintf(pSt_AVProtocol->st_VideoCodec.tszCodecLevel, _X("4.1"));
	_xstprintf(pSt_AVProtocol->st_VideoCodec.tszProfileID, _X("high"));
	_xstprintf(pSt_AVProtocol->st_VideoCodec.tszCodecPreset, _X("UNSPECIFIED"));
	_xstprintf(pSt_AVProtocol->st_VideoCodec.tszCodecTune, _X("UNSPECIFIED"));
	//音频参数
	pSt_AVProtocol->st_AVAudio.bEnable = true;
	pSt_AVProtocol->st_AVAudio.nBitRate = 128;
	pSt_AVProtocol->st_AVAudio.enAVCodec = 86018;  //AAC
	pSt_AVProtocol->st_AVAudio.nChannel = 2;
	pSt_AVProtocol->st_AVAudio.nSampleFmt = 1;
	pSt_AVProtocol->st_AVAudio.nSampleRate = 44100;
	pSt_AVProtocol->st_AudioCodec.nBitRateMax = 128;
	pSt_AVProtocol->st_AudioCodec.nBitRateMin = 128;
	_xstprintf(pSt_AVProtocol->st_AudioCodec.tszRateControl, _X("CBR"));

	pSt_AVProtocol->st_AudioFilter.bEBUR128 = false;
	pSt_AVProtocol->st_AudioFilter.bResampleChannel = false;
}
void CVConfig_Packet(XENGINE_CVCONFIGURE* pSt_CVProtocol)
{
	//竖转横支持
	pSt_CVProtocol->st_VideoFilter.st_FilterBGImage.bEnableBGImage = false;
	pSt_CVProtocol->st_VideoFilter.st_FilterBGImage.nHeight = 720;
	pSt_CVProtocol->st_VideoFilter.st_FilterBGImage.nWidth = 1280;
	_xstprintf(pSt_CVProtocol->st_VideoFilter.st_FilterBGImage.tszBGImageFile, _X("D:\\bgimage.png"));
	//文本支持
	pSt_CVProtocol->st_VideoFilter.st_FilterText.bEnableText = false;
	pSt_CVProtocol->st_VideoFilter.st_FilterText.nBorder = 0;
	pSt_CVProtocol->st_VideoFilter.st_FilterText.nSpeed = 0;
	pSt_CVProtocol->st_VideoFilter.st_FilterText.nTextAlpha = 100;
	pSt_CVProtocol->st_VideoFilter.st_FilterText.nTextSize = 40;
	pSt_CVProtocol->st_VideoFilter.st_FilterText.nTextXPoint = 100;
	pSt_CVProtocol->st_VideoFilter.st_FilterText.nTextYPoint = 100;
	pSt_CVProtocol->st_VideoFilter.st_FilterText.nTextTime = 0;
	_xstprintf(pSt_CVProtocol->st_VideoFilter.st_FilterText.tszTextColor, _X("0-0-255"));
	_xstprintf(pSt_CVProtocol->st_VideoFilter.st_FilterText.tszTextFont, _X("D:\\Fonts\\SourceHanSansCN.otf"));
	_xstprintf(pSt_CVProtocol->st_VideoFilter.st_FilterText.tszTextStr, _X("测试文本"));
	//水印图片叠加
	pSt_CVProtocol->st_VideoFilter.st_FilterWaterMaker.bEnableWaterMaker = false;
	pSt_CVProtocol->st_VideoFilter.st_FilterWaterMaker.dlWMSize = 1;
	pSt_CVProtocol->st_VideoFilter.st_FilterWaterMaker.nWMTime = 0;
	pSt_CVProtocol->st_VideoFilter.st_FilterWaterMaker.nWMXPoint = 100;
	pSt_CVProtocol->st_VideoFilter.st_FilterWaterMaker.nWMYPoint = 100;
	_xstprintf(pSt_CVProtocol->st_VideoFilter.st_FilterWaterMaker.tszWMImage, _X("D:\\wm.png"));
	//水印图片消除
	pSt_CVProtocol->st_VideoFilter.st_FilterDelogo.bEnable = false;
	pSt_CVProtocol->st_VideoFilter.st_FilterDelogo.nDeLogoH = 100;
	pSt_CVProtocol->st_VideoFilter.st_FilterDelogo.nDeLogoW = 100;
	pSt_CVProtocol->st_VideoFilter.st_FilterDelogo.nDeLogoX = 100;
	pSt_CVProtocol->st_VideoFilter.st_FilterDelogo.nDeLogoY = 100;
}

//project must be x64 application debug or release version, because the avcodec module is compiled in x64 architecture
int main()
{
	bool bIsMerge = false;         //是不是合并
	XNETHANDLE xhToken = 0;              //转码TOKEN
	LPCXSTR lpszCreateName = _X("G:\\output.mp4");     //创建转码的目标地址
	LPCXSTR lpszCreateFmt = _X("mp4");     //创建转码的媒体格式
	LPCXSTR lpszSourceFile = _X("G:\\1.mp4");     //转码的源文件地址

	XENGINE_AVCONFIGINFO st_AVProtocol = {};
	XENGINE_CVCONFIGURE st_CVProtocol = {};
	XENGINE_AICONFIGURE st_AIProtocol = {};
	int nMSGLen = 0;
	XCHAR* ptszMSGBuffer = NULL;
	XCHAR tszRequestStr[XPATH_2MAX] = {};
	XCHAR tszMSGBuffer[XPATH_2MAX] = {};
	CAPPProtocol_Packet m_ProtocolPacket;
	CAPPProtocol_Parse m_ProtocolParse;

	AVConfig_Packet(&st_AVProtocol);
	CVConfig_Packet(&st_CVProtocol);
	{
		m_ProtocolPacket.APPProtocol_Packet_ToolCreate(tszMSGBuffer, &nMSGLen, lpszCreateName, lpszCreateFmt, 0, 0);
		_xstprintf(tszRequestStr, _X("http://127.0.0.1:5000/api?function=create"));
		if (!APIClient_Http_Request(_X("POST"), tszRequestStr, tszMSGBuffer, NULL, &ptszMSGBuffer, &nMSGLen))
		{
			_xtprintf(_X("创建token失败,无法继续.网络错误,错误码:%lX\n"), APIClient_GetLastError());
			return false;
		}
		if (!m_ProtocolParse.APPProtocol_Parse_ToolCreate(ptszMSGBuffer, nMSGLen, &xhToken))
		{
			_xtprintf(_X("创建token失败,协议数据错误,内容:%s\n"), ptszMSGBuffer);
			return false;
		}
		BaseLib_Memory_FreeCStyle((XPPMEM)&ptszMSGBuffer);
		_xtprintf(_X("创建token成功,本地转码TOKEN:%lld\n"), xhToken);
	}

	{
		nMSGLen = 0;
		memset(tszMSGBuffer, 0, XPATH_2MAX);
		memset(tszRequestStr, 0, XPATH_2MAX);

		m_ProtocolPacket.APPProtocol_Packet_ToolCodec(tszMSGBuffer, &nMSGLen, &st_AVProtocol);
		_xstprintf(tszRequestStr, _X("http://127.0.0.1:5000/api?function=codec&token=%lld"), xhToken);
		if (!APIClient_Http_Request(_X("POST"), tszRequestStr, tszMSGBuffer, NULL, &ptszMSGBuffer, &nMSGLen))
		{
			_xtprintf(_X("设置编解码失败,无法继续.网络错误,错误码:%lX\n"), APIClient_GetLastError());
			return false;
		}
		if (!m_ProtocolParse.APPProtocol_Parse_ToolReply(ptszMSGBuffer, nMSGLen))
		{
			_xtprintf(_X("解析编解码错误,协议数据错误,内容:%s\n"), ptszMSGBuffer);
			return false;
		}
		BaseLib_Memory_FreeCStyle((XPPMEM)&ptszMSGBuffer);
		_xtprintf(_X("token:%lld:配置编码器成功\n"), xhToken);
	}
	if (st_CVProtocol.st_VideoFilter.st_FilterBGImage.bEnableBGImage || st_CVProtocol.st_VideoFilter.st_FilterDelogo.bEnable || st_CVProtocol.st_VideoFilter.st_FilterText.bEnableText || st_CVProtocol.st_VideoFilter.st_FilterWaterMaker.bEnableWaterMaker || st_AIProtocol.bEnableAI)
	{
		nMSGLen = 0;
		memset(tszMSGBuffer, 0, XPATH_2MAX);
		memset(tszRequestStr, 0, XPATH_2MAX);
		_xstprintf(tszRequestStr, _X("http://127.0.0.1:5000/api?function=filter&value=%lld&action=create"), xhToken);
		if (!APIClient_Http_Request(_X("GET"), tszRequestStr, NULL, NULL, &ptszMSGBuffer, &nMSGLen))
		{
			_xtprintf(_X("创建滤镜失败,无法继续.网络错误,错误码:%lX\n"), APIClient_GetLastError());
			return false;
		}
		if (!m_ProtocolParse.APPProtocol_Parse_ToolReply(ptszMSGBuffer, nMSGLen))
		{
			_xtprintf(_X("创建滤镜失败,协议数据错误,内容:%s\n"), ptszMSGBuffer);
			return false;
		}
		BaseLib_Memory_FreeCStyle((XPPMEM)&ptszMSGBuffer);
		_xtprintf(_X("token:%lld:启用滤镜处理功能成功\n"), xhToken);
		//滤镜
		if (st_CVProtocol.st_VideoFilter.st_FilterDelogo.bEnable || st_CVProtocol.st_VideoFilter.st_FilterText.bEnableText || st_CVProtocol.st_VideoFilter.st_FilterWaterMaker.bEnableWaterMaker || st_AIProtocol.bEnableAI)
		{
			nMSGLen = 0;
			memset(tszMSGBuffer, 0, XPATH_2MAX);
			memset(tszRequestStr, 0, XPATH_2MAX);
			m_ProtocolPacket.APPProtocol_Packet_ToolFilter(tszMSGBuffer, &nMSGLen, &st_CVProtocol);
			_xstprintf(tszRequestStr, _X("http://127.0.0.1:5000/api?function=filter&value=%lld&action=insert"), xhToken);
			if (!APIClient_Http_Request(_X("POST"), tszRequestStr, tszMSGBuffer, NULL, &ptszMSGBuffer, &nMSGLen))
			{
				_xtprintf(_X("设置图像处理滤镜失败,无法继续.网络错误,错误码:%lX\n"), APIClient_GetLastError());
				return false;
			}
			if (!m_ProtocolParse.APPProtocol_Parse_ToolReply(ptszMSGBuffer, nMSGLen))
			{
				_xtprintf(_X("置图像处理滤镜失败,协议数据错误,内容:%s\n"), ptszMSGBuffer);
				return false;
			}
			BaseLib_Memory_FreeCStyle((XPPMEM)&ptszMSGBuffer);
			_xtprintf(_X("token:%lld:启用滤镜配置成功\n"), xhToken);
		}
		//竖转横
		if (st_CVProtocol.st_VideoFilter.st_FilterBGImage.bEnableBGImage)
		{
			nMSGLen = 0;
			memset(tszMSGBuffer, 0, XPATH_2MAX);
			memset(tszRequestStr, 0, XPATH_2MAX);
			m_ProtocolPacket.APPProtocol_Packet_ToolFilter(tszMSGBuffer, &nMSGLen, &st_CVProtocol);
			_xstprintf(tszRequestStr, _X("http://127.0.0.1:5000/api?function=filter&value=%lld&action=bgset"), xhToken);
			if (!APIClient_Http_Request(_X("POST"), tszRequestStr, tszMSGBuffer, NULL, &ptszMSGBuffer, &nMSGLen))
			{
				_xtprintf(_X("设置视频竖转横处理失败,无法继续.网络错误,错误码:%lX\n"), APIClient_GetLastError());
				return false;
			}
			if (!m_ProtocolParse.APPProtocol_Parse_ToolReply(ptszMSGBuffer, nMSGLen))
			{
				_xtprintf(_X("设置视频竖转横处理失败,协议数据错误,内容:%s\n"), ptszMSGBuffer);
				return false;
			}
			BaseLib_Memory_FreeCStyle((XPPMEM)&ptszMSGBuffer);
			_xtprintf(_X("token:%lld:启用滤镜竖转横成功\n"), xhToken);
		}
		//AI
		if (st_AIProtocol.bEnableAI)
		{
			nMSGLen = 0;
			memset(tszMSGBuffer, 0, XPATH_2MAX);
			memset(tszRequestStr, 0, XPATH_2MAX);
			m_ProtocolPacket.APPProtocol_Packet_ToolAi(tszMSGBuffer, &nMSGLen, &st_AIProtocol);
			_xstprintf(tszRequestStr, _X("http://127.0.0.1:5000/api?function=ai&token=%lld"), xhToken);
			if (!APIClient_Http_Request(_X("POST"), tszRequestStr, tszMSGBuffer, NULL, &ptszMSGBuffer, &nMSGLen))
			{
				_xtprintf(_X("设置视频AI处理失败,无法继续.网络错误,错误码:%lX\n"), APIClient_GetLastError());
				return false;
			}
			if (!m_ProtocolParse.APPProtocol_Parse_ToolReply(ptszMSGBuffer, nMSGLen))
			{
				_xtprintf(_X("设置视频AI处理失败,协议数据错误,内容:%s\n"), ptszMSGBuffer);
				return false;
			}
			BaseLib_Memory_FreeCStyle((XPPMEM)&ptszMSGBuffer);
			_xtprintf(_X("token:%lld:启用AI功能成功\n"), xhToken);
		}
	}
	//是不是合并
	if (bIsMerge)
	{
		int nListCount = 0;
		XCHAR** pptszListFile;

		SystemApi_File_EnumFileA(lpszSourceFile, &pptszListFile, &nListCount, false, 1, true);
		for (int i = 0; i < nListCount; i++)
		{
			nMSGLen = 0;
			memset(tszMSGBuffer, 0, XPATH_2MAX);
			memset(tszRequestStr, 0, XPATH_2MAX);
			_xstprintf(tszRequestStr, _X("http://127.0.0.1:5000/api?function=play&token=%lld"), xhToken);
			m_ProtocolPacket.APPProtocol_Packet_ToolPlayer(tszMSGBuffer, &nMSGLen, pptszListFile[i]);
			if (!APIClient_Http_Request(_X("POST"), tszRequestStr, tszMSGBuffer, NULL, &ptszMSGBuffer, &nMSGLen))
			{
				_xtprintf(_X("请求开始转码失败,无法继续.网络错误,错误码:%lX\n"), APIClient_GetLastError());
				return false;
			}
			if (!m_ProtocolParse.APPProtocol_Parse_ToolReply(ptszMSGBuffer, nMSGLen))
			{
				_xtprintf(_X("解析转码操作失败,无法继续.协议错误,内容:%s\n"), ptszMSGBuffer);
				return false;
			}
			_xtprintf(_X("请求开始合并转码,总文件:%d,插入文件:%s\n"), nListCount, pptszListFile[i]);
			BaseLib_Memory_FreeCStyle((XPPMEM)&ptszMSGBuffer);
		}
	}
	else
	{
		nMSGLen = 0;
		memset(tszMSGBuffer, 0, XPATH_MAX);
		memset(tszRequestStr, 0, XPATH_MAX);
		_xstprintf(tszRequestStr, _X("http://127.0.0.1:5000/api?function=play&token=%lld"), xhToken);
		m_ProtocolPacket.APPProtocol_Packet_ToolPlayer(tszMSGBuffer, &nMSGLen, lpszSourceFile);
		if (!APIClient_Http_Request(_X("POST"), tszRequestStr, tszMSGBuffer, NULL, &ptszMSGBuffer, &nMSGLen))
		{
			_xtprintf(_X("请求开始转码失败,无法继续.网络错误,错误码:%lX\n"), APIClient_GetLastError());
			return false;
		}
		if (!m_ProtocolParse.APPProtocol_Parse_ToolReply(ptszMSGBuffer, nMSGLen))
		{
			_xtprintf(_X("解析转码操作失败,无法继续.协议错误,内容:%s\n"), ptszMSGBuffer);
			return false;
		}
		BaseLib_Memory_FreeCStyle((XPPMEM)&ptszMSGBuffer);
		_xtprintf(_X("token:%lld:开始处理转码文件成功\n"), xhToken);
	}
	std::this_thread::sleep_for(std::chrono::seconds(3));
	while (true)
	{
		XCHAR tszAPIAddr[XPATH_MAX] = { };
		_xstprintf(tszAPIAddr, _X("http://127.0.0.1:5000/api?function=token&value=%lld"), xhToken);

		if (!APIClient_Http_Request(_X("GET"), tszAPIAddr, NULL, NULL, &ptszMSGBuffer, &nMSGLen))
		{
			_xtprintf(_X("请求心跳信息失败,无法继续.网络错误,错误码:%lX\n"), APIClient_GetLastError());
			return false;
		}
		Json::Value st_JsonRoot;
		JSONCPP_STRING st_JsonError;
		Json::CharReaderBuilder st_JsonRBuilder;

		std::unique_ptr<Json::CharReader> const pSt_JsonReader(st_JsonRBuilder.newCharReader());
		if (!pSt_JsonReader->parse(ptszMSGBuffer, ptszMSGBuffer + nMSGLen, &st_JsonRoot, &st_JsonError))
		{
			_xtprintf(_X("token:%lld:转码失败\n"), xhToken);
			return false;
		}
		printf("%s\n", ptszMSGBuffer);

		Json::Value st_JsonData = st_JsonRoot["data"];
		if (0 == st_JsonData["nStatus"].asInt())
		{
			_xtprintf(_X("token:%lld:转码完成\n"), xhToken);

			memset(tszAPIAddr, 0, XPATH_MAX);
			_xstprintf(tszAPIAddr, _X("http://127.0.0.1:5000/api?function=stop&token=%lld"), xhToken);
			APIClient_Http_Request(_X("GET"), tszAPIAddr, NULL, NULL, &ptszMSGBuffer, &nMSGLen);
			break;
		}
		
		BaseLib_Memory_FreeCStyle((XPPMEM)&ptszMSGBuffer);
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}
	return 0;
}