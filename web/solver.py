import os, sys, io
import numpy as np
from matplotlib.backends.backend_agg import FigureCanvasAgg as FigureCanvas
from matplotlib.figure import Figure

from vtk import vtkStructuredGridReader
from vtk.util import numpy_support as VN

sys.path.append(os.path.join(os.path.dirname( __file__ ), os.pardir, 'solver'))
import diffusion

def solve():
    print(diffusion.solve(0.0, 0.25, 0.5, 1.0))
    reader = vtkStructuredGridReader()
    reader.SetFileName('../sol/solution0.vtk')
    reader.ReadAllVectorsOn()
    reader.ReadAllScalarsOn()
    reader.Update()

    data = reader.GetOutput()

    dim = data.GetDimensions()
    vec = list(dim)
    vec = [i-1 for i in dim]
    vec.append(3)

    x = np.zeros(data.GetNumberOfPoints())
    y = np.zeros(data.GetNumberOfPoints())
    z = np.zeros(data.GetNumberOfPoints())
    c = data.GetPointData().GetArray('Val')

    for i in range(data.GetNumberOfPoints()):
            x[i], y[i], z[i] = data.GetPoint(i)

    x = x.reshape(dim[0:2], order='F')
    y = y.reshape(dim[0:2], order='F')
    z = z.reshape(dim[0:2], order='F')
    c = VN.vtk_to_numpy(data.GetPointData().GetArray('Val'))
    c = c.reshape(dim[0:2], order='F')

    fig = Figure()
    axis = fig.add_subplot(111)

    # TODO: Set equal aspect ratio axes
    # axis.set_aspect('equal')
    axis.contourf(x, y, c)
    canvas = FigureCanvas(fig)
    output = io.BytesIO()
    canvas.print_png(output)
    fig.savefig('./static/img/img.png')
    return output

def force_aspect(ax,aspect=1):
    im = ax.get_images()
    extent =  im[0].get_extent()
    ax.set_aspect(abs((extent[1]-extent[0])/(extent[3]-extent[2]))/aspect)
