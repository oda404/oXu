#include"pipeline.hpp"

namespace oxu
{
    void Pipeline::makeRequest(Request request)
    {
        std::unique_lock<std::mutex> lock(mtx);
        pipeline.push_back(request);
    }

    bool Pipeline::pollRequest(Request &targetRequest)
    {
        std::unique_lock<std::mutex> lock(mtx);
        bool ret = static_cast<bool>(pipeline.size());

        if(pipeline.size() > 0)
        {
            targetRequest = pipeline[0];
            pipeline.erase(pipeline.begin());
        }

        return ret;
    }
}