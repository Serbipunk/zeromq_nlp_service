//#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <set>
#include <sstream>
#include <string>
#include <cstring>
#include <memory.h>


#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <cmath>

#include <stdarg.h>
#include <stdint.h>
#include <sys/types.h>
#include <cctype>
#include <functional> 
#include <locale>
#include <sys/types.h>
//#include <hash_map>
//#include <tr1/unordered_map>
#include <unordered_map>
//#include <ext/hash_map>
#include <limits>


typedef unsigned int uint;

#ifndef CPPJIEBA_HEADERS_H
#define CPPJIEBA_HEADERS_H


#endif
 

#ifndef CPPCOMMON_HEADERS_H
#define CPPCOMMON_HEADERS_H



#endif


//////argv_functs.h
#ifndef CPPCOMMON_ARGV_FUNCTS_H
#define CPPCOMMON_ARGV_FUNCTS_H

namespace CPPCOMMON
{
    using namespace std;
    bool getArgvMap(int argc, const char* const* argv, map<string, string>& mpss);
    class ArgvContext
    {
        public :
            ArgvContext(int argc, const char* const * argv);
            ~ArgvContext();
        public:
            string toString();
            string operator [](uint i);
            string operator [](const string& key);
        public:
            bool isKeyExist(const string& key);
        private:
            vector<string> _args;
            map<string, string> _mpss;
            set<string> _sset; 
	};
	
	using namespace std;
	template<typename T>
		string vecToString(const vector<T>& vec)
		{
			if(vec.empty())
			{
				return "[]";
			}
			stringstream ss;
			ss<<"["<<vec[0];
			for(unsigned int i = 1; i < vec.size(); i++)
			{
				ss<<","<<vec[i];
			}
			ss<<"]";
			return ss.str();
		}
	template<typename T>
		bool isInVec(const vector<T>& vec, const T& item)
		{
			typename vector<T>::const_iterator it	= find(vec.begin(), vec.end(), item);
			return it != vec.end();
		}
	template<typename T>
		void splitVec(const vector<T>& vecSrc, vector< pair<T, vector<T> > >& outVec, const vector<T>& patterns)
		{
			vector<T> tmp;
			T pattern;
			size_t patternSize = patterns.size();
			for(size_t i = 0; i < vecSrc.size(); i++)
			{
				size_t patternPos = patternSize;
				for(size_t j = 0; j < patternSize; j++)
				{
					if(patterns[j] == vecSrc[i])
					{
						patternPos = j;
						break;
					}
				}
				if(patternPos != patternSize)
				{
					if(!tmp.empty())
					{
						outVec.push_back(make_pair<T, vector<T> >(pattern, tmp));
						tmp.clear();
					}
					pattern = patterns[patternPos];
				}
				else
				{
					tmp.push_back(vecSrc[i]);
				}
			}
			if(!tmp.empty())
			{
				outVec.push_back(make_pair<T, vector<T> >(pattern, tmp));
			}
		}

	template<typename T>
		void splitVec(const vector<T>& vecSrc, vector< vector<T> >& outVec, const vector<T>& patternVec)
		{
			vector<T> tmp;
			for(size_t i = 0; i < vecSrc.size(); i++)
			{
				bool flag = false;
				for(size_t j = 0; j < patternVec.size(); j++)
				{
					if(patternVec[j] == vecSrc[i])
					{
						flag = true;
						break;
					}
				}
				if(flag)
				{
					if(!tmp.empty())
					{
						outVec.push_back(tmp);
						tmp.clear();
					}
				}
				else
				{
					tmp.push_back(vecSrc[i]);
				}
			}
			if(!tmp.empty())
			{
				outVec.push_back(tmp);
			}
		}
    
}



#endif

//////config.h
#ifndef CPPCOMMON_CONFIG_H
#define CPPCOMMON_CONFIG_H

namespace CPPCOMMON
{
    using std::map;
    using std::string;
    using std::cout;
    using std::endl;
    using std::ifstream;
    class Config
    {
        public:
            Config();
            ~Config();
            bool init(const string& configFile);
            void display();
            string getByKey(const string& key);
        private:
            string _stripComment(const string& line);
            map<string, string> _map;
            bool _isInit;

    };
}

namespace CPPCOMMON
{
    extern Config gConfig;
}

#endif

//////encodeing.h
#ifndef CPPCOMMON_ENCODING_H
#define CPPCOMMON_ENCODING_H
namespace CPPCOMMON
{
    using namespace std;

    //const char* const  UTF8ENC = "utf-8";
    //const char* const  GBKENC = "gbk";

    //class UnicodeEncoding
    //{
    //    private:
    //        string _encoding;
    //        vector<string> _encVec;
    //    public:
    //        UnicodeEncoding(const string& enc);
    //        ~UnicodeEncoding();
    //    public:
    //        bool setEncoding(const string& enc);
    //        string encode(const Unicode& unicode);
    //        string encode(UnicodeConstIterator begin, UnicodeConstIterator end);
    //        bool decode(const string& str, Unicode& unicode);
    //    public:
    //        size_t getWordLength(const string& str);
    //};
}

#endif

//////file_functs.h
#ifndef CPPCOMMON_FILE_FUNCTS_H
#define CPPCOMMON_FILE_FUNCTS_H
namespace CPPCOMMON
{
    using namespace std;
    bool checkFileExist(const string& filePath);
    bool createDir(const string& dirPath, bool p = true);
    bool checkDirExist(const string& dirPath);

}

#endif

//////io_fincts.h
#ifndef CPPCOMMON_IO_FUNCTS_H
#define CPPCOMMON_IO_FUNCTS_H
namespace CPPCOMMON
{
    using namespace std;
    string loadFile2Str(const char * const filepath);
}
#endif

//////logger.h
#ifndef CPPCOMMON_LOGGER_H
#define CPPCOMMON_LOGGER_H

#define LL_DEBUG 0
#define LL_INFO 1
#define LL_WARN 2
#define LL_ERROR 3
#define LL_FATAL 4
#define LEVEL_ARRAY_SIZE 5
#define CSTR_BUFFER_SIZE 1024

typedef unsigned int uint;

//#define LogDebug(msg) Logger::Logging(LL_DEBUG, msg, __FILE__, __LINE__)
//#define LogInfo(msg) Logger::Logging(LL_INFO, msg, __FILE__, __LINE__)
//#define LogWarn(msg) Logger::Logging(LL_WARN, msg, __FILE__, __LINE__)
//#define LogError(msg) Logger::Logging(LL_ERROR, msg, __FILE__, __LINE__)
//#define LogFatal(msg) Logger::Logging(LL_FATAL, msg, __FILE__, __LINE__)

#define LogDebug(fmt, ...) Logger::LoggingF(LL_DEBUG, __FILE__, __LINE__, fmt, ## __VA_ARGS__)
#define LogInfo(fmt, ...) Logger::LoggingF(LL_INFO, __FILE__, __LINE__, fmt, ## __VA_ARGS__)
#define LogWarn(fmt, ...) Logger::LoggingF(LL_WARN, __FILE__, __LINE__, fmt, ## __VA_ARGS__)
#define LogError(fmt, ...) Logger::LoggingF(LL_ERROR, __FILE__, __LINE__, fmt, ## __VA_ARGS__)
#define LogFatal(fmt, ...) Logger::LoggingF(LL_FATAL, __FILE__, __LINE__, fmt, ## __VA_ARGS__)


namespace CPPCOMMON
{
    using namespace std;
    class Logger
    {
        public:
            Logger();
            ~Logger();
        public:
            static bool Logging(uint level, const string& msg, const char* fileName, int lineNo);
            static bool Logging(uint level, const char * msg, const char* fileName, int lineNo);
            static bool LoggingF(uint level, const char* fileName, int lineNo, const string& fmt, ...);
        private:
            static char _cStrBuf[CSTR_BUFFER_SIZE];
            static const char * _logLevel[LEVEL_ARRAY_SIZE];
            static const char * _logFormat;
            static const char * _timeFormat;
            static time_t _timeNow;
    };
}

#endif

//////map_functs.h
#ifndef CPPCOMMON_MAP_FUNCTS_H
#define CPPCOMMON_MAP_FUNCTS_H

namespace CPPCOMMON
{
    using namespace std;

    template <typename T>
        string setToString(const set<T>& st)
        {
            if(st.empty())
            {
                return "{}";
            }
            stringstream ss;
            ss<<'{';
            typename set<T>::const_iterator it = st.begin();
            ss<<*it;
            it++;
            while(it != st.end())
            {
                ss<<", "<<*it;
                it++;
            }
            ss<<'}';
            return ss.str();
        }

    template<typename T1, typename T2>
        string mapToString(const map<T1, T2>& mp)
        {
            if(mp.empty())
            {
                return "{}";
            }
            stringstream ss;
            ss<<'{';
            typename map<T1, T2>::const_iterator it = mp.begin();
            ss<<it->first<<": "<<it->second;
            it++;
            while(it != mp.end())
            {
                ss<<", "<<it->first<<": "<<it->second;
                it++;
            }
            ss<<'}';
            return ss.str();
        }

    template<typename T1, typename T2>
        string pairToString(const pair<T1, T2>& p)
        {
            stringstream ss;
            ss<<p.first<<":"<<p.second;
            return ss.str();
        }

    template<class kT, class vT>
        void printMap(const map<kT, vT>& mp)
        {
            for(typename map<kT, vT>::const_iterator it = mp.begin(); it != mp.end(); it++)
            {
                cout<<it->first<<' '<<it->second<<endl;
            }
        }

    template<class kT, class vT>
        vT getMap(const map<kT, vT>& mp, const kT & key, const vT & defaultVal)
        {
            typename map<kT, vT>::const_iterator it;
            it = mp.find(key);
            if(mp.end() == it)
            {
                return defaultVal;
            }
            return it->second;
        }

}

#endif

//////typedef.h
#ifndef CPPCOMMON_TYPEDEFS_H
#define CPPCOMMON_TYPEDEFS_H

namespace CPPCOMMON
{
    typedef std::vector<uint16_t> Unicode;
    typedef std::vector<uint16_t>::const_iterator UnicodeConstIterator;
}

#endif


//////vec_functs.h
#ifndef CPPCOMMON_VEC_FUNCTS_H
#define CPPCOMMON_VEC_FUNCTS_H

#define FOR_VECTOR(vec, i) for(size_t i = 0; i < vec.size(); i++)

#define PRINT_VECTOR(vec) FOR_VECTOR(vec, i)\
{\
    cout<<vec[i]<<endl;\
}

#define PRINT_MATRIX(mat) FOR_VECTOR(mat, i) \
{\
    FOR_VECTOR(mat[i], j)\
    {\
        cout<<"["<<i<<","<<j<<"]:"<<mat[i][j]<<endl;\
    }\
}

namespace CPPCOMMON
{
    using namespace std;
}

//#include "vec_functs.tcc"

#endif


//////str_functs.h
#ifndef CPPCOMMON_STR_FUNCTS_H
#define CPPCOMMON_STR_FUNCTS_H

namespace CPPCOMMON
{
    using namespace std;
    string string_format(const char*, ...) ;
    string joinStr(const vector<string>& source, const string& connector);
    vector<string> splitStr(const string& source, const string& pattern = " \t\n");
    bool splitStr(const string& source, vector<string>& res, const string& pattern = " \t\n");
    bool splitStrMultiPatterns(
                const string& strSrc, 
                vector<string>& outVec, 
                const vector<string>& patterns
                );
    string upperStr(const string& str);
    string lowerStr(const string& str);
    string replaceStr(const string& strSrc, const string& oldStr, const string& newStr, int count = -1);
    string stripStr(const string& str, const string& patternstr = " \n\t");
    std::string &ltrim(std::string &s) ;
    std::string &rtrim(std::string &s) ;
    std::string &trim(std::string &s) ;
    unsigned int countStrDistance(const string& A, const string& B);
    unsigned int countStrSimilarity(const string& A, const string& B);


    bool uniStrToVec(const string& str, Unicode& vec);
    string uniVecToStr(const Unicode& vec);

    inline uint16_t twocharToUint16(char high, char low);

    inline pair<char, char> uint16ToChar2(uint16_t in);

    inline void printUnicode(const Unicode& unicode);

    inline bool strStartsWith(const string& str, const string& prefix);

    inline bool strEndsWith(const string& str, const string& suffix);
    
}
#endif

//////globals.h
#ifndef CPPJIEBA_GLOBALS_H
#define CPPJIEBA_GLOBALS_H



namespace CppJieba
{

    using namespace std;
    //using std::tr1::unordered_map;
    using std::unordered_map;
    //using __gnu_cxx::hash_map;
    //using namespace stdext;
    //typedefs
    typedef std::vector<std::string>::iterator VSI;
    typedef std::vector<uint16_t> Unicode;
    typedef Unicode::const_iterator UniConIter;
    typedef unordered_map<uint16_t, struct TrieNode*> TrieNodeMap;
    typedef unordered_map<uint16_t, double> EmitProbMap;

    const double MIN_DOUBLE = -3.14e+100;
    const double MAX_DOUBLE = 3.14e+100;
    enum CHAR_TYPE { CHWORD = 0, DIGIT_OR_LETTER = 1, OTHERS = 2};
}

#endif


//////ChineseFilter.h
#ifndef CPPJIEBA_CHINESEFILTER_H
#define CPPJIEBA_CHINESEFILTER_H


namespace CppJieba
{
	class ChFilterIterator;
    class ChineseFilter
    {
        public:
            typedef ChFilterIterator  iterator;
        public:
            ChineseFilter();
            ~ChineseFilter();
        public:
            bool feed(const std::string& str);
            iterator begin();
            iterator end();
        private:
            Unicode _unico;
        private:
            //friend class ChFilterIterator;
    };

    class ChFilterIterator
    {
        public:
            const Unicode * ptUnico;
            UniConIter begin;
            UniConIter end;
            CHAR_TYPE charType;
            ChFilterIterator& operator++();
            ChFilterIterator operator++(int);
            bool operator==(const ChFilterIterator& iter);
            bool operator!=(const ChFilterIterator& iter);
            ChFilterIterator& operator=(const ChFilterIterator& iter);
        
        public:
            ChFilterIterator(const Unicode * ptu, UniConIter be, UniConIter en, CHAR_TYPE is):ptUnico(ptu), begin(be), end(en), charType(is){};
            ChFilterIterator(const Unicode * ptu):ptUnico(ptu){*this = _get(ptUnico->begin());};
        private:
            ChFilterIterator();
        private:
            CHAR_TYPE _charType(uint16_t x)const;
            ChFilterIterator _get(UniConIter iter);

    };
}


#endif


//////SegmentInterface.h
#ifndef CPPJIEBA_SEGMENTINTERFACE_H
#define CPPJIEBA_SEGMENTINTERFACE_H

namespace CppJieba
{
    class SegmentInterface
    {
        //public:
        //    virtual ~SegmentInterface(){};
        public:
            virtual bool cut(Unicode::const_iterator begin , Unicode::const_iterator end, vector<string>& res) const = 0;
            virtual bool cut(const string& str, vector<string>& res) const = 0;
    };
}

#endif

//////SegmentBase.h
#ifndef CPPJIEBA_SEGMENTBASE_H
#define CPPJIEBA_SEGMENTBASE_H

namespace CppJieba
{
    using namespace CPPCOMMON;
    class SegmentBase: public SegmentInterface
    {
        public:
            SegmentBase(){_setInitFlag(false);};
            virtual ~SegmentBase(){};
        private:
            bool _isInited;
        protected:
            bool _getInitFlag()const{return _isInited;};
            bool _setInitFlag(bool flag){return _isInited = flag;};
            bool cut(const string& str, vector<string>& res)const;
            bool cut(Unicode::const_iterator begin, Unicode::const_iterator end, vector<string>& res)const = 0;

    };
}

#endif



//////HMMSegment.h
#ifndef CPPJIBEA_HMMSEGMENT_H
#define CPPJIBEA_HMMSEGMENT_H



namespace CppJieba
{
    using namespace CPPCOMMON;
    class HMMSegment: public SegmentBase
    {
        public:
            /*
             * STATUS:
             * 0:B, 1:E, 2:M, 3:S
             * */
            enum {B = 0, E = 1, M = 2, S = 3, STATUS_SUM = 4};
        private:
            char _statMap[STATUS_SUM];
            double _startProb[STATUS_SUM];
            double _transProb[STATUS_SUM][STATUS_SUM];
            EmitProbMap _emitProbB;
            EmitProbMap _emitProbE;
            EmitProbMap _emitProbM;
            EmitProbMap _emitProbS;
            vector<EmitProbMap* > _emitProbVec;
            
        public:
            HMMSegment();
            virtual ~HMMSegment();
        public:
            bool init(const char* const modelPath);
            bool dispose();
        public:
            bool cut(Unicode::const_iterator begin, Unicode::const_iterator end, vector<Unicode>& res)const ;
            bool cut(const string& str, vector<string>& res)const;
            bool cut(Unicode::const_iterator begin, Unicode::const_iterator end, vector<string>& res)const;
            //virtual bool cut(const string& str, vector<string>& res)const;

        private:
            bool _viterbi(Unicode::const_iterator begin, Unicode::const_iterator end, vector<uint>& status)const;
            bool _loadModel(const char* const filePath);
            bool _getLine(ifstream& ifile, string& line);
            bool _loadEmitProb(const string& line, EmitProbMap& mp);
            bool _decodeOne(const string& str, uint16_t& res);
            double _getEmitProb(const EmitProbMap* ptMp, uint16_t key, double defVal)const ;

            
    };
}

#endif









//////TransCode.h
#ifndef CPPJIEBA_TRANSCODE_H
#define CPPJIEBA_TRANSCODE_H

typedef unsigned int uint;

namespace CppJieba
{

    using namespace CPPCOMMON;
    namespace TransCode
    {
        inline bool decode(const string& str, vector<uint16_t>& vec)
        {
            char ch1, ch2;
            if(str.empty())
            {
                return false;
            }
            vec.clear();
            size_t siz = str.size();
            for(uint i = 0;i < siz;)
            {
                if(!(str[i] & 0x80)) // 0xxxxxxx
                {
                    vec.push_back(str[i]);
                    i++;
                }
                else if ((unsigned char)str[i] <= 0xdf && i + 1 < siz) // 110xxxxxx
                {
                    ch1 = (str[i] >> 2) & 0x07;
                    ch2 = (str[i+1] & 0x3f) | ((str[i] & 0x03) << 6 );
                    vec.push_back(twocharToUint16(ch1, ch2));
                    i += 2;
                }
                else if((unsigned char)str[i] <= 0xef && i + 2 < siz)
                {
                    ch1 = (str[i] << 4) | ((str[i+1] >> 2) & 0x0f );
                    ch2 = ((str[i+1]<<6) & 0xc0) | (str[i+2] & 0x3f); 
                    vec.push_back(twocharToUint16(ch1, ch2));
                    i += 3;
                }
                else
                {
                    return false;
                }
            }
            return true;
        }


        inline bool encode(vector<uint16_t>::const_iterator begin, vector<uint16_t>::const_iterator end, string& res)
        {
            if(begin >= end)
            {
                return false;
            }
            res.clear();
            uint16_t ui;
            while(begin != end)
            {
                ui = *begin;
                if(ui <= 0x7f)
                {
                    res += char(ui);
                }
                else if(ui <= 0x7ff)
                {
                    res += char(((ui>>6) & 0x1f) | 0xc0);
                    res += char((ui & 0x3f) | 0x80);
                }
                else
                {
                    res += char(((ui >> 12) & 0x0f )| 0xe0);
                    res += char(((ui>>6) & 0x3f )| 0x80 );
                    res += char((ui & 0x3f) | 0x80);
                }
                begin ++;
            }
            return true;
        }
        inline bool encode(const vector<uint16_t>& sentence, string& res)
        {
            return encode(sentence.begin(), sentence.end(), res);
        }
    }
}

#endif




//////structs.h
#ifndef CPPJIEBA_STRUCTS_H
#define CPPJIEBA_STRUCTS_H


namespace CppJieba
{

    struct TrieNodeInfo
    {
        //string word;
        //size_t wLen;// the word's len , not string.length(), 
        Unicode word;
        size_t freq;
        string tag;
        double logFreq; //logFreq = log(freq/sum(freq));
        TrieNodeInfo():freq(0),logFreq(0.0)
        {
        }
        TrieNodeInfo(const TrieNodeInfo& nodeInfo):word(nodeInfo.word), freq(nodeInfo.freq), tag(nodeInfo.tag), logFreq(nodeInfo.logFreq)
        {
        }
        TrieNodeInfo(const Unicode& _word):word(_word),freq(0),logFreq(MIN_DOUBLE)
        {
        }
		string toString()const
		{
            string tmp;
            TransCode::encode(word, tmp);
            return string_format("{word:%s,freq:%d, logFreq:%lf}", tmp.c_str(), freq, logFreq);
		}
    };

    typedef unordered_map<uint, const TrieNodeInfo*> DagType;
    struct SegmentChar 
    {
        uint16_t uniCh;
        DagType dag;
        const TrieNodeInfo * pInfo;
        double weight;
        
        SegmentChar(uint16_t uni):uniCh(uni), pInfo(NULL), weight(0.0)
        {
        }
        
        /*const TrieNodeInfo* pInfo;
        double weight;
        SegmentChar(uint16_t unich, const TrieNodeInfo* p, double w):uniCh(unich), pInfo(p), weight(w)
        {
        }*/
    };
    /*
    struct SegmentContext
    {
        vector<SegmentChar> context;
        bool getDA
    };*/
    typedef vector<SegmentChar> SegmentContext;
    

    struct KeyWordInfo: public TrieNodeInfo
    {
        double idf;
        double weight;// log(wLen+1)*logFreq;
        KeyWordInfo():idf(0.0),weight(0.0)
        {
        }
        KeyWordInfo(const Unicode& _word):TrieNodeInfo(_word),idf(0.0),weight(0.0)
        { 
        }
        KeyWordInfo(const TrieNodeInfo& trieNodeInfo):TrieNodeInfo(trieNodeInfo)
        {
        }
        inline string toString() const
        {
            string tmp;
            TransCode::encode(word, tmp);
            return string_format("{word:%s,weight:%lf, idf:%lf}", tmp.c_str(), weight, idf);
        }
        KeyWordInfo& operator = (const TrieNodeInfo& trieNodeInfo)
        {
            word = trieNodeInfo.word;
            freq = trieNodeInfo.freq;
            tag = trieNodeInfo.tag;
            logFreq = trieNodeInfo.logFreq;
            return *this;
        }
    };

    inline string joinWordInfos(const vector<KeyWordInfo>& vec)
    {
        vector<string> tmp;
        for(uint i = 0; i < vec.size(); i++)
        {
            tmp.push_back(vec[i].toString());
        }
        return joinStr(tmp, ",");
    }
}

#endif


//////Trie.h
#ifndef CPPJIEBA_TRIE_H
#define CPPJIEBA_TRIE_H

namespace CppJieba
{
    using namespace CPPCOMMON;
    struct TrieNode
    {
        TrieNodeMap hmap;
        bool isLeaf;
        uint nodeInfoVecPos;
        TrieNode()
        {
            isLeaf = false;
            nodeInfoVecPos = 0;
        }
    };

    class Trie
    {

        private:
            TrieNode* _root;
            vector<TrieNodeInfo> _nodeInfoVec;

            bool _initFlag;
            int64_t _freqSum;
            double _minLogFreq;

        public:
            Trie();
            ~Trie();
            bool init();
            bool loadDict(const char * const filePath);
            bool dispose();

        private:
            void _setInitFlag(bool on){_initFlag = on;};
            bool _getInitFlag()const{return _initFlag;};

        public:
            const TrieNodeInfo* find(const string& str)const;
            const TrieNodeInfo* find(const Unicode& uintVec)const;
            const TrieNodeInfo* find(Unicode::const_iterator begin, Unicode::const_iterator end)const;
			bool find(const Unicode& unico, vector<pair<uint, const TrieNodeInfo*> >& res)const;

            const TrieNodeInfo* findPrefix(const string& str)const;

        public:
            //double getWeight(const string& str);
            //double getWeight(const Unicode& uintVec);
            //double getWeight(Unicode::const_iterator begin, Unicode::const_iterator end);
            double getMinLogFreq()const{return _minLogFreq;};
            
            //int64_t getTotalCount(){return _freqSum;};

            bool insert(const TrieNodeInfo& nodeInfo);

        private:
            bool _trieInsert(const char * const filePath);
            bool _countWeight();
            bool _deleteNode(TrieNode* node);

    };
}

#endif

//////MPSegment.h
#ifndef CPPJIEBA_MPSEGMENT_H
#define CPPJIEBA_MPSEGMENT_H



namespace CppJieba
{
    
    typedef vector<SegmentChar> SegmentContext;

    class MPSegment: public SegmentBase
    {
        private:
            Trie _trie;
            
        public:
            MPSegment();
            virtual ~MPSegment();
        public:
            bool init(const char* const filePath);
            bool dispose();
        public:
            //bool cut(const string& str, vector<TrieNodeInfo>& segWordInfos)const;
            bool cut(const string& str, vector<string>& res)const;
            bool cut(Unicode::const_iterator begin, Unicode::const_iterator end, vector<string>& res)const;
            bool cut(const string& str, vector<TrieNodeInfo>& segWordInfos)const;
            bool cut(Unicode::const_iterator begin , Unicode::const_iterator end, vector<TrieNodeInfo>& segWordInfos)const;
            //virtual bool cut(const string& str, vector<string>& res)const;

        private:
            bool _calcDAG(SegmentContext& segContext)const;
            bool _calcDP(SegmentContext& segContext)const;
            bool _cut(SegmentContext& segContext, vector<TrieNodeInfo>& res)const;


    };
}

#endif


//////MixSegment.h
#ifndef CPPJIEBA_MIXSEGMENT_H
#define CPPJIEBA_MIXSEGMENT_H

namespace CppJieba
{
    class MixSegment: public SegmentBase
    {
        private:
            MPSegment _mpSeg;
            HMMSegment _hmmSeg;
        public:
            MixSegment();
            virtual ~MixSegment();
        public:
            bool init(const char* const _mpSegDict, const char* const _hmmSegDict);
            bool dispose();
        public:
            //virtual bool cut(const string& str, vector<string>& res) const;
            bool cut(const string& str, vector<string>& res)const;
            bool cut(Unicode::const_iterator begin, Unicode::const_iterator end, vector<string>& res)const;
    };
}

#endif

//////KeyWordExt.h
#ifndef CPPJIEBA_KEYWORDEXT_H
#define CPPJIEBA_KEYWORDEXT_H

namespace CppJieba
{

    class KeyWordExt
    {
        private:
            MPSegment _segment;
            //vector<string> _priorSubWords;
            set<Unicode> _stopWords;
        public:
            KeyWordExt();
            ~KeyWordExt();
            bool init(const char* const segDictFile);
            bool dispose();
            bool loadStopWords(const char * const filePath);
        private:
            //bool _loadPriorSubWords(const char * const filePath);


        public:
            bool extract(const string& title, vector<KeyWordInfo>& keyWordInfos, uint topN);
            bool extract(const vector<string>& words, vector<KeyWordInfo>& keyWordInfos, uint topN);
        private:
            static bool _wordInfoCompare(const KeyWordInfo& a, const KeyWordInfo& b);
        private:
            bool _extract(vector<KeyWordInfo>& keyWordInfos, uint topN);
            bool _extTopN(vector<KeyWordInfo>& wordInfos, uint topN);
        private:
            //sort by word len - idf
            bool _sortWLIDF(vector<KeyWordInfo>& wordInfos);
        private:
            bool _filter(vector<KeyWordInfo>& );
            bool _filterDuplicate(vector<KeyWordInfo>& );
            bool _filterSingleWord(vector<KeyWordInfo>& );
            bool _filterSubstr(vector<KeyWordInfo>& );
            bool _filterStopWords(vector<KeyWordInfo>& );
        private:
            inline bool _isSubIn(const vector<Unicode>& words, const Unicode& word)const
            {

                for(uint j = 0; j < words.size(); j++)
                {
                    if(word != words[j] && words[j].end() != search(words[j].begin(), words[j].end(), word.begin(), word.end()))
                    {
                        return true;
                    }
                }
                return false;
            }
            //bool _prioritizeSubWords(vector<KeyWordInfo>& wordInfos);
            //bool _isContainSubWords(const string& word);

    };

}

#endif





