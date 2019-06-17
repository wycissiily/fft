#include<algorithm>
#include"wave.h"
#include<cmath>
using namespace std;
const double pi=acos(-1);
static int n;
int l=0,r[MAXN];
void init(){
	for(;n;n>>=1)l++;
    n=1<<l;
	for(int i=0;i<n;i++)r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
}
struct complex{
	double re,im;
	complex(double re=0,double im=0):re(re),im(im){}
	complex operator+(complex b)const{return complex(re+b.re,im+b.im);}
	complex operator-(complex b)const{return complex(re-b.re,im-b.im);}
	complex operator*(complex b)const{return complex(re*b.re-im*b.im,re*b.im+im*b.re);}
}a[MAXN];
void FFT(complex c[]){
	for(int i=0;i<n;i++)if(i<r[i])swap(c[i],c[r[i]]);
	for(int i=1;i<n;i<<=1){
		complex omn(cos(pi/i),sin(pi/i));
		for(int j=0;j<n;j+=(i<<1)){
			complex om(1,0);
			for(int k=0;k<i;k++,om=om*omn){
				complex x=c[j+k],y=om*c[j+k+i];
				c[j+k]=x+y;
				c[j+k+i]=x-y;
			}
		}
	}
}