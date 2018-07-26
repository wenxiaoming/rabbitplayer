//
// Created by kevin on 2017/12/1.
//

#ifndef RABBITPLAYER_THREADINTERFACE_H
#define RABBITPLAYER_THREADINTERFACE_H

namespace muduo {
    class ThreadInterface {
    public:
        virtual void threadFunc() = 0;
    };
}
#endif //RABBITPLAYER_THREADINTERFACE_H
