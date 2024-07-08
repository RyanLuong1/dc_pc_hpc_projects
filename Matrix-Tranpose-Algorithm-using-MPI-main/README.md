# 474-Project2
Project 2: Implement a distributed algorithm using MPI (Matrix Transpose)

Group members: Ryan Luong and Anthony Sanchez

Anthony Sanchez sanchezanthony244@csu.fullerton.edu

Ryan Luong ryan12@csu.fullerton.edu

# Description of Project
We chose the matrix transpose algorithm. A matrix is transposing means if we take a n x m matrix and invert it, then the result will be a m x n matrix. MPI_Broadcast and MPI_Gather will help achieve this.

The language we used was python.

The commands to run it

mpirun --oversubscribe -n 11 pyython3 main.py input1.txt

mpirun --oversubscribe -n 12 pyython3 main.py input2.txt

Install mpi4py

pip3 install mpi4py



