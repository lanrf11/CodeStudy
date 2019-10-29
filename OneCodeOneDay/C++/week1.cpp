//day 1 task 1: Fibnacci(n)

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



//day 1 task 2:
/*
把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。
输入一个非递减排序的数组的一个旋转，输出旋转数组的最小元素。
例如数组{3,4,5,1,2}为{1,2,3,4,5}的一个旋转，该数组的最小值为1。
NOTE：给出的所有元素都大于0，若数组大小为0，请返回0。
*/
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

//day 2 task 1:
/*
给定一个double类型的浮点数base和int类型的整数exponent。求base的exponent次方。
保证base和exponent不同时为0
*/
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


