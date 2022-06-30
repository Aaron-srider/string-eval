//
// Created by c w on 2022/6/30.
//

#ifndef REVERSE_POLISH_NOTATION_BIGNUMBERCALCULATION_H
#define REVERSE_POLISH_NOTATION_BIGNUMBERCALCULATION_H

#include "iostream"
//using namespace std;

class BigNumberCalculation
{
public:
    BigNumberCalculation() {}                                  //默认构造函数
    bool cmp(std::string a, std::string b);                   //比较两个“数字”的大小
    void Carry(std::string &c, int t);                   //进位操作，当某一位超过十是使用此函数进位
    std::string Add(std::string a, std::string b);                 //大数加法
    std::string Less(std::string a, std::string b);                //大数减法
    std::string Multiply(std::string a, std::string b);            //大数乘法
    std::string Except_Judge(std::string a, std::string b, int n); //大数除法模式选择（大数小或小除大）
    std::string Except_A(std::string a, std::string b, int n);     //大除小
    std::string Except_B(std::string a, std::string b, int n);     //小除大高精度除法，其中n为自定义的小数位数
    std::string Module(std::string a, std::string b);              //大数求模
};

/*比较大小*/
bool BigNumberCalculation::cmp(std::string a, std::string b)
{
    if (a.size() < b.size()) //首先比较长度
        return true;         //长度大的肯定大
    if (a.size() > b.size())
        return false;
    return a < b; //若长度相等可直接比较
}

/*进位操作*/
void BigNumberCalculation::Carry(std::string &c, int t)
{
    for (; t < c.size(); t++) //遍历寻找大于十的位
    {
        if (c[t] - '0' >= 10) //如果大于十
        {
            int size_s = 0;
            int sum_s = c[t + size_s] - '0'; //该位所代表的数字
            while (sum_s)
            {
                if (size_s == 0)
                    c[t] = sum_s % 10 + '0'; //当前位
                else
                    c[t + size_s] += sum_s % 10; //后位
                sum_s /= 10;
                size_s++;
            }
        }
        else
            break;
    }
}

/*大数相加*/
std::string BigNumberCalculation::Add(std::string a, std::string b)
{
    std::string c(std::max(a.size(), b.size()) + 1, '0'); //初始化结果字符串
    reverse(a.begin(), a.end());                //反转字符串
    reverse(b.begin(), b.end());
    if (a.size() < b.size()) //补零，使两串长度相等
        a.insert(a.end(), b.size() - a.size(), '0');
    else if (b.size() < a.size())
        b.insert(b.end(), a.size() - b.size(), '0');
    for (int i = 0; i < a.size(); i++) //按位相加
    {
        int size = 0;
        int sum = a[i] - '0' + b[i] - '0';
        while (sum)
        {
            c[i + size] += sum % 10;
            if (c[i + size] - '0' >= 10)
                Carry(c, i + size); //进位
            size++;
            sum /= 10;
        }
    }
    reverse(c.begin(), c.end());            //反转
    c = c.substr(c.find_first_not_of('0')); //去除多余的前导零
    return c;
}

/*大数相减*/
std::string BigNumberCalculation::Less(std::string a, std::string b)
{
    if (a == b) //剪枝，如果相等直接返回零
        return "0";
    bool flag = false;
    std::string c(std::max(a.size(), b.size()) + 1, '0');
    if (cmp(a, b)) //始终保持a > b，并记录初始a，b的关系以便确定结果的符号
    {
        swap(a, b);
        flag = true;
    }
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    b.insert(b.end(), a.size() - b.size(), '0');
    for (int i = 0; i < a.size(); i++) //按位相减
    {
        if (a[i] < b[i]) //不够则借数，想象一些列竖式做减法
        {
            for (int j = i + 1; j < a.size(); j++)
            {
                if (a[j] >= '1')
                {
                    a[j] -= 1;
                    for (int t = j - 1; t > i; t--)
                        a[t] = '9';
                    a[i] += 10;
                    break;
                }
            }
        }
        c[i] += a[i] - b[i];
    }
    reverse(c.begin(), c.end());
    c = c.substr(c.find_first_not_of('0'));
    if (flag) //如果，a小于b，在结果串的前面加负号
        c.insert(c.begin(), '-');
    return c;
}

/*大数相乘*/
std::string BigNumberCalculation::Multiply(std::string a, std::string b)
{
    if (cmp(a, b)) //保证a > b
        swap(a, b);
    std::string c(a.size() + b.size() + 1, '0');
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    for (int i = 0; i < b.size(); i++) //一串的任一位与另一串的所有位依次相乘
    {
        for (int j = 0; j < a.size(); j++)
        {
            int size = 0;
            int sum = (b[i] - '0') * (a[j] - '0');
            //int ant = c[i + j] + sum;
            while (sum)
            {
                c[i + j + size] += sum % 10;
                if (c[i + j + size] - '0' >= 10) //进位
                    Carry(c, i + j + size);
                size++;
                sum /= 10;
            }
        }
    }
    reverse(c.begin(), c.end());
    c = c.substr(c.find_first_not_of('0'));
    return c;
}

/*大数相除判断*/
std::string BigNumberCalculation::Except_Judge(std::string a, std::string b, int n) //用来判断是大除小还是小除大
{
    if (a[0] == 0)
        return "0";
    if (b[0] == 0)
        return "ERROR";
    if (a == b)
        return "1";
    if (cmp(a, b))
        return Except_B(a, b, n);
    else
        return Except_A(a, b, n);
}

/*大除小*/
std::string BigNumberCalculation::Except_A(std::string a, std::string b, int n)
{
    std::string c("0"), d = b;
    std::string e;
    std::string s("1");
    while (!cmp(a, d))                    //剪枝，将除数扩大到小于被除数的最大值（每次扩大十倍）
        d.insert(d.end(), '0'), s += '0'; //补零（相当于扩大十倍）
    d.pop_back();                         //根据循环最后会多补一个零，所以再去掉
    s.pop_back();
    while (!cmp(d, b) && d != "")
    {
        if (!cmp(a, d))
        {
            a = Less(a, d); //将除法转化为减法
            c = Add(c, s);  //商增加（利用加法）
            if (a == "0")   //整除，直接跳出
                break;
        }
        else //否则减小除数的值
        {
            d.pop_back();
            s.pop_back();
        }
    }
    if (n) //如果有小数位要求，将余数和除数作为被除数与除数进行小除大的运算
    {
        e = Except_B(a, b, n);
        e.erase(e.begin()); //最后返回的字符串形式为“0.xxxxxxxx”，此操作将消去小数点前的零
        c += e;             //两串相加
    }
    return c;
}

/*小除大*/
std::string BigNumberCalculation::Except_B(std::string a, std::string b, int n)
{
    int t = -1;
    std::string c("0.");
    if (a == "0")
    {
        c.insert(c.end(), n, '0');
        return c;
    }
    while (t != n && a != "00")
    {
        int l = 0;
        if (cmp(a, b)) //补零，相当于除法中不够除时添加零
        {
            a += '0';
            if (t >= 0)
                c += '0';
            t++;
        }
        //if (t > 0) c += '0';
        //t++;
        while (!cmp(a, b)) //转化为减法
        {
            a = Less(a, b);
            l++;
        }
        if (l != 0) //如果有商
        {
            a += '0';     //补零
            c += '0' + l; //结果串加商
            t++;          //位数加一
        }
    }
    if (c.size() - 2 < n)                           //如果不能得到需要的位数，例如1/2 = 0.5，要求三位小数的话达不到
        c.insert(c.end(), n - (c.size() - 2), '0'); //在末尾补零
    return c;
}

/*求模*/
std::string BigNumberCalculation::Module(std::string a, std::string b) //很简单，利用减法循环相减，不能减了剩下的就是余数
{
    if (!cmp(a, b))
    {
        while (!cmp(a, b))
            a = Less(a, b);
        return a;
    }
    else
    {
        return a;
    }
}

int main(int argc, char *argv[])
{
    std::string str1, str2;
    char a;
    int n = 0;
    while (true)
    {
        std::cin >> str1;
        std::cin >> a;
        std::cin >> str2;
        if (a == '/')
            std::cin >> n;
        BigNumberCalculation demo;
        switch (a)
        {
            case '+':

                std::cout << "相加等于：" << std::endl
                     << demo.Add(str1, str2) << std::endl;
                break;
            case '-':
                std::cout << "相减等于：" << std::endl
                     << demo.Less(str1, str2) << std::endl;
                break;
            case '*':
                std::cout << "相乘等于：" << std::endl
                     << demo.Multiply(str1, str2) << std::endl;
                break;
            case '/':
                std::cout << "相除等于：" << std::endl
                     << demo.Except_Judge(str1, str2, n);
                break;
            case '%':
                std::cout << "求模等于：" << std::endl
                     << demo.Module(str1, str2) << std::endl;
                break;
            default:
                break;
        }
    }
    system("pause");
    return 0;
}

#endif //REVERSE_POLISH_NOTATION_BIGNUMBERCALCULATION_H
