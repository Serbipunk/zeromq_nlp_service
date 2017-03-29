# a NLP service powered by ZEROMQ

NLP programs have to load tons of math models. It's a good choice to separate NLP program from web-service-infrastructure.

We compare the C++ NLP module as the **Worker** to the Python control module as the **Leader**. The **Leader** arranges for the **Worker** to do its job and collects its achievement.

While the process loop between **Leader** and **Worker** is synchronous, you can use Secretary assistant-python-script for making *asynchronous* calls to Worker.


-----------

## dependency

* protobuf and python-protobuf

* Zeromq and pyzmq

-----------

## deploy this service

All shells should be run at $(zeromq_nlp_service) directory.

### 1. start Worker service

```
./build/bin/Worker
```

### 2. run synchronized Leader script

```
python ./build/bin/Leader_synchronous.py
```
  
### 3. run asynchronized Leader script

#### 3.1 Secretary service should be deployed at first.

```
python build/bin/Secretary_asynchronous.py
```
  
#### 3.2 run asynchronized Leader script

```
python build/bin/Leader_asynchronous.py
```
