/*
* Unit testing main Function
* Created by Robel Sharma
*/

#include "CurlCore.h"
#include <sstream>
#include "string.h"
#include <iostream>

#include <stdio.h>
#include <stdlib.h>

#define CEASY_CURL "eAskGitHub v1.0"

CurlCore *m_pCore;

string sWelCome = "\nWelcome to github metadata fetcher "+ (string)CEASY_CURL+" !!\nIt's a very simple command line app who will try to\nfill your all want for github metadata(THE API).\n\n";

int main(void)
{

  m_pCore = new CurlCore();
  string sAuthUri = "https://api.github.com/repos";
  string sUserName="";
  string sRepo ;
  string sTTL = "";
  string sAgain="";
  while(1)
   {
		cout<<sWelCome<<endl;
		cout <<"Please enter github username: ";
		cin>>sUserName;

		cout <<"Please enter your one repository name: ";
		cin>>sRepo;

		m_pCore->VerifyUser(sAuthUri, sUserName, sRepo, sTTL, "");

		cout<<"*****************************************************************"<<endl;
		cout<<endl;

		cout<<"Want to continue ?(y/n):";
		cin>>sAgain;
		if(sAgain == "n")
		 exit(0);

	}
  return 0;
}
