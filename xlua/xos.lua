--lua os 库 -- http://www.jb51.net/article/57639.htm
--[[
*1.os.clock ()
功能：返回一个程序使用CPU时间的一个近似值


*2.os.date ([format [, time] ])
功能：返回一个按format格式化日期、时间的字串或表
若设置time参数，则按time指定的时间格式化，否则按当前时间格式化
参数format:
      "!" : 按格林尼治时间进行格式化。
  　　　　"*t": 将返一个带year(4位),month(1-12), day (1--31), hour (0-23), min (0-59), sec (0-60), wday (星期几, 星期天为1), yday (年内天数), and isdst (是否为日光节约时间true/false)的带键名的表; 
            若没有"*t"则返回一个按C的strftime函数格式化的字符串
            若不带参数，则按当前系统的设置返回格式化的字符串 os.date() <=> os.date("%c")

os.date会将日期格式化为一个字符串如下:
%a      一星期中天数的简写                      （Wed）
%A      一星期中天数的全称                      （Wednesday）
%b      月份的简写                                  （Sep）
%B      月份的全称                                  （September）
%c      日期和时间                                   （09/16/98 23:48:10）
%d      一个月中的第几天                          （16）[0 ~ 31]
%H      24小时制中的小时数                      （23）[00 ~ 23]
%I      12小时制中的小时数                       （11）[01 ~ 12]
%j      一年中的第几天                             （259）[01 ~ 366]
%M      分钟数                                       （48）[00 ~ 59]
%m      月份数                                       （09）[01 ~ 12]    
%P      "上午(am)" 或 "下午(pm)"               (pm)
%S      秒数                                          （10）[00 ~ 59]
%w      一星期中的第几天                         （3）[0 ~ 6 = 星期天 ~ 星期六]

%W　　一年中的第几个星期　　　　　　　　0 ~ 52
%x      日期                                          （09/16/98）
%X      时间                                          （23:48:10）
%y      两位数的年份                               （90）[00 ~ 99]
%Y      完整的年份                                 （2009）
%%      字符串'%'

print(os.date("today is %A, in %B"))      -->today is Tuesday, in May


*3.os.difftime (t2, t1)
功能：返回t1到t2相差的秒数
t1 = os.time();
for i = 0, 10000000 do
 os.time();
end
t2 = os.time();
print(os.difftime(t2, t1));


*4.os.execute ([command])
功能：相当于C的system函数,返回系统状态码
os.execute("pause")


*5.os.exit()
功能：相当于C的exit函数,终止主程序,code为返回值


*6.os.getenv(varname)
功能：返回当前进程的环境变量varname的值,若变量没有定义时返回nil
print(os.getenv("USERDOMAIN"))
print(os.getenv("SystemRoot"))
print(os.getenv("Os2LibPath"))
print(os.getenv("ProgramFiles" ))
print(os.getenv("APPDATA" ))
print(os.getenv("ALLUSERSPROFILE" ))
print(os.getenv("CommonProgramFiles" ))
print(os.getenv("COMPUTERNAME" ))
print(os.getenv("USERNAME"))
print(os.getenv("USERPROFILE" ))
print(os.getenv("ComSpec"))
print(os.getenv("LOGONSERVER" ))
print(os.getenv("NUMBER_OF_PROCESSORS" ))
print(os.getenv("OS"))
print(os.getenv("PATHEXT" ))
print(os.getenv("PROCESSOR_ARCHITECTURE" ))
print(os.getenv("PROCESSOR_IDENTIFIER" ))
print(os.getenv("PROCESSOR_LEVEL" ))
print(os.getenv("PROCESSOR_REVISION" ))
print(os.getenv("USERDOMAIN"))
print(os.getenv("SystemRoot" ))
print(os.getenv("TEMP"))


*7.os.remove (filename)
功能：删除文件或一个空目录,若函数调用失败则返加nil加错误信息


*8.os.rename (oldname, newname)
功能：更改一个文件或目录名,若函数调用失败则返加nil加错误信息


*9.os.setlocale (locale [, category])
功能：设置程序的当前设置,函数返回最新的值，失败则返回nil


*10.os.time ([table])
功能：按table的内容返回一个时间值(数字),若不带参数则返回当前时间table的字段：
print(os.time());
-->1249887340
print(os.time({year=1970, month=1, day=1, hour=0}));
-->10500


*11.os.tmpname()
功能：返回一个临时文件名, 当前lua vm 下的一个临时文件名








]]