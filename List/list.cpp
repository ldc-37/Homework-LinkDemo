// Chain.cpp: 定义控制台应用程序的入口点。
//

#include "list.h"

using namespace std;
int main()
{
    Date * head = InitList ();
    //

    //
    while (1) {
        ShowCopyright ();
        ShowTime ();
        cout << "当前节点数量：" << NodeNum (head) << endl;
        UserInterface ();
        char keyPress = GetOption (head);
        switch (keyPress)
        {
        case 'C':CreateListRandom (head); break;
        case 'O':PrintList (head); break;
        case 'D':DeleteNode (head); break;
        case 'N':ShowIllegalNode (head); break;
        case 'T':ShowTotalDays (head); break;
        case 'P':PrimeNumberNode (head); break;


        case 'Z':FreeList (head); break;//test use
        default:cout << "选择错误，请重新选择......" << endl; break;
        }
        cout << endl;
        system ("pause");
        system ("cls");
    }
        
    return 0;
}

void ShowCopyright ()
{
    cout << "Copyright (c) 2017-2018 李定成(221701331). All Rights Reserved." << endl << endl;
}

void ShowTime ()
{
    time_t now = time (0);
    struct tm nowTime;
    localtime_s (&nowTime,&now);
    int hour = nowTime.tm_hour;
    int min = nowTime.tm_min;
    int sec = nowTime.tm_sec;
    int year = 1900 + nowTime.tm_year;
    int month = 1 + nowTime.tm_mon;
    int day = nowTime.tm_mday;
    int weekNum = nowTime.tm_wday;
    const char *weekChn[] = { "星期日", "星期一", "星期二", "星期三", "星期四", "星期五", "星期六" };
    const char *week = weekChn[weekNum];

    cout << "当前日期、时间：" << year << '.' << month << '.' << day << '(' << week << ") " << hour << ':' << min << ':' << sec << endl;

}

void UserInterface ()
{
    cout << "****************************************************************" << endl <<
        "*    C : 创建一个存放日期数据的 (无序)链表                     *" << endl <<
        "*    O : 显示链表前几个结点的日期数据                          *" << endl <<
        "*    S : 将整个链表的所有数据存入文件中                        *" << endl <<
        "*    X : 分屏显示日期数据文件的 (全部)内容                     *" << endl <<
        "*    N : 显示不能构成合法日期的 (所有)结点                     *" << endl <<
        "*    D : 删除链表的第一个、最后一个、不能构成合法日期的结点    *" << endl <<
        "*    I : 插入结点 (至链头、链尾、结点之前、结点之后)           *" << endl <<
        "*    T : 显示结点的日期对应的天数                              *" << endl <<
        "*    A : 链表按日期从小到大排序                                *" << endl <<
        "*    P : 查找链表中\"年月日\"都是素数的结点                      *" << endl <<
        "*    F : (单向)链表翻转                                        *" << endl <<
        "*    Q : 退出系统                                              *" << endl <<
        "****************************************************************" << endl <<
        "请选择 (C, O, S, X, N, D, I, T, A, P, F, Q) : ";
}

char GetOption (Date * head)
{
    char key;
    while (1) {
        if (_kbhit ()) {
            key = _getch ();
            if (key == 'q' || key == 'Q') {
                FreeList (head);
                exit (0);
            }
            else if (key >='a' && key <= 'z' || key >= 'A' && key <= 'Z'){
                if (key >= 'a' && key <= 'z') {
                    key -= 32;
                }
                cout << key << endl;
                return key;
                break;
            }
        }
    }
}

bool GetOptionYN () {
    char key;
    while (1) {
        if (_kbhit ()) {
            key = _getch ();
            if (key == 'y' || key == 'Y') {
                return true;
            }
            else if (key == 'n' || key == 'N') {
                return false;
            }
            else {
                cout << endl << "请输入正确选项(y/n)" << endl;
            }
        }
    }
}

Date * InitList ()
{
    Date * head = (Date*)malloc (sizeof (Date));
    head->next = NULL;
    return head;
}

Date * CreateListRandom (Date * head)
{
    FreeList (head);
    cout << "正在生成……" << endl;
    Date * p;
    srand ((unsigned int)(time (NULL)));
    for (int i = 0; i < INIT_NODE_NUM; ++i) {
        p = (Date*)malloc (sizeof (Date));
        if (p == NULL) {
            cout << "ERROR:申请内存空间失败！" << endl;
            return NULL;
        }
        p->year = MIN_YEAR + rand () % (MAX_YEAR - MIN_YEAR + 1);
        p->month = 1 + rand () % MONTH_NUM;
        p->day = 1 + rand () % DAY_NUM;
        p->next = head->next;
        head->next = p;
    }
    cout << "生成"<< INIT_NODE_NUM << "个日期节点完毕！" << endl;
    return head;
}

void PrintList (Date * head)
{
    if (IsEmptyLink (head)) {
        return;
    }
    int num;
    int nodeNum = NodeNum (head);
    bool legal;
    do {
        cout << "请输入要查看的节点数量,输入0为全部：";
        cin >> num;
        if (num == 0) {
            num = nodeNum;
        }
        legal = num > 0 && num <= nodeNum;
        if (!legal) {
            cout << "非法输入，请重新输入" << endl;
            cin.clear ();
            cin.ignore (1024,'\n');
        }
    } while (!legal);
    Date * p = head->next;
    for (int i = 0; i < num; ++i) {
        cout << p->year << '-' << p->month << '-' << p->day << '\t';
        p = p->next;
        if (i % 6 == 5) {
            cout << endl;
        }
    }
}

void ShowIllegalNode (Date * head)
{
    if (IsEmptyLink (head)) {
        return;
    }
    Date * p = head->next;
    int i = 0;
    cout << "不合法的日期如下：" << endl;
    do
    {
        if (IsIllegalDate (p)) {
            cout << p->year << '-' << p->month << '-' << p->day << '\t';
            if (++i % 6 == 0) {
                cout << endl;
            }
        }
        p = p->next;
    } while (p != NULL);
    if (i == 0) {
        cout << "没有不合法日期或不合法日期已被删除" << endl;
    }
}

void DeleteNode (Date * head)
{
    if (IsEmptyLink (head)) {
        return;
    }
    Date * first = head->next;
    head->next = head->next->next;
    free (first);
    first = NULL;
    Date * last = head;
    while (last->next->next != NULL) {
        last = last->next;
    }
    free (last->next);
    last->next = NULL;

    Date * pre = head, * p = pre->next;
    int numDeleted = 0;
    while (p != NULL) {
        if (IsIllegalDate (p)) {
            pre->next = p->next;
            free (p);
            p = pre->next;
            numDeleted++;
        }
        else {
            pre = p;
            p = p->next;
        }
    }
    cout << "删除完成！共删除" << 2 + numDeleted << "个节点" << endl;
}

int CountDays (Date * p)
{
    int totalDays = 0;
    for (int i = MIN_YEAR; i < p->year; ++i) {
        IsReapYear (i) ? totalDays += 366 : totalDays += 365;
    }
    for (int i = 0; i < p->month - 1; ++i) {
        totalDays += dayOfMonth[i];
    }
    if (IsReapYear (p->year) && (p->month >= 3 || p->month == 2 && p->day == 29)) {
        totalDays++;
    }
    return totalDays;
}

void ShowTotalDays (Date * head)
{
    if (IsEmptyLink (head)) {
        return;
    }
    int i = 0;
    Date * p = head->next;
    while (p != NULL) {
        cout << CountDays (p) << '\t';
        if (++i % 6 == 0) {
            cout << endl;
        }
        p = p->next;
    }
}

void PrimeNumberNode (Date * head) {
    if (IsEmptyLink (head)) {
        return;
    }
    Date * p = head->next;
    int i = 0;
    while (p != NULL) {
        if (IsPrimeNumber (p->year) && IsPrimeNumber (p->month) && IsPrimeNumber (p->day)) {
            cout << p->year << '-' << p->month << '-' << p->day << '\t';
            if (++i % 6 == 0) {
                cout << endl;
            }
        }
        p = p->next;
    }
}



void FreeList (Date * head)
{
    Date * pre = head->next, * next;
    if (pre != NULL) {
        next = pre->next;
        while (next != NULL) {
            free (pre);
            pre = next;
            next = pre->next;
        }
        free (pre);
    }
    head->next = NULL;
    cout << "已清空链表！" << endl;
}



//Judge
bool IsReapYear (int year)
{
    return (year % 4 == 0 && year % 100 != 0 || year % 400 == 0 ? true : false);
}

bool IsIllegalDate (Date * p)
{
    if (IsReapYear (p->year) && p->month == 2) {
        return (p->day > 29 ? true : false);
    }
    else {
        return (p->day > dayOfMonth[p->month - 1] ? true : false);
    }
}

bool IsPrimeNumber (int n)
{
    for (int i = 2; i <= sqrt (n); ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

//Common
bool IsEmptyLink (Date * head)
{
    if (head->next == NULL) {
        cout << "ERROR:链表为空，是否建立链表？(y/n)：" << endl;
        if (GetOptionYN ()) {
            CreateListRandom (head);
        }
        else {
            cout << "无法对空链表操作！" << endl;
            return true;
        }
    }
    return false;
}

int NodeNum (Date * head)
{
    int totalNum = 1;
    Date * p;
    p = head->next;
    if (p == NULL) {
        return 0;
    }
    while (p->next != NULL) {
        totalNum += 1;
        p = p->next;
    }
    return totalNum;
}


