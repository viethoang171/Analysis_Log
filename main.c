/*******************************************************************************
 *				 _ _                                             _ _
				|   |                                           (_ _)
				|   |        _ _     _ _   _ _ _ _ _ _ _ _ _ _   _ _
				|   |       |   |   |   | |    _ _     _ _    | |   |
				|   |       |   |   |   | |   |   |   |   |   | |   |
				|   |       |   |   |   | |   |   |   |   |   | |   |
				|   |_ _ _  |   |_ _|   | |   |   |   |   |   | |   |
				|_ _ _ _ _| |_ _ _ _ _ _| |_ _|   |_ _|   |_ _| |_ _|
								(C)2021 Lumi
 * Copyright (c) 2021
 * Lumi, JSC.
 * All Rights Reserved
 *
 * File name: Example.c
 *
 * Description: This code is used for tranning Lumi IOT member. It is the code form statandard.
 *
 * Author: PhuongNP
 *
 * Last Changed By:  $Author: phuongnp $
 * Revision:         $Revision: $
 * Last Changed:     $Date: $Jun 9, 2021
 *
 * Code sample:
 ******************************************************************************/
/******************************************************************************/
/*                              INCLUDE FILES                                 */
#include<stdio.h>
#include<string.h>
/******************************************************************************/

/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
#define FILENAME "log.txt"
#define MAXLENGTHFILE 5000
/******************************************************************************/

/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/

/******************************************************************************/
/*                              EXPORTED DATA                                 */
char fileStr[MAXLENGTHFILE];
int g_countNews=0;
/******************************************************************************/

/******************************************************************************/
/*                            PRIVATE FUNCTIONS                               */
/******************************************************************************/

/******************************************************************************/
/*                            EXPORTED FUNCTIONS                              */
int fileToStr (char* str)
{
    int status;
    FILE *fp=NULL;
    fp=fopen(FILENAME,"r");
    if(fp==NULL)
    {
        printf("File does not exist\n");
        return -1;
    }
    status=fread(str,MAXLENGTHFILE,1,fp);
    //printf("Noi dung cua file log.txt: \n%s",str);
    fclose(fp);
    fp=NULL;
    return status;
}

int count(char *file_text)
{
    int dem=0;
    char byMau[]="\"cmd\":\"set\"";
    char *pbyLocate=NULL;
    //printf("%d\n",file_text);
    do
    {
        if(pbyLocate==NULL)
            pbyLocate=strstr(file_text,byMau);
        else
            pbyLocate=strstr(pbyLocate+1,byMau);
        //printf("%d\n",pbyLocate);
        if(pbyLocate!=NULL)
            dem++;
    }while(pbyLocate!=NULL);
    return dem;
}
/******************************************************************************/

/******************************************************************************/
void task1()
{
    unsigned int dem=count(fileStr);
    printf("\nSo luong ban tin la: %d",dem);
}
void task2()
{
    char byTestCode[MAXLENGTHFILE]="";
    unsigned int dwCountNews=0;
    printf("\nNhap ma can tim: ");
    scanf("%s",byTestCode);
    //printf("\n%s\n",byTestCode);
    unsigned int dwStartNews=0;
    unsigned int dwEndNews;
    unsigned int dwLengthFile=strlen(fileStr);
     while(dwStartNews<dwLengthFile)
    {
        dwEndNews=dwStartNews;
        char byNews[MAXLENGTHFILE]="";
        unsigned int i=-1;
        while(fileStr[dwEndNews]!=10&&dwEndNews<dwLengthFile)
        {
            byNews[++i]=fileStr[dwEndNews];
            dwEndNews++;
        }
        //printf("%s\n",byNews);
        char *pbyTim=NULL;
        pbyTim=strstr(byNews,byTestCode);
        if(pbyTim!=NULL)
            dwCountNews++;
        dwStartNews=dwEndNews+1;
    }
    printf("\nSo ban tin gui di la: %d\n",dwCountNews);
}
void task3()
{
    char pbyBufferString[20][MAXLENGTHFILE];
    char pbyBufferEndPoint[20][MAXLENGTHFILE];
    unsigned int dwNumberBufferString=0;
    unsigned int dwLengthFile=strlen(fileStr);
    char *pbyCheckEnd=fileStr;
    pbyCheckEnd=fileStr;
    char *pbyStart=NULL;
    char *pbyEnd=NULL;
    char byEndLine[MAXLENGTHFILE]=""; //ASCII
    byEndLine[0]=10;
    for(int k=1;k<=18;k++)
    {
        char byNews[MAXLENGTHFILE]="";
        unsigned int dwNewsIndex=0;
        //printf("%d\n",file_text);
        pbyStart=strstr(pbyCheckEnd,"[INFO]");
        pbyEnd=strstr(pbyCheckEnd,byEndLine);
        //printf("%d\n%d\n",pbyStart,pbyEnd);
        char *it=NULL;
        for(it=pbyStart;it!=pbyEnd+1;it++)
            {
                byNews[dwNewsIndex++]=*it;
                //printf("333333333333333333333333\n");
            }
        char *pbyFindSwitch=strstr(byNews,"switch");
        if(pbyFindSwitch==NULL)
        {
            pbyCheckEnd=pbyEnd+1;
            continue;
        }
        char *pbyNewsCode=NULL;
        pbyNewsCode=strstr(pbyCheckEnd,"\"zwave");
        //printf("%d\n",pbyNewsCode);

        char *pbyNetWork=NULL;
        pbyNetWork=strstr(pbyNewsCode,"-");
        unsigned int dwLengthNetWork=0;
        char byResultNetWork[MAXLENGTHFILE]="";
        //printf("Do dai ma NetWork la:  %d\n",strlen(byResultNetWork));
        while(*(pbyNetWork+dwLengthNetWork)!=':')
            {
                byResultNetWork[dwLengthNetWork++]=*(pbyNetWork+dwLengthNetWork);
                //printf("2222222222222222222222\n");
            }
            //printf("%s\n",byResultNetWork);
        char *pbyEndPoint=NULL;
        pbyEndPoint=strstr(pbyNetWork+dwLengthNetWork,"-");
        //printf("%s\n",pbyEndPoint);
        unsigned int dwLengthEndPoint=0;
        char byResultEndPoint[MAXLENGTHFILE]="";
        while(*(pbyEndPoint+dwLengthEndPoint)!='"')
                byResultEndPoint[dwLengthEndPoint++]=*(pbyEndPoint+dwLengthEndPoint);
        pbyCheckEnd=pbyEnd+1;
        unsigned int dwCheckString=0;
        for(unsigned int i=1;i<=dwNumberBufferString;i++)
            if(strcmp(byResultNetWork,pbyBufferString[i])==0)
            {
                dwCheckString=1;
                break;
            }
        if(dwCheckString==0)
            {
                ++dwNumberBufferString;
                for(unsigned int j=0;j<strlen(byResultEndPoint);j++)
                pbyBufferEndPoint[dwNumberBufferString][j]=byResultEndPoint[j];
                for(unsigned int j=0;j<strlen(byResultNetWork);j++)
                pbyBufferString[dwNumberBufferString][j]=byResultNetWork[j];
            }
    }
    //printf("So luong string la: %d\n",dwNumberBufferString);
    //printf("%d\n",dwNumberBufferString);
    for(unsigned int i=1;i<=dwNumberBufferString;i++)
        printf("thiet bi %d co dia chi la : NWK %s, ENDPOINT %s\n",i,pbyBufferString[i],pbyBufferEndPoint[i]);
}

void task4()
{
    unsigned int dwCountErrorNews=0;
    char *pbyCheckEnd=fileStr;
    char byEnd[MAXLENGTHFILE]="";
    byEnd[0]=10;
    unsigned int dwLengthFile=strlen(fileStr);
    char byReqidCode[MAXLENGTHFILE]="";
    char byReqidCodeResponse[MAXLENGTHFILE]="";
    for(int k=1;k<=18;k++)
    {
        char *pbyEndNews=strstr(pbyCheckEnd,byEnd);
        unsigned int dwLengthNews=pbyEndNews-pbyCheckEnd;
        char *pbyFindDirect=strstr(pbyCheckEnd,"\"cmd\":");
        unsigned int dwLengthDirect=strlen("\"cmd\":");
        //printf("%d\n",pbyFindDirect);
        char *pbyEndDirect=strstr(pbyCheckEnd,",");
        char byDirect[MAXLENGTHFILE]="";
        for(unsigned int i=0;i<pbyEndDirect-pbyFindDirect-dwLengthDirect;i++)
            byDirect[i]=*(pbyFindDirect+i+dwLengthDirect);
        //printf("%s\n",byDirect);

        char *pbyFindReqid=strstr(pbyCheckEnd,"\"reqid\": \"");
        unsigned int dwLengthReqid=strlen("\"reqid\": \"");
        char *pbyFindReqidEnd=strstr(pbyFindReqid+dwLengthReqid,"\"");
        unsigned int dwLengthReqidCode=pbyFindReqidEnd-pbyFindReqid-dwLengthReqid;
        if(strcmp(byDirect,"\"set\"")==0)
        {
            byReqidCode[MAXLENGTHFILE]="";
            for(unsigned int i=0;i<dwLengthReqidCode;i++)
                byReqidCode[i]=*(pbyFindReqid+i+dwLengthReqid);
            //printf("%s\n",byReqidCode);
        }
        else
        {
            byReqidCodeResponse[MAXLENGTHFILE]="";
            for(unsigned int i=0;i<dwLengthReqidCode;i++)
                byReqidCodeResponse[i]=*(pbyFindReqid+i+dwLengthReqid);
            if(strcmp(byReqidCode,byReqidCodeResponse)!=0)
                dwCountErrorNews++;
        }
        pbyCheckEnd+=dwLengthNews+1;
    }
    printf("\nSo ban tin loi: %d",dwCountErrorNews);
}
void task5()
{
    char byEnd[]="";
    byEnd[0]=10;
    char *pbyCheckEnd=fileStr;
    for(unsigned int k=1;k<=18;k++)
    {
        //Tim Direct
        /*char *pbyFindDirect=strstr(pbyCheckEnd,"\"cmd\":");
        unsigned int dwLengthDirect=strlen("\"cmd\":");
        //printf("%d\n",pbyFindDirect);
        char *pbyEndDirect=strstr(pbyCheckEnd,",");
        char byDirect[MAXLENGTHFILE]="";
        for(unsigned int i=0;i<pbyEndDirect-pbyFindDirect-dwLengthDirect;i++)
            byDirect[i]=*(pbyFindDirect+i+dwLengthDirect);
            */

        char *pbyFindMinute=strstr(pbyCheckEnd,":");
        char *pbyFindSecond=strstr(pbyFindMinute+1,":");
        char *pbyFindEndTime=strstr(pbyFindSecond+1,"]");
        char byDelayMinute[MAXLENGTHFILE]="";
        char byDelaySecond[MAXLENGTHFILE]="";
        unsigned int dwLengthMinute=pbyFindSecond-pbyFindMinute-1;
        for(unsigned int i=0;i<dwLengthMinute;i++)
            byDelayMinute[i]=*(pbyFindMinute+i+1);
        unsigned int dwLengthSecond=pbyFindEndTime-pbyFindSecond-1;
        for(unsigned int i=0;i<dwLengthSecond;i++)
            byDelaySecond[i]=*(pbyFindSecond+i+1);
        printf("%s\n",byDelayMinute);
        printf("%s\n\n\n\n",byDelaySecond);
        char *pbyEnd=strstr(pbyCheckEnd+1,byEnd);
        unsigned int dwLengthNews=pbyEnd-pbyCheckEnd;
        pbyCheckEnd+=dwLengthNews;
    }
}
int main()
{
    fileToStr(fileStr);
    //task1();
    //task2();
    //task3();
    //task4();
    //task5();
    return 0;
}
