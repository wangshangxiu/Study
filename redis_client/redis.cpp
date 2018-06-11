#include <stdio.h>
#include <hiredis/hiredis.h>
#include <string.h>
int main(int argc, char *argv[])
{
	redisContext *conn = redisConnect("127.0.0.1", 6379);
	if (conn != NULL && conn->err) {
		printf("connection error: %s\n", conn->errstr);
		return 0;
	}
	
	redisReply *reply;
	reply = (redisReply*)redisCommand(conn, "Auth %s", "hugo123456");
	if ((strcmp(reply->str, "OK") == 0)){
		printf("auth successfully!\n");
	}
	freeReplyObject(reply);

	reply = (redisReply*)redisCommand(conn, "SET %s %s", "foo", "bar");
	freeReplyObject(reply);

	reply = (redisReply*)redisCommand(conn, "GET %s", "foo");
	printf("%s\n", reply->str);
	freeReplyObject(reply);
	
	
	redisAppendCommand(conn, "SET %s %s", "look", "carefully");
	redisAppendCommand(conn, "SET %s %s", "go", "ahead");
	redisGetReply(conn,(void**)&reply); // SET命令的返回
	printf("%s\n", reply->str);
	freeReplyObject(reply);
	
	redisGetReply(conn,(void**)&reply); // SET命令的返回
	printf("%s\n", reply->str);
	freeReplyObject(reply);
	
/*	redisGetReply(conn,(void**)&reply);//unpredictable
	printf("%s\n", reply->str);
	freeReplyObject(reply);
*/	
	redisFree(conn);
	return 0;
}
