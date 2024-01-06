#!/bin/bash

for k in 1 2; do
	for i in 1 2; do
		echo "Число узлов - $k.     Число процессов на узле - $i"
		for j in 32 64 128 256 512 1024 2048 4096; do
			sbatch --export=MATRIX_SIZE=$j slurm_"$k"_"$i".sh
		done
	done
done
