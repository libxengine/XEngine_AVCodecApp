#pragma once

class CAPPProtocol_Packet
{
public:
	CAPPProtocol_Packet();
	~CAPPProtocol_Packet();
public:
	bool APPProtocol_Packet_ToolCreate(XCHAR* ptszMSGBuffer, int* pInt_MSGLen, LPCXSTR lpszDestFile, LPCXSTR lpszDestType, int nHLSTime = 0, int nTotalRate = 0);
	bool APPProtocol_Packet_ToolCodec(XCHAR* ptszMSGBuffer, int* pInt_MSGLen, XENGINE_AVCONFIGINFO* pSt_AVProtocol);
	bool APPProtocol_Packet_ToolPlayer(XCHAR* ptszMSGBuffer, int* pInt_MSGLen, LPCXSTR lpszSourceFile, LPCXSTR lpszPlayerTime = _X("1"));
	bool APPProtocol_Packet_ToolFilter(XCHAR* ptszMSGBuffer, int* pInt_MSGLen, XENGINE_CVCONFIGURE* pSt_CVProtocol);
	bool APPProtocol_Packet_ToolAi(XCHAR* ptszMSGBuffer, int* pInt_MSGLen, XENGINE_AICONFIGURE* pSt_AIProtocol);
	bool APPProtocol_Packet_ToolCloud(XCHAR* ptszMSGBuffer, int* pInt_MSGLen, LPCXSTR lpszFile, XENGINE_CLOUDCONFIG* pSt_CloudConfig);
private:
};