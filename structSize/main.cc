#include<iostream>
using namespace std;
struct Password{
	static unsigned short  wPasswordLen;   
//	char chPasswordTxt[wPasswordLen];
};

struct EXCHANGEDPLATFORM{
	long lSubmitOrderID;
	unsigned int uiPlatFormID;
	//long lSubmitOrderID;
	//long lSubmitOrderID;
		    
	int m_status;
			//    int m_sgID;
			//        char* m_sessionID;
			//        //    char* m_json;
			//        //    int m_groupID;
			//        //    int m_clientID;
			//            uv_stream_t *m_stream;
			//                long m_loginTime;
};

int main(int argc, char *argv[]) {
//	cout << sizeof(Password) << endl;
	cout << sizeof(EXCHANGEDPLATFORM) << endl;
}
