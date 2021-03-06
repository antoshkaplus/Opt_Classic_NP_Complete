# this script reads all the scores
# and prints sorted entries with corresponding
# total scores

import glob
import os
import numpy


class Solution:
    def __init__(self, name):
        self.name = name
        self.local_scores = []
        self.max_solution_iteration = 0

    def add_local_score(self, s):
        self.local_scores.append(s)

    def add_max_solution_iteration(self, s):
        self.max_solution_iteration = max(self.max_solution_iteration, s)

    def init_global(self, best_scores):

        self.global_score = numpy.sum(numpy.subtract(self.local_scores, best_scores))

        # try to normilize by substracting average scores and then divide
        #self.global_score = int(10**6 * numpy.mean(numpy.divide(best_scores, self.local_scores)))


solutions = []
filenames = glob.glob("../scores/*")
for f_name in filenames:
    with open(f_name) as f:
        base = os.path.basename(f_name)
        sol = Solution(base)
        f.readline()
        for line in f:
            items = line.split(" ")
            score, max_solution_iteration = map(int, [items[2], items[3]])
            sol.add_local_score(score)
            sol.add_max_solution_iteration(max_solution_iteration)
        solutions.append(sol)

best_scores = map(min, zip(*[s.local_scores for s in solutions]))
map(lambda x: x.init_global(best_scores), solutions)
solutions.sort(key=lambda x: -x.global_score, reverse=True)

for s in solutions:
    print s.name, ":", s.global_score, " max sol iter:", s.max_solution_iteration