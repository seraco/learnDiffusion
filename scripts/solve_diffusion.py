#!/usr/bin/env python

import sys
import os
import random

sys.path.append(os.path.join(os.path.dirname( __file__ ), os.pardir, 'solver'))
import diffusion

def solve():
    diffusion.solve(0.0, random.random(), random.random(), 1.0)
