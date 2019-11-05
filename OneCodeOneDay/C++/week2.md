# day 1 task 1

剑指offer  
用两个栈来实现一个队列，完成队列的Push和Pop操作。  
队列中的元素为int类型。

~~~C++
#include <iostream>
#include<stack>

using namespace std;

class Solution
{
public:
    void push(int node) //stack1: in order
    {
        while(!stack2.empty())
        {
            stack1.push(stack2.top());
            stack2.pop();
        }
        stack1.push(node);
    }

    int pop() //stack2: reverse
    {
        while(!stack1.empty())
        {
            stack2.push(stack1.top());
            stack1.pop();
        }
        if(stack2.empty())
            return -1;
        else
        {
            int a = stack2.top();
            stack2.pop();
            return a;
        }
    }

private:
    stack<int> stack1;
    stack<int> stack2;
};


int main()
{
    Solution a;
    a.push(0);
    a.push(1);
    a.push(2);
    cout<<a.pop()<<endl;
    cout<<a.pop()<<endl<<endl;
    a.push(4);
    a.push(5);
    cout<<a.pop()<<endl;
    cout<<a.pop()<<endl;
    cout<<a.pop()<<endl;
    cout<<a.pop()<<endl;
    cout<<a.pop()<<endl;
    return 0;
}
// push时正序，pop时逆序
~~~

~~~C++
//优化
class Solution
{
public:
    void push(int node)
    {
        stack1.push(node);
    }

    int pop()
    {
        if(stack2.empty())
        {
            while(!stack1.empty())
            {
                stack2.push(stack1.top());
                stack1.pop();
            }
        }
        if(stack2.empty())
            return -1;
        else
        {
            int a = stack2.top();
            stack2.pop();
            return a;
        }
    }

private:
    stack<int> stack1;
    stack<int> stack2;
};
~~~

# day 2 task 2

剑指offer  
一只青蛙一次可以跳上1级台阶，也可以跳上2级。求该青蛙跳上一个n级的台阶总共有多少种跳法（先后次序不同算不同的结果）。

~~~C++
#include <iostream>
#include<stack>

using namespace std;

class Solution {
public:
    int jumpFloor(int number)
    {
        int count[number];
        count[0] = 1;
        count[1] = 2;
        if(number < 1)
            return 0;
        for(int i=2; i<number; i++)
            count[i] = count[i-1]+count[i-2];
        return count[number-1];
    }
};


int main()
{
    Solution a;
    int number = 3;
    cout<<a.jumpFloor(number)<<endl;
    return 0;
}

// f(n) = f(n-1) + f(n-2)
// f(1) = 1; f(2) = 2.
~~~

~~~C++
//优化
class Solution {
public:
    int jumpFloor(int number)
    {
        int pre1 = 1, pre2 = 2;
        int temp = pre2;
        if(number < 3)
            return number;
        for(int i=3; i<=number; i++)
        {
            temp = pre2;
            pre2 += pre1;
            pre1 = temp;
        }
        return pre2;
    }
};
~~~

