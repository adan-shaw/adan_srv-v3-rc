--[[函数返回时, lua vm 是否会释放函数所占用的内存?? 答案是不可能的, 就算是C 也不会在return 之后就释放函数变量所占用的内存, lua 甚是更不堪, 
C 会在下次函数调用的时候, 重新初始化上一次原来的函数内存地址, 再压入栈, 除非你用static 语句固定声明某个变量不需要再次初始化, 就直接推入栈,
这样的话该static 变量就会直接入栈, 但是lua 甚是奇怪, 甚至每次函数重复调用, 都会产生出新的内存占用, 无论该函数是否已经有母板在占用...复用性很差



collectgarbage("collect"): 显式执行一次回收

collectgarbage("count"): 以KB 为单位返回Lua 使用的总内存数

collectgarbage("restart"): 重启垃圾收集器的自动运行

collectgarbage("setpause"): 将arg 设为收集器的 间歇率, 返回 间歇率 的前一个值。

collectgarbage("setstepmul"): 返回步进倍率的前一个值。

collectgarbage("stop"): 停止垃圾收集器的运行, 在调用重启前, 收集器只会因显式的调用运行...

--这个只是加速回收垃圾的步长推进, 每推一步, 里执行回收就越近
collectgarbage("step"): 单步运行垃圾收集器, 步长"大小"由 arg 控制, 传入 0 时，收集器步进（不可分割的）一步
传入非 0 值, 收集器收集相当于 Lua 分配这些多（KB 字节）内存的工作, 如果收集器结束一个循环将返回 true

lua vm 如何做到削减,重用,和适当强制回收: http://www.cnblogs.com/gdev/archive/2012/08/22/lua-performance-tips-5.html
1.for i=1,100 do local a={11,1,11,1,1,1,1};print(a) end --本地变量竟然打出了100个不同table 的地址指针!! 
  也就是每次使用for 循环时, 你要确保尽量不要在for 里面创建or 定义or 使用一些copy new 内存块的函数如: tonumber, tostring 之流

2.table 里面:{a=1,b=2,c=3} 这种hash 方式劣于{1,2,3} 这种数组方式;;;;{{x,y},{x1,y1}} 这样方式劣于{x={x,x1},y={y,y1}}

3.tonumber tostring 每次调用其实都会返回新的地址, 分配新的内存, 所以诸如此类的函数要慎用...
  只有local tmp = 1;tmp = tmp + 1 这种情况才会指明复用tmp 地址, 脚本使用一个不小心就会变成内存炸弹...

4.一旦lua vm 里面某个业务逻辑已经操作完毕之后, 你可以马上显式调用collectgarbage("collect") 进行内存回收, 立即清理清理lua vm
  里面的垃圾内存, 减少lua vm 消耗系统内存, lua vm 的重用机制根本没有, 你以为是java vm??

5.一旦使用形如table copy(source_table, output_table), 如果你确定output_table 一定会覆盖source_table, 你可以在copy 函数退出
  之前将source_table = nil 加速source_table 的回收, 更显而易见的告诉lua vm 这块内存已经废弃了...
  ps: 一个赋值操作绝对不是消耗CPU 的重点, 应该说一个赋值操作完全可以是指而不见, 完全忽略...


]]

--例子:
--注意, lua vm 操作是全局函数
mytable = {"apple", "orange", "banana"}

print(collectgarbage("count"))

mytable = nil

print(collectgarbage("count"))

print(collectgarbage("collect"))

print(collectgarbage("count"))

--执行以上程序，输出结果如下(注意内存使用的变化)：

--20.9560546875
--20.9853515625
--0
--19.4111328125



