--[[
-- 初始化表--如果不同域引用时, 必须重新初始化, 以指定类型...
-- lua 里面的域很奇怪, if end for end function end 都是不同的作用域...
-- 作用域同名下的变量, 本地最大, 覆盖全局变量

-- 如你在本文件local table_name = {}
-- 但你又在某函数中直接table_name[i] = 123
-- 那么你在该函数中必须先重新初始化table_name = {}
-- 以确定table_name 的type() == "table", 否则table_name 只是一个空指针
-- local table_name = {} = local table_name = nil
-- 但是table 未初始化时传递给函数的都是一指针, 所以如果table = {} 光传递一指针
-- 进入另一个函数, 那么你就需要重新初始化

-- 重名变量会本地覆盖, 但是lua 还是不推荐重名变量, 除了部分tmp 命可以一定程度重复
-- 但是这也会消耗一定内存

--
-- table 指定key and value 赋值--需要明确type(val1) == "table" 的情况下才能使用
   mytable[1]= "Lua"


-- 移除引用--等待lua vm 垃圾回收或显示调用垃圾回收才会被释放内存
   mytable = nil

要点1:
由于table 是hash 的特性, <循环查找索引时>千万不要添加/删除元素, 改变其存储结构,
否则整个树存储结构会被改变...如果你for i=1,10 do...
当你找到1, 然后又插入了一个1-2 之间的值, 替代了原来的2元素, 那么原来的2 元素就会变成3,
新插入的元素会变成2,最后一个10 元素不会找到

    local t1 = {2, 4, 6, language="Lua", version="5", 8, 10, 12, web="hello lua"};  
    for key,value in ipairs(t1) do
      print(key, value)
    end
    输出结果：  
    1 2  
    2 4  
    3 6  
    4 8  
    5 10  
    6 12  
    web hello lua  
    language Lua  
    version 5 
    
要点2:
table copy 要用迭代器才能拷贝, 光循环遍历然后table[i] = val_i 会指空, 不能copy 

要点3:
table 排序后, 删除后面的元素不影响前面元素的序列
              删除前面的元素, 所有后面的元素序号向前推1(-1)
  

元表--> 其实就是向table 中插入块内存, 这个块内存可以是函数，可以是新的table...可以是lua api
这样就可以减少指针使用, 因为如果你要将一个函数转变成指针, 再将指针存入table  中会很麻烦
但是用元表, 你马上可以像插入元素一样简单地插入函数内存块
函数在内存中的表现也是code + data,,执行代码+数据, 实质也是块数据

如果你想临时插入函数或者动态插入函数, 元表适合你, 但是或者这也是攻击手段,
向一个table 里面注入function 跟sql 注入攻击一样搞笑, 例如直接os.exit()


]]
--
--
--1 table.concat (): 链接两个table

--2 table.insert (): 向table 插入元素--不能指定key != number 的插入 table.insert(t,2,"aa")
                                   --默认是按数组key 递增
--3 table.remove ()：移除table 元素  --默认是按数组key 递减

--4 table.sort ()  ：对给定的table进行升序排序--最大值在右边, 恒定--对值排序--仅限array 模式??--要试试

--5 table.unpack() ：table 数据形态时的拆分

--6 table_pack("test", "param1", "param2", "param3") -- 打包table 变成数组 1 2 3 4

--example :
fruits = {"banana","orange","apple"}
-- 返回 table 连接后的字符串
print("连接后的字符串 ",table.concat(fruits))

-- 指定连接字符
print("连接后的字符串 ",table.concat(fruits,", "))

-- 指定索引来连接 table
print("连接后的字符串 ",table.concat(fruits,", ", 2,3))

--执行以上代码输出结果为：
--连接后的字符串   bananaorangeapple
--连接后的字符串   banana, orange, apple
--连接后的字符串   orange, apple

--table.unpack(table, start, end) 用于返回 table 里的元素
--参数 start 是开始返回的元素位置, 默认是 1, 
--参数 end 是返回最后一个元素的位置, 默认是 table 最后一个元素的位置,
--参数 start、end 都是可选
--仅当table 为数组形态的时候, 用于返回数组中的值


--
--table 迭代器
local table1
for key,value in ipairs(table1) do
   print(key, value)
end

print(type("Hello world"))      --> string
print(type(10.4*3))             --> number
print(type(print))              --> function
print(type(type))               --> function
print(type(true))               --> boolean
print(type(nil))                --> nil
print(type(type(X)))            --> string

--[[
当table 不为数组形态时, 
不能用#table 来获取table 的长度, 此时求长度应当遍历table...

lua 提供number string 自动转换, 可能因为脚本翻译本身就需要将string 翻译成number, 
因此number 转变成string 消耗应该比较小, 
但是很多情况下还是需要tonumber() or tostring() 去明确用number 还是string

]]
