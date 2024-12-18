#include <stdio.h>

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
// Student 结构体类型
// stu 结构体变量

struct Struct
{
    int a;
    int b;
};

typedef struct Struct2 
{
    int c;
    int d;
}stu2;
// typedef struct Struct2 stu2

typedef struct Struct _str;
int main(int argc, char const *argv[])
{
    enum week w;
    printf("%d\n", Sunday);//7
    printf("%d\n", autumn);//4
    stu.id = 1;
    stu.age = 10;
    struct Struct s;
    _str s2;
    s2.a = 11;
    s2.b = 12;
    s.a = 1;
    s.b = 2;
    printf("id %d; age %d; a %d; b %d\n", stu.id, stu.age, s.a, s.b);
    //id 1; age 10; a 1; b 2
    printf("%d\n", num1);
    return 0;
}
