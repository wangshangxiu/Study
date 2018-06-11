#include <stdio.h>
#include <hiredis/hiredis.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
int main(int argc, char *argv[])
{
	if (argc < 2) {
		//printf("command err, input e.g.: %s ipaddress\n", argv[0]);
		printf("command err, input format: comm_name ipaddress auth\n");
		return 0;
	}

	redisContext *conn = redisConnect(argv[1], 6379);
	if (conn != NULL && conn->err) {
		printf("connection error: %s\n", conn->errstr);
		return 0;
	}
	
	redisReply *reply;
	//reply = (redisReply*)redisCommand(conn, "Auth %s", argv[2]);
	reply = (redisReply*)redisCommand(conn, "Auth %s", "123$abc");
	if ((strcmp(reply->str, "OK") == 0)){
		printf("auth successfully!\n");
	}
	freeReplyObject(reply);

	reply = (redisReply*)redisCommand(conn, "Keys *");
	if (reply->type == REDIS_REPLY_ARRAY && reply->elements != 0) {
		printf("total keys = %d\n", (int)reply->elements);
		static int cnt = 0;
		for(int i = 0; i < reply->elements; i++) {
			printf("order%d = %s, ", i, reply->element[i]->str);
			#if 0
			redisReply* ry = (redisReply*)redisCommand(conn, "HLEN %s", 
							reply->element[i]->str);
			if(ry->type == REDIS_REPLY_INTEGER && ry->integer < 17) {						printf("%s hlen = %d\n", reply->element[i]->str, (int)ry->integer);
			     cnt++;
			     //redisCommand(conn, "Del %s", reply->element[i]->str);	
			}
			freeReplyObject(ry);	
			#endif
			redisReply* ry = (redisReply*)redisCommand(conn, "HGET %s %s", 
				reply->element[i]->str, "TransactTime");	
			if (ry->type == REDIS_REPLY_STRING) {
				long t = atol(ry->str);
    				struct tm* localtm = localtime(&t);
    				char buf[60];
				strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S",localtm);
				printf("transcatime = %s\n", buf);
			}

			freeReplyObject(ry);		
		}
		printf("del keys = %d\n", cnt);
	}
	freeReplyObject(reply);
	
/*	reply = (redisReply*)redisCommand(conn, "SET %s %s", "foo", "bar");
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
*/	
/*	redisGetReply(conn,(void**)&reply);//unpredictable
	printf("%s\n", reply->str);
	freeReplyObject(reply);
*/	
	redisFree(conn);
	return 0;
}
