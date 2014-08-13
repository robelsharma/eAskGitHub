#include "CurlCore.h"
#include <sstream>
#include "string.h"
#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ENABLE_HTTPS

static std::string readBuffer;



static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{ 
    size_t realsize = size * nmemb;
    readBuffer.append((const char*)contents, realsize);
    return realsize;
}


CurlCore::CurlCore()
{
	Init();
}

CurlCore::~CurlCore()
{
	curl_easy_cleanup(m_pCurl);
}


void CurlCore::Init()
{
	m_pCurl = curl_easy_init();
}

bool CurlCore::VerifyUser(const string& sAuthUri, const string &sUserName, const string &sUserRepo, string &sTTL, string sCertificatePath)
{
	CURLcode res;
	string sUri = sAuthUri + "/" + sUserName;

	if(sUserRepo != "")
		sUri += "/"+sUserRepo+"/releases";

	//printf("Req URI: "<<sUri<<endl;
	if(m_pCurl)
	{
		curl_easy_setopt(m_pCurl, CURLOPT_URL, sUri.c_str());
		/* example.com is redirected, so we tell libcurl to follow redirection */ 
		curl_easy_setopt(m_pCurl, CURLOPT_FOLLOWLOCATION, 1L);

		// User-agent header 
		string sUserAgent = "CeasyCurl (sharma) v1.0";
		curl_easy_setopt(m_pCurl, CURLOPT_USERAGENT, sUserAgent.c_str());

		if(sCertificatePath == "")
		{
#ifdef ENABLE_HTTPS
			curl_easy_setopt(m_pCurl, CURLOPT_SSL_VERIFYPEER, 0L);
			curl_easy_setopt(m_pCurl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif
		}
		else
		{
			curl_easy_setopt(m_pCurl, CURLOPT_SSL_VERIFYPEER, 1);
			curl_easy_setopt(m_pCurl, CURLOPT_SSL_VERIFYHOST, 2);
			curl_easy_setopt(m_pCurl, CURLOPT_CAINFO, sCertificatePath.c_str());
		}		
	 	curl_easy_setopt(m_pCurl, CURLOPT_WRITEFUNCTION, WriteCallback);
		

		/* Perform the request, res will get the return code */ 
		res = curl_easy_perform(m_pCurl);
		//printf("Curl req performed"<<endl;
		char * url;
		long respcode=0;
		curl_easy_getinfo(m_pCurl, CURLINFO_RESPONSE_CODE, &respcode);
		
		/* Check for errors */ 
		if(res != CURLE_OK)
		  fprintf(stderr, "curl_easy_perform() failed: %s\n",
		          curl_easy_strerror(res));

		switch(respcode)
		{
			case 200:
			{
				// Parse the static string buffer readBuffer for username
				vector<string> sValues;
				printf("Your querry Succeeded :)\n");
				ParseJsonData(readBuffer, sValues);

				//for(int i=0;i<sValues.size();i++)
				{
					//printf("Response Values = %s\n", sValues[i].c_str());
				}
				readBuffer.clear();
				return true;
				break;	
			}
			case 401:
				printf("Un-Authorize\n");
				break;
			case 504:
				printf("Server Time-out\n");
				break;
			case 400:
				printf("Page not found\n");
				break;
			default:
			break;
		}
		readBuffer.clear();
 	}
	return false;
}

void CurlCore::ParseJsonData(string &sMsg, vector<string>& sParsedvalue)
{
	sParsedvalue.clear();

	int iCount = 0;
	for(char *p = strtok((char *)sMsg.c_str(), ","); p; p = strtok(NULL, ",")){
			
			
			string sTemp(p);
			
			
			int sPos = sTemp.find(":");
			int lPos = sTemp.size();
			string sAttr = sTemp.substr(0, sPos);

			if(sTemp[sPos + 1] == '"')
			{
				sPos += 1;
				lPos -= 1;
			}
			sTemp = sTemp.substr(sPos+1, lPos - sPos - 1);
		

			ShowInfo(sAttr, sTemp, iCount);
			
			sParsedvalue.push_back(sTemp);
		}
		iCount = 0;
}

void CurlCore::ShowInfo(string sAttr, string sData, int &iCount)
{
	

	if(sAttr == "\"name\"" && iCount == 0)
	{
		++iCount;
		printf("Project Title:=> ");
		printf(" %s\n", sData.c_str());
	}
	else if(sAttr == "\"name\"" && iCount == 1)
	{
		++iCount;
		printf("Project Binary:=> ");
		printf(" %s\n", sData.c_str());
	}
	else if(sAttr == "\"author\"")
	{
		printf("Creators' Login Name:=> ");

		int sPos = sData.find(":");
		int lPos = sData.size();
		string sAttr1 = sData.substr(0, sPos);

		if(sData[sPos + 1] == '"')
		{
			sPos += 1;
			lPos -= 1;
		}
		sData = sData.substr(sPos+1, lPos - sPos - 1);
		printf(" %s\n", sData.c_str());
	}
	else if(sAttr == "\"created_at\"")
	{
		printf("Create Date:=> ");
		printf(" %s\n", sData.c_str());
	}
	else if(sAttr == "\"published_at\"")
	{
		printf("Publish Date:=> ");
		printf(" %s\n", sData.c_str());
	}
	else if(sAttr == "\"uploader\"")
	{
		printf("Uploader Login Name:=> ");

		int sPos = sData.find(":");
		int lPos = sData.size();
		string sAttr1 = sData.substr(0, sPos);

		if(sData[sPos + 1] == '"')
		{
			sPos += 1;
			lPos -= 1;
		}
		sData = sData.substr(sPos+1, lPos - sPos - 1);
		printf(" %s\n", sData.c_str());
	}
	else if(sAttr == "\"type\"")
	{
		printf("User Privilege:=> ");
		printf(" %s\n", sData.c_str());
	}
	else if(sAttr == "\"site_admin\"")
	{
		printf("Are you an Admin for this site?:=> ");
		if(sData == "false}")
			printf("No\n");
		else 
			printf("No\n");
	}
	else if(sAttr == "\"content_type\"")
	{
		printf("Binary Package Type:=> ");
		printf(" %s\n", sData.c_str());
	}
	else if(sAttr == "\"download_count\"")
	{
		string sTotal = "|Downloaded: "+ sData + " times|";

		for(int i=0;i<sTotal.size();i++)
		printf("-");
		printf("\n");
		printf("%s\n", sTotal.c_str());

		for(int i=0;i<sTotal.size();i++)
		printf("-");
		printf("\n");
	}
	else if(sAttr == "\"updated_at\"")
	{
		printf("Binary Package updated at:=> ");
		printf(" %s\n", sData.c_str());
	}
	else if(sAttr == "\"browser_download_url\"")
	{
		printf("Download Link:=> ");
		sData = sData.substr(0, sData.size() - 2);
		printf(" %s\n", sData.c_str());
	}
}


