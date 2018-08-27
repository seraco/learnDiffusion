import os
import sys

from django.shortcuts import render
from django.http import HttpResponse

sys.path.append(os.path.join(os.path.dirname( __file__ ), os.pardir, os.pardir, 'solver'))
import diffusion

def index(request):
    return HttpResponse(diffusion.solve(0.0, 0.25, 0.5, 1.0))
