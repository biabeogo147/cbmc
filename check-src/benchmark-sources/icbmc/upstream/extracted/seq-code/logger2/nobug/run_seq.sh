#!/bin/bash

toolPath=~/seq-tools/interrupts

CBMC=~/cbmc-trunk/src/cbmc/cbmc
SATABS=~/conc-tools/satabs-3.2/satabs
UFO=$toolPath/ufo-svcomp14/bin/ufo-svcomp-par.py
UFO2=$toolPath/ufo-svcomp14/bin/ufo.py
CPA=$toolPath/CPAchecker-1.3.4-unix/scripts/cpa.sh
BLAST='ocamltune pblast.opt'

fileName='logger2_por_seq.c'
ppfileName='logger2_por_seq.i'

exptName=$1
prpFile='ALL.prp'
dataFolder='data-'$exptName
dataName=$dataFolder/'data_'$exptName
timeName=$dataFolder/'time_'$exptName

if [ -d $dataFolder ]
then
  echo "Folder " + $dataFolder+ " already exists. "
  #exit
fi

#mkdir $dataFolder

# start to rock
#(time $CPA -preprocess -sv-comp14 -disable-java-assertions -heap 10000m -spec $prpFile $fileName &> $dataName'_cpa.txt') &>> $timeName'_cpa.txt'
#
#(time $BLAST -alias empty -enable-recursion -noprofile -cref -sv-comp -lattice -include-lattice symb -nosserr -errorpathfile $dataFolder/blast.error -propertyfile $prpFile $ppfileName &> $dataName'_blast.txt') &>> $timeName'_blast.txt'
#
#(time $UFO2 $fileName &> $dataName'_ufo2.txt') &>> $timeName'_ufo2.txt' 
#
#(time $UFO -m64 --cex=$dataFolder'/ufo.trace' --spec=$prpFile $fileName &> $dataName'_ufo.txt') &>> $timeName'_ufo.txt' 
#
#(time $SATABS --error-label ERROR $fileName &> $dataName'_satabs.txt') &>> $timeName'_satabs.txt'
#
(time $CBMC --unwind 4 --error-label ERROR $fileName &> $dataName'_cbmc.txt') &>> $timeName'_cbmc.txt'
