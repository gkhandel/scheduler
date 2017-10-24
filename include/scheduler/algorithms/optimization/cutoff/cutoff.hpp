/*
 *  Copyright (c) 2017, Palo Alto Research Center (PARC)
 *  All rights reserved.
 *  The software herein is provided with Government Purpose Rights.
 */

#pragma once

#include <initializer_list>
#include <memory>
#include <vector>

#include <scheduler/utils/types.hpp>

namespace specops {

class Cutoff {
    public:
        using ptr = std::shared_ptr<Cutoff>;
        virtual ~Cutoff() = 0;
        virtual void reset() = 0;
        virtual bool stop(score) = 0;
};

class MultipleCutoff : public Cutoff {
    public:
        MultipleCutoff(std::initializer_list<Cutoff::ptr>);
        ~MultipleCutoff() = default;
        void reset() override;
        bool stop(score) override;
    private:
        std::vector<Cutoff::ptr> cutoffs;
};

}
