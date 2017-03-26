--lua io 库 -- http://www.cnblogs.com/chiguozi/p/5804951.html
--[[
I/O 库提供了两套不同风格的文件处理接口:
第一种风格使用隐式的文件fd , 它提供设置默认输入文件及默认输出文件的操作,
     所有的输入输出操作都针对这些默认文件...
第二种风格使用显式的文件fd 
当使用隐式文件fd 时, 所有的操作都由表 io 提供
若使用显式文件fd , io.open 会返回一个文件fd , 且所有的操作都由该文件fd 的方法来提供

当然为了语法严谨, 最好还是用显式, 用文件fd 操作比较适合--fd:do something
lua io 提供flush() 刷如缓冲操作

表io 中也提供了三个 和C 中含义相同的预定义文件句柄:
io.stdin io.stdout io.stderr, I/O 库永远不会关闭这些文件

除非另有说明: I/O 函数在出错时都返回 nil （第二个返回值为错误消息，第三个返回值为系统相关的错误码）
成功时返回与 nil 不同的值

--lua io api
*1.io:open(filename [, mode])

这个函数用字符串 mode 指定的模式打开一个文件, mode 字符串可以是下列任意值：

    "r": 只读模式, 这也是对已存在的文件的默认打开模式
    "w": 可写模式, 允许修改已经存在的文件和创建新文件(不可读)
    "a": 追加模式, 对于已存的文件允许追加新内容，但不允许修改原有内容, 同时也可以创建新文件
    "r+": 读写模式打开已存的在文件
    "w+": 如果文件已存在则删除文件中数据, 若文件不存在则新建文件, 读写模式打开
    "a+": 以可读的追加模式打开已存在文件, 若文件不存在则新建文件

mode 字符串可以在最后加一个 'b' ， 这会在某些系统上以二进制方式打开文件

当文件不存在时:
local fd = io.open("./test.txt")
fd:close()

模式"r","r+",会提示错误,这两种模式不会自动创建文件
模式"a","a+","w","w+"都会创建文件
w or w+ 会立即删除文件内容,即使不写入内容.

当文件存在时, 原文件:
test.txt
this is test 1
this is test 2

lua文件:
local fd = io.open("./test.txt", "r+")
print(fd:read("*a"))
fd:close()


*2.io:input([file])
--1.用文件名调用它时, （以文本模式）来打开该名字的文件, 并将文件句柄设为默认输入文件...
--2.如果用文件句柄去调用它, 就简单的将该句柄设为默认输入文件...
--3.如果调用时不传参数, 它返回当前的默认输入文件--隐式调用, 不推荐

在出错的情况下, 函数抛出错误而不是返回错误码

--文件名
io.input("./test.txt")
print(io.read("*a"))
io:close()

--文件句柄(需要使用可读模式)
local fd = io.open("./test.txt", "r")
print(file)
io.close()

Output:
this is test 1
this is test 2


*3.io:output([file])
--使用方法与io:input([file]) 差不多
print(io.output("./test.txt"))
io.write("123")
io.close()


*4.io.popen (prog [, mode])   这个函数和系统有关, 不是所有的平台都提供 !!
用一个分离进程开启程序 prog, 返回的文件句柄可用于从这个程序中读取数据 
（如果 mode 为 "r", 这是默认值） 或是向这个程序写入输入（当 mode 为 "w" 时）


*5.io.tmpfile() -- 返回一个临时文件的句柄
这个文件以更新模式打开, 在程序结束时会自动删除...

local fd = io.tmpfile()
print(io.type(file))
fd:close()

*6.io.type(obj) -- 检查 obj 是否是合法的文件句柄
如果 obj 它是一个打开的文件句柄, 返回字符串 "file"...
如果 obj 是一个关闭的文件句柄, 返回字符串 "closed file"...
如果 obj 不是文件句柄，返回 nil
local fd = io.tmpfile()
print(io.type(file))


*7.io.lines([filename]) -- 提供一个循环迭代器以遍历文件
如果指定了文件名则当遍历结束后将自动关闭该文件
若使用默认文件, 则遍历结束后不会自动关闭文件

for line in io.lines("./test.txt") do
    print(line)
end

注:Lua 5.3 有变动, 添加模式数: fd:lines() 返回一个迭代器函数
每次调用迭代器时, 都从文件中取一行数据, 和 io.lines 不同, 这个函数在循环结束后不会关闭文件

注:Lua 5.3 有变动,添加模式数: fd:read(...)
读文件 file, 指定的格式决定了要读什么
对于每种格式, 函数返回读出的字符对应的字符串或数字
若不能以该格式对应读出数据则返回 nil
（对于最后这种情况, 函数不会读出后续的格式） 
当调用时不传格式,它会使用默认格式读下一行

    **"*n": ** 从文件当前位置读入一个数字，如果该位置不为数字则返回 nil。
    **"*l": ** 读入当前行。
    **"*a": ** 读入从当前文件指针位置开始的整个文件内容。
    number: 读入指定字节数的内容。

local fd = io.open("./test.txt", "r")
print(fd:read("*l"))
print(fd:read("*n"))
print(fd:read(2))


*8.io:close() -- 关闭 file...
注意: 文件在句柄被垃圾回收时会自动关闭, 但是多久以后发生, 时间不可预期的
等价于 fd:close(), 不给出 file 时将关闭默认输出文件


*9.io:flush() -- 将写入的数据保存到 file 中
fd:flush() 有fd 就不需要指明


*10.fd:seek([whence [, offset] ]) -- 设置及获取基于文件开头处计算出的位置
设置的位置由 offset 和 whence 字符串 whence 指定的基点决定
基点可以是：
    "set": 基点为 0 （文件开头）；
    "cur": 基点为当前位置了；
    "end": 基点为文件尾；
当 seek 成功时, 返回最终从文件开头计算起的文件的位置
当 seek 失败时, 返回 nil 加上一个错误描述字符串
whence 的默认值是 "cur"， offset 默认为 0 
因此, 调用 fd:seek() 可以返回文件当前位置, 并不改变它
调用 fd:seek("set") 将位置设为文件开头（并返回 0）
调用 fd:seek("end") 将位置设到文件末尾, 并返回文件大小

local fd = io.open("./test.txt", "r+")
print(fd:seek("end"))
print(fd:seek("set"))
print(fd:seek())
print(fd:seek("cur", 10))
print(fd:seek("cur"))
print(fd:read(1))
print(fd:seek("cur"))
fd:write("123")
fd:close()

修改文件的值会影响read操作 以及以"r+"模式打开文件的write操作


]]