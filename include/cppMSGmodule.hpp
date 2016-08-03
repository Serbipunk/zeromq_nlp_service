#include <iostream>
#include <string>

using namespace std;

class CppMsgModule {
public:
	static bool msgStrToPcharArray(char**& pchar_array, int& count_array, const string& msg_str);

	static bool idArrayToMsgStr(string& msg_str, const int* p_id, const int count_id);
};
