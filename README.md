eAskGitHub
==========

Simple console for all github repo release API.


What?
-----
It is a c++ application with a binary. It is created to make the life simple for github repository API user. It uses curl.

Feature:
--------

1. It can receive any lenght of response from github.
2. It has it's own simple JSON parser method. 
3. It is powerfull tool to know your github release download count.
4. Makefile application.

Prerequisite:
-------------

1. Need libcurl.
2. Need Centos/Linux.
3. Not tested with windows(Hopefully it will work after windows curl library installation).

Roadmap:
--------
1. Implement every API of [GitHub API](https://developer.github.com/v3/repos/releases/).

Use:
----

In console just give command -

```
./eAskGit
```
Then just follow the hints available on console or answer the querry.

Test Result:
------------
```
./eAskGit

Welcome to github metadata fetcher eAskGitHub v1.0 !!
It's a very simple command line app who will try to
fill your all want for github metadata(THE API).


Please enter github username: robelsharma
Please enter your one repository name: videoconference
Your querry Succeeded :)
Project Title:=>  Chat and Video call simultaneously
Creators' Login Name:=>  robelsharma
User Privilege:=>  User
Are you an Admin for this site?:=> No
Create Date:=>  2014-08-09T08:04:29Z
Publish Date:=>  2014-08-09T08:15:36Z
Project Binary:=>  VideoConference-1.0.zip
Uploader Login Name:=>  robelsharma
User Privilege:=>  User
Are you an Admin for this site?:=> No
Binary Package Type:=>  application/zip
---------------------
|Downloaded: 6 times|
---------------------
Create Date:=>  2014-08-11T05:50:48Z
Binary Package updated at:=>  2014-08-11T05:50:54Z
Download Link:=>  https://github.com/robelsharma/VideoConference/releases/download/v1.0/VideoConference-1.0.zip
*****************************************************************

Want to continue ?(y/n):n
```

