#include<iostream>
#include<cstdio>
#include"fft.h"
#include<set>
using namespace std;
const double base=log(16.352),delta=log(2)/12;
int cnt;
double num[MAXN];
FILE *wav,*out;
RIFFhead blk;
WAVE head;
double han(double x){return (1-cos(2*pi*x))/2;}
double todbl(double x,double p){return x/32768*han(p/TIME_WINDOW);}
int turn(double x){return (log(x)-base)/delta;}
int main(){
	wav=fopen("1.wav","rb");
	out=fopen("1.txt","w");
	fread(&head,sizeof(WAVE),1,wav);
	fread(&blk,sizeof(RIFFhead),1,wav);
	fseek(wav,blk.siz,SEEK_CUR);
	fread(&blk,sizeof(RIFFhead),1,wav);
	n=TIME_WINDOW;
	init();
	cnt=blk.siz/sizeof(dat)/TIME_WINDOW;
	while(cnt--){
		fread(buf,sizeof(dat),TIME_WINDOW,wav);
		for(int i=0;i<n;i++)a[i]=todbl(buf[i].l,i);
		FFT(a);
		for(int i=0;i<n;i++){
			num[i]=a[i].re*a[i].re+a[i].im*a[i].im;
			num[i]=max(num[i]-MIN_VOLUME,0.);
		}
		set<int>s;
		for(int i=0;i<HZ_LIMIT;i++)if(num[i]>0)s.insert(turn(i*TIME_WINDOW/MAXN*4));
		for(int x:s)fprintf(out,"%s%d ",snd[x%12],x/12);
		fprintf(out,"\n");
		
	}
}