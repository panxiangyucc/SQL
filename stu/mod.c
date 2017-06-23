#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"

char * headname = "head.html";
char * footname = "footer.html";
int cgiMain()
{
  FILE * fd;

	char sno[12] = "\0";
	char sname[10] = "\0";
	char sbirthday[12] = "\0";
	char ssex[2] = "\0";
	char sphone[11] = "\0";
	int status = 0;

	char ch;

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");
	if(!(fd = fopen(headname, "r"))){
		fprintf(cgiOut, "Cannot open file, %s\n", headname);
		return -1;
	}
	ch = fgetc(fd);

	while(ch != EOF){
		fprintf(cgiOut, "%c", ch);
		ch = fgetc(fd);
	}
fclose(fd);

	status = cgiFormString("sno",  sno, 12);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get sno error!\n");
		return 1;
	}

	status = cgiFormString("sname",  sname, 10);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get sname error!\n");
		return 1;
	}

  status = cgiFormString("ssex",  ssex, 10);
  if (status != cgiFormSuccess)
  {
    fprintf(cgiOut, "get ssex error!\n");
    return 1;
  }

	status = cgiFormString("sbirthday",  sbirthday, 12);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get sbirthday error!\n");
		return 1;
	}

	status = cgiFormString("sphone",  sphone, 11);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get sphone error!\n");
		return 1;
	}

	//fprintf(cgiOut, "name = %s, age = %s, stuId = %s\n", name, age, stuId);

	int ret;
	char sql[128] = "\0";
	MYSQL *db;

	//初始化
	db = mysql_init(NULL);
	mysql_options(db, MYSQL_SET_CHARSET_NAME, "utf8");
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_init fail:%s\n", mysql_error(db));
		return -1;
	}

	//连接数据库
	db = mysql_real_connect(db, "127.0.0.1", "root", "123456", "stu",  3306, NULL, 0);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_real_connect fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}


	sprintf(sql, "update information set sname= '%s', sbirthday= '%s', ssex= '%s', \
sphone= %d where sno= %d ",  sname, sbirthday, ssex, atoi(sphone), atoi(sno));

	fprintf(cgiOut, "%s<hr>", sql);

	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}



	fprintf(cgiOut, "update student ok!\n");
	mysql_close(db);
	return 0;
}
