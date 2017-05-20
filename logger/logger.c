/*
 * logger.c
 *
 *  Created on: 2017/5/18
 *      Author: adan shaw
 */

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <errno.h>
//
//日志生成格式: 年月日, 时分秒...
//参数可能有: 消息名, 用户名, 房间id, 之类 --log_val 结构体
//其实不用不定参数, 只需要10个缓冲区就足够了, 你也不应该设计一个函数超过10 个参数 !!
//每个参数都为16 char 的buf !!
//
//刷写次数: 每20条一刷, 每20秒且条数不为0一刷(防止晚上还在刷)
//必须传入参数个数--减少格式化缓冲区的次数, 而且还能提醒你这个日志的用法, 但是格式化式必须全部格式化
//
//
char file_path[128] = "./log.x";
int full_out_count = 0;//模块坏死次数
int file_size_max = 1024000;//100W 字节一换
int file_size_cur = 0;
FILE* fd = 0;//需要初始化, 免得经常fopen file
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
//初始化日志模块, 有返回, 万一打开文件失败呢?
int xlog_init(void){
  fd = fopen(file_path,"a+");//以追+模式打开, 有+号表示没有文件时会自动创建
  if(fd != -1){
	file_size_cur = 0;//重置时这个必须被重置
	printf("xlog_init is good ...\n");
	return 0;
  }
  else
	return -1;
}
//
//无返回
void xlog_close(void){
  //强行执行一次冲刷
  fflush(fd);
  if(fd > 0)
    fclose(fd);
  else
	printf("xlog_close fail !!fd is error !~~\n");
}
//
//执行记录日志, 无返回
int xcount = 0;//temp 计数
time_t xt = 0; //temp 计时
int xsig = 0;  //是否已经被重置, 0 是未被重置; 1 是已经重置, 请等待
#define xlog_buf_len 256
char xlog_buf[xlog_buf_len];//256 个字符够了...
//
void xlog(struct log_val in_val,int n){
  if(xsig == 0){
    xt = time(NULL);
    xcount = 0;
    xsig = 1;
    //强行执行一次冲刷
    fflush(fd);
  }
  time_t t = time(NULL);//只是原始码--只有数字--一共10位, 月日时分秒, 2位一组
  struct tm *loc = localtime(&t);//转换成本地时间
  memset(&xlog_buf,'\0',xlog_buf_len);//格式化缓冲区
  //char xtmp_buf[32];
  sprintf(xlog_buf,"%d/%d/%d-_-%d:%d:%d__",loc->tm_year, loc->tm_mon, loc->tm_mday,loc->tm_hour, loc->tm_min, loc->tm_sec);
  int tmp = 0;
  for(;tmp < n;tmp++){
	switch(tmp){
	case 0: sprintf(&xlog_buf,"%s%s_",xlog_buf,in_val.xbuf0); break;
	case 1: sprintf(&xlog_buf,"%s%s_",xlog_buf,in_val.xbuf1); break;
	case 2: sprintf(&xlog_buf,"%s%s_",xlog_buf,in_val.xbuf2); break;
	case 3: sprintf(&xlog_buf,"%s%s_",xlog_buf,in_val.xbuf3); break;
	case 4: sprintf(&xlog_buf,"%s%s_",xlog_buf,in_val.xbuf4); break;
	case 5: sprintf(&xlog_buf,"%s%s_",xlog_buf,in_val.xbuf5); break;
	case 6: sprintf(&xlog_buf,"%s%s_",xlog_buf,in_val.xbuf6); break;
	case 7: sprintf(&xlog_buf,"%s%s_",xlog_buf,in_val.xbuf7); break;
	case 8: sprintf(&xlog_buf,"%s%s_",xlog_buf,in_val.xbuf8); break;
	case 9: sprintf(&xlog_buf,"%s%s",xlog_buf,in_val.xbuf9); break;
	}
  }
  int len = strlen(xlog_buf) + 1;
  //printf("%s\n",xlog_buf);printf("len = %d\n",len);//for test
  //tmp = fwrite(xlog_buf,len,xlog_buf_len,fd);//fwrite 按照二进制来写入--遇到数字变整形
  //tmp = fwrite(xlog_buf,sizeof(char),len,fd);//整形可能是4bit
  tmp = fprintf(fd,"%s\n",xlog_buf);//fprintf 是纯字符写入, 同样是缓存再写
  if(tmp != len){
	printf("xlog_fix start because fprintf error??tmp = %d, len = %d\n",tmp,len);
	xlog_fix();
  }
  else{
    //超出100w bit 就换文件
	printf("%s\n",xlog_buf);
    file_size_cur = file_size_cur + len;
    if(file_size_cur > file_size_max){
      printf("xlog_fix start because file_size_cur reset??file_size_cur = %d, file_size_max = %d\n",file_size_cur,file_size_max);
      xlog_fix();
    }
  }
  //超出20 次写入就冲刷一次,  超过20s 就冲刷一次
  if(xcount == 20)
	xsig = 0;
  if(t - xt > 20)
	xsig = 0;
}
//
//
void xlog_fix(void){
  xlog_close();
  int tmp;
  //尝试修复--重置资源
  printf("awful !!logger module is not working, now we trying to help it back to work !!\n");
  full_out_count = full_out_count + 2;
  sprintf(file_path,"%s%d",file_path,full_out_count);//换个文件名, 可能文件太大
  if(xlog_init() != 0){
    //坏死
    printf("logger module is dead, where is the manager ?? please take a look !!!important !!!\n");
    for(tmp = 0;tmp < 10;tmp++)
	  printf("******************************\n");
  }
  else
    printf("logger module is fixed, now it's good working ...file_path = %s\n",file_path);//修复成功
}
//
//error log错误日志记录
void xlog_err(char* err_msg){
  if(xsig == 0){
    xt = time(NULL);
    xcount = 0;
    xsig = 1;
    //强行执行一次冲刷
    fflush(fd);
  }
  time_t t = time(NULL);//只是原始码--只有数字--一共10位, 月日时分秒, 2位一组
  struct tm *loc = localtime(&t);//转换成本地时间
  memset(&xlog_buf,'\0',xlog_buf_len);//格式化缓冲区
  //char xtmp_buf[32];
  sprintf(xlog_buf,"%d/%d/%d-_-%d:%d:%d__",loc->tm_year, loc->tm_mon, loc->tm_mday,loc->tm_hour, loc->tm_min, loc->tm_sec);
  int tmp = 0;
  sprintf(&xlog_buf,"%s%s",xlog_buf,err_msg);
  int len = strlen(xlog_buf) + 1;
  //printf("%s\n",xlog_buf);printf("len = %d\n",len);//for test
  //tmp = fwrite(xlog_buf,len,xlog_buf_len,fd);//fwrite 按照二进制来写入--遇到数字变整形
  //tmp = fwrite(xlog_buf,sizeof(char),len,fd);//整形可能是4bit
  tmp = fprintf(fd,"%s\n",xlog_buf);//fprintf 是纯字符写入, 同样是缓存再写
  if(tmp != len){
	printf("xlog_fix start because fprintf error??tmp = %d, len = %d\n",tmp,len);
	xlog_fix();
  }
  else{
    //超出100w bit 就换文件
	printf("%s\n",xlog_buf);
    file_size_cur = file_size_cur + len;
    if(file_size_cur > file_size_max){
      printf("xlog_fix start because file_size_cur reset??file_size_cur = %d, file_size_max = %d\n",file_size_cur,file_size_max);
      xlog_fix();
    }
  }
  //超出20 次写入就冲刷一次,  超过20s 就冲刷一次
  if(xcount == 20)
	xsig = 0;
  if(t - xt > 20)
	xsig = 0;
}
//
//生成加密字典
int dictionary_size = 10001;
void xlog_dictionary(void){
  int xfd = fopen("./dictionary.x","a+");
  if(xfd == -1){
	printf("cant fopen ./dictionary.x !!errno = %d",errno);
	return;
  }
  char xhead[] = "unsigned int = {";
  char xbuf[32];
  unsigned int tmp = get_xrandom();
  char xend[32];
  sprintf(&xend,"%d};",tmp);
  unsigned int xramdom;
  //执行写入
  fprintf(xfd,"%s",xhead);
  for(tmp = 0;tmp < dictionary_size;tmp++){
	xramdom = get_xrandom();
	sprintf(&xbuf,"%d,",xramdom);
	fprintf(xfd,"%s",xbuf);
  }
  fprintf(xfd,"%s",xend);
  fflush(xfd);
  fclose(xfd);
}
