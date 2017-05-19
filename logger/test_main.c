/*
 * test_main.c
 *
 *  Created on: 2017/5/18
 *      Author: adan shaw
 */

struct log_val{
  char xbuf0[16];
  char xbuf1[16];
  char xbuf2[16];
  char xbuf3[16];
  char xbuf4[16];
  char xbuf5[16];
  char xbuf6[16];
  char xbuf7[16];
  char xbuf8[16];
  char xbuf9[16];
};
//
int main(void){
  net_cross_comm(5);//测试数据报生成工具
  //测试日志系统
  xlog_init();
  struct log_val test;
  int tmp = 0,n=10;
  for(;tmp < n;tmp++){
	switch(tmp){
	case 0: sprintf(test.xbuf0,"fuck you"); break;
	case 1: sprintf(test.xbuf1,"fuck you"); break;
	case 2: sprintf(test.xbuf2,"fuck you"); break;
	case 3: sprintf(test.xbuf3,"fuck you"); break;
	case 4: sprintf(test.xbuf4,"fuck you"); break;
	case 5: sprintf(test.xbuf5,"fuck you"); break;
	case 6: sprintf(test.xbuf6,"fuck you"); break;
	case 7: sprintf(test.xbuf7,"fuck you"); break;
	case 8: sprintf(test.xbuf8,"fuck you"); break;
	case 9: sprintf(test.xbuf9,"fuck you"); break;
	}
  }
  xlog(test,10);
  xlog(test,10);
  sleep(1);
  xlog(test,10);
  //暴力测试--2W 5S, 性能还可以...
  int start = time();
  for(;tmp < 20000;tmp++)
	xlog(test,10);
  printf("%d\n",start-time());
  printf("\n19000 times\n");
  xlog_close();
}
