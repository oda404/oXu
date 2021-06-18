#pragma once

#include<mutex>
#include<vector>

#include<oxu/framework/threading/request.hpp>

namespace oxu::framework::threading
{
    class Pipeline
    {
    private:
        std::vector<Request> pipeline;
        std::mutex mtx;

    public:
        void makeRequest(Request request);
        bool pollRequest(Request &targetRequest);
    };
}