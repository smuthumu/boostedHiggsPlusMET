#include "TChain.h"
#include "RA2bTree.cc"
#include "TString.h"

#include <iostream>
#include <vector>
#include <map>

static const TString BASE_DIR_DATA = "root://cmseos.fnal.gov//store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV17/";
static const TString BASE_DIR = "root://cmseos.fnal.gov//store/user/lpcsusyhad/SusyRA2Analysis2015/Run2ProductionV16/";
static const TString BASE_DIR_SIG = "root://cmseos.fnal.gov//store/user/lpcsusyhad/SusyRA2Analysis2015/Run2ProductionV16/VBF_G_V2/";
static const bool RE_MINIAOD = false;

class skimSamples{

public :

    enum region {kSignal,kLDP,kPhoton,kPhotonLoose,kPhotonLDP,kPhotonLDPLoose,kDYe,kDYm,kDYeLDP,kDYmLDP,kNumRegions};
    TString regionNames[kNumRegions]={"signal","LDP","photon","photonLoose","photonLDP","photonLDPLoose","DYe","DYm","DYeLDP","DYmLDP"};  
  
    map<TString,TString> fileNames;

    std::vector<RA2bTree*> ntuples,signalNtuples;
    std::vector<RA2bTree*> dataNtuple;
    std::vector<TString> sampleName, signalSampleName;
    std::vector<TString> dataSampleName;

    TString skimType;
   
    skimSamples(region r, vector<TString> backgrounds, vector<TString> signals, vector<TString> datas){

        skimType="";
        if( r == kSignal )
            skimType="tree_signal/";
        if( r == kLDP )
            skimType="tree_LDP/";
        if( r == kPhoton )
            skimType="tree_GJet_CleanVars/";
	if( r == kPhotonLDP )
            skimType="tree_GJetLDP_CleanVars/";
        if( r == kPhotonLoose )
            skimType="tree_GJetLoose_CleanVars/";
        if( r == kPhotonLDPLoose )
            skimType="tree_GJetLooseLDP_CleanVars/";
        if( r == kDYm )
            skimType="tree_DYm_CleanVars";
        if( r == kDYmLDP )
            skimType="tree_DYmLDP_CleanVars";
        if( r == kDYe )
            skimType="tree_DYe_CleanVars";
        if( r == kDYeLDP )
            skimType="tree_DYeLDP_CleanVars";

        ///////////////////////////////////////////////////////////////////////
        // - - - - - - - - - - BACKGROUND INPUTS - - - - - - - - - - - - - - //
        ///////////////////////////////////////////////////////////////////////
/*
        fileNames["ZJets_100to200"]   = "tree_ZJetsToNuNu_HT-100to200_MC2017.root";
        fileNames["ZJets_200to400"]   = "tree_ZJetsToNuNu_HT-200to400_MC2017.root";
        fileNames["ZJets_400to600"]   = "tree_ZJetsToNuNu_HT-400to600_MC2017.root";
        fileNames["ZJets_600to800"]   = "tree_ZJetsToNuNu_HT-600to800_MC2017.root";
        fileNames["ZJets_800to1200"]  = "tree_ZJetsToNuNu_HT-800to1200_MC2017.root";
        fileNames["ZJets_1200to2500"] = "tree_ZJetsToNuNu_HT-1200to2500_MC2017.root";
        fileNames["ZJets_2500toInf"]  = "tree_ZJetsToNuNu_HT-2500toInf_MC2017.root";
*/
        
        fileNames["ZJets_100to200"]   = "tree_ZJetsToNuNu_HT-100to200_MC2018.root";
        fileNames["ZJets_200to400"]   = "tree_ZJetsToNuNu_HT-200to400_MC2018.root";
        fileNames["ZJets_400to600"]   = "tree_ZJetsToNuNu_HT-400to600_MC2018.root";
        fileNames["ZJets_600to800"]   = "tree_ZJetsToNuNu_HT-600to800_MC2018.root";
        fileNames["ZJets_800to1200"]  = "tree_ZJetsToNuNu_HT-800to1200_MC2018.root";
        fileNames["ZJets_1200to2500"] = "tree_ZJetsToNuNu_HT-1200to2500_MC2018.root";
        fileNames["ZJets_2500toInf"]  = "tree_ZJetsToNuNu_HT-2500toInf_MC2018.root";

/*
        fileNames["WJets_100to200"]   = "tree_WJetsToLNu_HT-100to200_MC2017.root";
        fileNames["WJets_200to400"]   = "tree_WJetsToLNu_HT-200to400_MC2017.root";
        fileNames["WJets_400to600"]   = "tree_WJetsToLNu_HT-400to600_MC2017.root";
        fileNames["WJets_600to800"]   = "tree_WJetsToLNu_HT-600to800_MC2017.root";
        fileNames["WJets_800to1200"]  = "tree_WJetsToLNu_HT-800to1200_MC2017.root";
        fileNames["WJets_1200to2500"] = "tree_WJetsToLNu_HT-1200to2500_MC2017.root";
        fileNames["WJets_2500toInf"]  = "tree_WJetsToLNu_HT-2500toInf_MC2017.root";
*/

        fileNames["WJets_100to200"]   = "tree_WJetsToLNu_HT-100to200_MC2018.root";
        fileNames["WJets_200to400"]   = "tree_WJetsToLNu_HT-200to400_MC2018.root";
        fileNames["WJets_400to600"]   = "tree_WJetsToLNu_HT-400to600_MC2018.root";
        fileNames["WJets_600to800"]   = "tree_WJetsToLNu_HT-600to800_MC2018.root";
        fileNames["WJets_800to1200"]  = "tree_WJetsToLNu_HT-800to1200_MC2018.root";
        fileNames["WJets_1200to2500"] = "tree_WJetsToLNu_HT-1200to2500_MC2018.root";
        fileNames["WJets_2500toInf"]  = "tree_WJetsToLNu_HT-2500toInf_MC2018.root";


        fileNames["TT_600to800"] = "tree_TTJets_HT-600to800_MC2018.root";
        fileNames["TT_800to1200"] = "tree_TTJets_HT-800to1200_MC2018.root";
        fileNames["TT_1200to2500"] = "tree_TTJets_HT-1200to2500_MC2018.root";
        fileNames["TT_2500toInf"] = "tree_TTJets_HT-2500toInf_MC2018.root";
        fileNames["TT_1LFromT"] = "tree_TTJets_SingleLeptFromT_MC2018.root";
        fileNames["TT_1LFromTbar"] = "tree_TTJets_SingleLeptFromTbar_MC2018.root";
        fileNames["TT_2L"] = "tree_TTJets_DiLept_MC2018.root";
/*
        fileNames["TT_600to800"] = "tree_TTJets_HT-600to800_MC2017.root";
        fileNames["TT_800to1200"] = "tree_TTJets_HT-800to1200_MC2017.root";
        fileNames["TT_1200to2500"] = "tree_TTJets_HT-1200to2500_MC2017.root";
        fileNames["TT_2500toInf"] = "tree_TTJets_HT-2500toInf_MC2017.root";
        fileNames["TT_1LFromT"] = "tree_TTJets_SingleLeptFromT_MC2017.root";
        fileNames["TT_1LFromTbar"] = "tree_TTJets_SingleLeptFromTbar_MC2017.root";
        fileNames["TT_2L"] = "tree_TTJets_DiLept_MC2017.root";

	    fileNames["ST_s-channel"] = "tree_ST_s-channel_MC2017.root";
	    fileNames["ST_t-channel_antitop"] = "tree_ST_t-channel_antitop_MC2017.root";
	    fileNames["ST_t-channel_top"] = "tree_ST_t-channel_top_MC2017.root";
	    fileNames["ST_tW_antitop"] = "tree_ST_tW_antitop_MC2017.root";
	    fileNames["ST_tW_top"] = "tree_ST_tW_top_MC2017.root";
*/
        
	    fileNames["ST_s-channel"] = "tree_ST_s-channel_MC2018.root";
	    fileNames["ST_tW_antitop"] = "tree_ST_tW_antitop_MC2018.root";
	    fileNames["ST_tW_top"] = "tree_ST_tW_top_MC2018.root";

        fileNames["Other_TTGJets"] = "tree_TTGJets_MC2018.root";
        fileNames["Other_TTWJetsToQQ"] = "tree_TTWJetsToQQ_MC2018.root";
        fileNames["Other_TTWJetsToLNu"] = "tree_TTWJetsToLNu_MC2018.root";
        fileNames["Other_TTZToLLNuNu"] = "tree_TTZToLLNuNu_MC2018.root";
        fileNames["Other_TTZToQQ"] = "tree_TTZToQQ_MC2018.root";
        fileNames["Other_WWTo1L1Nu2Q"] = "tree_WWTo1L1Nu2Q_MC2018.root";
        fileNames["Other_WZTo1L3Nu"] = "tree_WZTo1L3Nu_MC2018.root";
        fileNames["Other_ZZTo2L2Q"] = "tree_ZZTo2L2Q_MC2018.root";

/*
        fileNames["Other_WWTo1L1Nu2Q"] = "tree_WWTo1L1Nu2Q_MC2017.root";
        fileNames["Other_WWTo2L2Nu"] = "tree_WWTo2L2Nu_MC2017.root";
        fileNames["Other_WWZ"] = "tree_WWZ_MC2017.root";
        fileNames["Other_WZTo1L1Nu2Q"] = "tree_WZTo1L1Nu2Q_MC2017.root";
        fileNames["Other_WZTo1L3Nu"] = "tree_WZTo1L3Nu_MC2017.root";
        fileNames["Other_WZZ"] = "tree_WZZ_MC2017.root";
        fileNames["Other_ZZTo2L2Q"] = "tree_ZZTo2L2Q_MC2017.root";
        fileNames["Other_ZZTo2Q2Nu"] = "tree_ZZTo2Q2Nu_MC2017.root";
        fileNames["Other_ZZZ"] = "tree_ZZZ_MC2017.root";
        fileNames["Other_TTTT"] = "tree_TTTT_MC2017.root";
        fileNames["Other_TTWJetsToLNu"] = "tree_TTWJetsToLNu_MC2017.root";
        fileNames["Other_TTWJetsToQQ"] = "tree_TTWJetsToQQ_MC2017.root";
        fileNames["Other_TTGJets"] = "tree_TTGJets_MC2017.root";
        fileNames["Other_TTZToLLNuNu"] = "tree_TTZToLLNuNu_MC2017.root";
        fileNames["Other_TTZToQQ"] = "tree_TTZToQQ_MC2017.root";
      */ 
 
         // These are already in singleTop section!!!
        fileNames["MET_2016B"] = "tree_MET_2016B.root";
        fileNames["MET_2016C"] = "tree_MET_2016C.root";
        fileNames["MET_2016D"] = "tree_MET_2016D.root";
        fileNames["MET_2016E"] = "tree_MET_2016E.root";
        fileNames["MET_2016F"] = "tree_MET_2016F.root";
        fileNames["MET_2016G"] = "tree_MET_2016G.root";
        fileNames["MET_2016H"] = "tree_MET_2016H.root";

	    fileNames["MET_2017B"] = "tree_MET_2017B.root";
	    fileNames["MET_2017C"] = "tree_MET_2017C.root";
        fileNames["MET_2017D"] = "tree_MET_2017D.root";
        fileNames["MET_2017E"] = "tree_MET_2017E.root";
        fileNames["MET_2017F"] = "tree_MET_2017F.root";
        //fileNames["MET_2017G"] = "tree_MET_2017G.root"; // 2017 dataset range is [B-F]
        //fileNames["MET_2017H"] = "tree_MET_2017H.root";

	    fileNames["MET_2018A"] = "tree_MET_2018A.root";
	    fileNames["MET_2018B"] = "tree_MET_2018B.root";
	    fileNames["MET_2018C"] = "tree_MET_2018C.root";
        fileNames["MET_2018D"] = "tree_MET_2018D.root";

        fileNames["VBFG_1000"] = "tree_VBF_ZZ_mG1000.root";

        fileNames["SingleElectron_2016C"] = "tree_SingleElectron_2016C.root";
        fileNames["SingleElectron_2016D"] = "tree_SingleElectron_2016D.root";
        fileNames["SingleElectron_2016E"] = "tree_SingleElectron_2016E.root";
        fileNames["SingleElectron_2016F"] = "tree_SingleElectron_2016F.root";
        fileNames["SingleElectron_2016G"] = "tree_SingleElectron_2016G.root";
        fileNames["SingleElectron_2016H"] = "tree_SingleElectron_2016H.root";

        fileNames["SingleMuon_2016B"] = "tree_SingleMuon_2016B.root";
        fileNames["SingleMuon_2016C"] = "tree_SingleMuon_2016C.root";
        fileNames["SingleMuon_2016D"] = "tree_SingleMuon_2016D.root";
        fileNames["SingleMuon_2016E"] = "tree_SingleMuon_2016E.root";
        fileNames["SingleMuon_2016F"] = "tree_SingleMuon_2016F.root";
        fileNames["SingleMuon_2016G"] = "tree_SingleMuon_2016G.root";
        fileNames["SingleMuon_2016H"] = "tree_SingleMuon_2016H.root";

 	    fileNames["SinglePhoton_2016B"] = "tree_SinglePhoton_2016B.root";
 	    fileNames["SinglePhoton_2016C"] = "tree_SinglePhoton_2016C.root";
 	    fileNames["SinglePhoton_2016D"] = "tree_SinglePhoton_2016D.root";
 	    fileNames["SinglePhoton_2016E"] = "tree_SinglePhoton_2016E.root";
 	    fileNames["SinglePhoton_2016F"] = "tree_SinglePhoton_2016F.root";
 	    fileNames["SinglePhoton_2016G"] = "tree_SinglePhoton_2016G.root";
 	    fileNames["SinglePhoton_2016H"] = "tree_SinglePhoton_2016H.root";

 	    fileNames["SinglePhoton_2017B"] = "tree_SinglePhoton_2017B.root";
 	    fileNames["SinglePhoton_2017C"] = "tree_SinglePhoton_2017C.root";
 	    fileNames["SinglePhoton_2017D"] = "tree_SinglePhoton_2017D.root";
 	    fileNames["SinglePhoton_2017E"] = "tree_SinglePhoton_2017E.root";
 	    fileNames["SinglePhoton_2017F"] = "tree_SinglePhoton_2017F.root";

 	    fileNames["SinglePhoton_2018A"] = "tree_EGamma_2018A.root";
	    fileNames["SinglePhoton_2018B"] = "tree_EGamma_2018B.root";
 	    fileNames["SinglePhoton_2018C"] = "tree_EGamma_2018C.root";
 	    fileNames["SinglePhoton_2018D"] = "tree_EGamma_2018D.root";

	for( auto name : backgrounds ){

	  if( fileNames.find(name) != fileNames.end() ){
	    TChain* temp = new TChain("tree");
	    //temp->Add(BASE_DIR+skimType+"/"+fileNames[name]);	  
	    temp->Add(BASE_DIR_DATA+skimType+"/"+fileNames[name]);	  
	    ntuples.push_back(new RA2bTree(temp));
	    sampleName.push_back(name);
	  }

	}	    

	for( auto name : signals ){

	  if( fileNames.find(name) != fileNames.end() ){
	    //TChain* temp = new TChain("tree");
	    TChain* temp = new TChain("TreeMaker2/PreSelection");
        //VBFG1000 = new TChain("TreeMaker2/PreSelection");
	    temp->Add(BASE_DIR_SIG+"/"+fileNames[name]);	  
	    //temp->Add(BASE_DIR+skimType+"/"+fileNames[name]);	  
	    signalNtuples.push_back(new RA2bTree(temp));
	    signalSampleName.push_back(name);
	  }

	}	    

	for( auto name : datas ){

	  if( fileNames.find(name) != fileNames.end() ){
	    TChain* temp = new TChain("tree");
	    //temp->Add(BASE_DIR+skimType+"/"+fileNames[name]);	  
	    temp->Add(BASE_DIR_DATA+skimType+"/"+fileNames[name]);	  
	    dataNtuple.push_back(new RA2bTree(temp));
	    dataSampleName.push_back(name);
	  }

	}	    
       
    };

    void dumpRegions(){
        cout << "index  name" << endl;
        for( int iReg = 0 ; iReg < kNumRegions ; iReg++ ){
            cout << iReg << "      " << regionNames[iReg] << endl;
        }
    };

    RA2bTree* findNtuple(TString name){
        for( int iSam = 0 ; iSam < sampleName.size() ; iSam++ ){
            if( sampleName[iSam] == name )
                return ntuples[iSam] ;
        }
        for( int iSam = 0 ; iSam < signalSampleName.size() ; iSam++ ){
            if( signalSampleName[iSam] == name )
                return signalNtuples[iSam] ;
        }
        return NULL;
    };

};
