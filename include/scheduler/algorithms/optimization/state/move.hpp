#pragma once

#include <memory>
#include <ostream>

#include <scheduler/utils/types.hpp>

namespace specops {

class Move {
    public:
        using const_ptr = std::shared_ptr<const Move>;
        virtual ~Move() = 0;
        virtual hash_type hash() const = 0;
        virtual std::ostream& write(std::ostream&) const = 0;
        bool operator== (const Move&) const;
    protected:
        virtual bool equals(const Move&) const = 0;
};

class InitialMove : public Move {
    public:
        InitialMove();
        ~InitialMove() = default;
        hash_type hash() const override;
        std::ostream& write(std::ostream&) const override;
    protected:
        bool equals(const Move&) const override;
};

class PairwiseInterchangeMove : public Move {
    public:
        PairwiseInterchangeMove(identifier, identifier, identifier, identifier);
        ~PairwiseInterchangeMove() = default;
        hash_type hash() const override;
        std::ostream& write(std::ostream&) const override;
    protected:
        bool equals(const Move&) const override;
    private:
        identifier job, operation, nextJob, nextOperation;
};

class ChangeAlternativeMove : public Move {
    public:
        ChangeAlternativeMove(identifier, identifier, identifier);
        ~ChangeAlternativeMove() = default;
        hash_type hash() const override;
        std::ostream& write(std::ostream&) const override;
    protected:
        bool equals(const Move&) const override;
    private:
        identifier job, operation, alternative;
};

// Functors
struct MoveHashFunctor {
    hash_type operator() (const Move::const_ptr& x) const noexcept {
        return x->hash();
    }
};

struct MoveEqualToFunctor {
    bool operator() (const Move::const_ptr& lhs, const Move::const_ptr& rhs) const noexcept {
        return *lhs == *rhs;
    }
};

}

namespace std {

ostream& operator<< (ostream&, const specops::Move&);

}
