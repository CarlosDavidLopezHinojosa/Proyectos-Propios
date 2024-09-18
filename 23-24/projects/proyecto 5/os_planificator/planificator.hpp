#ifndef PLANIFICATOR_HPP
#define PLANIFICATOR_HPP

#include <iostream>
#include <functional>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <memory>
#include <vector>
#include <list>
#include <cassert>

class process
{
public:

    enum state
    {
        NEW = 0,
        READY = 1,
        BLOCKED = 2,
        COMPLETED = 3
    };

    process(char label, size_t arrival, size_t cpu_time, size_t priority = 0)
    {
        label_ = label;
        cpu_time_ = resting_time_ = cpu_time;
        arrival_ = arrival;
        state_ = NEW;
        priority_ = priority;
    }

    ~process(){}

    char label() const { return label_; }
    size_t cpu_time() const { return cpu_time_; }
    size_t resting_time() const { return resting_time_; }
    size_t arrival() const { return arrival_; }
    size_t priority() const { return priority_; }
    state current_state() const { return state_; }
    bool is_completed() const { return state_ == COMPLETED; }

    void set_ready() { state_ = READY; }
    void set_completed() { state_ = COMPLETED; }
    void update_priority() { priority_++; }

    void execute()
    {
        if (resting_time_ > 0)
        {
            resting_time_--;
            if (resting_time_ == 0)
            {
                set_completed();
            }
        }
    }

protected:
    char label_;
    size_t cpu_time_;
    size_t resting_time_;
    size_t quantum_;
    size_t arrival_;
    size_t priority_;
    state state_;
};

class scheduling_algorithm
{
public:
    scheduling_algorithm(std::vector<process>& pv)
    {
        size_t cycles = 0;

        for (auto& proc : pv)
        {
            processes_.push_back(std::make_shared<process>(proc));
            cycles += proc.cpu_time();
        }

        cycles_ = cycles;

        // Ordenar los procesos por tiempo de llegada
        std::sort(processes_.begin(), processes_.end(), [](process_pointer& a, process_pointer& b) { return a->arrival() < b->arrival();});

        timeline_.resize(cycles_);

        for (auto& proc : processes_)
        {
            if (proc->arrival() < cycles_) {
                timeline_[proc->arrival()] = proc;
            }
        }

        assert(processes_[0]->arrival() == 0); 
    }

    virtual ~scheduling_algorithm() = default;

    size_t cycles() const { return cycles_;}

    using process_pointer = std::shared_ptr<process>;
    virtual std::list<char> schedule() = 0;

protected:
    size_t cycles_;
    std::vector<process_pointer> processes_; // The processes entry data table
    std::vector<process_pointer> timeline_;  // The processes timeline
};

class FCFS : public scheduling_algorithm
{
public:
    FCFS(std::vector<process>& pv) : scheduling_algorithm(pv) {}

    std::list<char> schedule() override
    {
        std::list<char> pl;
        std::queue<process_pointer> pq;

        for (size_t i = 0; i < cycles(); i++)
        {
            process_pointer new_p = timeline_[i];
            if (new_p)
            {
                pq.push(new_p);
            }

            if (!pq.empty())
            {
                process_pointer p = pq.front();

                if (p->is_completed())
                {
                    pq.pop();
                    if (!pq.empty())
                        p = pq.front();
                }

                p->execute();           
                pl.push_back(p->label());
            }
            else
            {
                pl.push_back('-');
            }
        }

        return pl;
    }
};


class RR : public scheduling_algorithm
{
public:
    RR(std::vector<process>& pv, size_t quantum) : scheduling_algorithm(pv) {quantum_ = quantum;} 
    size_t quantum() const { return quantum_; }

    std::list<char> schedule() override
    {
        std::list<char> pl;
        std::queue<process_pointer> pq;
        std::unordered_map<char,size_t> quantums;

        for (size_t i = 0; i < cycles(); i++)
        {
            process_pointer new_p = timeline_[i];
            if (new_p)
            {
                pq.push(new_p);
                quantums.insert({new_p->label(),quantum()});
            }

            if (!pq.empty())
            {
                process_pointer p = pq.front();
                size_t curr_q = quantums.at(p->label());

                if (p->is_completed())
                {
                    pq.pop();
                    if (!pq.empty())
                        p = pq.front();
                }
                else if (!curr_q)
                {
                    quantums.at(p->label()) = quantum();
                    pq.push(p);
                    pq.pop();
                    if (!pq.empty())                    
                        p = pq.front();
                }
                
                p->execute();
                --quantums.at(p->label());           
                pl.push_back(p->label());
            }
            else
            {
                pl.push_back('-');
            }
        }
        
        return pl;
    }


protected:
size_t quantum_;
};


class SPN : public scheduling_algorithm
{
public:
    SPN(std::vector<process>& pv) : scheduling_algorithm(pv) { }

    std::list<char> schedule() override
    {
        struct spn_comp
        {
            bool operator () (const process_pointer &a, const process_pointer &b) const 
            { 
                return a->cpu_time() > b->cpu_time(); 
            }
        };

        std::list<char> pl;
        std::priority_queue<process_pointer, std::vector<process_pointer>, spn_comp> pq;
        process_pointer curr_p = nullptr;

        for (size_t i = 0; i < cycles(); i++)
        {
            process_pointer new_p = timeline_[i];
            if (new_p)
            {
                pq.push(new_p);
            }

            if (!pq.empty() || curr_p)
            {
                if (!curr_p)
                {
                    curr_p = pq.top();
                    pq.pop();
                }

                curr_p->execute();
                pl.push_back(curr_p->label());

                if (curr_p->is_completed())
                {
                    curr_p = nullptr;
                }
            }
            else
            {
                pl.push_back('-');
            }
        }

        return pl;
        
    }
};


class SRT : public scheduling_algorithm
{
public:
    SRT(std::vector<process>& pv) : scheduling_algorithm(pv) { }

    std::list<char> schedule() override
    {
        struct srt_comp
        {
            bool operator () (const process_pointer &a, const process_pointer &b) const 
            { 
                return a->resting_time() > b->resting_time(); 
            }
        };

        std::list<char> pl;
        std::priority_queue<process_pointer, std::vector<process_pointer>, srt_comp> pq;

        for (size_t i = 0; i < cycles(); i++)
        {
            process_pointer new_p = timeline_[i];
            if (new_p)
            {
                pq.push(new_p);
            }

            if (!pq.empty())
            {
                process_pointer p = pq.top();

                if (p->is_completed())
                {
                    pq.pop();
                    if (!pq.empty())
                        p = pq.top();
                }

                p->execute();           
                pl.push_back(p->label());
            }
            else
            {
                pl.push_back('-');
            }
        }

        return pl;
    }


};


class MLPQ : public scheduling_algorithm
{
public:

    MLPQ(std::vector<process>& pv, size_t quantum) : scheduling_algorithm(pv) { quantum_ = quantum;}

    size_t quantum() const { return quantum_; }

    std::list<char> schedule() override
    {
        struct priority_comp
        {
            bool operator () (const process_pointer &a, const process_pointer &b) const 
            { 
                return a->priority() > b->priority(); 
            }
        };

        std::list<char> pl;
        std::priority_queue<process_pointer, std::vector<process_pointer>, priority_comp> pq;
        std::unordered_map<char,size_t> quantums;
        process_pointer curr_p = nullptr;

        for (size_t i = 0; i < cycles(); i++)
        {
            process_pointer new_p = timeline_[i];
            if (new_p)
            {
                pq.push(new_p);
                quantums.insert({new_p->label(),quantum()});
            }

            if (!pq.empty() || curr_p)
            {
                if (!curr_p)
                {
                    curr_p = pq.top();
                    pq.pop();
                }

                curr_p->execute();
                pl.push_back(curr_p->label());
                --quantums.at(curr_p->label());

                if (curr_p->is_completed())
                {
                    curr_p = nullptr;
                }
                else if (!quantums.at(curr_p->label()))
                {
                    pq.push(curr_p);
                    quantums.at(curr_p->label()) = quantum();
                    curr_p = nullptr;
                }                
            }
            else
            {
                pl.push_back('-');
            }
        }

        return pl;
    }
protected:
size_t quantum_;
};

class FBMLPQ : public scheduling_algorithm
{
public:
    FBMLPQ(std::vector<process>& pv, size_t quantum, size_t number_of_queues) : scheduling_algorithm(pv) 
    {
        quantum_ = std::make_shared<size_t>(quantum);
        func_ = nullptr;
        queues_ = number_of_queues;
    }

    FBMLPQ(std::vector<process>& pv, std::function<size_t(process)> func, size_t number_of_queues) : scheduling_algorithm(pv) 
    {
        quantum_ = nullptr;
        func_ = std::make_shared<std::function<size_t(process)>>(func);
        queues_ = number_of_queues;
    }

    size_t number_of_queues() const { return queues_; }

    std::list<char> schedule() override
    {
        std::function<size_t(process)> f;
        if (quantum_)
        {
            size_t q = quantum_.get()[0];
            f = [](process p){return 1;};
        }
        else
        {
            f = *func_;
        }


        struct priority_comp
        {
            bool operator () (const process_pointer &a, const process_pointer &b) const 
            { 
                return a->priority() >= b->priority(); 
            }
        };

        std::list<char> pl;
        std::priority_queue<process_pointer, std::vector<process_pointer>, priority_comp> pq;
        std::unordered_map<char,size_t> quantums;
        process_pointer curr_p = nullptr;

        for (size_t i = 0; i < cycles(); i++)
        {
            process_pointer new_p = timeline_[i];
            if (new_p)
            {
                pq.push(new_p);
                size_t q = f(*new_p);
                quantums.insert({new_p->label(),q});
            }

            if (!pq.empty() || curr_p)
            {
                if (!curr_p)
                {
                    curr_p = pq.top();
                    pq.pop();
                }

                curr_p->execute();
                pl.push_back(curr_p->label());
                --quantums.at(curr_p->label());

                if (curr_p->is_completed())
                {
                    curr_p = nullptr;
                }
                else if (quantums.at(curr_p->label()) == 0)
                {
                    pq.push(curr_p);
                    if (curr_p->priority() < number_of_queues())
                        curr_p->update_priority();
                    
                    quantums.at(curr_p->label()) = f(*curr_p);
                    curr_p = nullptr;
                }                
            }
            else
            {
                pl.push_back('-');
            }
        }

        return pl;
        

    }

protected:
std::shared_ptr<size_t> quantum_;
std::shared_ptr<std::function<size_t(process)>> func_;
size_t queues_;
};

#endif // PLANIFICATOR_HPP
