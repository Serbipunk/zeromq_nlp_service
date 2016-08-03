# a NLP service powered by ZEROMQ

most NLP program has to load tons of math model. It's a good choice to set NLP program independent from web-service-infrastructure.

We compare the C++ NLP module as the **Worker** and compare the Python control module as the **Leader**. The **Leader** arrange the **Worker** to do his job, and collect his achievement.

The process loop between **Leader** and **Worker** is synchronous.


-----------

## dependency

* protobuf and python-protobuf

* Zeromq and pyzmq

-----------

## how to use

when you finish making all.

#### ./build/bin/Worker

will open NLP Worker service.

#### python ./build/bin/Leader.py

will make Worker work for you and get worker's achievement.
