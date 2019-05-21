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
case $sampleName in
    *MET_2016*)
	echo "Processing it as data (2016, I don't care which year)"
	../bin/$anaExe "${selectionType}" "" "" "${sampleName}"
	;;
    *MET_2017*)
	echo "Processing it as data (2017, I don't care which year)"
	../bin/$anaExe "${selectionType}" "" "" "${sampleName}"
	;;
    *MET_2018*)
	echo "Processing it as data (2018, I don't care which year)"
	../bin/$anaExe "${selectionType}" "" "" "${sampleName}"
	;;
    *VBFG_*)
	echo "Processing it as signal sample"
	../bin/$anaExe "${selectionType}" "" "${sampleName}" ""
	;;
    *)
	echo "Processing it as MC"
	../bin/$anaExe "${selectionType}" "${sampleName}" "" ""
	;;
esac

mv *.root $currDir/

echo "Done....... EXITing"