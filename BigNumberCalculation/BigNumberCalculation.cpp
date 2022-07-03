//
// Created by c w on 2022/6/30.
//

#include "BigNumberCalculation.h"
#include "MacroStatus.h"

/*比较大小*/
bool BigNumberCalculation::cmp(std::string a, std::string b) {
    if (a.size() < b.size()) //首先比较长度
        return true;         //长度大的肯定大
    if (a.size() > b.size())
        return false;
    return a < b; //若长度相等可直接比较
}

/*进位操作*/
void BigNumberCalculation::Carry(std::string &c, int t) {
    for (; t < c.size(); t++) //遍历寻找大于十的位
    {
        if (c[t] - '0' >= 10) //如果大于十
        {
            int size_s = 0;
            int sum_s = c[t + size_s] - '0'; //该位所代表的数字
            while (sum_s) {
                if (size_s == 0)
                    c[t] = sum_s % 10 + '0'; //当前位
                else
                    c[t + size_s] += sum_s % 10; //后位
                sum_s /= 10;
                size_s++;
            }
        } else
            break;
    }
}

///*大数相加*/
//std::string BigNumberCalculation::Add(std::string a, std::string b) {
//    std::string c(std::max(a.size(), b.size()) + 1, '0'); //初始化结果字符串
//    reverse(a.begin(), a.end());                //反转字符串
//    reverse(b.begin(), b.end());
//    if (a.size() < b.size()) //补零，使两串长度相等
//        a.insert(a.end(), b.size() - a.size(), '0');
//    else if (b.size() < a.size())
//        b.insert(b.end(), a.size() - b.size(), '0');
//    for (int i = 0; i < a.size(); i++) //按位相加
//    {
//        int size = 0;
//        int sum = a[i] - '0' + b[i] - '0';
//        while (sum) {
//            c[i + size] += sum % 10;
//            if (c[i + size] - '0' >= 10)
//                Carry(c, i + size); //进位
//            size++;
//            sum /= 10;
//        }
//    }
//    reverse(c.begin(), c.end());            //反转
//    c = c.substr(c.find_first_not_of('0')); //去除多余的前导零
//    return c;
//}

/*大数相减*/
std::string BigNumberCalculation::Less(std::string a, std::string b) {
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
            for (int j = i + 1; j < a.size(); j++) {
                if (a[j] >= '1') {
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
std::string BigNumberCalculation::Multiply(std::string a, std::string b) {
    if (cmp(a, b)) //保证a > b
        swap(a, b);
    std::string c(a.size() + b.size() + 1, '0');
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    for (int i = 0; i < b.size(); i++) //一串的任一位与另一串的所有位依次相乘
    {
        for (int j = 0; j < a.size(); j++) {
            int size = 0;
            int sum = (b[i] - '0') * (a[j] - '0');
            //int ant = c[i + j] + sum;
            while (sum) {
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
//
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

/*大数相加*/
std::string BigNumberCalculation::Add(std::string a, std::string b) {
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
        while (sum) {
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

/*大除小*/
std::string BigNumberCalculation::Except_A(std::string a, std::string b, int n) {
    std::string c("0"), d = b;
    std::string e;
    std::string s("1");
    while (!cmp(a, d))                    //剪枝，将除数扩大到小于被除数的最大值（每次扩大十倍）
        d.insert(d.end(), '0'), s += '0'; //补零（相当于扩大十倍）
    d.pop_back();                         //根据循环最后会多补一个零，所以再去掉
    s.pop_back();
    while (!cmp(d, b) && d != "") {
        if (!cmp(a, d)) {
            a = Less(a, d); //将除法转化为减法
            c = Add(c, s);  //商增加（利用加法）
            if (a == "0")   //整除，直接跳出
                break;
        } else //否则减小除数的值
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
std::string BigNumberCalculation::Except_B(std::string a, std::string b, int n) {
    int t = -1;
    std::string c("0.");
    if (a == "0") {
        c.insert(c.end(), n, '0');
        return c;
    }
    while (t != n && a != "00") {
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
    if (!cmp(a, b)) {
        while (!cmp(a, b))
            a = Less(a, b);
        return a;
    } else {
        return a;
    }
}

void BigNumberCalculation::DeleteZero(std::string number, std::string &result) {
    result.clear();
    int i;
    for (i = 0; i < number.size(); i++) {
        if (number[i] != '0') {
            break;
        }
    }

    if (i < number.size()) {
        result = number.substr(i, number.size() - i);
    }

    if (result.size() == 0) {
        result.push_back('0');
    }
}

//#include "common/CommonUtils.h"
void BigNumberCalculation::Abs(const std::string *a, std::string *result) {
    if (PositiveOrZero(a)) {
        *result = *a;
        return;
    }

    *result = a->substr(1, a->size() - 1);
}


int BigNumberCalculation::Compare(const std::string *a, const std::string *b) {
    std::string operand1;
    DeleteZero(*a, operand1);

    std::string operand2;
    DeleteZero(*b, operand2);

    if (PositiveOrZero(&operand1) && IsNegative(&operand2)) {
        return 1;
    }
    if (PositiveOrZero(&operand2) && IsNegative(&operand1)) {
        return -1;
    }

    if (PositiveOrZero(&operand1) && PositiveOrZero(&operand2)) {
        if (operand1.size() > operand2.size()) {
            return 1;
        }
        if (operand2.size() > operand1.size()) {
            return -1;
        }
        //fix bug
        //for(int i = operand1.size() - 1; i >= 0; i--){
        for (int i = 0; i < operand1.size(); i++) {
            if (operand1[i] == operand2[i]) {
                continue;
            }
            return operand1[i] - operand2[i];
        }
        return 0;
    }

    if (IsNegative(&operand1) && IsNegative(&operand2)) {
        std::string operand1_abs;
        std::string operand2_abs;
        Abs(&operand1, &operand1_abs), Abs(&operand2, &operand2_abs);
        return -PositiveOrZeroCompare(operand1_abs, operand2_abs);
    }
}

int BigNumberCalculation::PositiveOrZeroCompare(std::string operand1, std::string operand2) {
    if (operand1.size() > operand2.size()) {
        return 1;
    }
    if (operand2.size() > operand1.size()) {
        return -1;
    }
    for (int i = operand1.size() - 1; i >= 0; i--) {
        if (operand1[i] == operand2[i]) {
            continue;
        }
        return operand1[i] - operand2[i];
    }
    return 0;
}

bool BigNumberCalculation::PositiveOrZero(const std::string *basicString) {
    return !IsNegative(basicString);
}

bool BigNumberCalculation::IsNegative(const std::string *basicString) {
    if ((*basicString)[0] == '-') {
        return true;
    }
    return false;
}

void BigNumberCalculation::PositiveAdd(const std::string *a, const std::string *b, std::string *c) {

    int max_len = std::max(a->size(), b->size()) + 1;

    std::string operand1, operand2;
    operand1 = *a;
    operand2 = *b;

    c->clear();
    reverse(operand1.begin(), operand1.end());
    reverse(operand2.begin(), operand2.end());

    while (operand1.size() < max_len) {
        operand1.push_back('0');
    }
    while (operand2.size() < max_len) {
        operand2.push_back('0');
    }

    auto *carries = new SingleInt[max_len];
    memset(carries, 0, max_len);

    for (int i = 0; i < operand1.size(); i++) //按位相加
    {
        int sum = 0;

        sum = operand1[i] - '0' + operand2[i] - '0' + carries[i];

        c->push_back(sum % 10 + '0');

        int carry = sum / 10;

        carries[i + 1] = carry;
    }

    for (int i = c->size() - 1; (*c)[i] == '0'; i--) {
        c->erase(i);
    }

    if (c->size() == 0) {
        *c = std::string("0");
    } else {
        reverse(c->begin(), c->end());
    }

    return;
}

void BigNumberCalculation::PositiveSub(std::string a, std::string b, std::string &c) {
    c.clear();

    bool take_opposite = false;
    if (Compare(&a, &b) < 0) {
        take_opposite = true;
    }

    std::string a_abs, b_abs;
    Abs(&a, &a_abs);
    Abs(&b, &b_abs);

    if (Compare(&a, &b) == 0) {
        c.push_back('0');
        return;
    }

    std::string big_positive, small_positive;

    big_positive = Compare(&a_abs, &b_abs) > 0 ? a_abs : b_abs;
    small_positive = Compare(&a_abs, &b_abs) < 0 ? a_abs : b_abs;

    int max_len = std::max(a.size(), b.size());
    reverse(big_positive.begin(), big_positive.end());
    reverse(small_positive.begin(), small_positive.end());

    while (big_positive.size() < max_len) {
        big_positive.push_back('0');
    }
    while (small_positive.size() < max_len) {
        small_positive.push_back('0');
    }

    unsigned char *borrows = new unsigned char[max_len];
    memset(borrows, 0, max_len);

    for (int i = 0; i < big_positive.size(); i++) {
        int sub = 0;


        sub = big_positive[i] - '0' - borrows[i] - (small_positive[i] - '0');

        if (sub < 0) {
            borrows[i + 1]++;
            sub += 10;
        }

        c.push_back(sub + '0');

        //int size = 0;
        //int sum = a[i] - '0' + b[i] - '0';
        //while (sum) {
        //    c[i + size] += sum % 10;
        //    if (c[i + size] - '0' >= 10)
        //        Carry(c, i + size); //进位
        //    size++;
        //    sum /= 10;
        //}
    }

    //for (int i = c->size() - 1; (*c)[i] == '0'; i--) {
    //    c->erase(i);
    //}
    //
    //if (c->size() == 0) {
    //    *c = std::string("0");
    //} else {
    //    reverse(c->begin(), c->end());
    //}

    reverse(c.begin(), c.end());

    std::string result;
    DeleteZero(c, result);
    c = result;

    if (take_opposite) {
        c.insert(c.begin(), '-');
    }
    return;
}

void BigNumberCalculation::Add(const std::string *a, const std::string *b, std::string *c) {
    c->clear();
    if (PositiveOrZero(a) && PositiveOrZero(b)) {
        PositiveAdd(a, b, c);
        return;
    }

    if (PositiveOrZero(a) && !PositiveOrZero(b) ||
        PositiveOrZero(b) && !PositiveOrZero(a)
            ) {
        std::string positive, negative;
        positive = PositiveOrZero(a) ? *a : *b;
        negative = IsNegative(a) ? *a : *b;
        std::string negative_abs;
        Abs(&negative, &negative_abs);
        PositiveSub(positive, negative_abs, *c);

        return;
    }

    std::string a_abs, b_abs;
    Abs(a, &a_abs);
    Abs(b, &b_abs);

    PositiveAdd(&a_abs, &b_abs, c);

    std::string result;
    Opposite(c, &result);
    *c = result;
}


void BigNumberCalculation::Opposite(const std::string *original, std::string *opposite) {
    if (Positive(original)) {
        *opposite = std::string("-") + *original;
        return;
    }

    if (Zero(original)) {
        *opposite = std::string("0");
        return;
    }

    *opposite = original->substr(1, original->size() - 1);

}

bool BigNumberCalculation::Positive(const std::string *a) {
    if (Zero(a)) {
        return false;
    }

    if (IsNegative(a)) {
        return false;
    }

    return true;
}

bool BigNumberCalculation::Zero(const std::string *a) {
    if (a->size() == 1 && (*a)[0] == '0') {
        return true;
    }
    return false;
}

void BigNumberCalculation::Sub(const std::string *a, const std::string *b, std::string *c) {

    c->clear();
    std::string a_abs, b_abs;

    Abs(a, &a_abs);
    Abs(b, &b_abs);

    if (PositiveOrZero(a) &&
        PositiveOrZero(b)) {
        PositiveSub(*a, *b, *c);

        return;
    }

    if (PositiveOrZero(a) && IsNegative(b)) {
        PositiveAdd(a, &b_abs, c);
        return;
    }

    if (IsNegative(a) && IsNegative(b)) {
        PositiveSub(b_abs, a_abs, *c);
        return;
    }

    BigNumberCalculation::PositiveAdd(&a_abs, &b_abs, c);

    std::string result;
    Opposite(c, &result);
    *c = std::move(result);

}

void BigNumberCalculation::PositiveMultiply(const std::string *a, const std::string *b, std::string *c) {

    int max_carry_len = a->size() > b->size() ? a->size() + 1 : b->size() + 1;
    std::string operand1 = *a;
    std::string operand2 = *b;

    if (Compare(&operand1, &operand2) < 0) {
        swap(operand1, operand2);
    }

    *c = std::string(operand1.size() + operand2.size() + 1, '0');
    reverse(operand1.begin(), operand1.end());
    reverse(operand2.begin(), operand2.end());


    auto *carries = new SingleInt[max_carry_len];
    auto *each_turn = new Byte[max_carry_len];
    *c = "0";
    for (int i = 0; i < operand2.size(); i++) {
        memset(carries, 0, max_carry_len);
        memset(each_turn, '0', max_carry_len);

        for (int j = 0; j < operand1.size(); j++) {

            int single_multiply_result = (operand2[i] - '0') * (operand1[j] - '0') + carries[j];
            each_turn[j] = single_multiply_result % 10 + '0';
            carries[j + 1] = single_multiply_result / 10;

            if (j == operand1.size() - 1) {
                each_turn[j + 1] = carries[j + 1] + '0';
            }


        }
        std::string this_turn = std::string((const char *) each_turn, max_carry_len);
        for (int k = 0; k < i; k++) {
            this_turn.insert(this_turn.begin(), '0');
        }
        std::reverse(this_turn.begin(), this_turn.end());
        std::string delete_zero;
        DeleteZero(this_turn, delete_zero);
        this_turn = std::move(delete_zero);


        std::string temp_sum;
        BigNumberCalculation::Add(&this_turn, c, &temp_sum);
        *c = temp_sum;
    }
}

void BigNumberCalculation::Multiply(const std::string *a, const std::string *b, std::string *c) {
    c->clear();
    std::string a_abs, b_abs;
    Abs(a, &a_abs);
    Abs(b, &b_abs);
    if (SameSign(a, b)) {
        PositiveMultiply(&a_abs, &b_abs, c);
        return;
    }

    std::string result;
    PositiveMultiply(&a_abs, &b_abs, &result);
    Opposite(&result, c);
    return;
}

bool BigNumberCalculation::SameSign(const std::string *a, const std::string *b) {
    if (IsNegative(a) && IsNegative(b) ||
        PositiveOrZero(a) && PositiveOrZero(b)) {
        return true;
    }
    return false;
}


EN_RV BigNumberCalculation::PositiveDivide(const std::string *a, const std::string *b, std::string *c) {
    c->clear();
    if (Zero(b)) {
        return ENR_DIVIDE_BY_ZERO;
    }

    if (Compare(a, b) < 0) {
        *c = std::string("0");
        return ENR_OK;
    }

    int a_len = a->size();
    int b_len = b->size();

    int turn = a_len - b_len + 1;

    std::string quotient;
    std::string temp_a = a->substr(0, b_len);
    std::string temp_r;
    std::string r;

    for (int i = 0; i < turn; i++) {
        int count = 0;
        std::string sub_result;
        Sub(&temp_a, b, &sub_result);

        while (PositiveOrZero(&sub_result)) {
            count++;
            std::string temp;
            Sub(&temp_a, b, &temp);
            temp_a = temp;
            Sub(&temp_a, b, &sub_result);
        }
        quotient.push_back(count + '0');
        temp_r = temp_a;
        if (i != turn - 1) {
            temp_a = temp_r + (*a)[b_len + i];
        }
    }
    r = temp_r;
    std::string temp;
    DeleteZero(quotient, temp);
    quotient = std::move(temp);
    *c = quotient;
    return ENR_OK;
}

EN_RV BigNumberCalculation::Divide(const std::string *a, const std::string *b, std::string *c) {
    c->clear();
    std::string a_abs, b_abs;
    Abs(a, &a_abs);
    Abs(b, &b_abs);
    EN_RV rv;

    if (SameSign(a, b)) {
        rv = PositiveDivide(&a_abs, &b_abs, c);
        return rv;
    }

    std::string result;
    rv = PositiveDivide(&a_abs, &b_abs, &result);
    if (rv != ENR_DIVIDE_BY_ZERO) {
        Opposite(&result, c);
    }
    return rv;
}