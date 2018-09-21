#include<iostream>
#include<string>
#include<cstdio>
#include<cstdlib>

void keyi();
void cpush(int& c);

template<typename T>
class Stack
{
	private:
		T* head;
		int len;
		int cap;

	public:
		Stack(int cap):cap(cap),len(0)
		{
			head = new T[cap];
		}
		~Stack()
		{
			delete head;
		}

		void push(int data)
		{
			head[len] = data;
			++len;
		}
		T pop()
		{
			if(len == 0)
				return 0;
			T d = head[len-1];

			--len;

			return d;
		}
		bool empty()
		{
			if(len == 0)
				return 1;
			else
				return 0;
		}
		int size()
		{
			return len;
		}
		T top()
		{
			if(len == 0)
				return -1;
			return head[len-1];
		}
		void zero()
		{
			len = 0;
		}

};

Stack<char> s(200);
Stack<char> v(200);
std::string exp1;
std::string exp2;

int main()
{
	while(1)
	{
		int i;

		std::cout << "请输入式子：>>>";
		std::cin >> exp1;
	
		int j = -10;	

		for(i = 0; i < exp1.size(); ++i)
		{
			switch(exp1[i])
			{
				case '+':
					{
						while(1)
						{
							if(s.top() == '*' || s.top() == '/' || s.top() == '-' || s.top() == '+' || s.top() != -1 && s.top() != '(')
								keyi();
							else
								break;
						}
						s.push('+');
					}
					break;	
				case '-':
					{
						while(1)
						{
							if(s.top() == '*' || s.top() == '/' || s.top() == '+' || s.top() == '-' || s.top() != -1 && s.top() != '(')
								keyi();
							else
								break;
						}
						s.push('-');
					}
					break;	
				case '*':
					{
						while(1)
						{
							if(s.top() == '/' || s.top() == '*')
								keyi();
							else
								break;
						}

						s.push('*');
					}
					break;	
				case '/':
					{
						while(1)
						{
							if(s.top() == '*' || s.top() == '/')
								keyi();
							else
								break;
						}
						s.push('/');
					}
					break;
				case '(':
					{
						s.push('(');
					}
					break;	
				case ')':
					{
						while(1)
						{
							if(s.top() != '(')
							{
								exp2.append(1,' ');
								exp2.append(1,s.pop());
							}
							else
							{
								s.pop();
								break;
							}
						}
					}
					break;
				default:
					{
						if((i - j) != 1)
							exp2.append(1,' ');
						exp2.append(exp1,i,1);
						j = i;
					}
			}
		}	
		while(!s.empty())
		{
			keyi();
		}

//			std::cout <<"后缀表达式："<< exp2 <<std::endl;	


		int c = 0;;
		for(i = 0; i < exp2.size(); ++i)
		{	
			if(exp2[i] >= '0' && exp2[i] <= '9')
			{
				v.push(exp2[i]);
			}
			else if(exp2[i] == ' ')
				v.push(' ');	
			else
			{
				v.pop();	
				int a = 0,b = 0;
				int time = 0;
				char j[20],k;
				while(v.top() != ' ')
				{	
					for(int z = 0; z < time; ++z)
						j[time-z] = j[time-z-1];
					j[0] = v.top();
					v.pop();
					++time;
				}
				j[time] = '\0';
				b = atoi(j);
							//std::cout<< b << std::endl;//测试运算符两边的输出结果
				v.pop();
				time = 0;
				while(v.top() != ' ')
				{
					if(v.top() == -1)
					{
						j[0] = '0';
						j[1] = '\0';
						time == 1;
						break;
					}
					for(int z = 0; z < time; ++z)
						j[time-z] = j[time-z-1];
					j[0] = v.top();
					v.pop();
					++time;
				}
				j[time] = '\0';
				a = atoi(j);
							//std::cout<< a << std::endl;//测试运算符两边的输出结果
				/*			
				 *只能实现两个数的运算
				 v.pop();
				 b = atoi(&j);
				 j = v.top();
				 v.pop();
				 a = atoi(&j);
				 */			//std::cout<< a << ' ' << b << std::endl;
				switch(exp2[i])
				{
					case '+':
						{
							c = a + b;		
							cpush(c);
						}
						break;	
					case '-':
						{
							c = a - b;
							cpush(c);
						}
						break;	
					case '*':
						{
							c = a * b;
							cpush(c);
						}
						break;	
					case '/':
						{
							if(b == 0)
							{
								std::cout<< "除数不能为零！" <<std::endl;
								goto beg;	
							}
							c = a / b;
							cpush(c);
						}
						break;
				}
			}
		}

		std::cout << c << std::endl;	
	beg:	exp1.clear();
		exp2.clear();
		s.zero();
		v.zero();
	}
	return 0;
}

void keyi()
{
	exp2.append(1,' ');
	exp2.append(1,s.pop());
}

void cpush(int& c)
{
	char str[20] = {0};
	int x = 0;

	sprintf(str,"%d",c);
	while(str[x] != '\0')
	{
		v.push(str[x]);
		++x;
	}
}
