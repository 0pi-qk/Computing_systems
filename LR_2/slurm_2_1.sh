#!/bin/bash
#SBATCH --output=tmp.log
#SBATCH --nodes=2                      # Количество узлов (виртуальных машин)
#SBATCH --ntasks-per-node=1            # Количество процессов на каждом узле
#SBATCH -t 00:30:00                    # Максимальное время выполнения

# Запуск MPI-программы
echo -e "2x1 - $(mpiexec -np 2 ./build/LR_2 "$MATRIX_SIZE")" | tee -a ./result.log
rm tmp.log
