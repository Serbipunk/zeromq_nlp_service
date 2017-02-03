# a NLP service powered by ZEROMQ

most NLP program has to load tons of math model. It's a good choice to set NLP program independent from web-service-infrastructure.

We compare the C++ NLP module as the **Worker** and compare the Python control module as the **Leader**. The **Leader** arrange the **Worker** to do his job, and collect his achievement.

The process loop between **Leader** and **Worker** is synchronous.

But you can use Secretary assistant-python-script to accomplish the *asynchronous* calling of Worker.


-----------

## dependency

* protobuf and python-protobuf

* Zeromq and pyzmq

-----------

## deploy this service

All the shells should be run at $(zeromq_nlp_service) directory.

### 1. start Worker service

  ./build/bin/Worker

### 2. run synchronized Leader script

  python ./build/bin/Leader_synchronous.py
  
### 3. run asynchronized Leader script

#### 3.1 Secretary service should be deployed at first.

  python build/bin/Secretary_asynchronous.py
  
#### 3.2 run asynchronized Leader script

  python build/bin/Leader_asynchronous.py