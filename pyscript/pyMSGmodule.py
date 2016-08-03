# ! /usr/bin/python
# coding:utf-8

import titlebook_pb2

def strListToMsgStr(str_list):
    if not isinstance(str_list, list):
        raise ValueError(str(str_list)+' is not list')

    title_book=titlebook_pb2.TitleList()
    for str_item in str_list:
        if not isinstance(str_item, str):
            raise ValueError(str(str_item)+' is not str')
        title_book.title.append(str_item)

    return title_book.SerializeToString()


def msgStrToIdList(msg_str):
    id_book=titlebook_pb2.IdList()
    id_book.ParseFromString(msg_str)
    id_list=[]

    for id_num in id_book.id:
        id_list.append(id_num)

    return id_list
    

if __name__=='__main__':

    str_list=["教育部考试中心托福网考网上报名",
                 "皇马6-4马竞登顶欧冠",
                 "evernote 安装最新版本后，个别笔记本无法同步？",
                 "ios私有api 能修改运营商名称吗？",
                 "提前博弈A股纳入MSCI"]

    try:
        # msg_str=strListToMsgStr(str_list+[1])
        msg_str=strListToMsgStr(str_list)
        print msg_str
    except Exception as error:
        print error

    print '*'*10

    ifile=open('idbook.protomodel', 'r')
    id_str=ifile.read()
    ifile.close()

    try:
        id_list=msgStrToIdList(id_str)
        print id_list
    except Exception as error:
        print error
