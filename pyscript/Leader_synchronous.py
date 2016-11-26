#!/usr/bin/python
#coding:utf-8

import zmq
import sys
sys.path.insert(0, 'build')
import pyMSGmodule as MSG


Worker_port = 5555


if __name__=='__main__':

    # Client is created with a socket type “zmq.REQ”
    Leader_Req_context = zmq.Context()
    print "Connecting to server..."
    Leader_Req_socket = Leader_Req_context.socket(zmq.REQ)
    Leader_Req_socket.connect("tcp://localhost:%d" % Worker_port)

    str_list=["教育部考试中心托福网考网上报名",
                "皇马6-4马竞登顶欧冠",
                "evernote 安装最新版本后，个别笔记本无法同步？",
                "ios私有api 能修改运营商名称吗？",
                "提前博弈A股纳入MSCI"]*10

    # serialize str_list into msg_str
    msg_str=''
    try:
        # msg_str=strListToMsgStr(str_list+[1])
        msg_str=MSG.strListToMsgStr(str_list)
        print msg_str
    except Exception as error:
        print error
        exit()

    # #send request to CPP Server
    Leader_Req_socket.send (msg_str)

    # #get the reply from CPP Server
    # function is blocked here until having reply
    message = Leader_Req_socket.recv()
    print '\n\n', message, '\n'
    id_list = MSG.msgStrToIdList(message)
    print id_list
