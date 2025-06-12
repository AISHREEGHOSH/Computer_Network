#include<stdio.h>
#include<string.h>
#include<math.h>
#include<winsock2.h>

int main(){
    WSADATA wsa;
    SOCKET sock;
    int sd;
    struct sockaddr_in sad,cad;
    sd=socket(AF_INET,SOCK_STREAM,0);
    sad.sin_family=AF_INET;
    sad.sin_port=htons(9995);
    sad.sin_addr.s_addr=inet_addr("127.0.0.1");
    connect(sd,(struct sockaddr*)&sad,sizeof(sad));




    char data[100],data1[100];
    int dl,sl,i,j=0,sum[100],t,c,k;
    printf("\n enter the data \n");
    scanf("%d",data);

    dl=strlen(data);

    while(1){
        printf("\n Enter the segment length \n");
        scanf("%d",&sl);
        for(i=1;i<sl/2;i++){
            if(pow(2,i)==sl){
                j=1;
                break;
            }
        }if(j==1){
            break;
        }else{
            printf("\n Segment length must be power of two");
        }
    }
    if(dl%sl!=0){
        i=sl-(dl%sl);
        for(j=0;j<i;j++){
            data1[j]='0';
            
        }
        strcat(data1,data);
        strcpy(data,data1);
        dl=dl+i;
    }
    for(i=0;i<sl;i++){
        sum[i]=0;
    }

    for(i=dl;i>0;i-sl){
        c=0;
        k=sl-1;
       for(j=i-1;j>=i-sl;j--){
        t=(sum[k]+(data[j]-48)+c);
        sum[k]=t%2;
        c=t/2;
        k--;
       }
       if(c==1){
        for(j=sl-1;j>=0;j--){
            t=sum[j]+c;
            sum[j]=t%2;
            c=t/2;
        }
       } 
    }
    printf("\n Checksum=");
    for(i=0;i<sl;i++){
        if(sum[i]==0)
            sum[i]=1;
        else
            sum[i]=0;
        printf("%d",sum[i]);
        data[dl+i]==sum[i]+48;
    }
    data[dl+i]="\0";
    printf("\n Code word is : %s",data);
    send(sd,data,sizeof(data),0);
    return 0;

}


// #include <stdio.h>
// #include <string.h>
// #include <math.h>
// #include<winsock2.h>
// int main() {
//     WSADATA wsa;
//     SOCKET sock;
//     int sd;
//     struct sockaddr_in sad,cad;
//     sd=socket(AF_INET,SOCK_STREAM,0);
//     sad.sin_family=AF_INET;
//     sad.sin_port=htons(9995);
//     sad.sin_addr.s_addr=inet_addr("127.0.0.1");
//     connect(sd,(struct sockaddr*)&sad,sizeof(sad));
// // *************START CODE FOR CHKSUM SENDER ************//
// char data[100],data1[100];
// int t,c,k,dl,sl,i,j=0,sum[100];
// printf("\n enter the data \n");
// scanf("%s",data);
// dl=strlen(data);

// //*** this done to mandet seglen must in pow of 2***********
// while(1){
// printf("\n enter the segment length \n");
// scanf("%d",&sl);
// for(i=1;i<=sl/2;i++)
// {
// if(pow(2,i)==sl)
// {
// j=1;
// break;
// }
// }
// if(j==1)
// break;
// else
// printf("\n segment length must in pow of 2\n");
// }



// //*************************************************************
// //if data length not divisable by segl adding 0 at front of data
// if((dl%sl)!=0)
// {
// i=sl-(dl%sl);
// for(j=0;j<i;j++)
// data1[j]='0';
// strcat(data1,data);
// strcpy(data,data1);
// dl=dl+i;
// }
// // ************
// for(i=0;i<sl;i++)
// sum[i]=0;
// for(i=dl;i>0;i=i-sl)
// {
// c=0;
// k=sl-1;
// for(j=i-1;j>=i-sl;j--)
// {
// t=(sum[k]+(data[j]-48)+c);
// sum[k]=t%2;
// c=t/2;
// k--;
// }
// if(c==1)
// {
// for(j=sl-1;j>=0;j--)
// {
// t=sum[j]+c;
// sum[j]=t%2;
// c=t/2;
// }
// }
// }
// printf("\n Checksum = ");
// for(i=0;i<sl;i++){
// if(sum[i]==0)
// sum[i]=1;
// else
// sum[i]=0;
// printf("%d",sum[i]);
// data[dl+i]=sum[i]+48;
// }
// data[dl+i]='\0';
// printf("\ncode word is: %s",data);
// send(sd,data,sizeof(data),0);
// // *************END CODE FOR CHKSUM SENDER ************//
// return(0);
// }


