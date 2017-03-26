package.path = "./?.lua"
local redis  = require "redis"  --装载连接引擎
local db_conn           --redis db conn
local host = {"192.168.1.120"}  --ip
local port = 6379       --port
local db_name = 6666    --db 范围由redis 配置决定的, 0 - n
local auth              --验证手段
--
--连接redis 服务器, 成功返回连接指针, 失败返回nil
local function redis_connect()
    --db_conn = redis.connect {host,port,db_name,auth}
    db_conn = redis.connect {host,port,db_name}
    if db_conn then
      print("lua vm connect looks right, now we gonna ping redis server!!")
      local tmp = db_conn:ping()
      if not tmp then
        print("lua connect redis is good !!")
        return db_conn
      else
        print("lua connect redis is exception")
        return nil
      end
    else
      print("lua vm connect redis fail !!")
      return nil
    end
end

if redis_connect() == nil then
  print("connect redis fail...")
else
  print("connect redis success...")
end

--[[
--使用不要再面向对象包装了, 本来已经抱装过了...
local red_key    --键 = redis hash body -- redis db 下的键, value 值 = hash body
local ha_key     --域-field-hash key
local value      --值

--1-hset
local r = db_conn:hset(red_key,"key1","val1")

--2-hmset
local table_tmp = {31,4,32,4}
--这里直接打开table 是因为table = {31,4,32,4} 这样的格式
local r = db_conn:hmset(red_key,table.unpack(table_tmp))
--正常版本
local r = db_conn:hmset(red_key,"key1","val1","key2","val2")

--3-hget
local r = db_conn:hget(red_key,"key1")

--4-hkeys
local r = db_conn:hkeys(red_key)

--5-hvals--获取所有key 值
local r = db_conn:hvals(red_key)

--6-hdel
--直接拆table
local table_tmp
local r = db_conn:hdel(red_key,table.unpack(table_tmp))
--正常版本
local r = db_conn:hdel(red_key,"key1")

--7.hmget
local table_tmp
local r = db_conn:hmget(red_key,table.unpack(ha_key))
--正常版本
local r = db_conn:hmget(red_key,"key1","val1")

--8.hgetall
local r = db_conn:hgetall(red_key)

--9.hincrby--数组table 默认计数+1--增量也可以为负数
local adjust = 1
local r = db_conn:hincrby(red_key, ha_key, adjust)

--10.zrank--显示ha_key 在red_key 中的位置--排名
local r = db_conn:zrank(red_key,ha_key)

--11.
local r = db_conn:zrevrank(red_key,ha_key)

--12.
local r = db_conn:zrange(red_key,low,high,"WITHSCORES")

--13.
local r = db_conn:zrevrange(red_key,low,high,"WITHSCORES")

--14.
local r = db_conn:zincrby(red_key,add,ha_key)

--15.
local r = db_conn:zadd(red_key,add,ha_key)

--16.
local r = db_conn:zcard(red_key)

--17.
local r = db_conn:zscore(red_key,ha_key)

--18.
local r = db_conn:zrangebyscore(red_key,low,high)

--19.
local r = db_conn:zrem(red_key, value)

--20.
local r = db_conn:lpush(red_key, ...)

--21.
local r = db_conn:rpush(red_key, value)

--22.
local r = db_conn:lrange(red_key,low,high)

--23.
local r = db_conn:lset(red_key,index,value)

--24.
local r = db_conn:lpop(red_key)

--25.
local r = db_conn:rpop(red_key)

--26.
local r = db_conn:lrem(red_key,0,ha_key)

--27.
local r = db_conn:llen(red_key)

--28.
local r = db_conn:lindex(red_key,index)

--29.
local r = db_conn:del(red_key)

--30.
local r = db_conn:hlen(red_key)

--31.
local r = db_conn:keys(red_key)

--]]
--[[
Redis在2.6推出了脚本功能，允许开发者使用Lua语言编写脚本传到Redis中执行。使用脚本的好处如下:

1.减少网络开销：本来5次网络请求的操作，可以用一个请求完成，原先5次请求的逻辑放在redis服务器上完成。使用脚本，减少了网络往返时延。
2.原子操作：Redis会将整个脚本作为一个整体执行，中间不会被其他命令插入。
3.复用：客户端发送的脚本会永久存储在Redis中，意味着其他客户端可以复用这一脚本而不需要使用代码完成同样的逻辑。

实现一个访问频率控制，某个ip在短时间内频繁访问页面，需要记录并检测出来，就可以通过Lua脚本高效的实现

在redis客户端机器上，新建一个文件ratelimiting.lua，内容如下:

local times = redis.call('incr',KEYS[1])
if times == 1 then
    redis.call('expire',KEYS[1], ARGV[1])
end

if times > tonumber(ARGV[2]) then
    return 0
end
return 1


在redis客户端机器上，如何测试这个脚本呢？如下：
redis-cli --eval ratelimiting.lua rate.limitingl:127.0.0.1 , 10 3

--eval参数是告诉redis-cli读取并运行后面的Lua脚本，ratelimiting.lua是脚本的位置，后面跟着是传给Lua脚本的参数。
其中","前的rate.limiting:127.0.0.1是要操作的键，可以再脚本中用KEYS[1]获取，","后面的10和3是参数，
在脚本中能够使用ARGV[1]和ARGV[2]获得。注：","两边的空格不能省略，否则会出错

结合脚本的内容可知这行命令的作用是将访问频率限制为每10秒最多3次，
所以在终端中不断的运行此命令会发现当访问频率在10秒内小于或等于3次时返回1，否则返回0。

]]