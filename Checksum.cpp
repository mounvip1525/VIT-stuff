#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;
void sender(bool data[],int size,int k);
void modifier(bool data[],int size,int k,bool checkSum[]);
void receiver(bool data[],int size,int k,bool checkSum[]);
void sender(bool data[],int size,int k){
int i,j,z=0,c=0,temp=0,index=0;
int segmentSize=size/k;
bool adder[segmentSize]={0};
adder[segmentSize-1]=1;
bool sum[segmentSize]={0};
bool checkSum[segmentSize]={0};
int sender_data[k][segmentSize];
for(i=0;i<k;i++){
for(j=0;j<segmentSize;j++){
sender_data[i][j]=data[index];
index=index+1;
}
}
for(j=0;j<k;j++){
c=0;
for(i = segmentSize-1; i >= 0 ; i--){
temp=sum[i];
 sum[i] = ((sender_data[j][i] ^ temp) ^ c);
 c = ((sender_data[j][i] & temp) | (sender_data[j][i] & c)) | (temp & c);
 }
 if(c==1){
 c=0;
 for(i =0; i<segmentSize ; i++){
 temp=sum[i];
 sum[i] = ((temp ^ adder[i]) ^ c);
 c = ((temp & adder[i]) | (temp & c)) | (adder[i] & c);
 }
}
}
cout<<"\nSender sum: ";
 for(z=0; z<segmentSize; z++) {
 cout<<sum[z];
}
cout<<"\nCheckSum: ";
for(z=0; z<segmentSize; z++) {
 if(sum[z]==1){
 checkSum[z]=0;
 } else {
 checkSum[z]=1;
 }
 cout<<checkSum[z];
}
modifier(data,size,k,checkSum);
}
void modifier(bool data[],int size,int k,bool checkSum[]){
int i,j;
int random_index=rand() % size;
data[random_index]=1;
cout<<"\nData in modifying function: ";
for(i=0;i<size;i++){
cout<<data[i];
}
receiver(data,size,k,checkSum);
}
void receiver(bool data[],int size,int k,bool checkSum[]){
int index,i,j,temp,c,z,flag=0;
int segmentSize=size/k;
bool adder[segmentSize]={0};
bool sum[segmentSize]={0};
adder[segmentSize-1]=1;
int receiver_data[k][segmentSize];
for(i=0;i<k;i++){
for(j=0;j<segmentSize;j++){
receiver_data[i][j]=data[index];
index=index+1;
}
}
cout<<"\nReceiver data: ";
for(i=0;i<k;i++){
for(j=0;j<segmentSize;j++){
cout<<receiver_data[i][j];
}
}
for(j=0;j<k;j++){
c=0;
for(i = segmentSize-1; i >= 0 ; i--){
temp=sum[i];
 sum[i] = ((receiver_data[j][i] ^ temp) ^ c);
 c = ((receiver_data[j][i] & temp) | (receiver_data[j][i] & c)) | (temp & c);
 }
 if(c==1){
 c=0;
 for(i =0; i<segmentSize ; i++){
 temp=sum[i];
 sum[i] = ((temp ^ adder[i]) ^ c);
 c = ((temp & adder[i]) | (temp & c)) | (adder[i] & c);
 }
}
}
for(i=0;i<segmentSize;i++){
temp=sum[i];
sum[i]=((temp ^ checkSum[i]) ^ c);
c = ((temp & checkSum[i]) | (temp & c)) | (checkSum[i] & c);
}
cout<<"\nReceiver sum: ";
for(i=0;i<segmentSize;i++)
cout<<sum[i];
cout<<"\nReceiver Checksum: ";
for(i=0;i<segmentSize;i++){
if(sum[i]==1){
sum[i]=0;
} else{
sum[i]=1;
flag=1;
}
cout<<sum[i];
}
if(flag==1){
cout<<"\nYour message has been rejected";
} else{
cout<<"\nYour message has been accepted";
}
}
int main(){
int size,k,i;
srand(time(0));
cout<< "Enter the size of the data(in bits):";
cin>> size;
bool data[size];
cout<< "\nEnter k value:";
cin>>k;
if(size%k!=0){
cout<<"\n Error";
exit(0);
} else {
cout<<"Enter the data in a boolean array format \n";
for(i=0;i<size;i++){
cin>>data[i];
}
}
sender(data,size,k);
}
