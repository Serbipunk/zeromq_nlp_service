// #include "stdafx.h"
#include "combinition.h"



//////argv_functs.cpp
namespace CPPCOMMON
{
    bool getArgvMap(int argc, const char* const * argv, map<string,string>& mpss)
    {
        mpss.clear();
        for(int i = 0; i < argc; i++)
        {
            if(strStartsWith(argv[i], "--"))
            {
                if(i + 1 < argc && !strStartsWith(argv[i+1], "--"))
                {
                    mpss[argv[i]] = argv[i+1];
                    i++;
                }
                else
                {
                    return false;
                }
            }
        }
        return true;
    }

    ArgvContext::ArgvContext(int argc, const char* const * argv)
    {
        for(int i = 0; i < argc; i++)
        {
            if(strStartsWith(argv[i], "-"))
            {
                if(i + 1 < argc && !strStartsWith(argv[i + 1], "-"))
                {
                    _mpss[argv[i]] = argv[i+1];
                    i++;
                }
                else
                {
                    _sset.insert(argv[i]);
                }
            }
            else
            {
                _args.push_back(argv[i]);
            }
        }
    }

    ArgvContext::~ArgvContext()
    {
    }

    string ArgvContext::toString()
    {
        stringstream ss;
        ss<<vecToString<string>(_args)<<mapToString<string, string>(_mpss)<<setToString<string>(_sset);
        return ss.str();
    }

    string ArgvContext::operator [](uint i)
    {
        if(i < _args.size())
        {
            return _args[i];
        }
        return "";
    }
    
    string ArgvContext::operator [](const string& key)
    {
        map<string, string>::const_iterator it = _mpss.find(key);
        if(it != _mpss.end())
        {
            return it->second;
        }
        return "";
    }
    
    bool ArgvContext::isKeyExist(const string& key)
    {
        if(_mpss.find(key) != _mpss.end() || _sset.find(key) != _sset.end())
        {
            return true;
        }
        return false;
    }
}

//////config.cpp
namespace CPPCOMMON
{
    Config::Config()
    {
        _isInit = false;
    }

    Config::~Config()
    {
    }

    bool Config::init(const string& configFile)
    {
        char msgBuf[1024];
        if(_isInit)
        {
            LogFatal("already have been initialized. ");
            return false;
        }
        ifstream ifile(configFile.c_str());
        if(!ifile)
        {
            sprintf(msgBuf, "open configFile[%s] failed.", configFile.c_str());
            LogFatal(msgBuf);
            return false;
        }
        string line, key, value;
        vector<string> vecBuf;
        while(getline(ifile, line))
        {
            line = _stripComment(line);
            if(line.empty())
            {
                continue;
            }
            vecBuf = splitStr(line, "=");
            if(2 != vecBuf.size())
            {
                sprintf(msgBuf, "line[%s] is illegal.", line.c_str());
                LogFatal(msgBuf);
                return false;
            }
            key = vecBuf[0];
            value = vecBuf[1];
            if(_map.end() != _map.find(key))
            {
                sprintf(msgBuf, "key[%s] already exists.", key.c_str());
                LogFatal(msgBuf);
                return false;
            }
            _map[key] = value;
        }
        ifile.close();
        _isInit = true;
        return true;
    }

    void Config::display()
    {
        for(map<string, string>::iterator it = _map.begin(); it != _map.end(); it++)
        {
            cout<<"("<<it->first<<","<<it->second<<")"<<endl;
        }
    }
    
    string Config::getByKey(const string& key)
    {
        if(_map.end() != _map.find(key))
        {
            return _map[key];
        }
        else
        {
            return "";
        }
    }

    string Config::_stripComment(const string& line)
    {
        string res = line;
        string::size_type pos = res.find('#');
        if(string::npos != pos)
        {
            res = res.substr(0, pos);
        }
        return stripStr(res);
    }

}

namespace CPPCOMMON
{
    Config gConfig;
}

//////encodeing.cpp
namespace CPPCOMMON
{
    
    //UnicodeEncoding::UnicodeEncoding(const string& enc)
    //{
    //    
    //    _encVec.push_back(UTF8ENC);
    //    _encVec.push_back(GBKENC);
    //    
    //    if(!isInVec<string>(_encVec, enc))
    //    {
    //        //default
    //        _encoding = UTF8ENC;
    //    }
    //    else
    //    {
    //        _encoding = enc;
    //    }
    //}

    //UnicodeEncoding::~UnicodeEncoding()
    //{
    //}
    //
    //bool UnicodeEncoding::setEncoding(const string& enc)
    //{
    //    if(!isInVec<string>(_encVec, enc))
    //    {
    //        return false;
    //    }
    //    _encoding = enc;
    //    return true;
    //}

    //string UnicodeEncoding::encode(UnicodeConstIterator begin, UnicodeConstIterator end)
    //{
    //    if(begin >= end)
    //    {
    //        return "";
    //    }
    //    Unicode unicode(begin, end);
    //    return encode(unicode);
    //}

    //string UnicodeEncoding::encode(const Unicode& unicode)
    //{
    //    if(unicode.empty())
    //    {
    //        return "";
    //    }
    //    if(UTF8ENC == _encoding)
    //    {
    //        return unicodeToUtf8(unicode);
    //    }
    //    else if(GBKENC  == _encoding)
    //    {
    //        return utf8ToGbk(unicodeToUtf8(unicode));
    //    }
    //    return "";
    //}

    //bool UnicodeEncoding::decode(const string& str, Unicode& unicode)
    //{
    //    if(str.empty())
    //    {
    //        return false;
    //    }
    //    if(UTF8ENC == _encoding)
    //    {
    //        return utf8ToUnicode(str, unicode);
    //    }
    //    else if(GBKENC == _encoding)
    //    {
    //        return utf8ToUnicode(gbkToUtf8(str), unicode);
    //    }
    //    return false;
    //}

    //size_t UnicodeEncoding::getWordLength(const string& str)
    //{
    //    Unicode unicode;
    //    decode(str, unicode);
    //    return unicode.size();
    //}

}

//////file_functs.cpp
namespace CPPCOMMON
{
    bool checkFileExist(const string& filePath)
    {
        fstream _file;
        _file.open(filePath.c_str(), ios::in);
        if(_file)
          return true;
        return false;
    }
    bool createDir(const string& dirPath, bool p)
    {
        string dir_str(dirPath);
        string cmd = "mkdir";
        if(p)
        {
            cmd += " -p";
        }
        cmd += " " + dir_str; 
        int res = system(cmd.c_str());
        return res;
    }
    bool checkDirExist(const string& dirPath)
    {
        return checkFileExist(dirPath);
    }
}

//////io_fincts.cpp
namespace CPPCOMMON
{
    string loadFile2Str(const char * const filepath)
    {
        ifstream in(filepath);
        istreambuf_iterator<char> beg(in), end;
        string str(beg, end);
        in.close();
        return str;
    }
}

//////logger.cpp
namespace CPPCOMMON
{
    char Logger::_cStrBuf[CSTR_BUFFER_SIZE];
    const char * Logger::_logLevel[LEVEL_ARRAY_SIZE] = {
        "DEBUG","INFO","WARN","ERROR","FATAL"
    };

    const char * Logger::_logFormat = "%s [File:%s] [Line:%d] [%s] Msg:%s\n";
    const char * Logger::_timeFormat = "%Y-%m-%d %H:%M:%S";
    time_t Logger::_timeNow;
    Logger::Logger()
    {
    }

    Logger::~Logger()
    {
    }

    bool Logger::LoggingF(uint level, const char* fileName, int lineNo, const string& fmt, ...)
    {
		/*
        int size = 256;
        string msg;
        va_list ap;
        while (1) {
            msg.resize(size);
            va_start(ap, fmt);
            int n = vsnprintf((char *)msg.c_str(), size, fmt.c_str(), ap);
            va_end(ap);
            if (n > -1 && n < size) {
                msg.resize(n);
                break;
            }
            if (n > -1)
              size = n + 1;
            else
              size *= 2;
        }
        return Logging(level, msg, fileName, lineNo);
		*/
		
		return true;
    }

    bool Logger::Logging(uint level, const string& msg,  const char * fileName, int lineNo)
    {
        return Logging(level, msg.c_str(), fileName, lineNo);
    }
    

    bool Logger::Logging(uint level, const char * msg, const char* fileName, int lineNo)
    {
        if(level > LL_FATAL)
        {
            cerr<<"level's value is out of range"<<endl;
            return false;
        }
        time(&_timeNow);
        size_t ret = strftime(_cStrBuf, sizeof(_cStrBuf), _timeFormat, localtime(&_timeNow));
        if(0 == ret)
        {
            fprintf(stderr, "stftime failed.\n");
            return false;
        }
        if(level >= LL_WARN)
        {
            fprintf(stderr, _logFormat, _cStrBuf, fileName, lineNo, _logLevel[level], msg);
        }
        else
        {
            fprintf(stdout, _logFormat, _cStrBuf, fileName, lineNo, _logLevel[level], msg);
            fflush(stdout);
        }
        return true;
    }
}

//////str_functs.cpp
namespace CPPCOMMON
{	
	inline uint16_t twocharToUint16(char high, char low)
    {
        return (((uint16_t(high) & 0x00ff ) << 8) | (uint16_t(low) & 0x00ff));
    }


	inline pair<char, char> uint16ToChar2(uint16_t in)
    {
        pair<char, char> res;
        res.first = (in>>8) & 0x00ff; //high
        res.second = (in) & 0x00ff; //low
        return res;
    }

	inline void printUnicode(const Unicode& unicode)
    {
        cout<<uniVecToStr(unicode)<<endl;
    }

	inline bool strStartsWith(const string& str, const string& prefix)
    {
        //return str.substr(0, prefix.size()) == prefix;
        if(prefix.length() > str.length())
        {
            return false;
        }
        return 0 == str.compare(0, prefix.length(), prefix);
    }

	inline bool strEndsWith(const string& str, const string& suffix)
    {
        if(suffix.length() > str.length())
        {
            return false;
        }
        return 0 == str.compare(str.length() -  suffix.length(), suffix.length(), suffix);
    }

    //http://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf
    string string_format(const char* fmt, ...) 
    {
        int size = 256;
        std::string str;
        va_list ap;
        while (1) {
            str.resize(size);
            va_start(ap, fmt);
            int n = vsnprintf((char *)str.c_str(), size, fmt, ap);
            va_end(ap);
            if (n > -1 && n < size) {
                str.resize(n);
                return str;
            }
            if (n > -1)
              size = n + 1;
            else
              size *= 2;
        }
        return str;
    }

    string joinStr(const vector<string>& src, const string& connectorStr)
    {
        string res = "";
        int len = src.size();
        if(0 == len)
        {
            return "";
        }
        for(int i = 0; i < len - 1; i++)
        {
            res += stripStr(src[i]);
            res += connectorStr;
        }
        res += stripStr(src[len-1]);
        return res;
    }

    vector<string> splitStr(const string& source, const string& pattern)
    {
        vector<string> res;
        splitStr(source, res, pattern);
        return res;
    }

    bool splitStr(const string& source, vector<string>& res, const string& pattern)
    {
        if(source.empty())
        {
            return false;
        }
        res.clear();

        size_t start = source.find_first_not_of(pattern);
        size_t end;
        if(string::npos == start)
        {
            return false;
        }
        while(string::npos != start)
        {
            end = source.find_first_of(pattern, start);
            if(string::npos == end)
            {
                res.push_back(source.substr(start));
                return true;
            }
            res.push_back(source.substr(start, end - start));
            start = source.find_first_not_of(pattern,  end);
        }
        return true;
    }

    string stripStr(const string& str, const string& patternStr)
    {
        if(str.empty())
        {
            return str;
        }
        string::size_type posL = str.find_first_not_of(patternStr);
        if(string::npos == posL)
        {
            return str;
        }
        string::size_type posR = str.find_last_not_of(patternStr);
        return str.substr(posL, posR - posL + 1);

    }


    //http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
    // trim from start
    std::string &ltrim(std::string &s) 
    {
		//不就是把开头的连续空格清除么？
        //s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));

		int l_space = 0;
		for(int i = 0; i < s.size(); i++)
		{
			if(s.at(i) == ' ')
			{
				l_space ++;
			}
			else
			{
				break;
			}
		}
		if(l_space != 0)
		{
			s.erase( s.begin(), s.begin()+l_space );
		}

        return s;
    }

    // trim from end
    std::string &rtrim(std::string &s) 
    {
		//不就是吧最后的连续空格清除么？
        //s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
		int r_space = 0;
		for(int i = s.size()-1; i >= 0; i--)
		{
			if(s.at(i) == ' ')
			{
				r_space ++;
			}
			else
			{
				break;
			}
		}
		if(r_space != 0)
		{
			s.erase( s.end()-r_space, s.end() );
		}


        return s;
    }

    // trim from both ends
    std::string &trim(std::string &s) 
    {
        return ltrim(rtrim(s));
    }

    bool splitStrMultiPatterns(
                const string& strSrc, 
                vector<string>& outVec, 
                const vector<string>& patterns
                )
    {
        char transChar = '#';
        uint transLenThreshold = 10;
        string transStr;
        transStr += transChar;
        while(strSrc.find(transStr) != string::npos)
        {
            transStr += transChar;
            if(transStr.size() > transLenThreshold)
              return false;
        }
        string strSrcMutable = strSrc;
        for(uint i = 0; i < patterns.size(); i++)
        {
            strSrcMutable = replaceStr(strSrcMutable, patterns[i], transStr);
        }
        splitStr(strSrcMutable, outVec, transStr);
        return true;
    }

    string upperStr(const string& strIn)
    {
        string str = strIn;
        transform(str.begin(), str.end(), str.begin(), (int (*)(int))toupper);
        return str;
    }

    string lowerStr(const string& strIn)
    {
        string str = strIn;
        transform(str.begin(), str.end(), str.begin(), (int (*)(int))tolower);
        return str;
    }

    string replaceStr(const string& strSrc, const string& oldStr, const string& newStr, int count)
    {
        string strRet = strSrc;
        size_t pos = 0;
        int l_count = 0;
        if(-1 == count)
          count = strRet.size();
        while((pos = strRet.find(oldStr, pos)) != string::npos)
        {
            strRet.replace(pos, oldStr.size(), newStr);
            if(++l_count >= count)
              break;
            pos += newStr.size();
        }
        return strRet;
    }

    unsigned int countStrDistance(const string& A, const string& B)
    {
        unsigned int lenA = A.size();
        unsigned int lenB = B.size();
        unsigned int len = (lenA < lenB ? lenA : lenB);
        unsigned int res = lenA + lenB - 2 * len;
        for(size_t i = 0; i < len; i++)
        {
            if(A[i] != B[i])
              res++;
        }
        return res;
    }

    unsigned int countStrSimilarity(const string& A, const string& B)
    {
        unsigned int lenA = A.size();
        unsigned int lenB = B.size();
        unsigned int len = (lenA < lenB ? lenA : lenB);
        unsigned int res = 0;
        for(size_t i = 0; i < len; i++)
        {
            if(A[i] == B[i])
              res++;
        }
        return res;
    }

    //unicode str to vec
    bool uniStrToVec(const string& str, Unicode& vec)
    {
        vec.clear();
        if(str.empty() || str.size() % 2)
        {
            return false;
        }
        for(uint i = 0; i < str.size(); i+=2)
        {
            vec.push_back(twocharToUint16(str[i], str[i + 1]));
        }

        return true;
    }

    //unicode vec to str
    string uniVecToStr(const Unicode& vec)
    {
        string res("");
        for(uint i = 0; i < vec.size(); i++)
        {
            pair<char,char> pa = uint16ToChar2(vec[i]);
            res += pa.first;
            res += pa.second;
        }
        return res;
    }
}

//////ChineseFilter.cpp
namespace CppJieba
{
    ChineseFilter::ChineseFilter()
    {
    }
    
    ChineseFilter::~ChineseFilter()
    {
    }

    bool ChineseFilter::feed(const string& str)
    {
        return TransCode::decode(str, _unico);
    }

    ChineseFilter::iterator ChineseFilter::begin()
    {
        return iterator(&_unico);
    }

    ChineseFilter::iterator ChineseFilter::end()
    {
        return iterator(&_unico, _unico.end(), _unico.end(), OTHERS);
    }
    
	ChFilterIterator& ChFilterIterator::operator++()
    {
        return *this = _get(end);
    }
    ChFilterIterator ChFilterIterator::operator++(int)
    {
        ChFilterIterator res = *this;
        *this = _get(end);
        return res;
    }
    bool ChFilterIterator::operator==(const ChFilterIterator& iter)
    {
        return begin == iter.begin && end == iter.end;
    }
    bool ChFilterIterator::operator!=(const ChFilterIterator& iter)
    {
        return !(*this == iter);
    }
    ChFilterIterator& ChFilterIterator::operator=(const ChFilterIterator& iter)
    {
        ptUnico = iter.ptUnico;
        begin = iter.begin;
        end = iter.end;
        charType = iter.charType;
        return *this;
    }

	CHAR_TYPE ChFilterIterator::_charType(uint16_t x)const
    {
        if((0x0030 <= x && x<= 0x0039) || (0x0041 <= x && x <= 0x005a ) || (0x0061 <= x && x <= 0x007a))
        {
            return DIGIT_OR_LETTER;
        }
        if(x >= 0x4e00 && x <= 0x9fff)
        {
            return CHWORD;
        }
        return OTHERS;
    }
    ChFilterIterator ChFilterIterator::_get(UniConIter iter)
    {
        UniConIter _begin = iter;
        const UniConIter& _end = ptUnico->end();
        if(iter == _end)
        {
            return ChFilterIterator(ptUnico, end, end, OTHERS);
        }
        CHAR_TYPE charType = _charType(*iter);
        iter ++;
        while(iter != _end &&charType ==  _charType(*iter))
        {
            iter++;
        }
        return ChFilterIterator(ptUnico, _begin, iter, charType);
    }

	ChFilterIterator::ChFilterIterator()
	{
	}
    
}



//////HMMSegment.cpp
namespace CppJieba
{
    HMMSegment::HMMSegment()
    {
        memset(_startProb, 0, sizeof(_startProb));
        memset(_transProb, 0, sizeof(_transProb));
        _statMap[0] = 'B';
        _statMap[1] = 'E';
        _statMap[2] = 'M';
        _statMap[3] = 'S';
        _emitProbVec.push_back(&_emitProbB);
        _emitProbVec.push_back(&_emitProbE);
        _emitProbVec.push_back(&_emitProbM);
        _emitProbVec.push_back(&_emitProbS);
    }
    
    HMMSegment::~HMMSegment()
    {
        dispose();
    }

    bool HMMSegment::init(const char* const modelPath)
    {
        return _setInitFlag(_loadModel(modelPath));
    }
    
    bool HMMSegment::dispose()
    {
        _setInitFlag(false);
        return true;
    }

    bool HMMSegment::_loadModel(const char* const filePath)
    {
        LogInfo("loadModel [%s] start ...", filePath);
        ifstream ifile(filePath);
        string line;
        vector<string> tmp;
        vector<string> tmp2;
        //load _startProb
        if(!_getLine(ifile, line))
        {
            return false;
        }
        splitStr(line, tmp, " ");
        if(tmp.size() != STATUS_SUM)
        {
            LogError("start_p illegal");
            return false;
        }
        for(uint j = 0; j< tmp.size(); j++)
        {
            _startProb[j] = atof(tmp[j].c_str());
            //cout<<_startProb[j]<<endl;
        }

        //load _transProb
        for(uint i = 0; i < STATUS_SUM; i++)
        {
            if(!_getLine(ifile, line))
            {
                return false;
            }
            splitStr(line, tmp, " ");
            if(tmp.size() != STATUS_SUM)
            {
                LogError("trans_p illegal");
                return false;
            }
            for(uint j =0; j < STATUS_SUM; j++)
            {
                _transProb[i][j] = atof(tmp[j].c_str());
                //cout<<_transProb[i][j]<<endl;
            }
        }

        //load _emitProbB
        if(!_getLine(ifile, line) || !_loadEmitProb(line, _emitProbB))
        {
            return false;
        }
        
        //load _emitProbE
        if(!_getLine(ifile, line) || !_loadEmitProb(line, _emitProbE))
        {
            return false;
        }
        
        //load _emitProbM
        if(!_getLine(ifile, line) || !_loadEmitProb(line, _emitProbM))
        {
            return false;
        }

        //load _emitProbS
        if(!_getLine(ifile, line) || !_loadEmitProb(line, _emitProbS))
        {
            return false;
        }

        LogInfo("loadModel [%s] end.", filePath);

        return true;
    }

    bool HMMSegment::cut(Unicode::const_iterator begin, Unicode::const_iterator end, vector<Unicode>& res)const
    {
        if(!_getInitFlag())
        {
            LogError("not inited.");
            return false;
        }
        vector<uint> status; 
        if(!_viterbi(begin, end, status))
        {
            LogError("_viterbi failed.");
            return false;
        }

        Unicode::const_iterator left = begin;
        Unicode::const_iterator right;
        for(uint i =0; i< status.size(); i++)
        {
            if(status[i] % 2) //if(E == status[i] || S == status[i])
            {
                right = begin + i + 1;
                res.push_back(Unicode(left, right));
                left = right;
            }
        }
        return true;
    }

    bool HMMSegment::cut(const string& str, vector<string>& res)const
    {
        return SegmentBase::cut(str, res);
    }

    bool HMMSegment::cut(Unicode::const_iterator begin, Unicode::const_iterator end, vector<string>& res) const
    {
        if(!_getInitFlag())
        {
            LogError("not inited.");
            return false;
        }
        if(begin == end)
        {
            return false;
        }
        vector<Unicode> words;
        if(!cut(begin, end, words))
        {
            return false;
        }
        string tmp;
        for(uint i = 0; i < words.size(); i++)
        {
            if(TransCode::encode(words[i], tmp))
            {
                res.push_back(tmp);
            }
        }
        return true;
    }

    bool HMMSegment::_viterbi(Unicode::const_iterator begin, Unicode::const_iterator end, vector<uint>& status)const
    {
        if(begin == end)
        {
            return false;
        }

        size_t Y = STATUS_SUM;
        size_t X = end - begin;
        size_t XYSize = X * Y;
        int * path;
        double * weight;
        uint now, old, stat;
        double tmp, endE, endS;
        
        try
        {
            path = new int [XYSize];
            weight = new double [XYSize];
        }
        catch(const std::bad_alloc&)
        {
            LogError("bad_alloc");
            return false;
        }
        if(NULL == path || NULL == weight)
        {
            LogError("bad_alloc");
            return false;
        }

        //start
        for(uint y = 0; y < Y; y++)
        {
            weight[0 + y * X] = _startProb[y] + _getEmitProb(_emitProbVec[y], *begin, MIN_DOUBLE);
            path[0 + y * X] = -1;
        }
        //process
        //for(; begin != end; begin++)
        for(uint x = 1; x < X; x++)
        {
            for(uint y = 0; y < Y; y++)
            {
                now = x + y*X;
                weight[now] = MIN_DOUBLE;
                path[now] = E; // warning
                for(uint preY = 0; preY < Y; preY++)
                {
                    old = x - 1 + preY * X;
                    tmp = weight[old] + _transProb[preY][y] + _getEmitProb(_emitProbVec[y], *(begin+x), MIN_DOUBLE);
                    if(tmp > weight[now])
                    {
                        weight[now] = tmp;
                        path[now] = preY;
                    }
                }
            }
        }

        endE = weight[X-1+E*X];
        endS = weight[X-1+S*X];
        stat = 0;
        if(endE > endS)
        {
            stat = E;
        }
        else
        {
            stat = S;
        }
        
        status.assign(X, 0);
        for(int x = X -1 ; x >= 0; x--)
        {
            status[x] = stat;
            stat = path[x + stat*X];
        }

        delete [] path;
        delete [] weight;
        return true;
    }

    bool HMMSegment::_getLine(ifstream& ifile, string& line)
    {
        while(getline(ifile, line))
        {
            trim(line);
            if(line.empty())
            {
                continue;
            }
            if(strStartsWith(line, "#"))
            {
                continue;
            }
            return true;
        }
        return false;
    }

    bool HMMSegment::_loadEmitProb(const string& line, EmitProbMap& mp)
    {
        if(line.empty())
        {
            return false;
        }
        vector<string> tmp, tmp2;
        uint16_t unico = 0;
        splitStr(line, tmp, ",");
        for(uint i = 0; i < tmp.size(); i++)
        {
            splitStr(tmp[i], tmp2, ":");
            if(2 != tmp2.size())
            {
                LogError("_emitProb illegal.");
                return false;
            }
            if(!_decodeOne(tmp2[0], unico))
            {
                LogError("TransCode failed.");
                return false;
            }
            mp[unico] = atof(tmp2[1].c_str());
        }
        return true;
    }

    bool HMMSegment::_decodeOne(const string& str, uint16_t& res)
    {
        Unicode ui16;
        if(!TransCode::decode(str, ui16) || ui16.size() != 1)
        {
            return false;
        }
        res = ui16[0];
        return true;
    }

    double HMMSegment::_getEmitProb(const EmitProbMap* ptMp, uint16_t key, double defVal)const
    {
        EmitProbMap::const_iterator cit = ptMp->find(key);
        if(cit == ptMp->end())
        {
            return defVal;
        }
        return cit->second;
        
    }
}

//////KeyWordExt.cpp
namespace CppJieba
{

    KeyWordExt::KeyWordExt()
    {
    }
    
    KeyWordExt::~KeyWordExt()
    {
    }

    bool KeyWordExt::init(const char* const segDictFile)
    {
        LogInfo("KeyWordExt init start ...");
        if(!_segment.init(segDictFile))
        {
            LogError("_segment.init failed.");
            return false;
        }
        return true;
    }

    bool KeyWordExt::loadStopWords(const char * const filePath)
    {

        LogInfo("_loadStopWords(%s) start", filePath);
        if(!_stopWords.empty())
        {
            LogError("_stopWords has been loaded before! ");
            return false;
        }
        if(!checkFileExist(filePath))
        {
            LogError("cann't find file[%s].",filePath);
            return false;
        }

        ifstream ifile(filePath);
        string line;
        Unicode word;
        while(getline(ifile, line))
        {
            if(!TransCode::decode(line, word))
            {
                LogError("decode failed .");
                return false;
            }
            _stopWords.insert(word);
        }
        LogInfo("load stopwords[%d] finished.", _stopWords.size());
        
        return true;
    }
    
    bool KeyWordExt::dispose()
    {
        _segment.dispose();
        return true;
    }

    bool KeyWordExt::_wordInfoCompare(const KeyWordInfo& a, const KeyWordInfo& b)
    {
        return a.weight > b.weight;
    }

    bool KeyWordExt::_sortWLIDF(vector<KeyWordInfo>& wordInfos)
    {
        for(uint i = 0; i < wordInfos.size(); i++)
        {
            KeyWordInfo& wInfo = wordInfos[i];
            wInfo.idf = - wInfo.logFreq;
            wInfo.weight = log(double(wInfo.word.size() + 1)) * wInfo.idf;
        }
        sort(wordInfos.begin(), wordInfos.end(), _wordInfoCompare);
        return true;
    }

    bool KeyWordExt::_extTopN(vector<KeyWordInfo>& wordInfos, uint topN)
    {
        int dis = wordInfos.size() - topN;
        if(dis <= 0)
        {
            return true;
        }
        
        if(uint(dis) <= topN)
        {
            for(int i = 0; i< dis; i++)
            {
                wordInfos.pop_back();
            }
        }
        else// in case that topN << size;
        {
            
            vector<KeyWordInfo> tmp(wordInfos.begin(), wordInfos.begin() + topN);
            wordInfos.swap(tmp);
        }
        return true;
    }


    bool KeyWordExt::extract(const vector<string>& words, vector<KeyWordInfo>& keyWordInfos, uint topN)
    {
        if(words.empty())
        {
            return false;
        }

        keyWordInfos.clear();
        for(uint i = 0; i < words.size(); i++)
        {
            Unicode uniWord;
            if(!TransCode::decode(words[i], uniWord))
            {
                LogError("decode failed");
                return false;
            }
            keyWordInfos.push_back(uniWord);
        }

        return _extract(keyWordInfos, topN);
    }

    bool KeyWordExt::extract(const string& title, vector<KeyWordInfo>& keyWordInfos, uint topN)
    {
        if(title.empty())
        {
            return false;
        }
        
        vector<TrieNodeInfo> trieNodeInfos; 
        Unicode unico;
        if(!TransCode::decode(title, unico))
        {
            return false;
        }
        _segment.cut(unico.begin(), unico.end(), trieNodeInfos);

        keyWordInfos.clear();
        for(uint i = 0; i < trieNodeInfos.size(); i++)
        {
            keyWordInfos.push_back(trieNodeInfos[i]);
        }
        return _extract(keyWordInfos, topN);
    }

    bool KeyWordExt::_extract(vector<KeyWordInfo>& keyWordInfos, uint topN)
    {
        if(!_filter(keyWordInfos))
        {
            LogError("_filter failed.");
            return false;
        }

        if(!_sortWLIDF(keyWordInfos))
        {
            LogError("_sortWLIDF failed.");
            return false;
        }

        if(!_extTopN(keyWordInfos, topN))
        {
            LogError("_extTopN failed.");
            return false;
        }

        return true;
    }

    bool KeyWordExt::_filter(vector<KeyWordInfo>& wordInfos)
    {
        if(!_filterDuplicate(wordInfos))
        {
            LogError("_filterDuplicate failed.");
            return false;
        }

        if(!_filterSingleWord(wordInfos))
        {
            LogError("_filterSingleWord failed.");
            return false;
        }

        if(!_filterStopWords(wordInfos))
        {
            LogError("_filterStopWords failed.");
            return false;
        }

        if(!_filterSubstr(wordInfos))
        {
            LogError("_filterSubstr failed.");
            return false;
        }

        return true;
    }

    bool KeyWordExt::_filterStopWords(vector<KeyWordInfo>& wordInfos)
    {
        if(_stopWords.empty())
        {
            return true;
        }
        for(vector<KeyWordInfo>::iterator it = wordInfos.begin(); it != wordInfos.end();)
        {
            if(_stopWords.find(it->word) != _stopWords.end())
            {
                it = wordInfos.erase(it);
            }
            else
            {
                it ++;
            }
        }
        return true;
    }


    bool KeyWordExt::_filterDuplicate(vector<KeyWordInfo>& wordInfos)
    {
        set<Unicode> st;
        for(vector<KeyWordInfo>::iterator it = wordInfos.begin(); it != wordInfos.end(); )
        {
            if(st.find(it->word) != st.end())
            {
                it = wordInfos.erase(it);
            }
            else
            {
                st.insert(it->word);
                it++;
            }
        }
        return true;
    }

    bool KeyWordExt::_filterSingleWord(vector<KeyWordInfo>& wordInfos)
    {
        for(vector<KeyWordInfo>::iterator it = wordInfos.begin(); it != wordInfos.end();)
        {

            // filter single word
            if(1 == it->word.size())
            {
                it = wordInfos.erase(it);
            }
            else
            {
                it++;
            }
        }
        return true;
    }

    bool KeyWordExt::_filterSubstr(vector<KeyWordInfo>& wordInfos)
    {
        vector<Unicode> tmp ;
        for(uint i = 0; i < wordInfos.size(); i++)
        {
            tmp.push_back(wordInfos[i].word);
        }

        for(vector<KeyWordInfo>::iterator it = wordInfos.begin(); it != wordInfos.end(); )
        {
            if(_isSubIn(tmp, it->word))
            {
                it = wordInfos.erase(it);
            }
            else
            {
                it++;
            }
        }

        return true;
    }

    //bool KeyWordExt::_isContainSubWords(const string& word)
    //{
    //    for(uint i = 0; i < _priorSubWords.size(); i++)
    //    {
    //        if(string::npos != word.find(_priorSubWords[i]))
    //        {
    //            return true;
    //        }
    //    }
    //    return false;
    //}

    //bool KeyWordExt::_prioritizeSubWords(vector<KeyWordInfo>& wordInfos)
    //{
    //    if(2 > wordInfos.size())
    //    {
    //        return true;
    //    }

    //    KeyWordInfo prior;
    //    bool flag = false;
    //    for(vector<KeyWordInfo>::iterator it = wordInfos.begin(); it != wordInfos.end(); )
    //    {
    //        if(_isContainSubWords(it->word))
    //        {
    //            prior = *it;
    //            it = wordInfos.erase(it);
    //            flag = true;
    //            break;
    //        }
    //        else
    //        {
    //            it ++;
    //        }
    //    }
    //    if(flag)
    //    {
    //        wordInfos.insert(wordInfos.begin(), prior);
    //    }
    //    return true;
    //}
}

//////MixSegment.cpp
namespace CppJieba
{
    MixSegment::MixSegment()
    {
    }
    
    MixSegment::~MixSegment()
    {
        dispose();
    }

    bool MixSegment::init(const char* const mpSegDict, const char* const hmmSegDict)
    {
        if(_getInitFlag())
        {
            LogError("inited.");
            return false;
        }
        if(!_mpSeg.init(mpSegDict))
        {
            LogError("_mpSeg init");
            return false;
        }
        if(!_hmmSeg.init(hmmSegDict))
        {
            LogError("_hmmSeg init");
            return false;
        }
        return _setInitFlag(true);
    }
    
    bool MixSegment::dispose()
    {
        if(!_getInitFlag())
        {
            return true;
        }
        _mpSeg.dispose();
        _hmmSeg.dispose();
        _setInitFlag(false);
        return true;
    }
    bool MixSegment::cut(const string& str, vector<string>& res)const
    {
        return SegmentBase::cut(str, res);
    }

    bool MixSegment::cut(Unicode::const_iterator begin, Unicode::const_iterator end, vector<string>& res)const
    {
        if(!_getInitFlag())
        {
            LogError("not inited.");
            return false;
        }
		if(begin == end)
		{
			return false;
		}
        vector<TrieNodeInfo> infos;
        if(!_mpSeg.cut(begin, end, infos))
        {
            LogError("mpSeg cutDAG failed.");
            return false;
        }
        Unicode unico;
        vector<Unicode> hmmRes;
        string tmp;
        for(uint i= 0; i < infos.size(); i++)
        {
            TransCode::encode(infos[i].word,tmp);
            if(1 == infos[i].word.size())
            {
                unico.push_back(infos[i].word[0]);
            }
            else
            {
                if(!unico.empty())
                {
                    hmmRes.clear();
                    if(!_hmmSeg.cut(unico.begin(), unico.end(), hmmRes))
                    {
                        LogError("_hmmSeg cut failed.");
                        return false;
                    }
                    for(uint j = 0; j < hmmRes.size(); j++)
                    {
                        TransCode::encode(hmmRes[j], tmp);
                        res.push_back(tmp);
                    }
                }
                unico.clear();
                TransCode::encode(infos[i].word, tmp);
                res.push_back(tmp);
            }
        }
        if(!unico.empty())
        {
            if(!_hmmSeg.cut(unico.begin(), unico.end(), hmmRes))
            {
                LogError("_hmmSeg cut failed.");
                return false;
            }
            for(uint j = 0; j < hmmRes.size(); j++)
            {
                TransCode::encode(hmmRes[j], tmp);
                res.push_back(tmp);
            }
        }
        
        return true;
    }
}

//////MPSegment.cpp
namespace CppJieba
{
    MPSegment::MPSegment()
    {
    }
    
    MPSegment::~MPSegment()
    {
        dispose();
    }

    bool MPSegment::init(const char* const filePath)
    {
        if(_getInitFlag())
        {
            LogError("already inited before now.");
            return false;
        }
        if(!_trie.init())
        {
            LogError("_trie.init failed.");
            return false;
        }
        LogInfo("_trie.loadDict(%s) start...", filePath);
        if(!_trie.loadDict(filePath))
        {
            LogError("_trie.loadDict faield.");
            return false;
        }
        LogInfo("_trie.loadDict end.");
        return _setInitFlag(true);
    }
    
    bool MPSegment::dispose()
    {
        if(!_getInitFlag())
        {
            return true;
        }
        _trie.dispose();
        _setInitFlag(false);
        return true;
    }

    bool MPSegment::cut(const string& str, vector<string>& res)const
    {
        return SegmentBase::cut(str, res);
    }

    bool MPSegment::cut(Unicode::const_iterator begin, Unicode::const_iterator end, vector<string>& res)const
    {
        if(!_getInitFlag())
        {
            LogError("not inited.");
            return false;
        }
        vector<TrieNodeInfo> segWordInfos;
        if(!cut(begin, end, segWordInfos))
        {
            return false;
        }
        string tmp;
        for(uint i = 0; i < segWordInfos.size(); i++)
        {
            if(TransCode::encode(segWordInfos[i].word, tmp))
            {
                res.push_back(tmp);
            }
            else
            {
                LogError("encode failed.");
            }
        }
        return true;
    }

    bool MPSegment::cut(Unicode::const_iterator begin , Unicode::const_iterator end, vector<TrieNodeInfo>& segWordInfos)const
    {
        if(!_getInitFlag())
        {
            LogError("not inited.");
            return false;
        }
        SegmentContext segContext;
        for(Unicode::const_iterator it = begin; it != end; it++)
        {
            segContext.push_back(SegmentChar(*it));
        }
        
        //calc DAG
        if(!_calcDAG(segContext))
        {
            LogError("_calcDAG failed.");
            return false;
        }

        if(!_calcDP(segContext))
        {
            LogError("_calcDP failed.");
            return false;
        }

        if(!_cut(segContext, segWordInfos))
        {
            LogError("_cut failed.");
            return false;
        }

        return true;
    }

    bool MPSegment::cut(const string& str, vector<TrieNodeInfo>& segWordInfos)const
    {
        if(!_getInitFlag())
        {
            LogError("not inited.");
            return false;
        }
        if(str.empty())
        {
            return false;
        }
        Unicode sentence;

        if(!TransCode::decode(str, sentence))
        {
            LogError("TransCode::decode failed.");
            return false;
        }
        return cut(sentence.begin(), sentence.end(), segWordInfos);

    }

    bool MPSegment::_calcDAG(SegmentContext& segContext)const
    {
        if(segContext.empty())
        {
            LogError("segContext empty.");
            return false;
        }

        Unicode unicode;
        for(uint i = 0; i < segContext.size(); i++)
        {
            unicode.clear();
            for(uint j = i ; j < segContext.size(); j++)
            {
                unicode.push_back(segContext[j].uniCh);
            }

			vector<pair<uint, const TrieNodeInfo*> > vp;
			if(_trie.find(unicode, vp))
			{
				for(uint j = 0; j < vp.size(); j++)
				{
					uint nextp = vp[j].first + i;
					segContext[i].dag[nextp] = vp[j].second; 
					//cout<<vp[j].first<<endl;
					//LogDebug(vp[j].second->toString());
				}
			}
            if(segContext[i].dag.end() == segContext[i].dag.find(i))
            {
                segContext[i].dag[i] = NULL;
            }
        }
        return true;
    }

    bool MPSegment::_calcDP(SegmentContext& segContext)const
    {
        if(segContext.empty())
        {
            LogError("segContext empty");
            return false;
        }
        
        for(int i = segContext.size() - 1; i >= 0; i--)
        {
            segContext[i].pInfo = NULL;
            segContext[i].weight = MIN_DOUBLE;
            for(DagType::const_iterator it = segContext[i].dag.begin(); it != segContext[i].dag.end(); it++)
            {
                uint nextPos = it->first;
                const TrieNodeInfo* p = it->second;
                double val = 0.0;
                if(nextPos + 1 < segContext.size())
                {
                    val += segContext[nextPos + 1].weight;
                }

                if(p)
                {
                    val += p->logFreq; 
                }
                else
                {
                    val += _trie.getMinLogFreq();
                }
                if(val > segContext[i].weight)
                {
                    segContext[i].pInfo = p;
                    segContext[i].weight = val;
                }
            }
        }
        return true;

    }

    bool MPSegment::_cut(SegmentContext& segContext, vector<TrieNodeInfo>& res)const
    {
        uint i = 0;
        while(i < segContext.size())
        {
            const TrieNodeInfo* p = segContext[i].pInfo;
            if(p)
            {
                res.push_back(*p);
                i += p->word.size();
            }
            else//single chinese word
            {
                TrieNodeInfo nodeInfo;
                nodeInfo.word.push_back(segContext[i].uniCh);
                nodeInfo.freq = 0;
                nodeInfo.logFreq = _trie.getMinLogFreq();
                res.push_back(nodeInfo);
                i++;
            }
        }
        return true;
    }

}

//////SegmentBase.cpp
namespace CppJieba
{
    bool SegmentBase::cut(const string& str, vector<string>& res)const
    {
        if(!_getInitFlag())
        {
            LogError("not inited.");
            return false;
        }
        ChineseFilter filter;
        filter.feed(str);
        for(ChineseFilter::iterator it = filter.begin(); it != filter.end(); it++)
        {
            if(it.charType == CHWORD)
            {
                cut(it.begin, it.end, res);
            }
            else
            {
                string tmp;
                if(TransCode::encode(it.begin, it.end, tmp))
                {
                    res.push_back(tmp);
                }
            }
        }
        return true;
    }
}

//////Trie.cpp
namespace CppJieba
{

    Trie::Trie()
    {

        _root = NULL;
        _freqSum = 0;
        _minLogFreq = MAX_DOUBLE;
        _initFlag = false;
    }
    
    Trie::~Trie()
    {
        dispose();
    }
    
    bool Trie::init()
    {
        if(_getInitFlag())
        {
            LogError("already initted!");
            return false;
        }
        try
        {
            _root = new TrieNode;
        }
        catch(const bad_alloc& e)
        {
            return false;
        }
        if(NULL == _root)
        {
            return false;
        }
        _setInitFlag(true);
        return true;
    }

    bool Trie::loadDict(const char * const filePath)
    {
        if(!_getInitFlag())
        {
            LogError("not initted.");
            return false;
        }

        if(!checkFileExist(filePath))
        {
            LogError("cann't find fiel[%s].",filePath);
            return false;
        }
        bool res = false;
        res = _trieInsert(filePath);

        if(!res)
        {
            LogError("_trieInsert failed.");
            return false;
        }
        res = _countWeight();
        if(!res)
        {
            LogError("_countWeight failed.");
            return false;
        }
        return true;
    }

    bool Trie::_trieInsert(const char * const filePath)
    {
		std::cout << "loading Seg Dictionary:";

        ifstream ifile(filePath);
        string line;
        vector<string> vecBuf;
        
		int num = 0;
        TrieNodeInfo nodeInfo;
        while(getline(ifile, line))
        {
            vecBuf.clear();
            splitStr(line, vecBuf, " ");
            if(3 < vecBuf.size())
            {
                LogError("line[%s] illegal.", line.c_str());
                return false;
            }
            if(!TransCode::decode(vecBuf[0], nodeInfo.word))
            {
                return false;
            }
            nodeInfo.freq = atoi(vecBuf[1].c_str());
            if(3 == vecBuf.size())
            {
                nodeInfo.tag = vecBuf[2];
            }

            //insert node
            if(!insert(nodeInfo))
            {
                LogError("insert node failed!");
            }

			//输出提示
			num ++;
			if(num == 1000)
			{
				std::cout << '.';
				num = 0;
			}
        }
		std::cout << '\n';
        return true;
    }

    bool Trie::dispose()
    {
        if(!_getInitFlag())
        {
            return false;
        }
        bool ret = _deleteNode(_root);
        if(!ret)
        {
            LogFatal("_deleteNode failed!");
            return false;
        }
        _root = NULL;
        _nodeInfoVec.clear();

        _setInitFlag(false);
        return ret;
    }

    const TrieNodeInfo* Trie::findPrefix(const string& str)const
    {
        if(!_getInitFlag())
        {
            LogFatal("trie not initted!");
            return NULL;
        }
        Unicode uintVec;
        
        if(!TransCode::decode(str, uintVec))
        {
            LogError("TransCode::decode failed.");
            return NULL;
        }

        //find
        TrieNode* p = _root;
        uint pos = 0;
        uint16_t chUni = 0;
        const TrieNodeInfo * res = NULL;
        for(uint i = 0; i < uintVec.size(); i++)
        {
            chUni = uintVec[i];
            if(p->isLeaf)
            {
                pos = p->nodeInfoVecPos;
                if(pos >= _nodeInfoVec.size())
                {
                    LogFatal("node's nodeInfoVecPos is out of _nodeInfoVec's range");
                    return NULL;
                }
                res = &(_nodeInfoVec[pos]);
                
            }
            if(p->hmap.find(chUni) == p->hmap.end())
            {
                break;
            }
            else
            {
                p = p->hmap[chUni];
            }
        }
        return res;
    }

    const TrieNodeInfo* Trie::find(const string& str)const
    {
        Unicode uintVec;
        if(!TransCode::decode(str, uintVec))
        {
            return NULL;
        }
        return find(uintVec);
    }

    const TrieNodeInfo* Trie::find(const Unicode& uintVec)const
    {
        if(uintVec.empty())
        {
            return NULL;
        }
        return find(uintVec.begin(), uintVec.end());
    }

    const TrieNodeInfo* Trie::find(Unicode::const_iterator begin, Unicode::const_iterator end)const
    {
        
        if(!_getInitFlag())
        {
            LogFatal("trie not initted!");
            return NULL;
        }
        if(begin >= end)
        {
            return NULL;
        }
        TrieNode* p = _root;
        for(Unicode::const_iterator it = begin; it != end; it++)
        {
            uint16_t chUni = *it;
            if(p->hmap.find(chUni) == p-> hmap.end())
            {
                return NULL;
            }
            else
            {
                p = p->hmap[chUni];
            }
        }
        if(p->isLeaf)
        {
            uint pos = p->nodeInfoVecPos;
            if(pos < _nodeInfoVec.size())
            {
                return &(_nodeInfoVec[pos]);
            }
            else
            {
                LogFatal("node's nodeInfoVecPos is out of _nodeInfoVec's range");
                return NULL;
            }
        }
        return NULL;
    }

	bool Trie::find(const Unicode& unico, vector<pair<uint, const TrieNodeInfo*> >& res)const
	{
        if(!_getInitFlag())
        {
            LogFatal("trie not initted!");
            return false;
        }
        TrieNode* p = _root;
        //for(Unicode::const_iterator it = begin; it != end; it++)
        for(uint i = 0; i < unico.size(); i++)
        {
            if(p->hmap.find(unico[i]) == p-> hmap.end())
            {
				break;
            }
			p = p->hmap[unico[i]];
			if(p->isLeaf)
			{
				uint pos = p->nodeInfoVecPos;
				if(pos < _nodeInfoVec.size())
				{
					res.push_back(make_pair(i, &_nodeInfoVec[pos]));
				}
				else
				{
					LogFatal("node's nodeInfoVecPos is out of _nodeInfoVec's range");
					return false;
				}
			}
        }
		return !res.empty();
	}

    bool Trie::_deleteNode(TrieNode* node)
    {
        for(TrieNodeMap::iterator it = node->hmap.begin(); it != node->hmap.end(); it++)
        {
            TrieNode* next = it->second;
            _deleteNode(next);
        }
        
        delete node;
        return true;
    }


    bool Trie::insert(const TrieNodeInfo& nodeInfo)
    {
        if(!_getInitFlag())
        {
            LogFatal("not initted!");
            return false;
        }

        
        const Unicode& uintVec = nodeInfo.word;
        TrieNode* p = _root;
        for(uint i = 0; i < uintVec.size(); i++)
        {
            uint16_t cu = uintVec[i];
            if(NULL == p)
            {
                return false;
            }
            if(p->hmap.end() == p->hmap.find(cu))
            {
                TrieNode * next = NULL;
                try
                {
                    next = new TrieNode;
                }
                catch(const bad_alloc& e)
                {
                    return false;
                }
                p->hmap[cu] = next;
                p = next;
            }
            else
            {
                p = p->hmap[cu];
            }
        }
        if(NULL == p)
        {
            return false;
        }
        if(p->isLeaf)
        {
            LogError("this node already inserted");
            return false;
        }

        p->isLeaf = true;
        _nodeInfoVec.push_back(nodeInfo);
        p->nodeInfoVecPos = _nodeInfoVec.size() - 1;

        return true;
    }

    bool Trie::_countWeight()
    {
        if(_nodeInfoVec.empty() || 0 != _freqSum)
        {
            LogError("_nodeInfoVec is empty or _freqSum has been counted already.");
            return false;
        }
        
        //freq total freq
        for(size_t i = 0; i < _nodeInfoVec.size(); i++)
        {
            _freqSum += _nodeInfoVec[i].freq;
        }

        if(0 == _freqSum)
        {
            LogError("_freqSum == 0 .");
            return false;
        }
        
        //normalize
        for(uint i = 0; i < _nodeInfoVec.size(); i++)
        {
            TrieNodeInfo& nodeInfo = _nodeInfoVec[i];
            if(0 == nodeInfo.freq)
            {
                LogFatal("nodeInfo.freq == 0!");
                return false;
            }
            nodeInfo.logFreq = log(double(nodeInfo.freq)/double(_freqSum));
            if(_minLogFreq > nodeInfo.logFreq)
            {
                _minLogFreq = nodeInfo.logFreq;
            }
        }
        
        return true;
    }
}
