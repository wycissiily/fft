static const int TIME_WINDOW=9866;
static const int MAXN=16384;
static const int HZ_LIMIT=1000;
static const int MIN_VOLUME=20000;
static const char* snd[]={"C","C#","D","D#","E","F","F#","G","G#","A","A#","B"};
struct RIFFhead{int id,siz;};
struct WAVE{
	RIFFhead head;
	int wave,fmt,len;
	short code,chan;
	int bps,spd;
	short alg,bt;
};
struct dat{short l,r;}buf[MAXN];