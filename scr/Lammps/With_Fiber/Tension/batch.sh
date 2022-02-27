#!/usr/local_rwth/bin/zsh

### Request the memory you need for your job. You can specify this
### in either MB (1024M) or GB (4G).
#SBATCH --mem-per-cpu=3900M

### Request 12 processes, all on a single node
#SBATCH --nodes=2
#SBATCH --ntasks=12

### Request the time you need for execution. The full format is D-HH:MM:SS
### You must at least specify minutes or days and hours and may add or
### leave out any other parameters
#SBATCH --time=1-24:00:00

### Load required modules
module load CHEMISTRY
module load lammps

### start the MPI binary
$MPIEXEC $FLAGS_MPI_BATCH lmp_rwth -in config_Model.in