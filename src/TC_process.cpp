// #include "stdafx.h"

#include "TC_process.h"

#include <memory.h>


std::vector<int> v_query;


int sqlite3_exec_callback(void *data, int n_columns, char **col_values, char **col_names)
{

    for (int i = 1; i < n_columns; i++)
    {
    	//printf("%s\t", col_values[i]);
		v_query.push_back( atoi(col_values[i]) );
    }
	//printf("\n");

    return 0;
}


void query_word(sqlite3 * conn, char * word)
{
	v_query.clear();				//��ռ������

	char * err_msg = NULL;			//������ʾ
	char sql[1000];

	sprintf(sql, "select * from [keyword] where word=\'%s\';", word);

	sqlite3_exec(conn, sql, &sqlite3_exec_callback, 0, &err_msg);
}

////
void cut(const CppJieba::SegmentInterface * seg, const char * const filePath, char * outfile, int n_word)
{
	std::ofstream ofile(outfile, std::ios::out);
	ofile << n_word << "\n";

	std::ifstream ifile(filePath);

	std::vector<std::string> res;
	std::string line;
	while(getline(ifile, line))
	{
		if(!line.empty())			//�������س���		 ����һ�������У�һ����Ҫ��ǲ���
		{
			if(line.size() < 2)			//���س��У����ߵ����У����ţ�
			{
				continue;
			}
			res.clear();
			seg->cut(line, res);
			
			//���д���
			if(res.size() < n_word)				//������NULL
			{
				int n_NULL = n_word - res.size();
				for(int i = 0; i < n_NULL; i++)
				{
					ofile << "NULL" << "\n";
				}
				for(int i = 0; i < res.size(); i++)
				{
					ofile << res.at(i).c_str();
					ofile << "\n";
				}
			}
			else
			{
				for(int i = res.size()-n_word; i < res.size(); i++)
				{
					ofile << res.at(i).c_str();
					ofile << "\n";
				}
			}


		}
	}

	res.clear();

	ifile.close();
	ofile.close();
}


void cut(const CppJieba::SegmentInterface * seg, std::list<char *> & l_lines, std::vector<std::vector<char *> *> & v_lines_words, int n_word)
{
	std::list<char *>::iterator i_l_lines = l_lines.begin();
	while( i_l_lines != l_lines.end() )
	{
		std::string line( (char *)(*i_l_lines) );
		std::vector<std::string> res0;

		std::vector<std::string> res;

		
		//���д���
		seg->cut(line, res0);

		//�ִʺ���й��˴���
		for(int i = 0; i < res0.size(); i++)
		{
			bool isINVALID = false;
			if( strcmp( res0.at(i).c_str(), "\t" ) == 0 )
			{
				isINVALID = true;
			}
			//else if( strcmp( res0.at(i).c_str(), " " ) == 0 )
			//{
			//	isINVALID = true;
			//}

			if(isINVALID == false)
			{
				res.push_back( res0.at(i) );
			}
		}
		

		std::vector<char *> * p_procRes = new std::vector<char *>;
		v_lines_words.push_back( p_procRes );

		
		if(res.size() < n_word)				//��������NULL
		{
			int n_NULL = n_word - res.size();
			for(int i = 0; i < n_NULL; i++)
			{
				//ofile << "NULL" << "\n";
				char * newWord = new char [5];
				strcpy(newWord, "NULL");
				p_procRes->push_back( newWord );
			}
			for(int i = 0; i < res.size(); i++)
			{
				//ofile << res.at(i).c_str();
				//ofile << "\n";
				int len = strlen( res.at(i).c_str() );
				char * newWord = new char [len+1];
				strcpy(newWord, res.at(i).c_str());
				p_procRes->push_back( newWord );
			}
		}
		else//�����㹻
		{
			for(int i = res.size()-n_word; i < res.size(); i++)
			{
				//ofile << res.at(i).c_str();
				//ofile << "\n";
				int len = strlen( res.at(i).c_str() );
				char * newWord = new char [len+1];
				strcpy(newWord, res.at(i).c_str());
				p_procRes->push_back( newWord );
			}
		}
		

		//�ͷ�
		res0.clear();
		res.clear();

		i_l_lines++;
	}
	
}

void cut(const CppJieba::SegmentInterface * seg, char ** p_text, int n_text, std::vector<std::vector<char *> *> & v_lines_words, int n_word)
{
	//std::list<char *>::iterator i_l_lines = l_lines.begin();
	//while( i_l_lines != l_lines.end() )
	for(int i = 0; i < n_text; i++)
	{
		//std::string line( (char *)(*i_l_lines) );
		std::string line( (char *)( p_text[i] ) );
		std::vector<std::string> res0;

		std::vector<std::string> res;

		
		//���д���
		seg->cut(line, res0);

		//�ִʺ���й��˴���
		for(int i = 0; i < res0.size(); i++)
		{
			bool isINVALID = false;
			if( strcmp( res0.at(i).c_str(), "\t" ) == 0 )
			{
				isINVALID = true;
			}
			//else if( strcmp( res0.at(i).c_str(), " " ) == 0 )
			//{
			//	isINVALID = true;
			//}

			if(isINVALID == false)
			{
				res.push_back( res0.at(i) );
			}
		}
		

		std::vector<char *> * p_procRes = new std::vector<char *>;
		v_lines_words.push_back( p_procRes );

		
		if(res.size() < n_word)				//��������NULL
		{
			int n_NULL = n_word - res.size();
			for(int i = 0; i < n_NULL; i++)
			{
				//ofile << "NULL" << "\n";
				char * newWord = new char [5];
				strcpy(newWord, "NULL");
				p_procRes->push_back( newWord );
			}
			for(int i = 0; i < res.size(); i++)
			{
				//ofile << res.at(i).c_str();
				//ofile << "\n";
				int len = strlen( res.at(i).c_str() );
				char * newWord = new char [len+1];
				strcpy(newWord, res.at(i).c_str());
				p_procRes->push_back( newWord );
			}
		}
		else//�����㹻
		{
			for(int i = res.size()-n_word; i < res.size(); i++)
			{
				//ofile << res.at(i).c_str();
				//ofile << "\n";
				int len = strlen( res.at(i).c_str() );
				char * newWord = new char [len+1];
				strcpy(newWord, res.at(i).c_str());
				p_procRes->push_back( newWord );
			}
		}
		

		//�ͷ�
		res0.clear();
		res.clear();

		//i_l_lines++;
	}
	
}



//�ļ����������ʵ��
termFilter::termFilter( const char * loadPath )
{
	std::ifstream ifile;
	ifile.open( loadPath, std::ios::in );

	char line[100];
	while( !ifile.eof() )
	{
		ifile.getline( line, 100 );

		if( strlen(line) > 0 )
		{
			char * term = new char [strlen( line ) + 1];
			strcpy(term, line);

			cantPassediterms.push_back(term);
		}

		//std::cout << line;
	}
}

void termFilter::appendFilter( char * loadPath )
{
	std::ifstream ifile;
	ifile.open( loadPath, std::ios::in );

	char line[100];
	while( !ifile.eof() )
	{
		ifile.getline( line, 100 );

		if( strlen(line) > 0 )
		{
			char * term = new char [strlen( line ) + 1];
			strcpy(term, line);

			cantPassediterms.push_back(term);
		}

		//std::cout << line;
	}
}

termFilter::~termFilter()
{
	for(int i = 0; i <cantPassediterms.size(); i++)
	{
		delete [] cantPassediterms.at(i);
	}
	cantPassediterms.clear();
}

termFilter::termFilter() {
	;
}

termFilter & termFilter::operator=(const termFilter & otf) {
	cantPassediterms.resize ( otf.cantPassediterms.size() );
	for (int i=0; i < otf.cantPassediterms.size(); ++i) {
		char * temp = new char [ strlen (otf.cantPassediterms[i]) + 1 ];
		memcpy( temp, otf.cantPassediterms[i], strlen (otf.cantPassediterms[i]) + 1 );
		cantPassediterms[i] = temp;
	}

	return (*this);
}


bool termFilter::termIsPass(char * term)
{
	for(int i = 0; i <cantPassediterms.size(); i++)
	{
		//���ҵ��ˣ�����Ϊ��
		if( strcmp( cantPassediterms.at(i), term )==0 )
		{
			return false;
		}
	}

	//��û�ҵ�������Ϊ��
	return true;
}


void cut(const CppJieba::SegmentInterface * seg, char ** p_text, int n_text, std::vector<std::vector<char *> *> & v_lines_words, int n_word, termFilter & filter)
{
	//std::list<char *>::iterator i_l_lines = l_lines.begin();
	//while( i_l_lines != l_lines.end() )
	for(int i = 0; i < n_text; i++)
	{
		//std::string line( (char *)(*i_l_lines) );
		std::string line( (char *)( p_text[i] ) );
		std::vector<std::string> res0;

		std::vector<std::string> res;

		
		//���д���
		seg->cut(line, res0);

		//�ִʺ���й��˴���
		for(int i = 0; i < res0.size(); i++)
		{
			/*
			bool isINVALID = false;
			if( strcmp( res0.at(i).c_str(), "\t" ) == 0 )
			{
				isINVALID = true;
			}
			//else if( strcmp( res0.at(i).c_str(), " " ) == 0 )
			//{
			//	isINVALID = true;
			//}

			if(isINVALID == false)
			{
				res.push_back( res0.at(i) );
			}*/
			if( filter.termIsPass( (char*)(res0.at(i).c_str()) ) )
			{
				res.push_back( res0.at(i) );
			}
		}
		

		std::vector<char *> * p_procRes = new std::vector<char *>;
		v_lines_words.push_back( p_procRes );

		
		if(res.size() < n_word)				//��������NULL
		{
			int n_NULL = n_word - res.size();
			for(int i = 0; i < n_NULL; i++)
			{
				//ofile << "NULL" << "\n";
				char * newWord = new char [5];
				strcpy(newWord, "NULL");
				p_procRes->push_back( newWord );
			}
			for(int i = 0; i < res.size(); i++)
			{
				//ofile << res.at(i).c_str();
				//ofile << "\n";
				int len = strlen( res.at(i).c_str() );
				char * newWord = new char [len+1];
				strcpy(newWord, res.at(i).c_str());
				p_procRes->push_back( newWord );
			}
		}
		else//�����㹻
		{
			for(int i = res.size()-n_word; i < res.size(); i++)
			{
				//ofile << res.at(i).c_str();
				//ofile << "\n";
				int len = strlen( res.at(i).c_str() );
				char * newWord = new char [len+1];
				strcpy(newWord, res.at(i).c_str());
				p_procRes->push_back( newWord );
			}
		}
		

		//�ͷ�
		res0.clear();
		res.clear();

		//i_l_lines++;
	}
	
}



//void textCategorization(std::list<char *>& l_text, std::list<int>& l_labels)
//����˵����p_text Ϊn_text���ַ�ָ�룻 p_labelsΪn_text����ǩ��int��ָ��
void textCategorization_new(char ** p_text, int n_text, int * p_labels, char * outputPath)
{
	int n_word = N_WORD;

	std::vector< std::vector<char *> * > v_lines_words;		//�����еĴ�����б�
	std::vector< std::vector<int> * > v_class_tf;		//ÿ������ÿ���г��ִ�Ƶ���б�
	std::vector< std::vector<double> * > v_featureVector;		//��������

	////���õĹ���
	//�ָ���seg
	CppJieba::MPSegment seg;
	//��ʼ��
	//bool init_res = seg.init("C:\\languageData_new\\jieba.dict.utf8");
	bool init_res = seg.init("dependency/jieba.dict.utf8");
	////��ʼ����ѯ����sqlite3��
	sqlite3 * conn = NULL;	//������ݿ�
	// char * err_msg = NULL;	//����ʧ�ܵ�ԭ��
	//����ݿ⣬��������
	//if( SQLITE_OK != sqlite3_open("C:\\languageData_new\\new_dictionary.sqlite", &conn) )
	if( SQLITE_OK != sqlite3_open("dependency/new_dictionary.sqlite", &conn) )
	{
		printf("can't open the database.");
		exit(-1);
	}
	//������
	//struct svm_model * svmModel = svm_load_model("C:\\languageData_new\\trainingSet.txt.model");
	struct svm_model * svmModel = svm_load_model("dependency/trainingSet.txt.model");
	//���������
	//termFilter filter("C:\\languageData_new\\symbelTerms.txt");
	termFilter filter("dependency/symbelTerms.txt");


	//cut( �ָ����� �����ļ��� ����ļ��� ���ֵĴ� )
	//cut(&seg, "title_utf8.txt", "title_res_utf8.txt", n_word);				//�ֵ�ִ�

	//cut(&seg, l_text, v_lines_words, n_word);
	cut(&seg, p_text, n_text, v_lines_words, n_word, filter);


	/*
	//����ִʽ��
	std::ofstream ofile1;
	ofile1.open("split_res.txt", std::ios::out);
	//std::vector< std::vector<char *> * > v_lines_words;
	for(int iSen = 0; iSen < v_lines_words.size(); iSen++)
	{
		std::vector<char *> * pSen = v_lines_words.at(iSen);
		for(int iWord = 0; iWord < pSen->size(); iWord++)
		{
			ofile1 << pSen->at(iWord) << "\n";
		}
	}
	ofile1.close();
	*/
	



	//��ÿ���ʣ��ڴʵ���Ѱ����Ӧ��Ƶ��
	for(int iSen = 0; iSen < v_lines_words.size(); iSen++)
	{
		std::vector<int> * pSen_fp = new std::vector<int>;
		v_class_tf.push_back(pSen_fp);

		//std::cout << "querying no." << iSen+1 << "\n";
		char message_t[50];
		//sprintf(message_t, "\rquerying no.%d", iSen+1);
		sprintf(message_t, "\r�����%d��", iSen+1);
		std::cout << message_t;

		for( int iWord = 0; iWord < (*v_lines_words.at(iSen)).size(); iWord++ )	//ÿ����10����
		{
			char * pWord = (*v_lines_words.at(iSen)).at(iWord);
			
			//����ݿ������Ƶ���ѯ
			query_word(conn, pWord);

			if( v_query.size() != N_DIMEN )		//������������
			{
				for(int i = 0; i < N_DIMEN; i++)
				{
					pSen_fp->push_back( 0 );
				}
			}
			else		//����û�г�������
			{
				for(int i = 0; i < N_DIMEN; i++)
				{
					pSen_fp->push_back( v_query.at(i) );
				}
			}
		}
	}


	/*
	//����������
	//std::vector< std::vector<int> * > v_class_tf;		//ÿ������ÿ���г��ִ�Ƶ���б�
	std::ofstream ofile;
	ofile.open( "frequency.txt", std::ios::out );
	for(int iSen = 0; iSen < v_class_tf.size(); iSen++)
	{
		std::vector<int> * pSen_fp = v_class_tf.at( iSen );
		for( int iTF = 0; iTF < pSen_fp->size(); iTF++ )
		{
			ofile << pSen_fp->at(iTF) << "\t";
		}
		ofile << "\n";
	}
	ofile.close();
	*/

	
	//�������������������
	double class_n[N_DIMEN] = {13186.0, 133915.0, 29844.0, 14694.0, 235245};	//�ʵ���ÿ��ĸ���

	//std::vector< std::vector<int> * > v_class_tf;		//ÿ������ÿ���г��ִ�Ƶ���б�
	for(int iSen = 0; iSen < v_class_tf.size(); iSen++)
	{
		std::vector<int> * fp_thisSen = v_class_tf.at(iSen);			//�����������

		std::vector<double>	* pFeatureV = new std::vector<double>;		//�������������м����������
		v_featureVector.push_back(pFeatureV);

		for(int iWord = 0; iWord < 10; iWord++)			//ÿ�乲10����
		{
			double norm_fp[N_DIMEN];			//�����һ����TF
			double max_nfp = 0.0;		//���TF
			double sum_nfp = 0.0;		//TF֮��

			for(int i = 0; i < N_DIMEN; i++)
			{
				norm_fp[i] = 10000.0 * (double)(fp_thisSen->at( N_DIMEN*iWord + i ))/class_n[i];
				sum_nfp += norm_fp[i];
				if(max_nfp < norm_fp[i])
				{
					max_nfp = norm_fp[i];
				}
			}

			max_nfp /= 10.0;		//�ǳ���10�󾭹�sigmoid����
			double f1 = 2.0/( 1.0 + exp(-0.10986*max_nfp) ) - 1.0;

			if(sum_nfp != 0)
			{
				pFeatureV->push_back( f1 );
				for(int i = 0; i < N_DIMEN; i++)
				{
					pFeatureV->push_back( norm_fp[i]/sum_nfp );
				}
			}
			else
			{
				pFeatureV->push_back( f1 );
				for(int i = 0; i < N_DIMEN; i++)
				{
					pFeatureV->push_back( 0.0 );
				}
			}
		}
	}
	

	/*
	//�����������
	//std::vector< std::vector<double> * > v_featureVector;		//��������
	std::ofstream ofile2;
	ofile2.open("featureVector.txt", std::ios::app);
	for(int iVec = 0; iVec < v_featureVector.size(); iVec++)
	{
		std::vector<double> * v_Vector = v_featureVector.at(iVec);
		for(int iCell = 0; iCell < v_Vector->size(); iCell++)
		{
			ofile2 << iCell+1 << ":" << v_Vector->at(iCell) << " ";
		}
		ofile2 << "\n";
	}
	ofile2.close();
	*/

	
	////svm������~

	for(int iFV = 0; iFV < v_featureVector.size(); iFV++)	//����ÿ����¼
	{
		std::vector<double> * pFV = v_featureVector.at(iFV);
		struct svm_node * svmData = (struct svm_node *)malloc( (50+1)*sizeof(struct svm_node) );
		for(int i = 0; i < 50; i++)
		{
			svmData[i].index = i+1;
			svmData[i].value = pFV->at(i);
		}
		svmData[50].index = -1;

		int label = svm_predict(svmModel, svmData);

		//l_labels.push_back(label);
		p_labels[iFV] = label;
		
		//std::cout << iFV+1 << " : " << label << "\n";

		free(svmData);
	}
	
	
	//���Ԥ�����
	if( outputPath != NULL )
	{
		std::ofstream ofile3;
		ofile3.open( outputPath, std::ios::out );
		for(int i = 0; i < n_text; i++)
		{
			ofile3 << p_labels[i] << "\n";
		}
		ofile3.close();
	}
	

	//����
	
	
	/////�ͷŷִ���
	seg.dispose();
	//�ر�sqlite3����
	if( SQLITE_OK != sqlite3_close(conn) )
	{
		printf("can't close the database: %s/n", sqlite3_errmsg(conn));
		exit(-1);
	}
	//�ͷŷ�����
	free(svmModel);
	//�ͷ�ȡ���б�v_lines_words
	for( int iSen = 0; iSen < v_lines_words.size(); iSen++ )
	{
		std::vector<char *> * p_vSen = v_lines_words.at(iSen);
		for(int iWord = 0; iWord < p_vSen->size(); iWord++)
		{
			delete [] (char*)(p_vSen->at(iWord));
		}
		p_vSen->clear();
	}
	v_lines_words.clear();
	//�ͷŲ�ѯ��Ƶ�б�
	for( int iSen = 0; iSen < v_class_tf.size(); iSen++ )
	{
		v_class_tf.at(iSen)->clear();
	}
	v_class_tf.clear();
	//�ͷ�������������
	for( int iVec = 0; iVec < v_featureVector.size(); iVec++ )
	{
		v_featureVector.at(iVec)->clear();
	}
	v_featureVector.clear();

	v_query.clear();

	//return p_labels;
}

CateTeller::CateTeller() {
	// load Chinese word segment tools
	bool init_res = seg.init("dependency/jieba.dict.utf8");

	// word vector data
	conn = NULL;
	if( SQLITE_OK != sqlite3_open("dependency/new_dictionary.sqlite", &conn) ) {
		printf("can't open the database.");
		exit(-1);
	}

	// svm model
	svmModel = svm_load_model("dependency/trainingSet.txt.model");

	// filter
	filter = termFilter("dependency/symbelTerms.txt");
}

CateTeller::~CateTeller() {
	/////�ͷŷִ���
	seg.dispose();
	//�ر�sqlite3����
	if( SQLITE_OK != sqlite3_close(conn) ) {
		printf("can't close the database: %s/n", sqlite3_errmsg(conn));
		exit(-1);
	}
	//�ͷŷ�����
	free(svmModel);
}

void CateTeller::tell(char ** p_text, int n_text, int * p_labels) {
	int n_word = N_WORD;

	std::vector< std::vector<char *> * > v_lines_words;		//�����еĴ�����б�
	std::vector< std::vector<int> * > v_class_tf;		//ÿ������ÿ���г��ִ�Ƶ���б�
	std::vector< std::vector<double> * > v_featureVector;		//��������

	cut(&seg, p_text, n_text, v_lines_words, n_word, filter);

	//��ÿ���ʣ��ڴʵ���Ѱ����Ӧ��Ƶ��
	for(int iSen = 0; iSen < v_lines_words.size(); iSen++)
	{
		std::vector<int> * pSen_fp = new std::vector<int>;
		v_class_tf.push_back(pSen_fp);

		//std::cout << "querying no." << iSen+1 << "\n";
		char message_t[50];
		//sprintf(message_t, "\rquerying no.%d", iSen+1);
		sprintf(message_t, "\r�����%d��", iSen+1);
		// std::cout << message_t;

		for( int iWord = 0; iWord < (*v_lines_words.at(iSen)).size(); iWord++ )	//ÿ����10����
		{
			char * pWord = (*v_lines_words.at(iSen)).at(iWord);

			//����ݿ������Ƶ���ѯ
			query_word(conn, pWord);

			if( v_query.size() != N_DIMEN )		//������������
			{
				for(int i = 0; i < N_DIMEN; i++)
				{
					pSen_fp->push_back( 0 );
				}
			}
			else		//����û�г�������
			{
				for(int i = 0; i < N_DIMEN; i++)
				{
					pSen_fp->push_back( v_query.at(i) );
				}
			}
		}
	}

	//�������������������
	double class_n[N_DIMEN] = {13186.0, 133915.0, 29844.0, 14694.0, 235245};	//�ʵ���ÿ��ĸ���

	//std::vector< std::vector<int> * > v_class_tf;		//ÿ������ÿ���г��ִ�Ƶ���б�
	for(int iSen = 0; iSen < v_class_tf.size(); iSen++)
	{
		std::vector<int> * fp_thisSen = v_class_tf.at(iSen);			//�����������

		std::vector<double>	* pFeatureV = new std::vector<double>;		//�������������м����������
		v_featureVector.push_back(pFeatureV);

		for(int iWord = 0; iWord < 10; iWord++)			//ÿ�乲10����
		{
			double norm_fp[N_DIMEN];			//�����һ����TF
			double max_nfp = 0.0;		//���TF
			double sum_nfp = 0.0;		//TF֮��

			for(int i = 0; i < N_DIMEN; i++)
			{
				norm_fp[i] = 10000.0 * (double)(fp_thisSen->at( N_DIMEN*iWord + i ))/class_n[i];
				sum_nfp += norm_fp[i];
				if(max_nfp < norm_fp[i])
				{
					max_nfp = norm_fp[i];
				}
			}

			max_nfp /= 10.0;		//�ǳ���10�󾭹�sigmoid����
			double f1 = 2.0/( 1.0 + exp(-0.10986*max_nfp) ) - 1.0;

			if(sum_nfp != 0)
			{
				pFeatureV->push_back( f1 );
				for(int i = 0; i < N_DIMEN; i++)
				{
					pFeatureV->push_back( norm_fp[i]/sum_nfp );
				}
			}
			else
			{
				pFeatureV->push_back( f1 );
				for(int i = 0; i < N_DIMEN; i++)
				{
					pFeatureV->push_back( 0.0 );
				}
			}
		}
	}


	////svm������~

	for(int iFV = 0; iFV < v_featureVector.size(); iFV++)	//����ÿ����¼
	{
		std::vector<double> * pFV = v_featureVector.at(iFV);
		struct svm_node * svmData = (struct svm_node *)malloc( (50+1)*sizeof(struct svm_node) );
		for(int i = 0; i < 50; i++)
		{
			svmData[i].index = i+1;
			svmData[i].value = pFV->at(i);
		}
		svmData[50].index = -1;

		int label = svm_predict(svmModel, svmData);

		//l_labels.push_back(label);
		p_labels[iFV] = label;

		//std::cout << iFV+1 << " : " << label << "\n";

		free(svmData);
	}

	//// do some cleanup

	//�ͷ�ȡ���б�v_lines_words
	for( int iSen = 0; iSen < v_lines_words.size(); iSen++ )
	{
		std::vector<char *> * p_vSen = v_lines_words.at(iSen);
		for(int iWord = 0; iWord < p_vSen->size(); iWord++)
		{
			delete [] (char*)(p_vSen->at(iWord));
		}
		p_vSen->clear();
	}
	v_lines_words.clear();
	//�ͷŲ�ѯ��Ƶ�б�
	for( int iSen = 0; iSen < v_class_tf.size(); iSen++ )
	{
		v_class_tf.at(iSen)->clear();
	}
	v_class_tf.clear();
	//�ͷ�������������
	for( int iVec = 0; iVec < v_featureVector.size(); iVec++ )
	{
		v_featureVector.at(iVec)->clear();
	}
	v_featureVector.clear();

	v_query.clear();

}
