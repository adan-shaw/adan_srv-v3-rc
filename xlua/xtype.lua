--[[
lua VM对string 的管理机制为: string 永远只保留一份唯一 的copy...
所以 string使用 = 赋值操作, 应该是 引用

--lua 数据类型
Lua中有8个基本类型分别为：nil、boolean、number、string、userdata、function、thread和table

nil 这个最简单，只有值nil属于该类，表示一个无效值（在条件表达式中相当于false）
boolean 包含两个值：false和true
number  表示双精度类型的实浮点数
string  字符串由一对双引号或单引号来表示
function  由 C 或 Lua 编写的函数
userdata  表示任意存储在变量中的C数据结构
thread  表示执行的独立线路，用于执行协同程序
table ：
table 有两种形态: array or hash 
当key 全部为number 时, table 默认为array, 
当key 有一个不为number 时, table 默认为hash


type() 函数是一个安全函数, 一定会返回变量type 的字符串

--lua 中的全局变量:
1.全局变量的原形: 其实本质上也是一个table, 它把我们创建的全局变量都保存到一个table里了... 
这个table 默认的名字是: _G, 你可以通过setfenv(1, new_table_name) 更改全局变量table; 
setfenv 参数解析: 
1).第一个参数, 可以是即将要改变环境的函数, 也可以是一个数字. 
数字1代表当前函数, 数字2代表调用当前函数的函数,后面以此类推... 

2).第二个参数, 新的全局环境table... 

PS: 全局函数的作用域是--整个lua 虚拟机, 全局变量不会被lua 自动回收或显式回收, 言外之意是:
全局变量是不会被回收的

你要清楚一个概念: lua 就是一个单线程, 多内存块(伪造线程栈-协程-伪多线程)的一个虚拟机, 
这样做方便业务开发, 而且根据lua 小巧快速的特点, 其实单线程也很适合, 
lua 沙盒因为其快速小巧的特点完全符合并存多进程的设计, 只是线程间通信效率的确需要解决, 
但是skynet 就帮你解决了这个问题...

]]

