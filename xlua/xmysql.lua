--装载mysql 驱动
local luasql = require "luasql.mysql"

--创建环境对象
local env = luasql.mysql()

--连接数据库
local conn = env:connect("数据库名","用户名","密码","IP地址","端口")

--设置数据库的编码格式
conn:execute"SET NAMES UTF8"

--执行数据库操作--提交sql 语句
local cur = conn:execute("select * from role")

--用table 来获取一行result
local row = {}
row = cur:fetch(row,"a")

--文件对象的创建
local file = io.open("role.txt","w+");

while row do
  --打印出result table
  local var = string.format("%d %s\n", row.id, row.name)

  print(var)

  file:write(var)

  row = cur:fetch(row,"a")
end


file:close()  --关闭文件对象
conn:close()  --关闭数据库连接
env:close()   --关闭数据库环境