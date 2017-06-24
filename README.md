# adan_srv-v3-rc-building
# in adan_srv-v3-rc, we are trying to design a server gateway for skynet freamwork to support cluster ten skynet server...
# it just a forward server, seems like a router, but it's a special router, we're going to add there function inside to adan_srv-v3-rc
# 1.encryption data transmission(encryption algorithm by my own)
# 2.long keep-live socket communication by TCP/IP procotol
# 3.client -> gateway -> server or server -> gateway -> client ... one way travel, one socket one buffer, token mode control 
#
# now it's design details by chinese:
# 1.网关不做心跳控制(心跳包交由skynet 自己做, 很多情况下心跳包要附带业务数据, gateway 不适合做), 简单一个socket 长连接, 
# 传输对数据加密(保障数据安全), 附带校验码(防止网络不稳定的情况下仍然有校验标准), 
# 控制数据帧长度(分两种包型-单帧512b or 8192b=默认socket 缓冲区大小), <这个废弃>网关令牌(同一时刻只能让client or server 操作网关)
# 
#
# 2.关于为什么废弃网关令牌?? client 同时操作提交socket 对gateway 转发不影响?? 只要有两个缓冲区就不影响...
# socket 自身就有任务队列, 你提交操作不一定立即执行, OS 内部是有排序的, 所以肯定不会乱序...
# 想办法将socket 默认自带的buf 拿出来用, 这样每个操作都可以少一个cp, 直接将socket 缓冲区拿来用...
#
#
# 3.对于帧长度不限, 但不能超出8192b, 上面说分两种包型, 可以, 尽量制造更多的单帧包, 但是超出8192b 不发送并打印出来, 不做自动拆分模块...
