# a NLP service powered by ZEROMQ

Since most NLP program has to load tons of math model, it's better to be set as an NLP service, indepence of web-server program. 

On the other hand, another service, like asynchronous HTTP-web-server, should coorperate with the NLP service and give real client what he needs.

We compare the C++ NLP module as the **Worker** and compare the Python control module as the **Leader**. The **Leader** arrange the **Worker** to do his job, and collect his achievement.

The process loop between **Leader** and **Worker** is synchronous.


-----------

## dependency:

* protobuf and python-protobuf

* Zeromq and pyzmq

-----------

## how to use

when you finish making all.

#### ./build/bin/Worker

will open NLP Worker service.

#### python ./build/bin/Leader.py

will make Worker work for you and get worker's achievement.
