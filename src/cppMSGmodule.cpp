#include "cppMSGmodule.hpp"

#include <fstream>
#include <string>
#include "titlebook.pb.h"
#include <memory.h>

using namespace std;

bool CppMsgModule::msgStrToPcharArray(char**& pchar_array, int& count_array, const string& msg_str) {

	// Verify that the version of the library that we linked against is
	// compatible with the version of the headers we compiled against.
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	tutorial::TitleList title_list;
	// fstream input("titlebook.protomodel", ios::in);
	// if (!title_list.ParseFromIstream(&input)) {
	if (!title_list.ParseFromString(msg_str)) {
		cerr << "Failed to parse title book." << endl;
		return false;
	}

	pchar_array = new char* [title_list.title_size()];
	count_array = title_list.title_size();
	
	for(int i=0; i<title_list.title_size(); ++i) {
		std::string s = title_list.title(i);
		int s_len = s.length();
		pchar_array[i] = new char [s_len+1];
		memcpy(pchar_array[i], s.c_str(), s_len+1);
	}

	// Optional:  Delete all global objects allocated by libprotobuf.
	google::protobuf::ShutdownProtobufLibrary();

	return true;
}

bool CppMsgModule::idArrayToMsgStr(string& msg_str, const int* p_id, const int count_id) {
	// Verify that the version of the library that we linked against is
	// compatible with the version of the headers we compiled against.
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	tutorial::IdList id_list;

	for(int i=0; i<count_id; ++i) {
		id_list.add_id(p_id[i]);
	}

	// serialize id_list
	int size = id_list.ByteSize();
	char* buffer = (char* )malloc(size+1);
	if(!id_list.SerializeToArray(buffer, size)) {
		return false;
	}
	buffer[size]='\0';

	msg_str = string(buffer);

	// Optional:  Delete all global objects allocated by libprotobuf.
	google::protobuf::ShutdownProtobufLibrary();

	return true;
}

#ifdef RUN_TEST

int main() {

	//load titles
	ifstream ifile ("titlebook.protomodel", ios::in);
	string msg_str;
	if (ifile.is_open())
	{
    	ifile.seekg(0, ios::end);
    	streampos size = ifile.tellg();
    	char *contents = new char [size];
    	ifile.seekg (0, ios::beg);
    	ifile.read (contents, size);
    	ifile.close();
    	//... do something with it
    	msg_str = contents;
    	//cout << contents << endl;
    	delete [] contents;
	}
	cout << msg_str << endl;

	char** pca;
	string s="fuck";
	int* pi;
	int count;

	if( CppMsgModule::msgStrToPcharArray(pca, count, msg_str) ) {
		for(int i=0; i<count; ++i) {
			cout << pca[i] << endl;
		}
	}
	else {
		cerr << "cannot parse form string" << endl;
		return -1;
	}

	// *************

	cout << endl << endl;
	string out_msg;
	int a[3] = {1, 3, 5};

	if( CppMsgModule::idArrayToMsgStr(out_msg, a, 3) ) {
		std::cout << out_msg << endl;

		fstream output("idbook.protomodel", ios::out | ios::trunc);
		output << out_msg;
		output.close();
	}
	else {
		cerr << "cannot serialize object" << endl;
		return -1;
	}
	
	return 0;
}

#endif
