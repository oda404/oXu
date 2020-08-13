#pragma once

#include<stack>
#include<vector>

#include<oXu/core/threading/pipeline/request.hpp>

#include<oXu/utils/logger.hpp>

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