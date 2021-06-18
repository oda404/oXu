
#include<oxu/framework/threading/pipeline.hpp>

namespace oxu::framework::threading
{

void Pipeline::makeRequest(Request request)
{
    mtx.lock();
    pipeline.push_back(request);
    mtx.unlock();
}

bool Pipeline::pollRequest(Request &targetRequest)
{
    mtx.lock();
    bool ret = static_cast<bool>(pipeline.size());

    if(pipeline.size() > 0)
    {
        targetRequest = pipeline[0];
        pipeline.erase(pipeline.begin());
    }

    mtx.unlock();

    return ret;
}

}