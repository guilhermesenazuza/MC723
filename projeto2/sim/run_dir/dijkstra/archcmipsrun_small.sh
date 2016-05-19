#!/bin/sh

LD_LIBRARY_PATH=/home/ec2014/ra033324/y4k/classes/mc723a/projeto2/MC723/projeto2/sim/systemc/lib-linux64/:$LD_LIBRARY_PATH

DIJKSTRADIR=/home/ec2014/ra033324/y4k/classes/mc723a/projeto2/MC723/projeto2/sim/run_dir/dijkstra/
MIPSX=/home/ec2014/ra033324/y4k/classes/mc723a/projeto2/MC723/projeto2/sim/src/mips-1.0.2/mips.x

$MIPSX --load=${DIJKSTRADIR}/dijkstra_small.mips ${DIJKSTRADIR}/input.dat > ${DIJKSTRADIR}/output_small.dat 2>${DIJKSTRADIR}/mips_stderr.output

ls -lhat $DIJKSTRADIR

cat ${DIJKSTRADIR}/mips_stderr.output
