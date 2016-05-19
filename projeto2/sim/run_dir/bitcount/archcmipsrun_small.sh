#!/bin/sh

LD_LIBRARY_PATH=/home/ec2014/ra033324/y4k/classes/mc723a/projeto2/MC723/projeto2/sim/systemc/lib-linux64/:$LD_LIBRARY_PATH

BITCOUNTDIR=/home/ec2014/ra033324/y4k/classes/mc723a/projeto2/MC723/projeto2/sim/run_dir/bitcount/
MIPSX=/home/ec2014/ra033324/y4k/classes/mc723a/projeto2/MC723/projeto2/sim/src/mips-1.0.2/mips.x

$MIPSX --load=${BITCOUNTDIR}/bitcnts.mips 75000 > ${BITCOUNTDIR}/output_small.txt 2>${BITCOUNTDIR}/mips_stderr.output

ls -lhat $BITCOUNTDIR

cat ${BITCOUNTDIR}/mips_stderr.output
