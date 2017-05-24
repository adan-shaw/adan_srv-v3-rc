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
#define BUF_SIZE 384
struct data_frame{
  unsigned int key[8];		//32 = 8*4	-- 加密钥匙		--32
  unsigned int comm;		//4 -- 命令					--32
  unsigned int uid;			//4 -- uid
  unsigned int age;			//4 -- age
  unsigned int sex;			//4 -- sex
  unsigned int zip_code;	//4 -- 邮编
  unsigned int qq_code;		//4 -- qq 号码用整形记住, 到时候再转string
  unsigned int ts;			//4 -- 校验时所需的时间戳
  unsigned int u_backup;	//4 -- 备用
  //
  char uname[16];			//16						--32
  char upw[16];				//16
  char s_backup[32];		//32						--32
  char buf[BUF_SIZE];		//BUF_SIZE					--384
};
// 32 + 32 + 16 刚好就是 80
struct data_frame2{
  unsigned int key[8];		//32 = 8*4	-- 加密钥匙		--32
  unsigned int comm;		//4 -- 命令					--32
  unsigned int uid;			//4 -- uid
  unsigned int age;			//4 -- age
  unsigned int sex;			//4 -- sex
  unsigned int zip_code;	//4 -- 邮编
  unsigned int qq_code;		//4 -- qq 号码用整形记住, 到时候再转string
  unsigned int ts;			//4 -- 校验时所需的时间戳
  unsigned int u_backup;	//4 -- 备用
  //
  char upw[16];				//16						--16
};
//
//钥匙--unsigned int
struct xkey{
  unsigned int key1;
  unsigned int key2;
  unsigned int key3;
  unsigned int key4;
  unsigned int key5;
  unsigned int key6;
  unsigned int key7;
  unsigned int key8;
};
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
  for(;tmp < 20000;tmp++){
	xlog(test,10);
	xlog_err("if you seek amy tonight !!");
  }
  printf("%d\n",start-time());
  printf("\n19000 times\n");
  xlog_close();
  //
  //字典生成工具测试
  xlog_dictionary();
  //
  //字典随机数测试--百万测试
  int test_count = 0;
  int test_err = 0;
  for(tmp=0;tmp<1000000;tmp++){
  unsigned int xtmp = get_xrandom();
  test_count++;
  if(xtmp < 0){
    printf("%d\n",xtmp);
  	test_err++;
  }
  }
  printf("%d test finish,error count = %d\n",test_count,test_err);




  //
  //
  //加密测试

//
//



struct data_frame xtest;
xtest.comm = 1;
xtest.uid = 2;
xtest.age = 3;
xtest.sex = 4;
xtest.zip_code = 5;
xtest.qq_code = 6;
xtest.ts = 7;
xtest.u_backup = 8;

sprintf(xtest.uname,"%s","a");
sprintf(xtest.upw,"%s","b");
sprintf(xtest.s_backup,"%s","c");
sprintf(xtest.buf,"%s","d");






printf("原文～～～～～～～first\n");
//
//打印原文
printf("%d",xtest.comm);
printf("\n");
printf("%d",xtest.uid);
printf("\n");
printf("%d",xtest.age );
printf("\n");
printf("%d",xtest.sex);
printf("\n");
printf("%d",xtest.zip_code);
printf("\n");
printf("%d",xtest.qq_code);
printf("\n");
printf("%d",xtest.ts);
printf("\n");
printf("%d",xtest.u_backup);
printf("\n");
//
printf("%s",xtest.uname);
printf("\n");
printf("%s",xtest.upw);
printf("\n");
printf("%s",xtest.s_backup);
printf("\n");
printf("%s",xtest.buf);
printf("\n");

//
struct xkey xxkey;
get_key(&xxkey);
encode_uint(&xtest,&xxkey);
encode_char(&xtest,&xxkey);
hide_key(&xtest,&xxkey);//隐藏钥匙frist
//
//打印密文
printf("密文～～～～～～～second\n");
printf("%d",xtest.comm);
printf("\n");
printf("%d",xtest.uid);
printf("\n");
printf("%d",xtest.age );
printf("\n");
printf("%d",xtest.sex);
printf("\n");
printf("%d",xtest.zip_code);
printf("\n");
printf("%d",xtest.qq_code);
printf("\n");
printf("%d",xtest.ts);
printf("\n");
printf("%d",xtest.u_backup);
printf("\n");
//
printf("%s",xtest.uname);
printf("\n");
printf("%s",xtest.upw);
printf("\n");
printf("%s",xtest.s_backup);
printf("\n");
printf("%s",xtest.buf);
printf("\n");
//
restore_key(&xtest,&xxkey);//还原钥匙frist
decode_uint(&xtest,&xxkey);
decode_char(&xtest,&xxkey);
//
//打印结果
printf("解密文～～～～～～～last\n");
printf("%d",xtest.comm);
printf("\n");
printf("%d",xtest.uid);
printf("\n");
printf("%d",xtest.age );
printf("\n");
printf("%d",xtest.sex);
printf("\n");
printf("%d",xtest.zip_code);
printf("\n");
printf("%d",xtest.qq_code);
printf("\n");
printf("%d",xtest.ts);
printf("\n");
printf("%d",xtest.u_backup);
printf("\n");
//
printf("%s",xtest.uname);
printf("\n");
printf("%s",xtest.upw);
printf("\n");
printf("%s",xtest.s_backup);
printf("\n");
printf("%s",xtest.buf);
printf("\n");

//***********************************************************************************************************
struct data_frame2 xtest2;
xtest2.comm = 12;
xtest2.uid = 22;
xtest2.age = 32;
xtest2.sex = 42;
xtest2.zip_code = 52;
xtest2.qq_code = 62;
xtest2.ts = 72;
xtest2.u_backup = 82;

sprintf(xtest2.upw,"%s","bbbb");

printf("原文2222222222～～～～～～～first\n");
//
//打印原文
printf("%d",xtest2.comm);
printf("\n");
printf("%d",xtest2.uid);
printf("\n");
printf("%d",xtest2.age );
printf("\n");
printf("%d",xtest2.sex);
printf("\n");
printf("%d",xtest2.zip_code);
printf("\n");
printf("%d",xtest2.qq_code);
printf("\n");
printf("%d",xtest2.ts);
printf("\n");
printf("%d",xtest2.u_backup);
printf("\n");
//
printf("%s",xtest2.upw);
printf("\n");
//
encode_all2(&xtest2,&xxkey);
hide_key(&xtest2,&xxkey);//隐藏钥匙last
//
//打印密文
printf("密文222222222222222～～～～～～～second\n");
printf("%d",xtest2.comm);
printf("\n");
printf("%d",xtest2.uid);
printf("\n");
printf("%d",xtest2.age );
printf("\n");
printf("%d",xtest2.sex);
printf("\n");
printf("%d",xtest2.zip_code);
printf("\n");
printf("%d",xtest2.qq_code);
printf("\n");
printf("%d",xtest2.ts);
printf("\n");
printf("%d",xtest2.u_backup);
printf("\n");
//
printf("%s",xtest2.upw);
printf("\n");
//
restore_key(&xtest2,&xxkey);//还原钥匙frist
decode_all2(&xtest2,&xxkey);
//
//打印结果
printf("解密文222222222222～～～～～～～last\n");
printf("%d",xtest2.comm);
printf("\n");
printf("%d",xtest2.uid);
printf("\n");
printf("%d",xtest2.age );
printf("\n");
printf("%d",xtest2.sex);
printf("\n");
printf("%d",xtest2.zip_code);
printf("\n");
printf("%d",xtest2.qq_code);
printf("\n");
printf("%d",xtest2.ts);
printf("\n");
printf("%d",xtest2.u_backup);
printf("\n");
printf("%s",xtest2.upw);
printf("\n");
//1-2s 10W 还可以啊 -- 这种方法不考虑钥匙是否能还原, 先考虑加密和密文是否能够还原, 再想办法解决key 还原问题
//是设计加密算法的一些基本要素...先考虑能不能还原, 再考虑key 还原与隐藏
printf("big data test !!\n");
int Xstart = time();
int xxxtmp = 0;
for(;xxxtmp<100000;xxxtmp++){
	get_key(&xxkey);
	encode_uint(&xtest,&xxkey);
	encode_char(&xtest,&xxkey);
	hide_key(&xtest,&xxkey);//隐藏钥匙last
	//
	encode_all2(&xtest2,&xxkey);
	hide_key(&xtest2,&xxkey);//隐藏钥匙last
	//
	restore_key(&xtest,&xxkey);//还原钥匙frist
	decode_uint(&xtest,&xxkey);
	decode_char(&xtest,&xxkey);
	//
	restore_key(&xtest2,&xxkey);//还原钥匙frist
	decode_all2(&xtest2,&xxkey);
}
int Xend = time();
printf("takes time : %d---test count = %d\n",Xend - Xstart,xxxtmp);








}
