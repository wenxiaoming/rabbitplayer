#ifndef P2P_MANAGER_H
#define P2P_MANAGER_H

#include <muduo/base/Logging.h>
#include <muduo/base/Mutex.h>
#include <muduo/net/EventLoopThread.h>
#include <muduo/net/TcpClient.h>

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include "utility.h"
#include "codec.h"
#include "TrackerConnector.h"
#include "TrackerListener.h"
#include "NPConnector.h"
#include "SPConnector.h"

using namespace muduo;
using namespace muduo::net;

class P2PManager: public TrackerListener,
                  noncopyable,
                  public ThreadInterface
{
public:
    P2PManager();
    ~P2PManager();
    void connectTracker();
    void disConnectTracker();
    void checkTrackerStatus();
private:
    void threadFunc();
    Thread mThread;
public:
    //implement TrackerListener
    virtual void updateSpAddr(uint8_t spNum, NetAddress* spAddrArray);
    virtual void updateNpAddr();
    virtual void updateResInterval(BlockInterval interval);
    BlockInterval mBlockInterval;
private:
    NPConnector* mNpConnector;
    TrackerConnector* mTrackerConnector;
    SPConnector* mSPConnector;
    EventLoopThread mLoopThread;
    EventLoop* mEventLoop;
private:
    char resource_md5[MD5_LENGTH];
private:
    Condition* mSPConnectedCond;
    MutexLock mSPConnectedMutex;
    bool mSPConnectedFlag;
private:
    //for downloading from sp
    uint32_t mCurrDownload;
};

#endif