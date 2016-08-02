// #include "stdafx.h"

#include <iostream>
#include <fstream>
//#include "../cppjieba/headers.h"
#include "combinition.h"

#include <vector>
#include <list>
#include <string.h>

#include "sqlite3.h"

#include <stdlib.h>
#include <stdio.h>

#include "libClassifier.h"


#define N_WORD 10
#define N_DIMEN 5

#pragma once


extern std::vector<int> v_query;


////
void cut(const CppJieba::SegmentInterface * seg, std::list<char *> & l_lines, std::vector<std::vector<char *> *> & v_lines_words, int n_word);

void cut(const CppJieba::SegmentInterface * seg, const char * const filePath, char * outfile, int n_word);

void query_word(sqlite3 * conn, char * word);

int sqlite3_exec_callback(void *data, int n_columns, char **col_values, char **col_names);


//�ļ���������
class termFilter
{
public:
	std::vector<char *> cantPassediterms;

public:
	termFilter( const char * loadPath );
	termFilter();
	~termFilter();

	termFilter & operator=(const termFilter & rhs);

	void appendFilter( char * loadPath );

	bool termIsPass(char *);
};



void cut(const CppJieba::SegmentInterface * seg, char ** p_text, int n_text, std::vector<std::vector<char *> *> & v_lines_words, int n_word, termFilter & filter);

void textCategorization_new(char ** p_text, int n_text, int * p_labels, char * outputPath=NULL);

class CateTeller {
private:
	CppJieba::MPSegment seg;
	sqlite3 * conn;
	struct svm_model * svmModel;
	termFilter filter;

public:
	CateTeller();
	~CateTeller();

	void tell(char ** p_text, int n_text, int * p_labels);
};
