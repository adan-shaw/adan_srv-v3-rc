--[[
collectgarbage("collect"): 显式执行一次回收

collectgarbage("count"): 以KB 为单位返回Lua 使用的总内存数

collectgarbage("restart"): 重启垃圾收集器的自动运行

collectgarbage("setpause"): 将arg 设为收集器的 间歇率, 返回 间歇率 的前一个值。

collectgarbage("setstepmul"): 返回步进倍率的前一个值。

collectgarbage("stop"): 停止垃圾收集器的运行, 在调用重启前, 收集器只会因显式的调用运行...

--这个只是加速回收垃圾的步长推进, 每推一步, 里执行回收就越近
collectgarbage("step"): 单步运行垃圾收集器, 步长"大小"由 arg 控制, 传入 0 时，收集器步进（不可分割的）一步
传入非 0 值, 收集器收集相当于 Lua 分配这些多（KB 字节）内存的工作, 如果收集器结束一个循环将返回 true


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



