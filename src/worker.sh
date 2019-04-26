#!/bin/sh
anaExe=$1
selectionType=$2
sampleName=$3
currDir=$(pwd)

echo "Statring to setup CMSSW on worker node......"

source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc6_amd64_gcc630
scram p CMSSW CMSSW_10_1_7
cd CMSSW_10_1_7/src/
eval `scramv1 runtime -sh`
pwd
echo "Done setup CMSSW on worker node..... pwd and ls?"
ls

mv $currDir/tarballCondor.tar .
tar xf tarballCondor.tar
cd boostedHiggsPlusMET
#source setup.sh
cd src/
make $anaExe
echo "Running analysis"
../bin/$anaExe "${selectionType}" "${sampleName}" "" ""

mv *.root $currDir/

echo "Done....... EXITing"