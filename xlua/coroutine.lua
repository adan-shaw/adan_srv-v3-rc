--创建协程--只是创建协程内存块, 并未启动, 协程不是线程, 一装载好就自动启动, 
--协程启动还需要线程调入, 所以还需要coroutine.resume() 配合调入lua vm 当前线程,
--去跑协程里面的代码...

--1.coroutine.create() 创建一个协程内存块并返回该内存块的指针

--调入lua vm 执行线程跑协程...注意: 一个lua vm 永远只有一个线程
--2.coroutine.resume()

--3.coroutine.yield()  挂起当前协程返回lua vm 继续执行lua vm 中的内存数据

--4.coroutine.status() 查看协程的状态

--5.coroutine.wrap() 创建并马上调入lua vm 线程版本, 相当与create + resume

--6.coroutine.running() 返回一个正在跑的协程id 号

--