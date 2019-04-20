from multiprocessing import Process
import os

#os.environ["DYLD_LIBRARY_PATH"] = "/Users/whitbeck/root_build/lib"

backgroundSamples=[#"QCD_200to300",
#                   "ZJets_100to200",
#                   "ZJets_200to400",
                   "ZJets_1200to2500",
]

signalSamples=["VBFG_1000",
              ]

dataSamples=["MET_2018A",
#             "MET_2018D",
             #"MET_2017B"
             #"MET_2017C"
             #"MET_2017D",
             #"MET_2017E",
             #"MET_2017F",
             #"MET_2016G",
             #"MET_2016H"
             ]

def runPlotObsBaseline(sel,bkg,sig,data):
    print '../bin/plotObs_baseline "{0}" "{1}" "{2}" "{3}"'.format(sel,bkg,sig,data)
    os.system('../bin/plotObs_baseline "{0}" "{1}" "{2}" "{3}"'.format(sel,bkg,sig,data))

processes=[]
for sample in backgroundSamples : 
    p = Process(target=runPlotObsBaseline, args=("ZSBNoVBF",sample,"","") )
    #p = Process(target=runPlotObsBaseline, args=("ZNoSelection",sample,"","") )
    #p = Process(target=runPlotObsBaseline, args=("ZSBHPVBF",sample,"","") )
    p.start()
    processes.append(p)

for sample in signalSamples : 
    p = Process(target=runPlotObsBaseline, args=("ZSBNoVBF",sample,"","") )
    #p = Process(target=runPlotObsBaseline, args=("ZSBHPVBF","",sample, "") )
    p.start()
    processes.append(p)

for sample in dataSamples : 
    #p = Process(target=runPlotObsBaseline, args=("ZSBHPVBF","","", sample) )
    p = Process(target=runPlotObsBaseline, args=("ZSBNoVBF",sample,"","") )
    p.start()
    processes.append(p)

for p in processes : 
    p.join()

#os.system("hadd -f plotObs_photon_baseline.root plotObs_photon_baseline_*.root")
#os.system("rm plotObs_photon_baseline_*.root")
2    
    


