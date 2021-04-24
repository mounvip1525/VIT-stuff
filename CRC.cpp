#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
using namespace std;
void sender(int dividend[],int size,int mSize,int key[],int keySize);
void modifier(int modifier_msg[],int size,int mSize,int key[],int keySize);
void receiver(int receiver_msg[],int size,int mSize,int key[],int keySize);
void sender(int dividend[],int size,int mSize,int key[],int keySize){
int i,j,temp,temp_2;
int quotient[mSize]={0};
int f[keySize];
int sender_msg[mSize]={0};
srand(time(0));
for(i=0;i<mSize;i++){
sender_msg[i]=dividend[i];
}
for(i=0;i<size;i++){
temp=i;
if(dividend[i]==1){
for(j=0;j<keySize;j++){
temp_2=dividend[temp];
dividend[temp]=dividend[temp]^key[j];
f[j]=temp_2^key[j];
temp=temp+1;
}
quotient[i]=1;
} else{
quotient[i]=0;
}
}
cout<<"\nSender Quotient:";
for(i=0;i<size;i++){
cout<<quotient[i]<"-";
}
cout<<"\nSender Remainder:";
for(i=0;i<keySize;i++){
cout<<f[i]<"-";
}
j=1;
for(i=size;i<mSize;i++){
sender_msg[i]=f[j];
j++;
}
cout<<"\nSender Message:";
for(int i=0;i<mSize;i++)
cout<<sender_msg[i]<<"-";
modifier(sender_msg,size,mSize,key,keySize);
}
void modifier(int modifier_msg[],int size,int mSize,int key[],int keySize){
int random_index=rand() % mSize;
modifier_msg[random_index]=1;
cout<<"\nMessage in modifier:";
for(int i=0;i<mSize;i++)
cout<<modifier_msg[i]<<"-";
receiver(modifier_msg,size,mSize,key,keySize);
}
void receiver(int receiver_msg[],int size,int mSize,int key[],int keySize){
int quotient[size]={0};
int i,j,temp,temp_2,flag=0;
int f[keySize];
cout<<"\nMessage received: ";
for(i=0;i<mSize;i++)
cout<<receiver_msg[i]<<"-";
for(i=0;i<size;i++){
temp=i;
if(receiver_msg[i]==1){
for(j=0;j<keySize;j++){
temp_2=receiver_msg[temp];
receiver_msg[temp]=receiver_msg[temp]^key[j];
f[j]=temp_2^key[j];
temp=temp+1;
}
quotient[i]=1;
} else{
quotient[i]=0;
}
}
cout<<"\nReceiver Quotient: ";
for(i=0;i<size;i++){
cout<<quotient[i]<"-";
}
cout<<"\nReceiver Remainder: ";
for(i=0;i<keySize;i++){
cout<<f[i]<"-";
}
j=1;
for(i=size;i<mSize;i++){
receiver_msg[i]=f[j];
j++;
}
for(i=0;i<keySize;i++){
if(f[i]==1)
flag=1;
}
if(flag==1){
cout<<"\nYour message has been rejected";
} else {
cout<<"\nYour message has been accepted";
}
}
int main() {
int i,j,size,keySize;
cout<<"\nEnter the number of bits in key: ";
cin>>keySize;
int key[keySize];
cout<<"\nEnter the key value(binary array): \n";
for(i=0;i<keySize;i++){
cin>>key[i];
}
cout<<"Enter the size of the data: ";
cin>>size;
int mSize=size+keySize-1;
int dividend[mSize]={0};
cout<<"\nEnter the data(binary array): \n";
for(i=0;i<size;i++)
cin>>dividend[i];
cout<<"\nDivisor:";
for(i=0;i<keySize;i++)
cout<<key[i]<<"-";
cout<<"\nDividend";
for(i=0;i<mSize;i++)
cout<<dividend[i]<<"-";
sender(dividend,size,mSize,key,keySize);
return 0;
}
