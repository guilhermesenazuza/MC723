#!/bin/sh

LD_LIBRARY_PATH=/home/ec2014/ra033324/y4k/classes/mc723a/projeto2/MC723/projeto2/sim/systemc/lib-linux64/:$LD_LIBRARY_PATH

QSORTDIR=/home/ec2014/ra033324/y4k/classes/mc723a/projeto2/MC723/projeto2/sim/run_dir/qsort/
MIPSX=/home/ec2014/ra033324/y4k/classes/mc723a/projeto2/MC723/projeto2/sim/src/mips-1.0.2/mips.x

$MIPSX --load=${QSORTDIR}/qsort_small.mips ${QSORTDIR}/input_small.dat > ${QSORTDIR}/output_small.txt 2>${QSORTDIR}/mips_stderr.output

ls -lhat $QSORTDIR

cat ${QSORTDIR}/mips_stderr.output
