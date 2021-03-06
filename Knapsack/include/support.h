#pragma once

#include <vector>
#include <iostream>
#include <algorithm>

#include <ant/grid/grid.hpp>

using namespace std;

struct Item {
    int w {};
    int v {};
};

struct Problem {
    int capacity;
    vector<Item> items;
};

Problem ReadProblem(std::ifstream& in) {
    int itemCount;
    int capacity;
    in >> itemCount >> capacity;
    std::vector<Item> items(itemCount);
    for (auto& item : items) {
        in >> item.v >> item.w;
    }
    return {capacity, items};
}

int Value(Problem& pr, const vector<int> selection) {
    auto v = 0;
    auto capacity = pr.capacity;
    for (auto i = 0; i < pr.items.size(); ++i) {
        if (selection[i]) {
            v += pr.items[i].v;
            capacity -= pr.items[i].w;
        }
    }
    if (capacity < 0) throw std::runtime_error("solution not valid");
    return v;
}

// considered that each item can be used only once
pair<int, vector<int>> usual(const vector<Item>& items, int capacity) {
    int itemCount = items.size();

    vector<int> res(itemCount);
    vector<int> buffer((capacity + 1) * (itemCount + 1));

    // column 0 : 0 items
    for (int i = 0; i < capacity + 1; i++) {
        buffer[i * (itemCount + 1)] = 0;
    }
    // row 0 : 0 capacity
    for (int i = 0; i < itemCount + 1; i++) {
        buffer[i] = 0;
    }
    // loop by items
    for (int i = 1; i < itemCount + 1; i++) {
        const Item& t = items[i-1];
        // loop by capacity
        for (int j = 0; j < min(t.w, capacity + 1); j++) {
            buffer[j * (itemCount + 1) + i] = buffer[j * (itemCount + 1) + i - 1];
        }
        for (int j = t.w; j < capacity + 1; j++) {
            buffer[j * (itemCount + 1) + i] = max(buffer[j * (itemCount + 1) + i - 1],
                                                  buffer[(j - t.w) * (itemCount + 1) + i - 1] + t.v);
        }
    }

    int w = capacity;
    for (int i = itemCount; i > 0; i--) {
        if (buffer[w * (itemCount + 1) + i] == buffer[w * (itemCount + 1) + i - 1]) {
            res[i-1] = 0;
        } else {
            res[i-1] = 1;
            w -= items[i-1].w;
        }
    }

    return pair<int, vector<int>>(buffer[(capacity + 1) * (itemCount + 1) - 1], res);
}

vector<int> effectiveness(const vector<Item>& items) {
    auto val = [&](int i) {
        return 1. * items[i].v / items[i].w;
    };
    vector<int> indices(items.size());
    std::iota(indices.begin(), indices.end(), 0);
    std::sort(indices.begin(), indices.end(), [&](int i1, int i2) { return val(i1) > val(i2); });
    return indices;
}

// considered that each item can be used only once
pair<int, vector<int>> greedy(const vector<Item>& items, int capacity) {
    vector<int> res(items.size());
    int n = (int) items.size();

    vector<int> indices = effectiveness(items);

    int v = 0, i = 0, k = capacity;
    while ((k = k - items[indices[i]].w) >= 0 && i < n) {
        res[indices[i]] = 1;
        v += items[indices[i++]].v;
    }
    return pair<int, vector<int>>(v, res);
}

double relaxation(const vector<Item>& items, int capacity) {
    vector<int> indices = effectiveness(items);

    double k = capacity;
    double v = 0;
    for (auto i : indices) {
        double w = min<double>(k, items[i].w);
        v += w * items[i].v / items[i].w;
        k -= w;
        if (k == 0) break;
    }
    return v;
}