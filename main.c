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
    unsigned int dwCount=count(fileStr);
    printf("\nSo luong ban tin la: %d",dwCount);
}
void task2()
{
    char byAddressNWK[MAXLENGTHFILE]="";
    printf("\nNhap dia chi nwk cua thiet bi: %");
    scanf("%s",byAddressNWK);
    printf("\n");
    char *pbyCheckEnd=fileStr;
    char byEnd[MAXLENGTHFILE]="";
    byEnd[0]=10;
    char *pbyStart=NULL;
    char *pbyEnd=NULL;
    unsigned int dwCountNews=0;
    while(pbyCheckEnd!=NULL)
    {
        char byNews[MAXLENGTHFILE]="";
        unsigned int dwNewsIndex=0;
        //printf("%d\n",file_text);
        pbyStart=strstr(pbyCheckEnd,"[INFO]");
        pbyEnd=strstr(pbyCheckEnd+1,byEnd);
        //printf("%d\n%d\n",pbyStart,pbyEnd);
        char *it=NULL;
        if(pbyStart-pbyEnd<0)
        for(it=pbyStart;it!=pbyEnd+1;it++)
            {
                byNews[dwNewsIndex++]=*it;
                //printf("333333333333333333333333\n");
            }

        char *pbyFindSet=strstr(byNews,"\"set\"");
        if(pbyFindSet==NULL)
        {
            pbyCheckEnd=strstr(pbyCheckEnd+1,byEnd);
            continue;
        }
        char *pbyFindNwk=strstr(byNews,byAddressNWK);
        if(pbyFindNwk!=NULL)
            dwCountNews++;
        pbyCheckEnd=strstr(pbyCheckEnd+1,byEnd);
    }
    printf("\nSo ban tin gui di la: %d\n",dwCountNews);
}
void task3()
{
    char pbyBufferString[20][MAXLENGTHFILE];
    char pbyBufferEndPoint[20][MAXLENGTHFILE];
    unsigned int dwNumberBufferString=0;
    char byEnd[MAXLENGTHFILE]="";
    byEnd[0]=10;
    char *pbyCheckEnd=fileStr;
    char *pbyStart=NULL;
    char *pbyEnd=NULL;
    while(pbyCheckEnd!=NULL)
    {
        char byNews[MAXLENGTHFILE]="";
        unsigned int dwNewsIndex=0;
        //printf("%d\n",file_text);
        pbyStart=strstr(pbyCheckEnd,"[INFO]");
        pbyEnd=strstr(pbyCheckEnd+1,byEnd);
        //printf("%d\n%d\n",pbyStart,pbyEnd);
        char *it=NULL;
        if(pbyStart-pbyEnd<0)
        for(it=pbyStart;it!=pbyEnd+1;it++)
            {
                byNews[dwNewsIndex++]=*it;
                //printf("333333333333333333333333\n");
            }
        //printf("%s\n",byNews);

        char *pbyFindSet=strstr(byNews,"\"set\"");
        if(pbyFindSet==NULL)
        {
            pbyCheckEnd=strstr(pbyCheckEnd+1,byEnd);
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
        //printf("%s\n",byResultNetWork);
        //printf("%s\n\n\n\n\n",byResultEndPoint);
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

        //printf("%d\n",pbyCheckEnd);
        pbyCheckEnd=strstr(pbyCheckEnd+1,byEnd);
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
    char byReqidSet[MAXLENGTHFILE]="";
    char byReqidStatus[MAXLENGTHFILE]="";
    while(pbyCheckEnd!=NULL)
    {

        char *pbyEndNews=strstr(pbyCheckEnd+1,byEnd);
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
            byReqidSet[MAXLENGTHFILE]="";
            for(unsigned int i=0;i<dwLengthReqidCode;i++)
                byReqidSet[i]=*(pbyFindReqid+i+dwLengthReqid);
            //printf("%s\n",byReqidCode);
        }
        else
        {
            byReqidStatus[MAXLENGTHFILE]="";
            for(unsigned int i=0;i<dwLengthReqidCode;i++)
                byReqidStatus[i]=*(pbyFindReqid+i+dwLengthReqid);
            if(strcmp(byReqidSet,byReqidStatus)!=0)
                dwCountErrorNews++;
        }

        pbyCheckEnd=strstr(pbyCheckEnd+1,byEnd);
    }
    printf("\nSo ban tin loi: %d",dwCountErrorNews);
}
unsigned int pow10(int i)
{
    if(i==0)
        return 1;
    unsigned int dwResult=1;
    for(unsigned int k=1;k<=i;k++)
        dwResult*=10;
    return dwResult;
}
unsigned int stringToNum(char byStr[MAXLENGTHFILE])
{
    unsigned int dwResult=0;
    unsigned int dwLengthStr=strlen(byStr);
    for(int i=0;i<dwLengthStr;i++)
    {
        unsigned int dwChuSo=byStr[dwLengthStr-i-1]-48;
        dwResult+=dwChuSo*pow10(i);
    }
    return dwResult;
}
void task5()
{
    unsigned int dwMaxDelay=0;
    char byEnd[MAXLENGTHFILE]="";
    byEnd[0]=10;
    char *pbyCheckEnd=fileStr;

    char byMinuteSet[MAXLENGTHFILE]="";
    char byMinuteStatus[MAXLENGTHFILE]="";
    char bySecondSet[MAXLENGTHFILE]="";
    char bySecondStatus[MAXLENGTHFILE]="";

    char byReqidSet[MAXLENGTHFILE]="";
    char byReqidStatus[MAXLENGTHFILE]="";
    while(pbyCheckEnd!=NULL)
    {
        char *pbyFindMinute=strstr(pbyCheckEnd,":");
        //printf("%d\n",pbyFindMinute);




        //xu ly Time
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


        //FindDirect
        char *pbyFindDirect=strstr(pbyCheckEnd,"\"cmd\":");
        unsigned int dwLengthDirect=strlen("\"cmd\":");
        //printf("%d\n",pbyFindDirect);
        char *pbyEndDirect=strstr(pbyCheckEnd,",");
        char byDirect[MAXLENGTHFILE]="";
        for(unsigned int i=0;i<pbyEndDirect-pbyFindDirect-dwLengthDirect;i++)
            byDirect[i]=*(pbyFindDirect+i+dwLengthDirect);
        //printf("%s\n",byDirect);




        //FindCorrectNews
        char *pbyFindReqid=strstr(pbyCheckEnd,"\"reqid\": \"");
        unsigned int dwLengthReqid=strlen("\"reqid\": \"");
        char *pbyFindReqidEnd=strstr(pbyFindReqid+dwLengthReqid,"\"");
        unsigned int dwLengthReqidCode=pbyFindReqidEnd-pbyFindReqid-dwLengthReqid;
        if(strcmp(byDirect,"\"set\"")==0)
        {
            byReqidSet[MAXLENGTHFILE]="";
            for(unsigned int i=0;i<dwLengthReqidCode;i++)
                byReqidSet[i]=*(pbyFindReqid+i+dwLengthReqid);
            //printf("%s\n",byReqidCode);
        }
        else
        {
            byReqidStatus[MAXLENGTHFILE]="";
            for(unsigned int i=0;i<dwLengthReqidCode;i++)
                byReqidStatus[i]=*(pbyFindReqid+i+dwLengthReqid);
            if(strcmp(byReqidSet,byReqidStatus)!=0)
            {
                pbyCheckEnd=strstr(pbyCheckEnd+1,byEnd);
                continue;
            }
        }





        //Xu ly Direct
        if(strcmp(byDirect,"\"set\"")==0)
        {
            byMinuteSet[MAXLENGTHFILE]="";
            bySecondSet[MAXLENGTHFILE]="";
            for(unsigned int k=0;k<dwLengthMinute;k++)
                byMinuteSet[k]=*(byDelayMinute+k);
            unsigned int dwLengthSecondSet=0;
            for(unsigned int k=0;k<dwLengthSecond;k++)
                if(*(byDelaySecond+k)!='.')
                    bySecondSet[dwLengthSecondSet++]=*(byDelaySecond+k);
            //printf("Set: %s, %s\n",byMinuteSet,bySecondSet);
        }
        else
        {
            byMinuteStatus[MAXLENGTHFILE]="";
            bySecondStatus[MAXLENGTHFILE]="";
            for(unsigned int k=0;k<dwLengthMinute;k++)
                byMinuteStatus[k]=*(byDelayMinute+k);
            unsigned int dwLengthSecondStatus=0;
            for(unsigned int k=0;k<dwLengthSecond;k++)
                if(*(byDelaySecond+k)!='.')
                   bySecondStatus[dwLengthSecondStatus++]=*(byDelaySecond+k);
            //printf("Set: %s, %s\n",byMinuteSet,bySecondSet);
            //printf("Status: %s, %s\n",byMinuteStatus,bySecondStatus);
            unsigned int dwTimeDelay=(stringToNum(byMinuteStatus)-stringToNum(byMinuteSet))*60*1000+(stringToNum(bySecondStatus)-stringToNum(bySecondSet));
            //printf("%d\n",dwTimeDelay);
            if(dwTimeDelay>dwMaxDelay)
                dwMaxDelay=dwTimeDelay;
        }

        pbyCheckEnd=strstr(pbyCheckEnd+1,byEnd);
    }
    printf("Do tre lon nhat la: %d Millisecond\n",dwMaxDelay);
}
void duyetNews()
{
    char byEnd[MAXLENGTHFILE]="";
    byEnd[0]=10;
    char *pbyCheckEnd=NULL;
    do
    {
        if(pbyCheckEnd==NULL)
            pbyCheckEnd=strstr(fileStr,byEnd);
        else
            pbyCheckEnd=strstr(pbyCheckEnd+1,byEnd);
    }while(pbyCheckEnd!=NULL);
}
void task6()
{
    unsigned int dwSumTimeDelay=0;
    unsigned int dwCountCorrectNews=0;
    char byEnd[MAXLENGTHFILE]="";
    byEnd[0]=10;
    char *pbyCheckEnd=fileStr;

    char byMinuteSet[MAXLENGTHFILE]="";
    char byMinuteStatus[MAXLENGTHFILE]="";
    char bySecondSet[MAXLENGTHFILE]="";
    char bySecondStatus[MAXLENGTHFILE]="";

    char byReqidSet[MAXLENGTHFILE]="";
    char byReqidStatus[MAXLENGTHFILE]="";
    while(pbyCheckEnd!=NULL)
    {
        char *pbyFindMinute=strstr(pbyCheckEnd,":");
        //printf("%d\n",pbyFindMinute);




        //xu ly Time
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


        //FindDirect
        char *pbyFindDirect=strstr(pbyCheckEnd,"\"cmd\":");
        unsigned int dwLengthDirect=strlen("\"cmd\":");
        //printf("%d\n",pbyFindDirect);
        char *pbyEndDirect=strstr(pbyCheckEnd,",");
        char byDirect[MAXLENGTHFILE]="";
        for(unsigned int i=0;i<pbyEndDirect-pbyFindDirect-dwLengthDirect;i++)
            byDirect[i]=*(pbyFindDirect+i+dwLengthDirect);
        //printf("%s\n",byDirect);




        //FindCorrectNews
        char *pbyFindReqid=strstr(pbyCheckEnd,"\"reqid\": \"");
        unsigned int dwLengthReqid=strlen("\"reqid\": \"");
        char *pbyFindReqidEnd=strstr(pbyFindReqid+dwLengthReqid,"\"");
        unsigned int dwLengthReqidCode=pbyFindReqidEnd-pbyFindReqid-dwLengthReqid;
        if(strcmp(byDirect,"\"set\"")==0)
        {
            byReqidSet[MAXLENGTHFILE]="";
            for(unsigned int i=0;i<dwLengthReqidCode;i++)
                byReqidSet[i]=*(pbyFindReqid+i+dwLengthReqid);
            //printf("%s\n",byReqidCode);
        }
        else
        {
            byReqidStatus[MAXLENGTHFILE]="";
            for(unsigned int i=0;i<dwLengthReqidCode;i++)
                byReqidStatus[i]=*(pbyFindReqid+i+dwLengthReqid);
            if(strcmp(byReqidSet,byReqidStatus)!=0)
            {
                pbyCheckEnd=strstr(pbyCheckEnd+1,byEnd);
                continue;
            }
            else
                dwCountCorrectNews++;
        }





        //Xu ly Direct
        if(strcmp(byDirect,"\"set\"")==0)
        {
            byMinuteSet[MAXLENGTHFILE]="";
            bySecondSet[MAXLENGTHFILE]="";
            for(unsigned int k=0;k<dwLengthMinute;k++)
                byMinuteSet[k]=*(byDelayMinute+k);
            unsigned int dwLengthSecondSet=0;
            for(unsigned int k=0;k<dwLengthSecond;k++)
                if(*(byDelaySecond+k)!='.')
                    bySecondSet[dwLengthSecondSet++]=*(byDelaySecond+k);
            //printf("Set: %s, %s\n",byMinuteSet,bySecondSet);
        }
        else
        {
            byMinuteStatus[MAXLENGTHFILE]="";
            bySecondStatus[MAXLENGTHFILE]="";
            for(unsigned int k=0;k<dwLengthMinute;k++)
                byMinuteStatus[k]=*(byDelayMinute+k);
            unsigned int dwLengthSecondStatus=0;
            for(unsigned int k=0;k<dwLengthSecond;k++)
                if(*(byDelaySecond+k)!='.')
                   bySecondStatus[dwLengthSecondStatus++]=*(byDelaySecond+k);
            //printf("Set: %s, %s\n",byMinuteSet,bySecondSet);
            //printf("Status: %s, %s\n",byMinuteStatus,bySecondStatus);
            unsigned int dwTimeDelay=(stringToNum(byMinuteStatus)-stringToNum(byMinuteSet))*60*1000+(stringToNum(bySecondStatus)-stringToNum(bySecondSet));
            //printf("%d\n",dwTimeDelay);
            dwSumTimeDelay+=dwTimeDelay;
        }

        pbyCheckEnd=strstr(pbyCheckEnd+1,byEnd);
    }
    unsigned int dwAveTimeDelay=dwSumTimeDelay/dwCountCorrectNews;
    printf("Do tre trung binh la: %d Millisecond\n",dwAveTimeDelay);
}
int main()
{
    fileToStr(fileStr);
    task1();
    task2();
    task3();
    task4();
    task5();
    task6();
    return 0;
}
