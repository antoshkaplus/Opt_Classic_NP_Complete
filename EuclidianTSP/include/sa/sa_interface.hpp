#pragma once

struct SA_Interface {
    virtual vector<City> Solve() = 0;
    virtual vector<City> SolveKeepHistory(Count history_item_count) = 0;
    virtual const ant::opt::sa::History& history() const = 0;
    virtual bool time_limit_reached() const = 0;
    virtual Duration time_spent() const = 0;

    virtual ~SA_Interface() {}
};