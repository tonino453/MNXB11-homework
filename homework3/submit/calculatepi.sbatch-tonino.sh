#!/bin/bash

# Job name shown in squeue
#SBATCH -J "MNXB11 Pi tonino"
# Project account to charge
#SBATCH -A hep2023-1-6
# Partition (group of nodes) to run on
#SBATCH -p hep
# Run on one node, as one task, using one CPU core
#SBATCH -N 1
#SBATCH -n 1
#SBATCH --cpus-per-task=1
# Wall time limit: profiled 7:09 on the frontend, plus ~25% margin
#SBATCH --time=00:09:00
# Memory limit: profiled max RSS ~25.3 GB, plus ~10% margin
#SBATCH --mem=28G
# Output and error files, %j is replaced by the job ID
#SBATCH -o calculatePI_%j.out
#SBATCH -e calculatePI_%j.err

# Launch the calculatePI application inside the container
./run_in_container_calculatePI.sh
