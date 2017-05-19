/*
 * xstring.c
 *
 *  Created on: 2017/5/18
 *      Author: adan shaw
 */

#include <stdio.h>
//
//auto make net cross command -- 生成数据报互交报文(自己添加后缀) 如: #define sc_x1000_login 1000
void net_cross_comm(int n){
  printf("server to client\n");
  char xbuf[20];
  int tmp = 1000;
  n = n + 1000;
  for(;tmp < n;tmp++){
    sprintf(xbuf,"#define sc_x%d_ ",tmp);
    printf(xbuf);
	printf("%d\n",tmp);
  }
  printf("\n\n");
  printf("client to server\n");
  tmp = 1000;
  for(;tmp < n;tmp++){
    sprintf(xbuf,"#define cs_x%d_ ",tmp);
    printf(xbuf);
	printf("%d\n",tmp);
  }
  printf("\n\n");
}

