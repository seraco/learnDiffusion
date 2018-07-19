import multiprocessing as mp

from generate_train import gen_train


# print mp.cpu_count()
pool = mp.Pool(processes=4)

pool.map(gen_train, range(1, 2))
