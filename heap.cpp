#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define ll long long
#define pll pair<ll,ll>
#define rep(i,n) for(ll i=0;i<n;i++)
#define mod 1000000007
#define INF 1000000000000000000
#define ff first
#define ss second
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define pie 3.141592653589793238462643383279
#define PYES cout<<"YES"<<endl
#define PNO cout<<"NO"<<endl
#define SB(a) sort(a.begin(),a.end(),greater<ll>());
#define SS(a) sort(a.begin(),a.end());
#define vll vector<ll>
#define vpll vector<pll>
vector<bool> prime;
vector<ll> fact,inv,primes,factors,pf;
void fast()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
}
void factorize(ll a)
{
	factors.clear();
	for(ll i=1;i*i<=a;i++)
	{
		if (i*i==a) factors.pb(i);
		else if (a%i==0)
		{
			factors.pb(i);
			factors.pb(a/i);
		}
	}
	sort(factors.begin(),factors.end());
}
ll power(ll a,ll b)
{
	if(a==1||b==0)	return 1;
	ll c=power(a,b/2);
	ll res=1;
	res=c*c;
	if(res>=mod)	res%=mod;
	if(b%2)	res*=a;
	if(res>=mod)	res%=mod;
	return res;
}
ll modInv(int a)
{
	return power(a,mod-2);
}
void factorial(ll n)
{
	fact.resize(n+1);
	fact[0]=1;
	for(ll i=1;i<=n;i++)
	{
		fact[i]=fact[i-1]*i;
		if(fact[i]>=mod)	fact[i]%=mod;
	}
}
void InvFactorial(ll n)
{
	inv.resize(n+1);
	inv[0]=1;
	for(ll i=1;i<=n;i++)	inv[i]=modInv(fact[i]);
}
ll ncr(ll n,ll r)
{
	if(n<r||n<0||r<0)	return 0;
	ll b=inv[n-r];
	ll c=inv[r];
	ll a=fact[n]*b;
	if(a>=mod)	a%=mod;
	a*=c;
	if(a>=mod)	a%=mod;
	return a;
}
void remove_duplicates(vpll &v)
{
	sort(v.begin(),v.end());
	ll _size=unique(v.begin(),v.end())-v.begin();
	v.resize(_size);
}
unsigned ll gcd(unsigned ll u, unsigned ll v)
{
    if(u==0||v==0) return max(u,v);
    unsigned ll shift=__builtin_ctz(u|v);
	u>>=__builtin_ctz(u);
    do{
    	v>>=__builtin_ctz(v);
    	if(u>v)	swap(u,v);
    	v-=u;
    }while(v!=0);
    return u<<shift;
}
void sieve(ll n)
{
    prime.assign(n+1,1);
	prime[1]=false;
    for(ll p=2;p*p<=n;p++)
	{
		if(prime[p])
		{
			for(ll i=p*p;i<=n;i+=p)	prime[i]=false;
		}
	}	
    for(ll i=2;i<n+1;i++)
	{
		if(prime[i]) primes.push_back(i);
	} 
}
void prime_sieve(ll n)
{
	pf.assign(n+1,0);
	rep(i,n+1) pf[i]=i;
	for(ll i=2;i<=n;i++)
	{
		if (pf[i]==i)
		{
			for(ll j=i;j<=n;j+=i) pf[j]=i;
		}
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------------------
// Always remember: if (condition) if (condition) statement; This doesn't work !!
// Always increase boundaries for global or frequency questions
// pow((ll)10,i) doesn't work sometimes. It is better to use multiple of 10 in arrays. Always remember this.
// delete values when defining global if there are multiple testcases
// don't try to be smart and make stupid mistakes

// n = unique(a.begin(), a.end()) - a.begin();  // this is for making unique
// a.resize(n); 


// make vector of a class -> vector 1 containting values, vector 2 containing first location , int containing capacity,int containing first blank space


class dean{
    public:
    vector <int> values;
    vector <int> posn;
    int capacity;
    int blank;
    int g;
    int size_left;
    dean(int size);
    void insert(int n,int m);
};

dean::dean(int size){
    this->size_left=size-16;
    this->capacity=0;
    this->blank=0;
    this->g=0;
    
}

void dean::insert(int n,int m){
    values.pb(n);
    capacity++;
    size_left=size_left-(m+4);
    posn.pb(g);
    g=g+m;
    blank=blank+m;
}


class link{
    public:
    vector<dean*> v;
    int size_page;
    void insert(int n,int m);
    link(int n);
    void status();
    void search(ll n);
};

link::link(int n){
    this->size_page=n;
}

void link::insert(int n,int m){
    if (v.size()==0){
        dean* t=new dean(size_page);
        t->insert(n,m);
        v.pb(t);
    }
    else{
        int k=v.size();
        int e=0;
        for(int i=0;i<k;i++){
            if (v[i]->size_left>=(m+4)){
                e++;
                v[i]->insert(n,m);
                break;
            }
        }
        if (e==0){
            dean* t=new dean(size_page);
            t->insert(n,m);
            v.pb(t);
        }
    }
}

void link::search(ll n){
    rep(i,v.size()){
        rep(j,v[i]->capacity){
            if (v[i]->values[j]==n){
                cout<<i<<' '<<j<<endl;
                return;
            }
        }
    }
    cout<<-1<<' '<<-1<<endl;
    return;
}

void link::status(){
    cout<<v.size()<<' ';
    rep(i,v.size()){
        cout<<v[i]->capacity<<' ';
    }
    cout<<endl;
}




void solve()
{
    ll n;
    cin>>n;
    link* lin=new link(n);
    ll ans=-1;
    while(ans!=4){
        cin>>ans;
        if (ans==2){
            // cout<<'a'<<endl;
            lin->status();
            // cout<<'b'<<endl;
        }
        if (ans==1){
            int n,m;
            cin>>n>>m;
            // cout<<'c'<<endl;
            lin->insert(m,n);
            // cout<<'d'<<endl;
        }
        if (ans==3){
            int n;
            cin>>n;
            lin->search(n);
        }
    }
}
    
    
    


int main()
{
	fast();
	ll T=1;
// 	cin>>T;
	for(ll z=1;z<=T;z++) solve();
}