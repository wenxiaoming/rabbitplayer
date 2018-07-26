#include "P2PManager.h"
#include <stdio.h>

P2PManager::P2PManager()
:mThread(this, "P2PManager")
{
    mTrackerConnector = NULL;
    mNpConnector = NULL;
    mSPConnector = NULL;

    mEventLoop = mLoopThread.startLoop();

    mSPConnectedCond = new Condition(mSPConnectedMutex);

    mSPConnectedFlag = false;

    //hardcode resource id
    memcpy(resource_md5, "e54a58cc63ad1a32f28ef53006be2937", MD5_LENGTH);

    mThread.start();
}

P2PManager::~P2PManager()
{
    if(mTrackerConnector)
        delete mTrackerConnector;

    if(mNpConnector)
        delete mNpConnector;

    if(mSPConnector)
        delete mSPConnector;

    mThread.join();
}

void P2PManager::threadFunc()
{
    LOG_INFO << "threadFunc enter";
    while(true)
    {
        if(!mSPConnectedFlag)
        {
            mSPConnectedCond->wait();
            mSPConnectedFlag = true;
            mSPConnector->sendHello();
            LOG_INFO << "threadFunc mSPConnector->sendHello() ";
        } else
        {
            LOG_INFO << "threadFunc loop";
            usleep(1000000);
        }

    }
}

void P2PManager::connectTracker()
{
    char* param[] = {"192.168.2.104", "3333"};
    //start_client(2, param);

    //EventLoopThread loopThread;
    uint16_t port = static_cast<uint16_t>(atoi(param[1]));
    InetAddress serverAddr(param[0], port);

    mTrackerConnector = new TrackerConnector(this, mEventLoop, serverAddr, resource_md5);
    mTrackerConnector->connect();
    std::string line;
    while (std::getline(std::cin, line))
    {
        mTrackerConnector->write(line);
    }
    //Todo, wait for the connection is established.

    //login
    mTrackerConnector->login();

    CurrentThread::sleepUsec(1000*1000);  // wait for disconnect, see ace/logging/client.cc

}

void P2PManager::disConnectTracker()
{
    if(mTrackerConnector)
        mTrackerConnector->disconnect();
}

void P2PManager::checkTrackerStatus()
{
    if(mTrackerConnector)
        mTrackerConnector->getResInterval();
}

void P2PManager::updateSpAddr(uint8_t spNum, NetAddress* spAddrArray)
{
    if(spNum <= 0)
        return;

    sockaddr_in addr;

    //addr.sin_family = spAddrArray[0].sin_family;
    addr.sin_family = AF_INET;
    addr.sin_port = spAddrArray[0].sin_port;
    addr.sin_addr = spAddrArray[0].sin_addr;

    InetAddress serverAddr(addr);

    LOG_INFO << "SPConnector serverAddr toIp() " << serverAddr.toIp();
    LOG_INFO << "SPConnector serverAddr toIpPort() " << serverAddr.toIpPort();

    mSPConnector = new SPConnector(mEventLoop, serverAddr, resource_md5);
    mSPConnector->connect();

    mSPConnectedCond->notify();
}

void P2PManager::updateNpAddr()
{

}

void P2PManager::updateResInterval(BlockInterval interval)
{
    mBlockInterval = interval;
}
