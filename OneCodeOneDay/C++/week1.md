# day 1 task 1: 

Fibnacci(n)

~~~C++
class Solution {
public:
    int Fibonacci(int n) {

        /* Method 1:时间O(n)，空间O（n）
        int result = 0;
        int fib[n];
        for(int i=0; i<=n; i++)
        {
            if(i<2)
                fib[i] = i;
            else
                fib[i] = fib[i-1] + fib[i-2];
        }
        return fib[n];
        */

        //Method 2:时间O(n)，空间O（1）
        int a = 0;
        int b = 1;
        while(n-->0)
        {
            b += a;
            a = b - a;
        }
        return a;
    }
};
~~~



# day 1 task 2:

把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。  
输入一个非递减排序的数组的一个旋转，输出旋转数组的最小元素。  
例如数组{3,4,5,1,2}为{1,2,3,4,5}的一个旋转，该数组的最小值为1。  
NOTE：给出的所有元素都大于0，若数组大小为0，请返回0。

~~~C++
class Solution {
public:
    int minNumberInRotateArray(vector<int> rotateArray) 
    {
        /* method 1: 时间O(n),空间O(1)
        int n = rotateArray.size();
        if(n==0)
            return 0;
        int minvalue = rotateArray[0];
        for(int i=1; i<n; i++)
        {
            if(minvalue > rotateArray[i])
                minvalue = rotateArray[i];
        }
        return minvalue;
        */
        
        /* method 2: 时间O(n),空间O(1)
        int n = rotateArray.size();
        if(n==0)
            return 0;
        for(int i=1; i<n; i++)
            if(rotateArray[i-1] > rotateArray[i])
                return rotateArray[i];
        return rotateArray[0];
        */
        
        //method 3:时间O(logn),空间O(1)
        int n = rotateArray.size();
        if(n==0)
            return 0;
        int low = 0;
        int high = n - 1;
        int mid = 0;
        while(low < high){
            if (rotateArray[low] < rotateArray[high])
                return rotateArray[low];
            mid = low + (high - low) / 2;
            if(rotateArray[mid] > rotateArray[low])
                low = mid + 1;
            else if(rotateArray[mid] < rotateArray[high])
                high = mid;
            else low++;
        }
        return rotateArray[low];
    }
};
~~~



# day 2 task 1:

给定一个double类型的浮点数base和int类型的整数exponent, 求base的exponent次方。  
保证base和exponent不同时为0

~~~C++
class Solution {
public:
    double Power(double base, int exponent) {
        //method 1
        /*
        if(exponent == 1 || base == 0)
            return base;
        if(exponent == -1)
            return 1/base;
        if(exponent == 0)
            return 1;
        double p1 = Power(base, exponent/2);
        double p2 = Power(base, exponent - (exponent/2)*2);
        return p1*p1*p2;
        */

        //method 2: 快速幂方法
        if(base == 0)
            return 0;
        double ans = 1;
        int e = exponent>0 ? exponent: (-1 * exponent);
        while(e > 0)
        {
            if(e & 1 != 0)
                ans *= base;
            base *= base;
            e >>= 1;
        }
        return exponent>0 ? ans: 1.0/ans;
    }
};
~~~


# day 2 task 2:

输入一个整数，输出该数二进制表示中1的个数。其中负数用补码表示。

> 机器数：一个数在计算机中的二进制表示形式。  
机器数是带符号的，在计算机用一个数的最高位存放符号, 正数为0, 负数为1。  
十进制：+3 ，计算机字长为8位，转换成二进制就是00000011；-3 就是 10000011。

> 真值：将带符号位的机器数对应的真正数值称为机器数的真值。因为第一位是符号位，所以机器数的形式值就不等于真正的数值。  
0000 0001的真值 = +000 0001 = +1，1000 0001的真值 = –000 0001 = –1。

> 原码：符号位加上真值的绝对值, 即用第一位表示符号, 其余位表示值。  
[+1]原 = 0000 0001  
[-1]原 = 1000 0001

> 反码：正数的反码是其本身；负数的反码是在其原码的基础上, 符号位不变，其余各个位取反。  
[+1] = [00000001]原 = [00000001]反  
[-1] = [10000001]原 = [11111110]反

> 补码：正数的补码就是其本身；负数的补码是在其原码的基础上, 符号位不变, 其余各位取反, 最后+1. (即在反码的基础上+1)。  
[+1] = [00000001]原 = [00000001]反 = [00000001]补  
[-1] = [10000001]原 = [11111110]反 = [11111111]补

~~~C++
class Solution {
public:
     int  NumberOf1(int n) {
         
         //wrong: 负数时，n右移位，左边以1补，陷入死循环。
         /*
         int num=0;
         while(n != 0)
         {
             if((n & 1) != 0)
                 num++;
             n >>= 1;
         }
         return num;
         */
         
         
         //method 1
         /*
         int num=0;
         int flag=1;
         while(flag != 0)
         {
             if((n & flag) != 0)
                 num++;
             flag <<= 1;
         }
         return num;
         */
         
         //method 2
        int count = 0;
        while (n != 0)
        {
            ++count;
            n = (n - 1) & n; //***
        }
        return count;
     }
};
~~~


# day 3 task 1

输入一个链表，按链表从尾到头的顺序返回一个ArrayList。


~~~C++
// 遍历链表，将各个节点值依次存入vector中，再将vector逆序。
// vector.push_back(value);
#include <iostream>
#include<vector>
using namespace std;

struct ListNode
{
      int val;
      struct ListNode *next;
      ListNode(int x) :
            val(x), next(NULL) {
      }
};

class Solution
{
public:
    vector<int> printListFromTailToHead(ListNode* head)
    {
        vector<int> ArrayList;
        ListNode* curNode = head;
        while(curNode != NULL)
        {
            ArrayList.push_back(curNode->val);
            curNode = curNode->next;
        }
        int arrayLen = ArrayList.size();
        for(int i=0; i<arrayLen/2; i++)
        {
            int temp = ArrayList[i];
            ArrayList[i] = ArrayList[arrayLen-1-i];
            ArrayList[arrayLen-1-i] = temp;
        }
        return ArrayList;
    }
};

int main()
{
    ListNode* head = new ListNode(1);
    ListNode* second = new ListNode(2);
    ListNode* third = new ListNode(3);
    ListNode* four = new ListNode(4);
    head->next = second;
    second->next = third;
    third->next = four;

    Solution a;
    vector<int> arralist = a.printListFromTailToHead(head);
    for(int i=0; i<arralist.size();i++)
        cout << arralist[i] << " ";
    return 0;
}
~~~

~~~C++
//遍历链表，依次将节点的值放在vector头部。
// vector.insert(position, value);
class Solution
{
public:
    vector<int> printListFromTailToHead(ListNode* head)
    {
        vector<int> ArrayList;
        ListNode* curNode = head;
        while(curNode != NULL)
        {
            ArrayList.insert(ArrayList.begin(), curNode->val);
            curNode = curNode->next;
        }
        return ArrayList;
    }
};
~~~

# day 3 task 2

