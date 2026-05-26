#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <json/json.h>
#include <thread>
#include <XEngine_Include/XEngine_CommHdr.h>
#include <XEngine_Include/XEngine_Types.h>
#include <XEngine_Include/XEngine_ProtocolHdr.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Define.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Error.h>
#include <XEngine_Include/XEngine_Client/APIClient_Define.h>
#include <XEngine_Include/XEngine_Client/APIClient_Error.h>
#include <XEngine_Include/XEngine_SystemSdk/SystemApi_Define.h>
#include <XEngine_Include/XEngine_SystemSdk/SystemApi_Error.h>

#ifdef _DEBUG
#ifdef _WIN64
#pragma comment(lib,"../x64/Debug/jsoncpp")
#else
#pragma comment(lib,"../Debug/jsoncpp")
#endif
#else
#ifdef _WIN64
#pragma comment(lib,"../x64/Release/jsoncpp")
#else
#pragma comment(lib,"../Release/jsoncpp")
#endif
#endif
#pragma comment(lib,"XEngine_BaseLib/XEngine_BaseLib.lib")
#pragma comment(lib,"XEngine_Client/XClient_APIHelp.lib")
#pragma comment(lib,"XEngine_SystemSdk/XEngine_SystemApi.lib")
///////////////////////////////////////////////////////////////////////////
//                          导出的数据结构
///////////////////////////////////////////////////////////////////////////
typedef struct
{
	bool bEnable;
	XCHAR tszNameStr[XPATH_MIN];
	XCHAR tszMPSUrl[XPATH_MID];
	XCHAR tszCOSUrl[XPATH_MID];

	XCHAR tszSecretID[XPATH_MIN];
	XCHAR tszSecretKey[XPATH_MIN];

	struct
	{
		XCHAR tszRemoteUrl[XPATH_MID];
		XCHAR tszLocalUrl[XPATH_MID];
		XCHAR tszLocalDisk[XPATH_MID];
	}st_MapAddr;
	struct
	{
		XCHAR tszBucketName[64];
		XCHAR tszBucketPath[64];
		XCHAR tszBucketRegion[64];
	}st_BucketInfo;
	struct
	{
		XCHAR tszActionStr[XPATH_MIN];
		XCHAR tszVersionStr[XPATH_MIN];
		XCHAR tszRegion[XPATH_MIN];
	}st_UPFile;
	struct
	{
		XCHAR tszActionStr[XPATH_MIN];
		XCHAR tszVersionStr[XPATH_MIN];
		XCHAR tszRegion[XPATH_MIN];
	}st_QueryTask;
	struct
	{
		XCHAR tszSrcLanauage[8];
		XCHAR tszDstLanauage[8];
		bool bSubTitles;
		bool bCOSDelete;
	}st_AIDubbing;
}XENGINE_CLOUDCONFIG;
//基本配置
typedef struct
{
	XCHAR tszTemplateName[64];
	XCHAR tszTemplateFmt[16];
	int nTotalRate;
	int nHLSTime;
	int nThreads;
	bool bInit;
	bool bMutilHLS;
	bool bM3u8SameDir;
}XENGINE_AVCONFIGBASE;
//扩展配置
typedef struct
{
	AVCODEC_VIDEO_INFO st_AVVideo;
	AVCODEC_AUDIO_INFO st_AVAudio;
	//视频编解码器扩展参数
	struct
	{
		XCHAR tszENCodecGPU[64];
		XCHAR tszDECodecGPU[64];
		XCHAR tszRateControl[64];
		XCHAR tszProfileID[64];
		XCHAR tszCodecLevel[64];
		XCHAR tszCodecPreset[64];
		XCHAR tszCodecTune[64];
		int64_t nBitRateMin;                                          //最小码率
		int64_t nBitRateMax;                                          //最大码率
		int nBitRateSize;                                             //码率大小
		int nColor;                                                   //色域
		int nFrameRef;                                                //参考帧个数
		bool bGOPForce;                                               //强制GOP
		bool bGPUUsed;
	}st_VideoCodec;
	struct
	{
		struct
		{
			bool bEnableSubtitle;
			XCHAR tszSTTextColor[64];
			XCHAR tszSTTextFont[64];
			int nSTTextOutline;
			int nSTTextAlpha;
			int nSTTextPos;
			int nSTTextXPos;
			int nSTTextYPos;
			int nSTTextSize;
		}st_FilterSubtitle;
	}st_VideoFilter;
	//音频扩展编码参数
	struct
	{
		XCHAR tszRateControl[64];
		int64_t nBitRateMin;                                          //最小码率
		int64_t nBitRateMax;                                          //最大码率
	}st_AudioCodec;
	//音频滤镜参数
	struct
	{
		bool bResampleChannel;
		bool bEBUR128;
	}st_AudioFilter;
}XENGINE_AVCONFIGINFO;
typedef struct
{
	//视频滤镜参数
	struct
	{
		struct
		{
			bool bEnableText;
			int nSpeed;
			int nBorder;
			int nTextTime;
			int nTextSize;
			int nTextXPoint;
			int nTextYPoint;
			int nTextAlpha;
			XCHAR tszTextFont[XPATH_MID];
			XCHAR tszTextColor[64];
			XCHAR tszTextStr[64];
		}st_FilterText;
		struct
		{
			bool bEnableWaterMaker;
			double dlWMSize;
			int nWMXPoint;
			int nWMYPoint;
			int nWMTime;
			XCHAR tszWMImage[XPATH_MID];
		}st_FilterWaterMaker;
		struct
		{
			bool bEnableBGImage;
			int nWidth;
			int nHeight;
			XCHAR tszBGImageFile[XPATH_MID];
		}st_FilterBGImage;
		struct
		{
			bool bEnable;
			int nDeLogoX;
			int nDeLogoY;
			int nDeLogoW;
			int nDeLogoH;
		}st_FilterDelogo;
	}st_VideoFilter;
}XENGINE_CVCONFIGURE;
typedef struct
{
	bool bEnableAI;
	struct
	{
		bool bEnableTimeLimit;

		struct
		{
			bool bCheckFrame;
			double dlThreshold;
			int nCheckTime;
			int nCheckFrame;
		}st_CheckFrame;
		struct
		{
			bool bCheckBlack;
			double dlThreshold;
			int nCheckTime;
			int nCheckFrame;
		}st_CheckBlack;
	}st_AIVideo;
	struct
	{
		bool bEnableTimeLimit;

		struct
		{
			bool bCheckSilence;
			int nCheckTime;
		}st_CheckSilence;
	}st_AIAudio;

	struct
	{
		XCHAR tszCryptionPass[64];
		int nCryptionVideoType;
		int nCryptionAudioType;
		int nCryptionLevel;
	}st_AVCryption;
}XENGINE_AICONFIGURE;
#pragma pack(push)
#pragma pack(1)
typedef struct
{
	struct
	{
		bool bEnable;
	}st_Local;
	struct
	{
		bool bEnable;
		int nProgress;
	}st_Cloud;
	XNETHANDLE xhToken;
	double dlFileTime;
	double dlNowTime;
	double dlAvgTime;
	int nIndex;
	int nPort;
	int nStatus;
}AVPROTOCOL_PROCESS;
#pragma pack(pop)