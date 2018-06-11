#include<hiredis/hiredis.h>
#include<time.h>
#include<iostream>
#include<string.h>
#include <unistd.h>

using namespace std;
#define REDIS_TIMEOUT_SEC	10 
#define REDIS_TIMEOUT_MICR	200
#define REDIS_RECONNECT		10


int main(int argc, char *argv[]) {
	redisContext* context = NULL;
	struct timeval timeout = {REDIS_TIMEOUT_SEC, REDIS_TIMEOUT_MICR};
        context = redisConnectWithTimeout("47.75.72.244", 6379, timeout);
	if(context->err) {
		redisFree(context); 
		printf("connect redisServer err:%s\n", context->errstr);
		return -1;
	} 

	printf("connect redisServer success\n"); 

        redisReply *reply = (redisReply *)redisCommand(context, "auth %s", "123$abc");
        if (strcmp(reply->str, "OK") != 0) {
            printf("auth error, err=%s\n", reply->str);
            freeReplyObject(reply);
            return -1;
        } else {
            printf("auth successfully\n");
            freeReplyObject(reply);
        }

//        const char *cmd = "SET test 100";
        while(true) {
            reply = (redisReply *)redisCommand(context, "SMEMBERS %d", 10005);

            if (reply->type == REDIS_REPLY_ERROR) {
                    printf("command execute failure\n");
                    redisFree(context);
                    return -1;
            } else if (reply->type == REDIS_REPLY_ARRAY) {
                for(int i = 0; i < reply->elements; i++) {
                    if (reply->element[i]->type = REDIS_REPLY_STRING) {
                        cout << reply->element[i]->str << endl;
                        char* hashkey = reply->element[i]->str;
                        redisReply* hashRy = (redisReply*)redisCommand(context, "HGET %s %s", hashkey, "Symbol");
                        if (hashRy->type == REDIS_REPLY_STRING) {
                            cout << "Symbol:" << hashRy->str << endl;
                        }
                        freeReplyObject(hashkey);
                    } else {
                        ;
                    }
                }

               freeReplyObject(reply);
            } else {
                ;
            }


                //返回执行结果为状态的命令。比如set命令的返回值的类型是REDIS_REPLY_STATUS，然后只有当返回信息是"OK"时，才表示该命令执行成功。可以通过reply->str得到文字信息
        //	if(!(reply->type == REDIS_REPLY_STATUS && strcmp(reply->str, "OK") == 0)) {
        //		printf("command execute failure:%s\n", cmd);
        //		freeReplyObject(reply);
        //		redisFree(context);
        //		return -1;
        //	}

        //	freeReplyObject(reply);
        //	printf("%s execute success\n", cmd);

        //	const char *getVal = "GET test";
        //	reply = (redisReply *)redisCommand(context, getVal);

        //	if(reply->type != REDIS_REPLY_STRING)
        //	{
        //		printf("command execute failure:%s\n", getVal);
        //		freeReplyObject(reply);
        //		redisFree(context);
        //		return -1;
        //	}

        //	printf("GET test:%s\n", reply->str);
            printf("%s execute success\n", "SMEMBERS 10005");
            sleep(1.5);
        }

        redisFree(context);
}

