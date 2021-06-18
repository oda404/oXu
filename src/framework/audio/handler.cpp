
#include<oxu/framework/audio/handler.hpp>
#include<oxu/framework/threading/thread.hpp>

namespace oxu::framework::audio::handler
{

using namespace framework::threading;

    static Thread c_selfThread;

    static void updateThread()
    {
        Request l_request;
        while(true)
        {
            c_selfThread.capFPS();

            while(c_selfThread.pipeline.pollRequest(l_request))
            {
                switch(l_request.instruction)
                {
                case Audio::HALT_THREAD:
                    return;
                }
            }


            
        }
    }

    static void initThread()
    {
        c_selfThread.doneInit = true;
        updateThread();
    }

    void init()
    {
        c_selfThread.setMaxFPS(1000);
        c_selfThread.doneInit = false;
        c_selfThread.start([] { initThread(); });
        while(!c_selfThread.doneInit);
    }

    void shutDown()
    {
        c_selfThread.pipeline.makeRequest(Audio::HALT_THREAD);
        c_selfThread.join();
    }
}
