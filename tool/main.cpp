#include <iostream>
#include <string.h>
#include "TC_process.h"

int main(int argc, char** argv) {
	// char * text = "教育部考试中心托福网考网上报名";
	// char* text = "皇马6-4马竞登顶欧冠";
	char* text = "evernote 安装最新版本后，个别笔记本无法同步？";
	// char* text = "ios私有api 能修改运营商名称吗？";
	// char* text = "提前博弈A股纳入MSCI";
	char** p_texts = &text;
	int label = 0;

	CateTeller ct;

	for(int i=0; i<1000000; ++i) {

		ct.tell(p_texts, 1, &label);
		std::cout << std::endl << label << std::endl;

	}

	return 0;
}
