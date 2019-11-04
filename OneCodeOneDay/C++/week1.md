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

leetcode 周赛题目
> 首先，给你一个初始数组 arr。然后，每天你都要根据前一天的数组生成一个新的数组。  
    第 i 天所生成的数组，是由你对第 i-1 天的数组进行如下操作所得的：  
    假如一个元素小于它的左右邻居，那么该元素自增 1。
    假如一个元素大于它的左右邻居，那么该元素自减 1。
    首、尾元素 永不改变。  
    过些时日，你会发现数组将会不再发生变化，请返回最终所得到的数组。  
    示例 1：  
    输入：[6,2,3,4]  
    输出：[6,3,3,4]  
    解释：第一天，数组从 [6,2,3,4] 变为 [6,3,3,4]。
    无法再对该数组进行更多操作。  
    示例 2：  
    输入：[1,6,3,4,3,5]  
    输出：[1,4,4,4,4,5]  
    解释：第一天，数组从 [1,6,3,4,3,5] 变为 [1,5,4,3,4,5]。
    第二天，数组从 [1,5,4,3,4,5] 变为 [1,4,4,4,4,5]。
    无法再对该数组进行更多操作。

~~~C++
#include <iostream>
#include<vector>
using namespace std;

class Solution
{
public:
    vector<int> transformArray(vector<int>& arr)
    {
        vector<int> newarr;
        newarr.assign(arr.begin(),arr.end());
        int len = arr.size();
        bool isFinal = true;
        while(1)
        {
            arr.assign(newarr.begin(), newarr.end());
            for(int i=1; i<len-1; i++)
            {
                if(newarr[i]<arr[i-1] && newarr[i]<arr[i+1])
                {
                    newarr[i]++;
                    isFinal = false;
                }
                else if(newarr[i]>arr[i-1] && newarr[i]>arr[i+1])
                {
                    newarr[i]--;
                    isFinal = false;
                }
            }
            if(isFinal)
                break;
            else
                isFinal = true;
        }
        return arr;
    }
};

int main()
{
    vector<int> arr;
    arr.push_back(2);
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(1);
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(2);
    arr.push_back(1);
    for(int i=0; i<arr.size(); i++)
        cout<<arr[i]<<" ";
    cout<<endl;

    Solution a;
    vector<int> result = a.transformArray(arr);
    for(int i=0; i<result.size(); i++)
        cout<<result[i]<<" ";
    return 0;
}
~~~
> 审题很重要！！！   
> 一开始只对当前数组进行判别，导致错误；需要判别的对象是前一次得到的数组。 
>> 第 i 天所生成的数组，是由你对第 i-1 天的数组进行操作所得的。  

*注意：* vector 初始化方法；C++98中只能用构造函数初始化方法，C++11中可采用 vector<int> arr {1, 2, 3, 4};


# day 4 task 1

leetcode  
有两个长度相同的字符串 s1 和 s2，且它们其中 只含有 字符 "x" 和 "y"，你需要通过「交换字符」的方式使这两个字符串相同。  
每次「交换字符」的时候，你都可以在两个字符串中各选一个字符进行交换。  
交换只能发生在两个不同的字符串之间，绝对不能发生在同一个字符串内部。也就是说，我们可以交换 s1[i] 和 s2[j]，但不能交换 s1[i] 和 s1[j]。  
最后，请你返回使 s1 和 s2 相同的最小交换次数，如果没有方法能够使得这两个字符串相同，则返回 -1 。  
条件：1 <= s1.length, s2.length <= 1000; s1, s2 只包含 'x' 或 'y'。

~~~C++
#include <iostream>
using namespace std;

class Solution {
public:
    int minimumSwap(string s1, string s2)
    {
        int totalNum, xNum, sameNum, diffXNum, diffYNum, step;
        totalNum= xNum= sameNum= diffXNum= diffYNum= step = 0;
        int j=0;
        while(s1[j++] != '\0')
            totalNum++;
        for(int i=0; i<totalNum; i++)
        {
            if(s1[i]=='x')
                xNum++;
            if(s2[i]=='x')
                xNum++;
        }
        if(xNum%2)
            return -1;
        for(int i=0; i<totalNum; i++)
        {
            if(s1[i]==s2[i])
                sameNum++;
            else if(s1[i]=='x')
                diffXNum++;
        }
        diffYNum = totalNum - sameNum - diffXNum;
        step = diffYNum/2 + diffXNum/2 + diffXNum%2 * 2;
        return step;
    }
};

int main()
{
    string s1 = "xxyyxyxyxx";
    string s2 = "xyyxyxxxyx";
    Solution a;
    cout<<a.minimumSwap(s1,s2);
    return 0;
}

//分析问题的不同情况，得到求解的方法。
//1.是否能变换到相同。即x和y的个数必须是偶数。由于两个字符串长度相同，总长度为偶数，所以判断其中一个为偶数就可保证可变换到相同。
//2.除去目前已经相同的字符，剩余的字符会是如下2种情况的组合：
//  i.“xx”和“yy”：这种情况需要变换1次xx->xy,yy->xy;
//  ii."xy"和"yx":这种情况需要变换2次xy->xx->xy,yy->yy->xy。
~~~

~~~C++
//优化：
class Solution {
public:
    int minimumSwap(string s1, string s2)
    {
        int xDiffNum = 0, yDiffNum = 0;
        int sLen = s1.size();
        for(int i=0; i<sLen; i++)
        {
            if(s1[i] == s2[i])
                continue;
            else
                if(s1[i] == 'x')
                    xDiffNum++;
                else
                    yDiffNum++;
        }
        if((xDiffNum+yDiffNum)%2)
            return -1;
        return xDiffNum/2 + yDiffNum/2 + xDiffNum%2*2;
    }
};
~~~


# day 4 task 2

leetcode  
给你一个整数数组 nums 和一个整数 k。  
如果某个子数组中恰好有 k 个奇数数字，我们就认为这个子数组是「优美子数组」。  
请返回这个数组中「优美子数组」的数目。  
    1 <= nums.length <= 50000  
    1 <= nums[i] <= 10^5  
    1 <= k <= nums.length

~~~C++
#include <iostream>
#include<vector>
using namespace std;

class Solution
{
public:
    int numberOfSubarrays(vector<int>& nums, int k)
    {
        vector<int> oddPosition;
        int totalNum = nums.size();
        int oddNum = 0;
        int arrNum = 0;
        for(int i=0; i<totalNum; i++)
        {
            if(nums[i]%2)
            {
                oddPosition.push_back(i);
                oddNum++;
            }
        }
        if(k > oddNum)
            return 0;
        for(int i=0; i<=oddNum-k; i++)
        {
            if(i == 0)
                if(i==oddNum-k)
                    arrNum += (oddPosition[i]+1)*(totalNum-oddPosition[i+k-1]);
                else
                    arrNum += (oddPosition[i]+1)*(oddPosition[i+k]-oddPosition[i+k-1]);
            else if(i == oddNum-k)
                arrNum += (oddPosition[i]-oddPosition[i-1])*(totalNum-oddPosition[i+k-1]);
            else
                arrNum += (oddPosition[i]-oddPosition[i-1])*(oddPosition[i+k]-oddPosition[i+k-1]);
        }
        return arrNum;
    }
};

int main()
{
    vector<int> nums;
//    int k = 3;
//    nums.push_back(1);
//    nums.push_back(1);
//    nums.push_back(2);
//    nums.push_back(1);
//    nums.push_back(1);

//    int k = 1;
//    nums.push_back(2);
//    nums.push_back(4);
//    nums.push_back(6);

    int k = 2;
    nums.push_back(2);
    nums.push_back(2);
    nums.push_back(2);
    nums.push_back(1);
    nums.push_back(2);
    nums.push_back(2);
    nums.push_back(1);
    nums.push_back(2);
    nums.push_back(2);
    nums.push_back(2);


    Solution a;
    cout<<a.numberOfSubarrays(nums, k);
    return 0;
}

//首先计算奇数的个数，与 k 比较，判断是否存在优美子数组。
//而后，计算优美子数组的个数。
//i.存储奇数所在的数组位置 oddPosition[i]=j，即第i+1个奇数位于数组的第j+1个数；
//ii.分析奇数所在位置对优美子数组数目的计算方法。
//  a.如果总的奇数数目等于k：
//  b.如果总的奇数数目大于k，包含第1个奇数的优美子数组个数，不包含第1个和最后1个奇数的个数包含最后1个奇数的个数。
~~~

~~~C++
class Solution {
  public:
  int numberOfSubarrays(vector<int>& nums, int k) {
    int l = 0, c1 = 0, r = 0, c2 = 0, ret = 0;
    for (int i = 0; i < nums.size(); ++i) 
    {
        if (nums[i] & 1) 
            ++c1, ++c2;
        while (c1 > k)  
            if (nums[l++] & 1) 
                --c1;
        while (c2 >= k)  
            if (nums[r++] & 1) 
                --c2;
        ret += r - l;
    }
    return ret;
  }
};
~~~


# day 4 task 3

leetcode  

~~~C++
#include <iostream>
#include<vector>
using namespace std;

class Solution
{
public:
    string minRemoveToMakeValid(string s)
    {
        vector<char> strVec;
        vector<int> strPos;
        int i=0;
        string newstr="";
        while(s[i] != '\0')
        {
            if(s[i]=='(')
            {
                strVec.push_back(s[i]);
                strPos.push_back(i);
            }
            else if(s[i]==')')
            {
                if(strVec.empty())
                {
                    strVec.push_back(s[i]);
                    strPos.push_back(i);
                }
                else
                {
                    char preChar = strVec[strVec.size()-1];
                    if( preChar == '(')
                    {
                        strVec.pop_back();
                        strPos.pop_back();
                    }
                    else if(preChar == ')')
                    {
                        strVec.push_back(s[i]);
                        strPos.push_back(i);
                    }
                }
            }
            i++;
        }
        i = 0;
        int count = 0;

//      此部分一开始未讨论为空的情况，导致“abc”型的字符串没有输出。
        if(strPos.empty())
            newstr = s;
        else
        {
            while(s[i] != '\0')
            {
                if( i != strPos[count])
                    newstr += s[i];
                else if(count < (strPos.size()-1))
                    count++;
                i++;
            }
        }
        return newstr;
    }
};

int main()
{
//    string s = "a)b(c)d";
//    string s = "lee(t(c)o)de)";
//    string s = "))((";
      string s = "abc";
//    string s = "(a(b(c)d)";
    Solution a;
    cout<<a.minRemoveToMakeValid(s);
    return 0;
}
~~~

# day 4 task 4

leetcode
给你一个正整数数组 nums，你需要从中任选一些子集，然后将子集中每一个数乘以一个 任意整数，并求出他们的和。
假如该和结果为 1，那么原数组就是一个「好数组」，则返回 True；否则请返回 False。
~~~C++
#include <iostream>
#include<vector>
using namespace std;

class Solution
{
public:
    int gcd(int x, int y)
    {
        return y == 0? x : gcd(y, x%y);
    }
    bool isGoodArray(vector<int>& nums)
    {
        int minGcd = nums[0];
        for(auto a:nums)
        {
            minGcd = gcd(minGcd, a);
        }
        return minGcd == 1;
    }
};

int main()
{
    vector<int> nums;
//    nums.push_back(12);
//    nums.push_back(5);
//    nums.push_back(7);
//    nums.push_back(13);
//    nums.push_back(3);
    nums.push_back(6);
    nums.push_back(29);
    nums.push_back(6);
    nums.push_back(10);
    Solution a;
    cout<< a.isGoodArray(nums)<<endl;
    return 0;
}
~~~