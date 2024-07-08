from mpi4py import MPI
import sys

world_comm = MPI.COMM_WORLD
world_size = world_comm.Get_size()
my_rank = world_comm.Get_rank()

arguments = sys.argv
n, m = 0, 0
matrix = []
row_list = []
elapsed_time = 0

if my_rank == 0:
    t1 = MPI.Wtime()
    print(f'Original Matrix')
    with open(str(arguments[1]), "r") as input_file:
        for line in input_file:
            print(line)
            data = []
            for element in line.strip().split():
                if element.replace(",", "").isnumeric() and n != 0 and m != 0:
                    data.append(int(element.replace(",", "")))
                else:
                    if n == 0:
                        n = int(element)
                    elif m == 0:
                        m = int(element)
            if data:
                row_list.append(data)
    t2 = MPI.Wtime()
    elapsed_time += t2 - t1
    world_comm.Barrier()

else:
    world_comm.Barrier()

elapsed_time = world_comm.bcast(elapsed_time, root = 0)
n = world_comm.bcast(n, root = 0)
m = world_comm.bcast(m, root = 0)
row_list = world_comm.bcast(row_list, root = 0)

if elapsed_time >= 60:
    print(f'Time is over 60 minutes')
    world_comm.Abort()

for row in row_list:
    t1 = MPI.Wtime()
    row = world_comm.scatter(row, root = 0)
    matrix.append(row)
    t2 = MPI.Wtime()
    elapsed_time += t2 - t1

elapsed_time = world_comm.bcast(elapsed_time, root = 0)
transpose_matrix = world_comm.gather(matrix, root = 0)

if elapsed_time >= 60:
    print(f'Time is over 60 minutes')
    world_comm.Abort()

if my_rank == 0:
    print(f'Transposed Matrix\n')
    for row in transpose_matrix:
        print(f'{row}\n')
