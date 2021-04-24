#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include<time.h>
using namespace std;
int hSize;
int r_bits[10];
int sender(int sender_hamCode[],int r);
int modifier(int modifier_code[],int r);
int receiver(int receiver_hamCode[],int r);
int parity(int i,int d[]){
if(i==0){
int r=d[3]^d[5]^d[7]^d[9]^d[11];
r_bits[i]=r;
return r;
} else if(i==1){
int r=d[3]^d[6]^d[7]^d[10]^d[11];
r_bits[i]=r;
return r;
} else if(i==2){
int r=d[5]^d[6]^d[7]^d[12];
r_bits[i]=r;
return r;
} else{
int r=d[9]^d[10]^d[11];
r_bits[i]=r;
return r;
}
}
void reverse_array(int arr[], int start, int end)
{
 int temp;
 while (start < end)
 {
 temp = arr[start];
 arr[start] = arr[end];
 arr[end] = temp;
 start++;
 end--;
 }
}
int sender(int sender_hamCode[],int r){
int i;
for(i=0;i<r;i++){
int position=pow(2,i);
sender_hamCode[position]=parity(i,sender_hamCode);
}
cout<<"\nSender Ham Code: ";
for(i=hSize;i>0;i--){
cout<<sender_hamCode[i]<<"-";
}
modifier(sender_hamCode,r);
}
int modifier(int modifier_code[],int r){
int random_index=rand() % hSize;
modifier_code[random_index]=1;
cout<<"\nHam code in modifier: ";
for(int i=hSize;i>0;i--){
cout<<modifier_code[i]<<"-";
}
receiver(modifier_code,r);
}
int receiver(int receiver_hamCode[],int r){
int i,error_bit=0;
cout<<"\nReceiver Ham Code: ";
for(i=hSize;i>0;i--){
cout<<receiver_hamCode[i]<<"-";
}
int error_pos[r];
int temp_rBits[r];
for(i=0;i<r;i++){
temp_rBits[i]=r_bits[i];
}
for(i=0;i<r;i++){
int position=pow(2,i);
receiver_hamCode[position]=parity(i,receiver_hamCode);
}
for(i=0;i<r;i++){
error_pos[i]=temp_rBits[i]^r_bits[i];
}
int j=r-1;
for(i=0;i<r;i++){
error_bit=error_bit+error_pos[i]*pow(2,j);
j--;
}
if(error_bit>0){
cout<<"\nError in bit:"<<error_bit;
} else{
cout<<"\nMessage transmitted without error";
}
}
int main ()
{
int size,r=0,i,j=0,power=0;
srand(time(0));
size=8;
int data[size];
cout<<"Enter the data in array format(Size is 8 bits):\n";
for(i=0;i<size;i++){
cin>>data[i];
}
reverse_array(data,0,size-1);
// cout<<"\n reverse:";
// for(i=0;i<size;i++){
// cout<<data[i]<<"-";
// }
while(size+r+1>pow(2,r)){
r=r+1;
}
cout<<"\nR size: "<<r;
hSize=size+r;
int ham_data[hSize];
for(i=1;i<=hSize;++i){
if(i==pow(2,power)){
ham_data[i]=0;
power++;
} else {
ham_data[i]=data[j];
j++;
}
}
sender(ham_data,r);
}

