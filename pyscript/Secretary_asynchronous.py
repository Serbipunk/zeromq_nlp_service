#!/usr/bin/python
#coding:utf-8

import zmq
import time
import sys
from Queue import Queue
from threading import Thread

import sys
sys.path.insert(0, 'build')
import pyMSGmodule as MSG


Leader_port = 8964
Worker_port = 5555


msg_queue = Queue()

# ( A **Secretary** will say 'OK' immediately, when **Leader** assigns a task. )
# An important task of **Secretary** is his scheduling of **Worker**
# when the **Worker** is available && there is some task to do (in message_queue),
# the **Worker** will get his task by **Secretary**
# 
#   secretaryThread() will implement the preceding described works.
# 
# But waiting for the **Worker** finish this 
def secretaryThread(m_queue, flag):
    while True:
        if m_queue.qsize() > 0:
            uni_id, real_msg = m_queue.get()

            # give **Worker** his task
            # thread program will be blocked here
            #   print 'dododododdo'
            #   time.sleep(10)
            Worker_Req_context = zmq.Context()
            Worker_Req_socket = Worker_Req_context.socket(zmq.REQ)
            Worker_Req_socket.connect("tcp://localhost:%d" % Worker_port)

            leader_msg_str = real_msg[:]
            Worker_Req_socket.send(leader_msg_str)
            worker_msg = Worker_Req_socket.recv()
            # print worker_msg
            id_list = MSG.msgStrToIdList(worker_msg)
            print uni_id, '--', id_list

        else:
            time.sleep(1)

# set Secretary as Deamon Thread
Secretary = Thread(target=secretaryThread, args=(msg_queue, 1))
Secretary.setDaemon(True)
Secretary.start()

Leader_rep_context = zmq.Context()
Leader_rep_socket = Leader_rep_context.socket(zmq.REP)
Leader_rep_socket.bind("tcp://*:%d" % Leader_port)

# wait for the Leader's command && say OK.
while True:
    message = Leader_rep_socket.recv()
    uni_id = message[:message.find(' ')]
    real_msg = message[message.find(' ')+1:]

    msg_queue.put([uni_id, real_msg])

    print 'Received requiest', message
    Leader_rep_socket.send('OK, I will do it later.')
