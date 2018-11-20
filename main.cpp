#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int
main ()
{
    cout << "working......" << endl;
    char ch;                                //目前正在判断的字符
    int n = 0;                              //修正单个字符和单个字节的差异（应该是这个样子，不是太懂，如果不设计这个n的话，就会向文件中输入多个换行）
    bool flag = true;                       //如果需要向文件中写入数据，则flag为true
    int equalTimes = 0;                     //每一行等号出现的次数

    ifstream inStream;
    ofstream outStream;

    inStream.open ("text1.txt");            //打开从QQ拼音导出的词库文本文件
    if (inStream.fail ())
    {
        cout << "input file opening failed." << endl;
        exit (1);
    }

    outStream.open ("text2.txt");           //打开目标文件，也就是最终可以被ibus使用的词库文件
    if (outStream.fail ())
    {
        cout << "output file opening failed." << endl;
        exit (1);
    }

    while (inStream.get (ch))                //读入字符
    {
        if (ch == '=')                       //遇到等号，使equalTimes加一
            equalTimes ++ ;
        if (equalTimes == 2)                 //equalTimes为2时，不再向文件中输入本行的其他字符
        {
            n ++ ;
            flag = false;
            if (n == 1)
            {
                outStream.put ('\n');
            }
        }
        if (flag == true)					
            outStream.put (ch);
        if (ch == '\n')                      //遇到一行的换行符，将要到下一行读取数据，将相关数据设定到初始值
        {
            flag = true;
            equalTimes = 0;
            n = 0;
        }
    }

    inStream.close ();                      //关闭文件
    outStream.close ();

    cout << "done." << endl;
    return 0;
}
