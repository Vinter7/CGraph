/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: GSome.h
@Time: 2023/8/20 11:20
@Desc: 
***************************/

#ifndef CGRAPH_GSOME_H
#define CGRAPH_GSOME_H

#include <memory>
#include <mutex>
#include <condition_variable>

#include "../GGroup.h"

CGRAPH_NAMESPACE_BEGIN

template<CSize TriggerNum = 1>
class GSome : public GGroup {
protected:
    CStatus addElement(GElementPtr element) override;

    explicit GSome();

    /**
     * 异步处理 GSome中的所有信息
     * @param ptr
     * @return
     */
    CVoid process(GAsyncNodePtr ptr);

    CStatus run() override;

    CBool isSerializable() override;

    CVoid dump(std::ostream& oss) final;

    CGRAPH_NO_ALLOWED_COPY(GSome)

private:
    std::atomic<CSize> left_num_ {0};      // 还剩的触发结束的个数
    CStatus cur_status_ ;                      // 记录异步时刻的当前状态信息

    std::mutex lock_;
    std::condition_variable cv_;

    friend class GPipeline;
    friend class GStaticEngine;
    friend class GDynamicEngine;
    friend class UAllocator;
};

CGRAPH_NAMESPACE_END

#include "GSome.inl"

#endif //CGRAPH_GSOME_H
