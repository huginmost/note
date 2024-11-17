#include <iostream>
using namespace std;


//用法与c大概一致

enum week{
    Monday = 1,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday
};// 若monday未赋值1，则默认从0开始


typedef enum num{num0, num1} _num;
// 若typedef enum num{num0, num1} 则会警告 
//      useless storage class specifier in empty declaration;


enum Season {spring, summer=3, autumn, winter} season;
// spring = 1 summer = 3 autumn = 4 ...
struct Student
{
    int id;
    int age;
}stu;


struct Struct
{
    int a;
    int b;
};

typedef struct Struct _str;
int main(int argc, char const *argv[])
{
    enum week w;
    cout << Sunday << endl;//7
    cout << autumn << endl;//4
    stu.id = 1;
    stu.age = 10;
    Struct s;
    //与c不同的时 这里写 struct Struct 与 Struct 都是可以的
    _str s2;
    s2.a = 11;
    s2.b = 12;
    s.a = 1;
    s.b = 2;
    // printf("id %d; age %d; a %d; b %d\n", stu.id, stu.age, s.a, s.b);
    // //id 1; age 10; a 1; b 2
    // printf("%d\n", num1);

    return 0;
}
