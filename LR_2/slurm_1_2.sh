#!/bin/bash
#SBATCH --output=tmp.log
#SBATCH --nodes=1                      # Количество узлов (виртуальных машин)
#SBATCH --ntasks-per-node=2            # Количество процессов на каждом узле
#SBATCH -t 00:30:00                    # Максимальное время выполнения

# Запуск MPI-программы
echo -e "1x2 - $(mpiexec -np 1 ./build/LR_2 "$MATRIX_SIZE")" | tee -a ./result.log
rm tmp.log
