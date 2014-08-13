#ifndef _CURL_CORE_H_
#define _CURL_CORE_H_

#include <stdio.h>
#include <curl/curl.h>
#include <string>
#include <vector>


using namespace std;

class CurlCore{

	public: 
		CurlCore();
		~CurlCore();

	public:
		void Init();
		bool VerifyUser(const string& sAuthUri, const string &sUserName, const string &sUserRepo, string &sTTL, string sCertificatePath = "");
	private:
		void ParseJsonData(string &sMsg, vector<string>& sParsedvalue);
		void ShowInfo(string sAttr, string sData, int &iCount);
	public:
		CURL *m_pCurl;	

};

#endif


