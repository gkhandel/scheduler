/*
 *  Copyright (c) 2017, Palo Alto Research Center (PARC)
 *  All rights reserved.
 *  The software herein is provided with Government Purpose Rights.
 */

#include <scheduler/algorithms/optimization/state/move.hpp>

#include <typeinfo>

#include <scheduler/utils/hashing.hpp>

namespace specops {

Move::~Move() {
}

bool Move::operator== (const Move& rhs) const {
    if (typeid(*this) == typeid(rhs)) {
        return this->equals(rhs);
    }
    return false;
}

InitialMove::InitialMove() {
}

hash_type InitialMove::hash() const {
    return 0;
}

std::ostream& InitialMove::write(std::ostream& os) const {
    os << "InitialMove";
    return os;
}

bool InitialMove::equals(const Move&) const {
    return true;
}

PairwiseInterchangeMove::PairwiseInterchangeMove(identifier job,
                                                 identifier operation,
                                                 identifier nextJob,
                                                 identifier nextOperation) :
        job{job}, operation{operation}, nextJob{nextJob}, nextOperation{nextOperation} {
    if (job > nextJob) {
        this->job = nextJob;
        this->operation = nextOperation;
        this->nextJob = job;
        this->nextOperation = operation;
    }
    else if (job == nextJob && operation > nextOperation) {
        this->operation = nextOperation;
        this->nextOperation = operation;
    }
}

hash_type PairwiseInterchangeMove::hash() const {
    return cantorHashing(job, operation, nextJob, nextOperation);
}

std::ostream& PairwiseInterchangeMove::write(std::ostream& os) const {
    os << "PairwiseInterchangeMove J" << job << '-' << operation
       << " J" << nextJob << '-' << nextOperation;
    return os;
}

bool PairwiseInterchangeMove::equals(const Move& rhs) const {
    using const_ref = const PairwiseInterchangeMove&;
    const_ref casted = static_cast<const_ref>(rhs);
    return (job == casted.job && operation == casted.operation &&
            nextJob == casted.nextJob && nextOperation == casted.nextOperation);
}


ChangeAlternativeMove::ChangeAlternativeMove(identifier job,
                                             identifier operation,
                                             identifier alternative):
        job{job}, operation{operation}, alternative{alternative} {
}

hash_type ChangeAlternativeMove::hash() const {
    return cantorHashing(job, operation, alternative);
}

std::ostream& ChangeAlternativeMove::write(std::ostream& os) const {
    os << "ChangeAlternativeMove J" << job << '-' << operation << " to " << alternative;
    return os;
}

bool ChangeAlternativeMove::equals(const Move& rhs) const {
    using const_ref = const ChangeAlternativeMove&;
    const_ref casted = static_cast<const_ref>(rhs);
    return job == casted.job && operation == casted.operation && alternative == casted.alternative;
}

}

namespace std {

ostream& operator<< (ostream& os, const specops::Move& move) {
    return move.write(os);
}

}
