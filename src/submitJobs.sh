#!/bin/sh
input_Scan=$1
anaExe=$2
selectionType=$3
exeAtWorker="worker.sh"
filesToTransfer="tarballCondor.tar"

#rm tarballCondor.tar
cd $CMSSW_BASE/src/
tar -cf tarballCondor.tar * --exclude='*.tar' --exclude='*.eps' --exclude='*.png' --exclude='*.pdf' --exclude='*.stdout' --exclude='*.stderr' --exclude='plot*.root' --exclude='*.condor' --exclude='*/.git'
cd -
mv $CMSSW_BASE/src/tarballCondor.tar .
echo "Done making tar"
grep -v '^#' $input_Scan | while read -a massP
do
    echo "Making jdl file for " ${massP[0]}
    jdl_file="condor_${selectionType}_${input_Scan}_${massP[0]}_job.jdl"
    log_prefix="condor_${selectionType}_${input_Scan}_${massP[0]}_job"
    echo "universe = vanilla">$jdl_file
    echo "Executable = $exeAtWorker">>$jdl_file
    echo "Should_Transfer_Files = YES">>$jdl_file
    echo "WhenToTransferOutput = ON_EXIT_OR_EVICT">>$jdl_file
    echo "Transfer_Input_Files = ${filesToTransfer}">>$jdl_file
    echo "Output = ${log_prefix}.stdout">>$jdl_file
    echo "Error = ${log_prefix}.stderr">>$jdl_file
    echo "Log = ${log_prefix}.condor">>$jdl_file
    echo "notification = never">>$jdl_file
    echo "Arguments = ${anaExe} ${selectionType} ${massP[0]}">>$jdl_file
    echo "Queue">>$jdl_file
    condor_submit $jdl_file
done
