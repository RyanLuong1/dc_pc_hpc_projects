# cpsc479-project-2
Parallel Quicksort

For this project, we used C++ and OpenMP to parallelize the quicksort algorithm. In quicksort, an element is picked as a pivot and the array is partitioned around the pivot. So, the other elements are either larger or smaller than the pivot. Quicksort is recursive so the process is repeated on the partitions until it reaches the desired output. We used the OpenMP commands pragma omp parallel sections and pragma omp section to parallelize the algorithm. This report includes the pseudo code of the algorithm implemented for the project and two examples of the output. 


Group members:

Christian Josef Teodoro christianjte@csu.fullerton.edu
Jerry Gama jerry.gama@csu.fullerton.edu
Ryan Luong ryan12@csu.fullerton.edu
