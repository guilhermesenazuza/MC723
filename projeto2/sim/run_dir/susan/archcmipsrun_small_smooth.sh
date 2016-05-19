#!/bin/sh

LD_LIBRARY_PATH=/home/ec2014/ra033324/y4k/classes/mc723a/projeto2/MC723/projeto2/sim/systemc/lib-linux64/:$LD_LIBRARY_PATH

SUSANDIR=/home/ec2014/ra033324/y4k/classes/mc723a/projeto2/MC723/projeto2/sim/run_dir/susan/
MIPSX=/home/ec2014/ra033324/y4k/classes/mc723a/projeto2/MC723/projeto2/sim/src/mips-1.0.2/mips.x

$MIPSX --load=${SUSANDIR}/susan.mips ${SUSANDIR}/input_small.pgm ${SUSANDIR}/output_small.smoothing.pgm -s 2>${SUSANDIR}/mips_stderr.output

ls -lhat $SUSANDIR

cat ${SUSANDIR}/mips_stderr.output
