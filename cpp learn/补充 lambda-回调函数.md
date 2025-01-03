```c++
int a = 1;
int b = 2;
auto lambda = [a, &b](int x) -> int {
    b = x + a + b;// 可更改 b，不可更改 a
    return x + a;
};
```

1. 解释：
    - auto lambda：
      - auto 关键字用来推断 lambda 的类型，避免手动指定。C++ 编译器会根据 lambda 函数的返回类型和参数类型自动推导出 lambda 的类型。
1. 捕获列表 [a, &b]：

    - [a, &b] 是 捕获列表，指定 lambda 函数可以访问哪些外部变量。
      - a 被 按值捕获：这意味着 lambda 函数内部可以使用变量 a 的值，但不会改变外部 a 的值。
      - &b 被 按引用捕获：这意味着 lambda 函数内部对 b 的修改会直接影响外部的 b 变量。
2. (int x)：

    - 这是 lambda 函数的 参数列表，类似于普通函数的参数。这里 lambda 函数接受一个 int 类型的参数 x。
3. -> int：

    - 这是 返回类型，表示 lambda 函数会返回一个 int 类型的值。-> int 是 C++11 中 lambda 的语法，用来显式指定返回类型。虽然编译器有时可以推导出返回类型，但你仍然可以显式指定返回类型来提高可读性或处理一些复杂的情况。
4. 函数体 { return x + a + b; }：

     - 这是 lambda 函数的 主体，表示函数的实现。x + a + b 表示返回 x、a 和 b 的和。由于 a 是按值捕获，b 是按引用捕获，lambda 函数中的 a 和 b 分别访问外部 a 和 b 变量的值。


执行过程：
1. 定义和初始化：

    - lambda 被定义为一个 lambda 函数，并且可以立即使用。a 和 b 作为外部变量被捕获，a 按值捕获，b 按引用捕获。
2. 调用 lambda(20)：

    - 当调用 lambda(20) 时，x 传入值 20，a 和 b 分别是 10 和 20。
    - lambda 的执行体 x + a + b 计算 20 + 10 + 20 = 50，并将结果返回。
3. 输出结果：

    - 最终，std::cout 输出结果 35。但是，根据代码逻辑，结果应该是 50，而不是 35。如果你希望 lambda(20) 的结果为 35，需要将 a 或 b 修改为符合逻辑的数值。 


---

```cpp
#include <iostream>
#include <functional>

// 定义一个函数，它接受一个std::function作为回调函数
void process(int x, const std::function<void(int)>& callback) {
    std::cout << "Processing number: " << x << std::endl;
    callback(x);  // 调用回调函数
}

// 定义一个回调函数
void printResult(int result) {
    std::cout << "Callback called with result: " << result << std::endl;
}

int main() {
    // 使用函数指针
    process(10, printResult);

    // 使用lambda表达式作为回调
    process(20, [](int result) {
        std::cout << "Lambda called with result: " << result << std::endl;
    });

    return 0;
}
```