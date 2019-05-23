#include "TString.h"
#include "TChain.h"
#include "TH1F.h"
#include "TROOT.h"
#include "THStack.h"
#include "TPad.h"

#include <vector>
#include <map>
#include <iostream>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <cassert>
#include "plotterUtils.cc"
#include "skimSamples.cc"
#include "definitions.cc"
#include "RA2bTree.cc"
#include "TriggerEfficiencySextet.cc"

using namespace std;


int main(int argc, char** argv){
  
    skimSamples::system sys=skimSamples::kLPC;
    if( argc > 3 ) 
      sys=skimSamples::system(atoi(argv[3]));

    int MAX_EVENTS = 99999999;
    if( argc > 2 )
        MAX_EVENTS = atoi(argv[2]);
    
    assert(argc > 1);
    TString selection_label = argv[1];
    bool (*selectionFunc)(RA2bTree*);
    if( selection_label == "Monojet"){
       selectionFunc = baselineCutMonojet;
    /*}else if( selection_label == "baselineVBF" ){
        selectionFunc = baselineCut;*/
    }else
        assert(0);

    gROOT->ProcessLine(".L tdrstyle.C");
    gROOT->ProcessLine("setTDRStyle()");
  
    skimSamples skims(skimSamples::kSignal,sys);
    typedef plot<RA2bTree> plot;

    plot NVtxplot(*fillNVtx<RA2bTree>,"NVtx_"+selection_label,"NVtx",79,1.5,80.5);//1 bin
    plot METplot(*fillMET<RA2bTree>,"MET_"+selection_label,"MET [GeV]",56,200.,3000.);//50 GeV bin
    plot MET1plot(*fillMET<RA2bTree>,"MET1_"+selection_label,"MET [GeV]",23,250.,1400.);//40 GeV bin
    plot HTplot(*fillHT<RA2bTree>,"HT_"+selection_label,"H_{T} [GeV]",30,300,3300.);
    plot NJetsplot(*fillNJets<RA2bTree>,"NJets_"+selection_label,"n_{jets}",14,1.5,15.5);

    plot DeltaPhi1plot(*fillDeltaPhi1<RA2bTree>,"DeltaPhi1_"+selection_label,"#Delta#Phi_{1}",20,0,3.1415);
    plot DeltaPhi2plot(*fillDeltaPhi2<RA2bTree>,"DeltaPhi2_"+selection_label,"#Delta#Phi_{2}",20,0,3.1415);
    plot DeltaPhi3plot(*fillDeltaPhi3<RA2bTree>,"DeltaPhi3_"+selection_label,"#Delta#Phi_{3}",20,0,3.1415);
    plot DeltaPhi4plot(*fillDeltaPhi4<RA2bTree>,"DeltaPhi4_"+selection_label,"#Delta#Phi_{4}",20,0,3.1415);

    // Turn on the line below for SR only

    plot ZMTplot(*fillZMT<RA2bTree>,"ZMT_"+selection_label,"MT_{Z} [GeV]",50,0.,5000.); // 100 GeV bin
    plot ZMT1plot(*fillZMT<RA2bTree>,"ZMT1_"+selection_label,"MT_{Z} [GeV]",30,0.,3000.); // 100 GeV bin
    plot L1Jpt_plot(*fillJetPt1<RA2bTree>,"J1_Pt_"+selection_label,"Leading J p_{T} [GeV]",30,0.,3000.); //100 GeV bin;
    plot L1JEta_plot(*fillJetEta1<RA2bTree>,"J1_Eta_"+selection_label,"Leading J #eta [GeV]",50,-5.,5.); //50 GeV bin;
    plot Jet1CHFplot(*fillJet1CHF<RA2bTree>,"Jet1_CHF_"+selection_label,"Jet1_CHF",110,0.0,1.1);
    plot Jet1NHFplot(*fillJet1NHF<RA2bTree>,"Jet1_NHF_"+selection_label,"Jet1_NHF",110,0.0,1.1);
    plot Jet1CEMFplot(*fillJet1CEMF<RA2bTree>,"Jet1_CEMF_"+selection_label,"Jet1_CEMF",110,0.0,1.1);
    plot Jet1NEMFplot(*fillJet1NEMF<RA2bTree>,"Jet1_NEMF_"+selection_label,"Jet1_NEMF",110,0.0,1.1);



    vector<plot> plots;
    plots.push_back(NVtxplot);
    plots.push_back(METplot);
    plots.push_back(MET1plot);
    plots.push_back(HTplot);
    plots.push_back(NJetsplot);

    plots.push_back(DeltaPhi1plot);
    plots.push_back(DeltaPhi2plot);
    plots.push_back(DeltaPhi3plot);
    plots.push_back(DeltaPhi4plot);

    plots.push_back(ZMTplot);
    plots.push_back(ZMT1plot);
    plots.push_back(L1Jpt_plot);
    plots.push_back(L1JEta_plot);
    plots.push_back(Jet1CHFplot);
    plots.push_back(Jet1NHFplot);
    plots.push_back(Jet1CEMFplot);
    plots.push_back(Jet1NEMFplot);

    // background MC samples
    for( int iSample = 0 ; iSample < skims.ntuples.size() ; iSample++){

        RA2bTree* ntuple = skims.ntuples[iSample];

        for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
            plots[iPlot].addNtuple(ntuple,skims.sampleName[iSample]);
            plots[iPlot].setFillColor(ntuple,skims.fillColor[iSample]);
        }

        int numEvents = ntuple->fChain->GetEntries();
        ntupleBranchStatus<RA2bTree>(ntuple);
        TString filename;
        double weight = 0.;
        for( int iEvt = 0 ; iEvt < min(MAX_EVENTS,numEvents) ; iEvt++ ){
            ntuple->GetEntry(iEvt);
            if( iEvt % 1000000 == 0 ) cout << skims.sampleName[iSample] << ": " << iEvt << "/" << numEvents << endl;

            filename = ntuple->fChain->GetFile()->GetName();
            if( ( filename.Contains("SingleLept") || filename.Contains("DiLept") ) && ntuple->madHT>600. )continue;

            if(! selectionFunc(ntuple) ) continue;

            // print out trigger name
            /*
            int n = ntuple->TriggerNames->size();
            for(int i=0; i<n; i++){
                std::cout<<"Trigger Names: "<<ntuple->TriggerNames->at(i)<<std::endl;
            }
            */       
            // end of Trigger name printout
            // ---------- custom weights -----------
            std::vector<double> EfficiencyCenterUpDown = Eff_MetMhtSextetReal_CenterUpDown(ntuple->HT, ntuple->MHT, ntuple->NJets);
            weight = ntuple->Weight*lumi*customPUweights(ntuple)*EfficiencyCenterUpDown[0];
            if( skims.sampleName[iSample] == "TT" )
                weight *= ISRweights(ntuple);
            if( skims.sampleName[iSample] == "WJets" ){
                weight *= WJetsNLOWeights(ntuple);
            }
            if( skims.sampleName[iSample] == "ZJets" ){
                weight *= ZJetsNLOWeights(ntuple);
            }
            // ------------ end weights -------------
            for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++ ){
                plots[iPlot].fill(ntuple,weight);
            }
        }
    }

    // Signal samples
  
  vector<RA2bTree*> sigSamples;
    for( int iSample = 0 ; iSample < skims.signalNtuples.size() ; iSample++){
        std::cout<<"Skims check 1: "<<skims.signalSampleName[iSample]<<std::endl;
        RA2bTree* ntuple = skims.signalNtuples[iSample];
        sigSamples.push_back(ntuple);
        for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
            plots[iPlot].addSignalNtuple(ntuple,skims.signalSampleName[iSample]);
            plots[iPlot].setLineColor(ntuple,skims.sigLineColor[iSample]);
        }

        int numEvents = ntuple->fChain->GetEntries();
        std::cout<<"Skims check Num evts: "<<numEvents<<std::endl;
        ntupleBranchStatus<RA2bTree>(ntuple);
        for( int iEvt = 0 ; iEvt < min(MAX_EVENTS,numEvents) ; iEvt++ ){
        //for( int iEvt = 0 ; iEvt < min(0,numEvents) ; iEvt++ ){
            ntuple->GetEntry(iEvt);
            if( iEvt % 1000000 == 0 ) cout << skims.signalSampleName[iSample] << ": " << iEvt << "/" << numEvents << endl;
            if(! selectionFunc(ntuple) ) continue;
            for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
               if (skims.signalSampleName[iSample]=="NonTh154") 
                  plots[iPlot].fillSignal(ntuple,ntuple->Weight*lumi*0.000000012572); // 1 is fro XSec, change it later 
               /*if (skims.signalSampleName[iSample]=="VBFG1200") 
                  plots[iPlot].fillSignal(ntuple,ntuple->Weight*lumi*1);
               if (skims.signalSampleName[iSample]=="VBFG1400") 
                  plots[iPlot].fillSignal(ntuple,ntuple->Weight*lumi*1);
               if (skims.signalSampleName[iSample]=="VBFG1600") 
                  plots[iPlot].fillSignal(ntuple,ntuple->Weight*lumi*1);
               if (skims.signalSampleName[iSample]=="VBFG1800") 
                  plots[iPlot].fillSignal(ntuple,ntuple->Weight*lumi*1);*/
               //if (skims.signalSampleName[iSample]=="VBFG2000") 
                  //plots[iPlot].fillSignal(ntuple,ntuple->Weight*lumi*1);
              /* if (skims.signalSampleName[iSample]=="VBFG2500") 
                  plots[iPlot].fillSignal(ntuple,ntuple->Weight*lumi*1);
               if (skims.signalSampleName[iSample]=="VBFG3000") 
                  plots[iPlot].fillSignal(ntuple,ntuple->Weight*lumi*1);
               if (skims.signalSampleName[iSample]=="VBFG3500") 
                  plots[iPlot].fillSignal(ntuple,ntuple->Weight*lumi*1);
               if (skims.signalSampleName[iSample]=="VBFG4000") 
                  plots[iPlot].fillSignal(ntuple,ntuple->Weight*lumi*1);
               if (skims.signalSampleName[iSample]=="VBFG4500") 
                  plots[iPlot].fillSignal(ntuple,ntuple->Weight*lumi*1);*/
            }
        }
    }

    // Data samples
    RA2bTree* ntuple = skims.dataNtuple;
    for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
        plots[iPlot].addDataNtuple(ntuple,"data_MET");
    }
  
    int numEvents = ntuple->fChain->GetEntries();
    ntupleBranchStatus<RA2bTree>(ntuple);
        for( int iEvt = 0 ; iEvt < min(MAX_EVENTS,numEvents) ; iEvt++ ){
      //for( int iEvt = 0 ; iEvt < min(1000,numEvents) ; iEvt++ ){
        ntuple->GetEntry(iEvt);
        if( iEvt % 1000000 == 0 ) cout << "data_MET: " << iEvt << "/" << min(MAX_EVENTS,numEvents) << endl;
        if(! selectionFunc(ntuple) ) continue;
        if( !signalTriggerCut(ntuple) ) continue;
        for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
            plots[iPlot].fillData(ntuple);
        }
    }

    TFile* outputFile = new TFile("plotObs_"+selection_label+".root","RECREATE");

    for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
        TCanvas* can = new TCanvas("can","can",500,500);
        //plots[iPlot].dataHist = NULL;
        //plots[iPlot].DrawNoRatio(can,skims.ntuples,sigSamples,"../plots/plotObs_"+selection_label+"_plots");
        plots[iPlot].Draw(can,skims.ntuples,sigSamples,"../plots/plotObs_"+selection_label+"_plots",0.1,2.0,true);
        plots[iPlot].Write();
        plots[iPlot].sum->Write();
    }
    outputFile->Close();
}
