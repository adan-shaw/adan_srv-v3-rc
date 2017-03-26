--[[
lua 面向对象的实现: lua 可以用file + return 的模式, 返回一个满足指针的内存块, 
你可以在table 中加入变量or 函数, require 的实质就是直接装载file 到内存, 
直至遇到第一个return 后, 返回一个内存块... 但只能返回一个table...
虽然lua 支持多个函数返回对象, 但是在require 只返回一个对象

lua 装载内存块后并不能检测内存块是否正确, 你不能用长度检测, 非空检测等手段, 
检测返回table 是否正确... 因为如果table 出错的话, 很多情况是内存错位了, 
你应该先确定你要加载的lua file 是否语法正确, 并却loacl return_table = {}
and return return_table and return_table.function()等语句细节完整,
确保被装载的file 正确, 装载才会成功...


如果装载函数失败, 然后你使用return_table.function_name()
lua 对table 中找不到的变量都是统一返回nil 的, 例如:
local table = {}; if table.abc == nil then print("true")

所以调用时指针为空, 值为空: lua attempt to call a nil value 时, 应该检查以上3点



require 搜索路径有两种存在方式: 

package.path() 搜索lua 文件 : 
package.path = package.path ..';..\?.lua'; 

package.cpath() 搜索so 文件 : 
package.cpath = package.cpath ..';..\?.lua'; 

ps: 两点链接字符串, 被重载的两点还是挺好用的

]]

