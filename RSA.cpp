#include<iostream>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<cstring>

using namespace std;

int pr[10001];//��������
int num[200000] = {0};
void isprime()//����ɸ 
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
//շת����жϻ��� 
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
	out.open("���.txt", ios::out);
 
	srand((int)time(0));// ������������� 
	int rq = rand()%20+10;// Сһ�㣬����ʵ��̫�� 
	int rp = rand()%20+10;
	int q = pr[rq];
	int p = pr[rp];
	if(q == p)//����������p��q, ��p!=q
	{
		p = pr[rp-1];
	}
//	����˻�n=p*q����(n)=(p-1)(q-1)
	int n = p*q, rn = (p-1) * (q-1);
	int e = gete(rn);//e�릵(n)�����Լ��Ϊ1
	int d = getd(e,rn); //d:����d * e �� 1 (mod ��(n))
	 
	cout << "q:" << q << '\t' << "p:" << p << endl;
	cout<< "n:" << n << '\t' << "rn:" << rn << endl;
	cout << "��Կe:" << e << '\t' << "˽Կd:" << d << endl;
	
	out << "q:" << q << '\t' << "p:" << p << endl;
	out<< "n:" << n << '\t' << "rn:" << rn << endl;
	out << "��Կe:" << e << '\t' << "˽Կd:" << d << endl;
	out << "\n���ģ�"; 
	
    char mingwenstr[100],jiemistr[100];
    unsigned int mingwen[100],cbc[100] = {7},jiemi[100];
    int mingwenlen = 0;
    int *test = 0;
    
    cout << "\n�������ģ�";
    
    gets(mingwenstr);//Ϊ�˶�ȡ�ո�֮��� 
    
    mingwenlen = strlen(mingwenstr);
    test = new int(mingwenlen);
    
//	ѡ�����ģʽ
	cout << "1��ECB�������뱾(Ĭ��)\n2��CBC���ķ�������" << endl;
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
	    cout << "���ģ�"<< mingwenstr <<endl;
		cout << "���ĳ��ȣ�"<< mingwenlen << '\n';    
	    cout << "���ģ�";
	    
	    out << "���ģ�"<< mingwenstr <<endl;
		out << "���ĳ��ȣ�"<< mingwenlen << '\n';    
	    out << "���ģ�";
	    for(int i = 0;i<mingwenlen;i++)
	    {
	    	cout << test[i] << ' ';
	        out << test[i] << ' ';
		}    
	    cout << endl;
	    cout <<"���ܣ�";
	    out <<"\n���ܣ�";
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
	    
	    cout << "���ģ�" << mingwenstr << endl;
		cout << "���ĳ��ȣ�" << mingwenlen << '\n';    
	    cout << "���ģ�";
	    out << "���ģ�"<< mingwenstr <<endl;
		out << "���ĳ��ȣ�"<< mingwenlen << '\n';    
	    out << "���ģ�";
	    
		for(int i = 0;i<mingwenlen;i++)
		{
	        cout<< test[i] << ' ';
	        out << test[i] << ' ';	
		}
	    cout << endl;
	    out <<"\n���ܣ�";
	    cout <<"���ܣ�";
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
