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
# 不对数据帧长度进行控制(虽然单帧=512b or 8192b=默认socket 缓冲区大小, 但帧大小控制适合在skynet 中进行, 网关越简单越好) 
# <重点>不做网关令牌(即同一时刻只能让client or server 操作网关), 支持双边操作, 但是当client 提交数据和server 下发数据时,
# 如何避免冲突? 做个队列是多余的? 因为网关的网卡设备也只会有一个, 然后操作系统本身就有网络任务队列, 所以其实任务是先后有序没错的...
# 但是如果不做通信令牌, 当网关被冲击的时候可能危及业务机, 如果有令牌, 业务机拿到了令牌, 则client 就失去网关操作权, 所有提交操作都会被
# 网关拒绝, 攻击自然危及不到业务机, 网关看不到业务机的令牌许可就不会转发数据到业务机上面, 这样虽然是冗余的, 但是面对冲击的时候却是可靠的
# 
#
# 2.关于为什么废弃网关令牌?? client 同时操作提交socket 对gateway 转发不影响?? 只要有两个缓冲区就不影响...
# socket 自身就有任务队列, 你提交操作不一定立即执行, OS 内部是有排序的, 所以肯定不会乱序...
# 想办法将socket 默认自带的buf 拿出来用, 这样每个操作都可以少一个cp, 直接将socket 缓冲区拿来用...
#
#
# 3.网关不做日志记录? 做! 但是只对部分错误操作进行记录, 以分析网关是否收到client 冲击, 正确操作不需要太多记录, 因为网关最主要的功能
# 就是做到高效转发, 过滤冲击, 集成业务机...
