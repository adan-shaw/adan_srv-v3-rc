# adan_srv-v3-rc-building
# in adan_srv-v3-rc, we are trying to design a server gateway for skynet freamwork to support cluster ten skynet server...
# it just a forward server, seems like a router, but it's a special router, we're going to add there function inside to adan_srv-v3-rc
# 1.encryption data transmission(encryption algorithm by my own)
# 2.long keep-live socket communication by TCP/IP procotol
# 3.client -> gateway -> server or server -> gateway -> client ... one way travel, one socket one buffer, token mode control 
#
# now it's design details by chinese:
#
