//
//  Use this file to import your target's public headers that you would like to expose to Swift.
//

typedef void* CPersonModel;

#ifdef __cplusplus
extern "C" {
#endif
void printHellow(void);
int getRandomInt(void);


void player();

//Demo测试
CPersonModel create();
CPersonModel createBy(const char* name,int age);
void printPersonInfo(CPersonModel model);
const char* getPersonName(CPersonModel model);
void destoryModel(CPersonModel model);

#ifdef __cplusplus
}
#endif
