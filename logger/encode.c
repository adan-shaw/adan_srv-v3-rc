/*
 * encode.c
 *
 *  Created on: 2017/5/18
 *      Author: adan shaw
 */

//
//数据帧	-- 一共512
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
//
//数据帧	--这么想吧,mbuf 本来128 bit, 减去ip 头,20, 减去tcp 头 20... 还有mbuf 本身的大小8, 所以剩下只有 80bit 可用
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
//
//获取加密钥匙--unsigned int
void get_key(struct xkey* xtmp){
  xtmp->key1 = get_Xrandom();
  xtmp->key2 = get_Xrandom();
  xtmp->key3 = get_Xrandom();
  xtmp->key4 = get_Xrandom();
  xtmp->key5 = get_Xrandom();
  xtmp->key6 = get_Xrandom();
  xtmp->key7 = get_Xrandom();
  xtmp->key8 = get_Xrandom();
}
//
//拆分单个随机数, 用来加密字符, 因为字符都是1bit, 而钥匙是4 bit
//
//加密-unsigned int 部分
void encode_uint(struct data_frame* pdata,struct xkey* pxkey){

  pdata->comm = pxkey->key1 + pdata->comm - 123;
  pdata->uid = pxkey->key2 + pdata->uid - 456;
  pdata->age = pxkey->key3 + pdata->age - 789;
  pdata->sex = pxkey->key4 + pdata->sex - 147;
  pdata->zip_code = pxkey->key5 + pdata->zip_code - 258;
  pdata->qq_code = pxkey->key6 + pdata->qq_code - 369;
  pdata->ts = pxkey->key7 + pdata->ts - 321;
  pdata->u_backup = pxkey->key8 + pdata->u_backup - 654;
/*
  pdata->comm = pxkey->key1 + pdata->comm;
  pdata->uid = pxkey->key2 + pdata->uid;
  pdata->age = pxkey->key3 + pdata->age;
  pdata->sex = pxkey->key4 + pdata->sex;
  pdata->zip_code = pxkey->key5 + pdata->zip_code;
  pdata->qq_code = pxkey->key6 + pdata->qq_code;
  pdata->ts = pxkey->key7 + pdata->ts;
  pdata->u_backup = pxkey->key8 + pdata->u_backup;
  */
}
//
//加密字符部分--char
void encode_char(struct data_frame* pdata,struct xkey* pxkey){
  int tmp,tmp2;
  int count = 0;
  for(tmp = 0;tmp < 2;tmp++){
	pdata->uname[count] = pdata->uname[count] + pxkey->key1 + 1;//高位全部被截取了而已, 其实还是可行的
	count++;												    //4 bit 有前3 bit 被截取了, 但是直接相加并没有错
	pdata->uname[count] = pdata->uname[count] + pxkey->key2 + 2;
	count++;
	pdata->uname[count] = pdata->uname[count] + pxkey->key3 + 3;
	count++;
	pdata->uname[count] = pdata->uname[count] + pxkey->key4 + 4;
	count++;
	pdata->uname[count] = pdata->uname[count] + pxkey->key5 + 5;
	count++;
	pdata->uname[count] = pdata->uname[count] + pxkey->key6 + 6;
	count++;
	pdata->uname[count] = pdata->uname[count] + pxkey->key7 + 7;
	count++;
	pdata->uname[count] = pdata->uname[count] + pxkey->key8 + 8;
	count++;
  }
  //
  //
  count = 0;
  for(tmp = 0;tmp < 2;tmp++){
	pdata->upw[count] = pdata->upw[count] + pxkey->key4 + 9;//高位全部被截取了而已, 其实还是可行的
	count++;												//4 bit 有前3 bit 被截取了, 但是直接相加并没有错
	pdata->upw[count] = pdata->upw[count] + pxkey->key3 + 8;
	count++;
	pdata->upw[count] = pdata->upw[count] + pxkey->key2 + 7;
	count++;
	pdata->upw[count] = pdata->upw[count] + pxkey->key1 + 6;
	count++;
	pdata->upw[count] = pdata->upw[count] + pxkey->key5 + 5;
	count++;
	pdata->upw[count] = pdata->upw[count] + pxkey->key6 + 4;
	count++;
	pdata->upw[count] = pdata->upw[count] + pxkey->key7 + 3;
	count++;
	pdata->upw[count] = pdata->upw[count] + pxkey->key8 + 2;
	count++;
  }
  //
  //
  count = 0;
  for(tmp = 0;tmp < 4;tmp++){
	pdata->s_backup[count] = pdata->s_backup[count] + pxkey->key8 + 9;
	count++;
	pdata->s_backup[count] = pdata->s_backup[count] + pxkey->key1 + 8;
	count++;
	pdata->s_backup[count] = pdata->s_backup[count] + pxkey->key7 + 7;
	count++;
	pdata->s_backup[count] = pdata->s_backup[count] + pxkey->key2 + 6;
	count++;
	pdata->s_backup[count] = pdata->s_backup[count] + pxkey->key6 + 5;
	count++;
	pdata->s_backup[count] = pdata->s_backup[count] + pxkey->key3 + 4;
	count++;
	pdata->s_backup[count] = pdata->s_backup[count] + pxkey->key5 + 3;
	count++;
	pdata->s_backup[count] = pdata->s_backup[count] + pxkey->key4 + 2;
	count++;
  }
  //
  //384 = 12 * 4* 8
  count = 0;
  for(tmp = 0;tmp < 48;tmp++){
	pdata->buf[count] = pdata->buf[count] + pxkey->key5 + 1;
	count++;
	pdata->buf[count] = pdata->buf[count] + pxkey->key1 + 8;
	count++;
	pdata->buf[count] = pdata->buf[count] + pxkey->key8 + 7;
	count++;
	pdata->buf[count] = pdata->buf[count] + pxkey->key6 + 9;
	count++;
	pdata->buf[count] = pdata->buf[count] + pxkey->key2 + 5;
	count++;
	pdata->buf[count] = pdata->buf[count] + pxkey->key3 + 4;
	count++;
	pdata->buf[count] = pdata->buf[count] + pxkey->key4 + 2;
	count++;
	pdata->buf[count] = pdata->buf[count] + pxkey->key7 + 2;
	count++;
  }
}
//
//
//解密-unsigned int 部分
void decode_uint(struct data_frame* pdata,struct xkey* pxkey){

  pdata->comm = pdata->comm - pxkey->key1  + 123;
  pdata->uid = pdata->uid - pxkey->key2 + 456;
  pdata->age = pdata->age - pxkey->key3 + 789;
  pdata->sex = pdata->sex - pxkey->key4 + 147;
  pdata->zip_code = pdata->zip_code - pxkey->key5 + 258;
  pdata->qq_code = pdata->qq_code - pxkey->key6 + 369;
  pdata->ts = pdata->ts - pxkey->key7 + 321;
  pdata->u_backup = pdata->u_backup - pxkey->key8 + 654;
  /*
  pdata->comm = pxkey->key1 - pdata->comm;
  pdata->uid = pxkey->key2 - pdata->uid;
  pdata->age = pxkey->key3 - pdata->age;
  pdata->sex = pxkey->key4 - pdata->sex;
  pdata->zip_code = pxkey->key5 - pdata->zip_code;
  pdata->qq_code = pxkey->key6 - pdata->qq_code;
  pdata->ts = pxkey->key7 - pdata->ts;
  pdata->u_backup = pxkey->key8 - pdata->u_backup;
  */
}
//
//解密字符部分--char
void decode_char(struct data_frame* pdata,struct xkey* pxkey){
  int tmp,tmp2;
  int count = 0;
  for(tmp = 0;tmp < 2;tmp++){
	pdata->uname[count] = pdata->uname[count] - pxkey->key1 - 1;//高位全部被截取了而已, 其实还是可行的
	count++;												    //4 bit 有前3 bit 被截取了, 但是直接相加并没有错
	pdata->uname[count] = pdata->uname[count] - pxkey->key2 - 2;
	count++;
	pdata->uname[count] = pdata->uname[count] - pxkey->key3 - 3;
	count++;
	pdata->uname[count] = pdata->uname[count] - pxkey->key4 - 4;
	count++;
	pdata->uname[count] = pdata->uname[count] - pxkey->key5 - 5;
	count++;
	pdata->uname[count] = pdata->uname[count] - pxkey->key6 - 6;
	count++;
	pdata->uname[count] = pdata->uname[count] - pxkey->key7 - 7;
	count++;
	pdata->uname[count] = pdata->uname[count] - pxkey->key8 - 8;
	count++;
  }
  //
  //
  count = 0;
  for(tmp = 0;tmp < 2;tmp++){
	pdata->upw[count] = pdata->upw[count] - pxkey->key4 - 9;//高位全部被截取了而已, 其实还是可行的
	count++;												//4 bit 有前3 bit 被截取了, 但是直接相加并没有错
	pdata->upw[count] = pdata->upw[count] - pxkey->key3 - 8;
	count++;
	pdata->upw[count] = pdata->upw[count] - pxkey->key2 - 7;
	count++;
	pdata->upw[count] = pdata->upw[count] - pxkey->key1 - 6;
	count++;
	pdata->upw[count] = pdata->upw[count] - pxkey->key5 - 5;
	count++;
	pdata->upw[count] = pdata->upw[count] - pxkey->key6 - 4;
	count++;
	pdata->upw[count] = pdata->upw[count] - pxkey->key7 - 3;
	count++;
	pdata->upw[count] = pdata->upw[count] - pxkey->key8 - 2;
	count++;
  }
  //
  //
  count = 0;
  for(tmp = 0;tmp < 4;tmp++){
	pdata->s_backup[count] = pdata->s_backup[count] - pxkey->key8 - 9;
	count++;
	pdata->s_backup[count] = pdata->s_backup[count] - pxkey->key1 - 8;
	count++;
	pdata->s_backup[count] = pdata->s_backup[count] - pxkey->key7 - 7;
	count++;
	pdata->s_backup[count] = pdata->s_backup[count] - pxkey->key2 - 6;
	count++;
	pdata->s_backup[count] = pdata->s_backup[count] - pxkey->key6 - 5;
	count++;
	pdata->s_backup[count] = pdata->s_backup[count] - pxkey->key3 - 4;
	count++;
	pdata->s_backup[count] = pdata->s_backup[count] - pxkey->key5 - 3;
	count++;
	pdata->s_backup[count] = pdata->s_backup[count] - pxkey->key4 - 2;
	count++;
  }
  //
  //384 = 12 * 4* 8
  count = 0;
  for(tmp = 0;tmp < 48;tmp++){
	pdata->buf[count] = pdata->buf[count] - pxkey->key5 - 1;
	count++;
	pdata->buf[count] = pdata->buf[count] - pxkey->key1 - 8;
	count++;
	pdata->buf[count] = pdata->buf[count] - pxkey->key8 - 7;
	count++;
	pdata->buf[count] = pdata->buf[count] - pxkey->key6 - 9;
	count++;
	pdata->buf[count] = pdata->buf[count] - pxkey->key2 - 5;
	count++;
	pdata->buf[count] = pdata->buf[count] - pxkey->key3 - 4;
	count++;
	pdata->buf[count] = pdata->buf[count] - pxkey->key4 - 2;
	count++;
	pdata->buf[count] = pdata->buf[count] - pxkey->key7 - 2;
	count++;
  }
}
//
//隐藏钥匙
void hide_key(struct data_frame* pdata,struct xkey* pxkey){
  //钥匙换位
  pdata->key[1] = pdata->comm;
  pdata->key[2] = pdata->uid;
  pdata->key[3] = pdata->age;
  pdata->key[4] = pdata->sex;
  pdata->key[5] = pdata->zip_code;
  pdata->key[6] = pdata->qq_code;
  pdata->key[7] = pdata->ts;
  pdata->key[0] = pdata->u_backup;
  //钥匙赋值 并硬性掩码
  pdata->comm = pxkey->key1 + 357;
  pdata->uid = pxkey->key2 + 369;
  pdata->age = pxkey->key3 + 25;
  pdata->sex = pxkey->key4 + 18;
  pdata->zip_code = pxkey->key5 + 9;
  pdata->qq_code = pxkey->key6;
  pdata->ts = pxkey->key7 + 1020;
  pdata->u_backup = pxkey->key8 + 999;
}
//
//恢复钥匙
void restore_key(struct data_frame* pdata,struct xkey* pxkey){
  //恢复获取
  pxkey->key1 = pdata->comm - 357;
  pxkey->key2 = pdata->uid - 369;
  pxkey->key3 = pdata->age - 25;
  pxkey->key4 = pdata->sex - 18;
  pxkey->key5 = pdata->zip_code - 9;
  pxkey->key6 = pdata->qq_code;
  pxkey->key7 = pdata->ts - 1020;
  pxkey->key8 = pdata->u_backup - 999;
  //恢复uint 数据
  pdata->comm = pdata->key[1];
  pdata->uid = pdata->key[2];
  pdata->age = pdata->key[3];
  pdata->sex = pdata->key[4];
  pdata->zip_code = pdata->key[5];
  pdata->qq_code = pdata->key[6];
  pdata->ts = pdata->key[7];
  pdata->u_backup = pdata->key[0];
}
//***********************************************
//加密-data_frame2
void encode_all2(struct data_frame2* pdata,struct xkey* pxkey){
  pdata->comm = pxkey->key1 + pdata->comm - 123;
  pdata->uid = pxkey->key2 + pdata->uid - 456;
  pdata->age = pxkey->key3 + pdata->age - 789;
  pdata->sex = pxkey->key4 + pdata->sex - 147;
  pdata->zip_code = pxkey->key5 + pdata->zip_code - 258;
  pdata->qq_code = pxkey->key6 + pdata->qq_code - 369;
  pdata->ts = pxkey->key7 + pdata->ts - 321;
  pdata->u_backup = pxkey->key8 + pdata->u_backup - 654;
  int tmp;
  int count = 0;
  for(tmp = 0;tmp < 2;tmp++){
	pdata->upw[count] = pdata->upw[count] + pxkey->key4 + 9;//高位全部被截取了而已, 其实还是可行的
	count++;												//4 bit 有前3 bit 被截取了, 但是直接相加并没有错
	pdata->upw[count] = pdata->upw[count] + pxkey->key3 + 8;
	count++;
	pdata->upw[count] = pdata->upw[count] + pxkey->key2 + 7;
	count++;
	pdata->upw[count] = pdata->upw[count] + pxkey->key1 + 6;
	count++;
	pdata->upw[count] = pdata->upw[count] + pxkey->key5 + 5;
	count++;
	pdata->upw[count] = pdata->upw[count] + pxkey->key6 + 4;
	count++;
	pdata->upw[count] = pdata->upw[count] + pxkey->key7 + 3;
	count++;
	pdata->upw[count] = pdata->upw[count] + pxkey->key8 + 2;
	count++;
  }
}
//
//解密-data_frame2
void decode_all2(struct data_frame2* pdata,struct xkey* pxkey){
  pdata->comm = pdata->comm - pxkey->key1  + 123;
  pdata->uid = pdata->uid - pxkey->key2 + 456;
  pdata->age = pdata->age - pxkey->key3 + 789;
  pdata->sex = pdata->sex - pxkey->key4 + 147;
  pdata->zip_code = pdata->zip_code - pxkey->key5 + 258;
  pdata->qq_code = pdata->qq_code - pxkey->key6 + 369;
  pdata->ts = pdata->ts - pxkey->key7 + 321;
  pdata->u_backup = pdata->u_backup - pxkey->key8 + 654;
  int tmp;
  int count = 0;
  count = 0;
  for(tmp = 0;tmp < 2;tmp++){
	pdata->upw[count] = pdata->upw[count] - pxkey->key4 - 9;//高位全部被截取了而已, 其实还是可行的
	count++;												//4 bit 有前3 bit 被截取了, 但是直接相加并没有错
	pdata->upw[count] = pdata->upw[count] - pxkey->key3 - 8;
	count++;
	pdata->upw[count] = pdata->upw[count] - pxkey->key2 - 7;
	count++;
	pdata->upw[count] = pdata->upw[count] - pxkey->key1 - 6;
	count++;
	pdata->upw[count] = pdata->upw[count] - pxkey->key5 - 5;
	count++;
	pdata->upw[count] = pdata->upw[count] - pxkey->key6 - 4;
	count++;
	pdata->upw[count] = pdata->upw[count] - pxkey->key7 - 3;
	count++;
	pdata->upw[count] = pdata->upw[count] - pxkey->key8 - 2;
	count++;
  }
}

