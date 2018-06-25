#!/usr/bin/env python

from setTrainProblems import setTP
from solveTrainProblems import solveTP
from plotResidualsTrainProblems import plotResidualsTP

N = 10

setTP(N)
solveTP(N)
plotResidualsTP(N)
