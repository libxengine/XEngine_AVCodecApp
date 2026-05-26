#pragma once

class CAPPProtocol_Parse
{
public:
	CAPPProtocol_Parse();
	~CAPPProtocol_Parse();
public:
	bool APPProtocol_Parse_ToolReply(LPCXSTR lpszMSGBuffer, int nMSGLen, int* pInt_Code = NULL, XCHAR* ptszMSGBuffer = NULL);
	bool APPProtocol_Parse_ToolCreate(LPCXSTR lpszMSGBuffer, int nMSGLen, XNETHANDLE* pxhToken);
	bool APPProtocol_Parse_ToolAi(LPCXSTR lpszMSGBuffer, int nMSGLen, XENGINE_AICONFIGURE* pSt_AIConfigure);
	bool APPProtocol_Parse_ToolHeart(LPCXSTR lpszMSGBuffer, int nMSGLen, int* pInt_Status, XNETHANDLE* pInt_Token);
private:
};