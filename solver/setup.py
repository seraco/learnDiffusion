from distutils.core import setup, Extension

MOD = "diffusion"

setup(
    name = MOD,
    ext_modules = [
        Extension(
            MOD,
            sources=['diffusion_py.c', 'diffusion.c'],
            libraries=['png']
        )
    ],
    description = "Diffusion solver"
)
