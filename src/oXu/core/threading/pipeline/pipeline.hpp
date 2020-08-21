#pragma once

#include<mutex>
#include<vector>

#include<oXu/core/threading/pipeline/request.hpp>

namespace oxu
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