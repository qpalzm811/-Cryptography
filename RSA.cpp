#include<iostream>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<cstring>

using namespace std;

int pr[10001];//素数集合
int num[200000] = {0};
void isprime()//素数筛 
{
	int n = 200000;
	int k = -1;
	for(int i = 2; i <= n ; i++)
	{
		if(num[i] == 0)
		{
			pr[++k] = i;
			for(int j = 1; j*i <= n; j++) 
			{
				num[i*j] = 1;
			}
		}
	 } 
	 if(k == 10001)
	 {
	 	return;
	  } 
} 

int gcd(int a,int b)
//辗转相除判断互素 
{
    int t;
    while(b)
	{
        t=a;
        a=b;
        b=t%b;
    }
    return a;
}
bool husu(int a, int b)
{
	if(gcd(a,b) == true)
	return true;
	else
	return false;
}


int gete(int rn)
{
	int e = 2;
	while(e<1 || e>rn || !husu(e,rn))
	{
		e++;
	}
	return e;
 } 
 int getd(int e,int rn)
 {
 	int b = 1;
 	while( ( (e*b) % rn) != 1)
 	{
 		b++;
	 }
	 return b;
 }
 int rsa(int a,int b,int c)
 { 
    int t = a,y = 1;
    while(b!=0)
	{
        y *= t;
        y %= c;
        b--;
    }
    return y;
}

void CBC(unsigned int *str,unsigned int * cbc, int mingwenlen)
{
	for(int i = 0; i != mingwenlen; i++)
	{
		str[i] = str[i] ^ cbc[i];
	}
	cout <<endl;
}

int main (int argc, char **argv)
{
	isprime();
	ofstream out;
	out.open("结果.txt", ios::out);
 
	srand((int)time(0));// 设置随机数种子 
	int rq = rand()%20+10;// 小一点，大了实在太慢 
	int rp = rand()%20+10;
	int q = pr[rq];
	int p = pr[rp];
	if(q == p)//两个大素数p和q, 且p!=q
	{
		p = pr[rp-1];
	}
//	计算乘积n=p*q，Φ(n)=(p-1)(q-1)
	int n = p*q, rn = (p-1) * (q-1);
	int e = gete(rn);//e与Φ(n)的最大公约数为1
	int d = getd(e,rn); //d:满足d * e ≡ 1 (mod Φ(n))
	 
	cout << "q:" << q << '\t' << "p:" << p << endl;
	cout<< "n:" << n << '\t' << "rn:" << rn << endl;
	cout << "公钥e:" << e << '\t' << "私钥d:" << d << endl;
	
	out << "q:" << q << '\t' << "p:" << p << endl;
	out<< "n:" << n << '\t' << "rn:" << rn << endl;
	out << "公钥e:" << e << '\t' << "私钥d:" << d << endl;
	out << "\n明文："; 
	
    char mingwenstr[100],jiemistr[100];
    unsigned int mingwen[100],cbc[100] = {7},jiemi[100];
    int mingwenlen = 0;
    int *test = 0;
    
    cout << "\n输入明文：";
    
    gets(mingwenstr);//为了读取空格之类的 
    
    mingwenlen = strlen(mingwenstr);
    test = new int(mingwenlen);
    
//	选择分组模式
	cout << "1、ECB电子密码本(默认)\n2、CBC密文分组链接" << endl;
	short ch = 0;
	cin >> ch;

	if(ch == 2)
	{
		for(int i = 0; i != mingwenlen ; i++)
		{
			mingwen[i] = int (mingwenstr[i]);
		}
		CBC(mingwen, cbc, mingwenlen);
		for(int i = 0;i<mingwenlen;i++)
		{
	        test[i] = rsa( mingwen[i], e, n);
	    }    
	    
	    for(int i = 0;i<mingwenlen;i++)
		{
	        jiemi[i] = rsa(test[i], d, n);
	    }
	}
    
    if(ch == 1)
    {
    	for(int i = 0;i<mingwenlen;i++)
		{
        	test[i] = rsa((int)mingwenstr[i],e,n);
	    }    
	    for(int i = 0;i<mingwenlen;i++)
		{
	        jiemi[i] = rsa(test[i],d,n);
	    }
    	jiemi[mingwenlen] = '\0';    
	    cout << "明文："<< mingwenstr <<endl;
		cout << "明文长度："<< mingwenlen << '\n';    
	    cout << "密文：";
	    
	    out << "明文："<< mingwenstr <<endl;
		out << "明文长度："<< mingwenlen << '\n';    
	    out << "密文：";
	    for(int i = 0;i<mingwenlen;i++)
	    {
	    	cout << test[i] << ' ';
	        out << test[i] << ' ';
		}    
	    cout << endl;
	    cout <<"解密：";
	    out <<"\n解密：";
	    for(int i = 0; i != mingwenlen; i++)
	    {
	    	cout << char(jiemi[i]);
			out << char(jiemi[i]);	
		}     
	}
    else if(ch == 2)
	{
		for(int i = 0; i != mingwenlen+1 ; i++)
		{
			jiemi[i] = int (jiemi[i]);
			//cout << jiemi[i] << endl;
		}
    	CBC(jiemi, cbc, mingwenlen);
	    jiemi[mingwenlen] = '\0';
	    
	    cout << "明文：" << mingwenstr << endl;
		cout << "明文长度：" << mingwenlen << '\n';    
	    cout << "密文：";
	    out << "明文："<< mingwenstr <<endl;
		out << "明文长度："<< mingwenlen << '\n';    
	    out << "密文：";
	    
		for(int i = 0;i<mingwenlen;i++)
		{
	        cout<< test[i] << ' ';
	        out << test[i] << ' ';	
		}
	    cout << endl;
	    out <<"\n解密：";
	    cout <<"解密：";
	    for(int i = 0; i != mingwenlen; i++)
	    {
	    	cout << char(jiemi[i]); 
			out << char(jiemi[i]);   	
		}
    }  
    cout << endl; 
    out.close();
	system("pause");
	return 0;
}
