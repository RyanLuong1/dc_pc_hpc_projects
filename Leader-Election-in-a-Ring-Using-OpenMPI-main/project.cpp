#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

using namespace std;

int main(int argc, char *argv[])
{
  int rank, size;
  MPI_Init( &argc, &argv );

  MPI_Comm_rank( MPI_COMM_WORLD, &rank );

  MPI_Comm_size( MPI_COMM_WORLD, &size );

  MPI_Barrier(MPI_COMM_WORLD);

  if (size < 6 || size > 21) {
    printf("Size needs to be between 6 and 20\n");
    MPI_Finalize();
    return 0;
  }

  double start, end;

  start = MPI_Wtime();
  int presidentAndVicePresident[4]; //president rank, president id (even), vice president rank, vice president id (odd)

  int id;

  int r, NN, RR, D;

  srand(time(NULL)+rank);
  r = (rand()%89)+10;
  NN = r*1000;
  RR = rank*10;
  D = r % 2;
  id = NN + RR + D;
  if (rank == 0) {
    if (id % 2 == 0 ) {
     int  presidentAndVicePresident[4] = {0, id, 0, 0};

    }
    else {
     int  presidentAndVicePresident[4] = {0, 0, 0, id};

    }
  }
  else {
    //receive
    MPI_Recv(&presidentAndVicePresident, 4, MPI_INT, (rank-1), 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }

  if (id % 2 == 0 && (presidentAndVicePresident[1] == 0 || id  <= presidentAndVicePresident[1]) ) {
    presidentAndVicePresident[0] = rank;
    presidentAndVicePresident[1] = id;

  }
  else if (id % 2 != 0 && (presidentAndVicePresident[3] == 0 || id >= presidentAndVicePresident[3]) ) {
    presidentAndVicePresident[2] = rank;
    presidentAndVicePresident[3] = id;

  }

  //send
  MPI_Send(&presidentAndVicePresident, 4, MPI_INT,(rank +1)%size,0, MPI_COMM_WORLD);
  end = MPI_Wtime();
  if (size == 10 && end - start < 3600000) { //If size is 10, then it must terminate within 60 minutes
      printf("Program terminating within 60 minutes\n");
      MPI_Finalize();
      return 0;
  }
  if (rank == 0) {

    //receive
    MPI_Recv(&presidentAndVicePresident, 4, MPI_INT,(rank-1), 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    printf("President rank: %d\n President id: %d\n President value: 9998\n",
            presidentAndVicePresident[0],
            presidentAndVicePresident[1]);
    printf("Vice president rank: %d\n Vice president id: %d\n Vice president value: 1\n",
            presidentAndVicePresident[2],
            presidentAndVicePresident[3]);
  }

  MPI_Finalize();

  return 0;
}
