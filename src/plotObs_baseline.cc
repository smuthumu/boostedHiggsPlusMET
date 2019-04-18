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
#include "definitions.h"
#include "RA2bTree.cc"
#include "TriggerEfficiencySextet.cc"

using namespace std;

int MAX_EVENTS = 99999999;

void process(string selection_label,
	     string backgroundSample,
	     string signalSample,
	     string dataSample){

  // set up selectors
    bool (*selectionFunc)(RA2bTree*);
    if( selection_label == "ZNoSelection"){
        selectionFunc = baselineCutNoVBF;
    }else if( selection_label == "baselineVBF" ){
        selectionFunc = baselineCut;
    }else if( selection_label == "ZSRNoVBF"){
        selectionFunc = ZSignalRegionCutNoVBF;
    }else if( selection_label == "ZSRVBF"){
        selectionFunc = ZSignalRegionCut;
    }else if( selection_label == "ZSRHPNoVBF_SigBkg"){
        selectionFunc = ZSignalRegionHPCutNoVBF;
    }else if( selection_label == "ZSRHPVBF"){
        selectionFunc = ZSignalRegionHPCut;
    }else if( selection_label == "ZSRHPVBF-TightMjjdEta"){
        selectionFunc = ZSignalRegionHPCut;
    }else if( selection_label == "ZSRHPVBFEta"){
        selectionFunc = ZHPEtaCut;
    }else if( selection_label == "ZSRLPNoVBF"){
        selectionFunc = ZSignalRegionLPCutNoVBF;
    }else if( selection_label == "ZSRLPVBF"){
        selectionFunc = ZSignalRegionLPCut;
    }else if( selection_label == "ZSBNoVBF" ){
        selectionFunc = ZSidebandnoVBFCut;
    }else if( selection_label == "ZSBVBF" ){
        selectionFunc = ZSidebandCut;
    }else if( selection_label == "ZSBHPNoVBF" ){
        selectionFunc = ZSidebandHPCutnoVBF;
    }else if( selection_label == "ZSBHPVBF" ){
        selectionFunc = ZSidebandHPCut;
    }else if( selection_label == "ZSBLPNoVBF"){
        selectionFunc = ZSidebandLPCutnoVBF;
    }else if( selection_label == "ZSBLPVBF"){
        selectionFunc = ZSidebandLPCut;
    }else{
        assert(0);
    }

  // set up background samples
    vector<TString> backgroundSamples;
    if( backgroundSample != "" ){
        backgroundSamples.push_back(TString(backgroundSample));
    }

  // setup signal samples
    vector<TString> signalSamples;
    if( signalSample != "" ){
        signalSamples.push_back(TString(signalSample));
    }

  // setup data samples
    vector<TString> dataSamples;
    if( dataSample != "" ){
        dataSamples.push_back(TString(dataSample));
    }

    skimSamples skims(skimSamples::kSignal,backgroundSamples,signalSamples,dataSamples);
  

  // begin plotting sutff

  gROOT->ProcessLine(".L tdrstyle.C");
  gROOT->ProcessLine("setTDRStyle()");
  
  typedef plot<RA2bTree> plot;

  plot NVtxplot(*fillNVtx<RA2bTree>,"NVtx_"+selection_label,"NVtx",80,0.5,80.5);//1 bin
  plot METplot(*fillMET<RA2bTree>,"MET_"+selection_label,"MET [GeV]",70,200.,3000.);//40 GeV bin
  plot MET1plot(*fillMET<RA2bTree>,"MET1_"+selection_label,"MET [GeV]",25,200.,1200.);//40 GeV bin
  plot HTplot(*fillHT<RA2bTree>,"HT_"+selection_label,"H_{T} [GeV]",75,300,3300.); // 100 GeV bin
  plot NJetsplot(*fillNJets<RA2bTree>,"NJets_"+selection_label,"n_{jets}",9,1.5,10.5);
  plot NAK8Jetsplot(*fillNAK8Jets<RA2bTree>,"NAK8Jets_"+selection_label,"nAK8_{jets}",9,1.5,10.5);
  plot madHT(*fillMadHT<RA2bTree>,"madHT_"+selection_label,"Madgraph HT",19,100,2000);  
  plot METvsAK8Ptplot(*fillLeadingJetPt<RA2bTree>,*fillMET<RA2bTree>,"METvsAK8Pt_"+selection_label,"AK8 L1J p_{T} [GeV]","MET [GeV]",25,200.,1200.,25,200.,1200.);//40 GeV bin
  plot METvsAK4j1Ptplot(*fillJetPt1<RA2bTree>,*fillMET<RA2bTree>,"METvsAK4j1Pt_"+selection_label,"pt_{j1}^{AK4} [GeV]","MET [GeV]",25,0.,1000.,25,200.,1200.);
  plot METvsAK4j2Ptplot(*fillJetPt2<RA2bTree>,*fillMET<RA2bTree>,"METvsAK4j2Pt_"+selection_label,"pt_{j2}^{AK4} [GeV]","MET [GeV]",25,0.,1000.,25,200.,1200.);
  plot METvsAK4j3Ptplot(*fillJetPt3<RA2bTree>,*fillMET<RA2bTree>,"METvsAK4j3Pt_"+selection_label,"pt_{j3}^{AK4} [GeV]","MET [GeV]",25,0.,1000.,25,200.,1200.);
  plot METvsAK4j4Ptplot(*fillJetPt4<RA2bTree>,*fillMET<RA2bTree>,"METvsAK4j4Pt_"+selection_label,"pt_{j4}^{AK4} [GeV]","MET [GeV]",25,0.,1000.,25,200.,1200.);
 
     // AK4 Jets plots: pt, eta, phi, Nemf
  plot AK4j1pt_plot(*fillJetPt1<RA2bTree>,"AK4j1pt_"+selection_label,"pt_{j1}^{AK4} [GeV]",25,0,1000);//40 GeV bin
  plot AK4j2pt_plot(*fillJetPt2<RA2bTree>,"AK4j2pt_"+selection_label,"pt_{j2}^{AK4} [GeV]",25,0,1000);
  plot AK4j3pt_plot(*fillJetPt3<RA2bTree>,"AK4j3pt_"+selection_label,"pt_{j3}^{AK4} [GeV]",25,0,1000);
  plot AK4j4pt_plot(*fillJetPt4<RA2bTree>,"AK4j4pt_"+selection_label,"pt_{j4}^{AK4} [GeV]",15,0,600);

  plot AK4j1Eta1_plot(*fillJetEta1<RA2bTree>,"AK4j1Eta1_"+selection_label,"#eta_{j1}^{AK4} 1",100,-5.,5.); // 0.1 bin
  plot AK4j1Eta_plot(*fillJetEta1<RA2bTree>,"AK4j1Eta_"+selection_label,"#eta_{j1}^{AK4}",50,-5.,5.); // 0.2 bin
  plot AK4j2Eta_plot(*fillJetEta2<RA2bTree>,"AK4j2Eta_"+selection_label,"#eta_{j2}^{AK4}",50,-5.,5.);
  plot AK4j3Eta_plot(*fillJetEta3<RA2bTree>,"AK4j3Eta_"+selection_label,"#eta_{j3}^{AK4}",50,-5.,5.);
  plot AK4j4Eta_plot(*fillJetEta4<RA2bTree>,"AK4j4Eta_"+selection_label,"#eta_{j4}^{AK4}",50,-5.,5.);

  plot AK4j1Phi_plot(*fillJetPhi1<RA2bTree>,"AK4j1Phi_"+selection_label,"#phi_{j1}^{AK4}",35,-3.5,3.5);//0.2 bin
  plot AK4j2Phi_plot(*fillJetPhi2<RA2bTree>,"AK4j2Phi_"+selection_label,"#phi_{j2}^{AK4}",35,-3.5,3.5);
  plot AK4j3Phi_plot(*fillJetPhi3<RA2bTree>,"AK4j3Phi_"+selection_label,"#phi_{j3}^{AK4}",35,-3.5,3.5);
  plot AK4j4Phi_plot(*fillJetPhi4<RA2bTree>,"AK4j4Phi_"+selection_label,"#phi_{j4}^{AK4}",35,-3.5,3.5);

  plot AK4j1NEMF_plot(*fillJetNEMF1<RA2bTree>,"AK4j1NEMF_"+selection_label,"NEMF_{j1}^{AK4}",20,0.,1.); // 0.05
  plot AK4j2NEMF_plot(*fillJetNEMF2<RA2bTree>,"AK4j2NEMF_"+selection_label,"NEMF_{j2}^{AK4}",20,0.,1.);
  plot AK4j3NEMF_plot(*fillJetNEMF3<RA2bTree>,"AK4j3NEMF_"+selection_label,"NEMF_{j3}^{AK4}",20,0.,1.);
  plot AK4j4NEMF_plot(*fillJetNEMF4<RA2bTree>,"AK4j4NEMF_"+selection_label,"NEMF_{j4}^{AK4}",20,0.,1.);

  plot AK4j1NHEF_plot(*fillJetNHEF1<RA2bTree>,"AK4j1NHEF_"+selection_label,"NHEF_{j1}^{AK4}",20,0.,1.); // 0.05
  plot AK4j2NHEF_plot(*fillJetNHEF2<RA2bTree>,"AK4j2NHEF_"+selection_label,"NHEF_{j2}^{AK4}",20,0.,1.); // 0.05
  plot AK4j3NHEF_plot(*fillJetNHEF3<RA2bTree>,"AK4j3NHEF_"+selection_label,"NHEF_{j3}^{AK4}",20,0.,1.); // 0.05
  plot AK4j4NHEF_plot(*fillJetNHEF4<RA2bTree>,"AK4j4NHEF_"+selection_label,"NHEF_{j4}^{AK4}",20,0.,1.); // 0.05
    // 2D plot for AK4 Objects:
   //plot AK4j1ptvsEtaplot(*fillJetEta1<RA2bTree>,*fillJetPt1<RA2bTree>,"AK4j1ptvsEta_"+selection_label,"#eta_{j1}^{AK4}","pt_{j1}^{AK4} [GeV]",50,-5.,5.,25,0.,1000.);
  plot AK4j1ptvsEtaplot(*fillJetPt1<RA2bTree>,*fillJetEta1<RA2bTree>,"AK4j1EtavsPt_"+selection_label,"pt_{j1}^{AK4}","#eta_{j1}^{AK4} [GeV]",25,0.,1000.,50,-5.,5.);
  plot AK4j1PhivsEtaplot(*fillJetEta1<RA2bTree>,*fillJetPhi1<RA2bTree>,"AK4j1PhivsEta_"+selection_label,"#eta_{j1}^{AK4}","#phi_{j1}^{AK4}",50,-5.,5.,35,-3.5,3.5);
  plot AK4j1NEMFvsEtaplot(*fillJetEta1<RA2bTree>,*fillJetNEMF1<RA2bTree>,"AK4j1NEMFvsEta_"+selection_label,"#eta_{j1}^{AK4}","NEMF_{j1}^{AK4}",50,-5.,5.,20,0.,1.);
  plot AK4j1NEMFvsPtplot(*fillJetPt1<RA2bTree>,*fillJetNEMF1<RA2bTree>,"AK4j1NEMFvsPt_"+selection_label,"pt_{j1}^{AK4} [GeV]","NEMF_{j1}^{AK4}",25,0.,1000.,20,0.,1.);
  plot AK4j1NHEFvsEtaplot(*fillJetEta1<RA2bTree>,*fillJetNHEF1<RA2bTree>,"AK4j1NHEFvsEta_"+selection_label,"#eta_{j1}^{AK4}","NHEF_{j1}^{AK4}",50,-5.,5.,20,0.,1.);
  plot AK4j1NHEFvsPtplot(*fillJetPt1<RA2bTree>,*fillJetNHEF1<RA2bTree>,"AK4j1NHEFvsPt_"+selection_label,"pt_{j1}^{AK4} [GeV]","NHEF_{j1}^{AK4}",25,0.,1000.,20,0.,1.);
   //plot AK4j2ptvsEtaplot(*fillJetEta2<RA2bTree>,*fillJetPt2<RA2bTree>,"AK4j2ptvsEta_"+selection_label,"#eta_{j2}^{AK4}","pt_{j2}^{AK4} [GeV]",50,-5.,5.,25,0.,1000.);
  plot AK4j2ptvsEtaplot(*fillJetPt2<RA2bTree>,*fillJetEta2<RA2bTree>,"AK4j2EtavsPt_"+selection_label,"pt_{j2}^{AK4}","#eta_{j2}^{AK4} [GeV]",25,0.,1000.,50,-5.,5.);
  plot AK4j2PhivsEtaplot(*fillJetEta2<RA2bTree>,*fillJetPhi2<RA2bTree>,"AK4j2PhivsEta_"+selection_label,"#eta_{j2}^{AK4}","#phi_{j2}^{AK4}",50,-5.,5.,35,-3.5,3.5);
  plot AK4j2NEMFvsEtaplot(*fillJetEta2<RA2bTree>,*fillJetNEMF2<RA2bTree>,"AK4j2NEMFvsEta_"+selection_label,"#eta_{j2}^{AK4}","NEMF_{j2}^{AK4}",50,-5.,5.,20,0.,1.);
  plot AK4j2NEMFvsPtplot(*fillJetPt2<RA2bTree>,*fillJetNEMF2<RA2bTree>,"AK4j2NEMFvsPt_"+selection_label,"pt_{j2}^{AK4} [GeV]","NEMF_{j2}^{AK4}",25,0.,1000.,20,0.,1.);
  plot AK4j2NHEFvsEtaplot(*fillJetEta2<RA2bTree>,*fillJetNHEF2<RA2bTree>,"AK4j2NHEFvsEta_"+selection_label,"#eta_{j2}^{AK4}","NHEF_{j2}^{AK4}",50,-5.,5.,20,0.,1.);
  plot AK4j2NHEFvsPtplot(*fillJetPt2<RA2bTree>,*fillJetNHEF2<RA2bTree>,"AK4j2NHEFvsPt_"+selection_label,"pt_{j2}^{AK4} [GeV]","NHEF_{j2}^{AK4}",25,0.,1000.,20,0.,1.);

   //plot AK4j3ptvsEtaplot(*fillJetEta1<RA2bTree>,*fillJetPt1<RA2bTree>,"AK4j1ptvsEta_"+selection_label,"#eta_{j1}^{AK4}","pt_{j1}^{AK4} [GeV]",50,-5.,5.,25,0.,1000.);
  plot AK4j3ptvsEtaplot(*fillJetPt3<RA2bTree>,*fillJetEta3<RA2bTree>,"AK4j3EtavsPt_"+selection_label,"pt_{j3}^{AK4}","#eta_{j3}^{AK4} [GeV]",25,0.,1000.,50,-5.,5.);
  plot AK4j3PhivsEtaplot(*fillJetEta3<RA2bTree>,*fillJetPhi3<RA2bTree>,"AK4j3PhivsEta_"+selection_label,"#eta_{j3}^{AK4}","#phi_{j3}^{AK4}",50,-5.,5.,35,-3.5,3.5);
  plot AK4j3NEMFvsEtaplot(*fillJetEta3<RA2bTree>,*fillJetNEMF3<RA2bTree>,"AK4j3NEMFvsEta_"+selection_label,"#eta_{j3}^{AK4}","NEMF_{j3}^{AK4}",50,-5.,5.,20,0.,1.);
  plot AK4j3NEMFvsPtplot(*fillJetPt3<RA2bTree>,*fillJetNEMF3<RA2bTree>,"AK4j3NEMFvsPt_"+selection_label,"pt_{j3}^{AK4} [GeV]","NEMF_{j3}^{AK4}",25,0.,1000.,20,0.,1.);
  plot AK4j3NHEFvsEtaplot(*fillJetEta3<RA2bTree>,*fillJetNHEF3<RA2bTree>,"AK4j3NHEFvsEta_"+selection_label,"#eta_{j3}^{AK4}","NHEF_{j3}^{AK4}",50,-5.,5.,20,0.,1.);
  plot AK4j3NHEFvsPtplot(*fillJetPt3<RA2bTree>,*fillJetNHEF3<RA2bTree>,"AK4j3NHEFvsPt_"+selection_label,"pt_{j3}^{AK4} [GeV]","NHEF_{j3}^{AK4}",25,0.,1000.,20,0.,1.);

   //plot AK4j2ptvsEtaplot(*fillJetEta2<RA2bTree>,*fillJetPt2<RA2bTree>,"AK4j2ptvsEta_"+selection_label,"#eta_{j2}^{AK4}","pt_{j2}^{AK4} [GeV]",50,-5.,5.,25,0.,1000.);
  plot AK4j4ptvsEtaplot(*fillJetPt4<RA2bTree>,*fillJetEta4<RA2bTree>,"AK4j4EtavsPt_"+selection_label,"pt_{j4}^{AK4}","#eta_{j4}^{AK4} [GeV]",25,0.,1000.,50,-5.,5.);
  plot AK4j4PhivsEtaplot(*fillJetEta4<RA2bTree>,*fillJetPhi4<RA2bTree>,"AK4j4PhivsEta_"+selection_label,"#eta_{j4}^{AK4}","#phi_{j4}^{AK4}",50,-5.,5.,35,-3.5,3.5);
  plot AK4j4NEMFvsEtaplot(*fillJetEta4<RA2bTree>,*fillJetNEMF4<RA2bTree>,"AK4j4NEMFvsEta_"+selection_label,"#eta_{j4}^{AK4}","NEMF_{j4}^{AK4}",50,-5.,5.,20,0.,1.);
  plot AK4j4NEMFvsPtplot(*fillJetPt4<RA2bTree>,*fillJetNEMF4<RA2bTree>,"AK4j4NEMFvsPt_"+selection_label,"pt_{j4}^{AK4} [GeV]","NEMF_{j4}^{AK4}",25,0.,1000.,20,0.,1.);
  plot AK4j4NHEFvsEtaplot(*fillJetEta4<RA2bTree>,*fillJetNHEF4<RA2bTree>,"AK4j4NHEFvsEta_"+selection_label,"#eta_{j4}^{AK4}","NHEF_{j4}^{AK4}",50,-5.,5.,20,0.,1.);
  plot AK4j4NHEFvsPtplot(*fillJetPt4<RA2bTree>,*fillJetNHEF4<RA2bTree>,"AK4j4NHEFvsPt_"+selection_label,"pt_{j4}^{AK4} [GeV]","NHEF_{j4}^{AK4}",25,0.,1000.,20,0.,1.);

  plot DeltaPhi1plot(*fillDeltaPhi1<RA2bTree>,"DeltaPhi1_"+selection_label,"#Delta#Phi_{1}",16,0,3.2);
  plot DeltaPhi2plot(*fillDeltaPhi2<RA2bTree>,"DeltaPhi2_"+selection_label,"#Delta#Phi_{2}",16,0,3.2);
  plot DeltaPhi3plot(*fillDeltaPhi3<RA2bTree>,"DeltaPhi3_"+selection_label,"#Delta#Phi_{3}",16,0,3.2);
  plot DeltaPhi4plot(*fillDeltaPhi4<RA2bTree>,"DeltaPhi4_"+selection_label,"#Delta#Phi_{4}",16,0,3.2);
  plot DeltaPhiAK8JMETplot(*fillDeltaPhiAK8JMET<RA2bTree>,"DeltaPhiAK8JMET_"+selection_label,"#Delta#Phi(AK8J,MET)",16,0,3.2);

  plot J1pt_Massplot(*fillLeadingJetMass<RA2bTree>,"J1pt_Mass_"+selection_label,"m_{J} [GeV]",54,30.,300.);//5 Gev bin
  plot J1_SDMassplot(*fillLeadingJetSDMass<RA2bTree>,"J1_SDMass_"+selection_label,"SoftDrop m_{J} [GeV]",54,30.,300.);//5 Gev bin
  // Turn on the line below for SR only
  plot J1pt_Mass1plot(*fillLeadingJetMass<RA2bTree>,"J1pt_Mass1_"+selection_label,"m_{J} [GeV]",14,50.,120.);//5 Gev bin
  plot J1pt_Tau21plot(*fillLeadingTau21<RA2bTree>,"J1pt_Tau21_"+selection_label,"#tau_{21}",20,0.,1.);
  plot DDT_Tau21plot(*fillDDT<RA2bTree>,"DDT_Tau21_"+selection_label,"DDT",20,0.,1.);
  plot Tau21vsJMassplot(*fillLeadingJetSDMass<RA2bTree>,*fillLeadingTau21<RA2bTree>,"Tau21vsJMass_"+selection_label,"SoftDrop m_{J} [GeV]","#tau_{21}",34,30.,200.,20,0.,1.);

  plot GMassvsZMTplot(*fillGMass<RA2bTree>,*fillZMT<RA2bTree>,"GMassvsZMT_"+selection_label,"M_{G} [GeV]","MT_{Z} [GeV]",25,500.,3000.,45,500.,5000.); // 100 GeV bin
  plot GMassplot(*fillGMass<RA2bTree>,"GMass_"+selection_label,"M_{G} [GeV]",25,500.,3000.); // 100 GeV bin
  plot GMass1plot(*fillGMass<RA2bTree>,"GMass1_"+selection_label,"M_{G} [GeV]",70,0.,7000.); // 100 GeV bin
  plot GMass2plot(*fillGMass<RA2bTree>,"GMass2_"+selection_label,"M_{G} [GeV]",65,500.,7000.); // 100 GeV bin
  plot ZMTplot(*fillZMT<RA2bTree>,"ZMT_"+selection_label,"MT_{Z} [GeV]",45,500.,5000.); // 100 GeV bin
  plot ZMT1plot(*fillZMT<RA2bTree>,"ZMT1_"+selection_label,"MT_{Z} [GeV]",25,500.,3000.); // 100 GeV bin
  plot ZMT2plot(*fillZMT<RA2bTree>,"ZMT2_"+selection_label,"MT_{Z} [GeV]",20,500.,2500.); // 100 GeV bin
  plot ZMT3plot(*fillZMT<RA2bTree>,"ZMT3_"+selection_label,"MT_{Z} [GeV]",30,2000.,5000.); // 100 GeV bin
  plot ZMT4plot(*fillZMT<RA2bTree>,"ZMT4_"+selection_label,"MT_{Z} [GeV]",20,0.,2000.); // 100 GeV bin

  plot J1pt_Ptplot(*fillLeadingJetPt<RA2bTree>,"AK8L1J_Pt_"+selection_label,"p_{T,J} [GeV]",70,200.,3000.); //40 GeV bi n;
  plot J1pt_Pt1plot(*fillLeadingJetPt<RA2bTree>,"AK8L1J_Pt1_"+selection_label,"p_{T,J} [GeV]",35,200.,1600.); //40 GeV bin;
  plot J1pt_Etaplot(*fillLeadingJetEta<RA2bTree>,"J1pt_Eta_"+selection_label,"#eta_{AK8J} [GeV]",50,-5.,5.); //50 GeV bin;
  plot J1pt_Eta1plot(*fillLeadingJetEta<RA2bTree>,"J1pt_Eta1_"+selection_label,"#eta_{AK8J} [GeV]",30,-3.,3.); //0.2 GeV bin;

  plot VBFmjj_plot(*fillVBF_Mjj<RA2bTree>,"VBFmjj_"+selection_label,"m_{jj}^{VBF} [GeV]",40,0,4000);
  plot VBFptjj_plot(*fillVBF_Ptjj<RA2bTree>,"VBFptjj_"+selection_label,"pt_{jj}^{VBF} [GeV]",40,0,2000);
  plot VBFj1pt_plot(*fillVBF_j1Pt<RA2bTree>,"VBFj1pt_"+selection_label,"pt_{j1}^{VBF} [GeV]",25,0,1000);
  plot VBFj2pt_plot(*fillVBF_j2Pt<RA2bTree>,"VBFj2pt_"+selection_label,"pt_{j2}^{VBF} [GeV]",25,0,1000);
  plot VBFdEta_plot(*fillVBF_dEta<RA2bTree>,"VBFdEta_"+selection_label,"#Delta#eta^{VBF}",50,0,10);
  plot VBFdPhi_plot(*fillVBF_dPhi<RA2bTree>,"VBFdPhi_"+selection_label,"#Delta#Phi VBF(j1,j2)",16,0,3.2);
  plot VBFj1Eta_plot(*fillVBF_j1Eta<RA2bTree>,"VBFj1Eta_"+selection_label,"#eta_{j1}^{VBF}",50,-5.,5.);
  plot VBFj2Eta_plot(*fillVBF_j2Eta<RA2bTree>,"VBFj2Eta_"+selection_label,"#eta_{j2}^{VBF}",50,-5.,5.);
  plot VBFj1Phi_plot(*fillVBF_j1Phi<RA2bTree>,"VBFj1Phi_"+selection_label,"#Phi_{j1}^{VBF}",32,-3.2,3.2);
  plot VBFj2Phi_plot(*fillVBF_j2Phi<RA2bTree>,"VBFj2Phi_"+selection_label,"#Phi_{j2}^{VBF}",32,-3.2,3.2);
  plot VBFj1j2Eta_plot(*fillVBF_j1j2Eta<RA2bTree>,"VBFj1j2Eta_"+selection_label,"#eta_{j1.j2}^{VBF}",100,-25,25);

 
  vector<plot> plots;
  plots.push_back(NVtxplot);
  plots.push_back(METplot);
  plots.push_back(MET1plot);
  plots.push_back(HTplot);
  plots.push_back(NJetsplot);
  plots.push_back(NAK8Jetsplot); 
  plots.push_back(madHT);
  plots.push_back(METvsAK8Ptplot);
  plots.push_back(METvsAK4j1Ptplot);
  plots.push_back(METvsAK4j2Ptplot);
  plots.push_back(METvsAK4j3Ptplot);
  plots.push_back(METvsAK4j4Ptplot);

  plots.push_back(AK4j1pt_plot);
  plots.push_back(AK4j2pt_plot);
  plots.push_back(AK4j3pt_plot);
  plots.push_back(AK4j4pt_plot);

  plots.push_back(AK4j1Eta1_plot);
  plots.push_back(AK4j1Eta_plot);
  plots.push_back(AK4j2Eta_plot);
  plots.push_back(AK4j3Eta_plot);
  plots.push_back(AK4j4Eta_plot);

  plots.push_back(AK4j1Phi_plot);
  plots.push_back(AK4j2Phi_plot);
  plots.push_back(AK4j3Phi_plot);
  plots.push_back(AK4j4Phi_plot);

  plots.push_back(AK4j1NEMF_plot);
  plots.push_back(AK4j2NEMF_plot);
  plots.push_back(AK4j3NEMF_plot);
  plots.push_back(AK4j4NEMF_plot);

  plots.push_back(AK4j1NHEF_plot);
  plots.push_back(AK4j2NHEF_plot);
  plots.push_back(AK4j3NHEF_plot);
  plots.push_back(AK4j4NHEF_plot);

  plots.push_back(AK4j1ptvsEtaplot);
  plots.push_back(AK4j1PhivsEtaplot);
  plots.push_back(AK4j1NEMFvsEtaplot);
  plots.push_back(AK4j1NEMFvsPtplot);
  plots.push_back(AK4j1NHEFvsEtaplot);
  plots.push_back(AK4j1NHEFvsPtplot);

  plots.push_back(AK4j2ptvsEtaplot  );
  plots.push_back(AK4j2PhivsEtaplot );
  plots.push_back(AK4j2NEMFvsEtaplot);
  plots.push_back(AK4j2NEMFvsPtplot );
  plots.push_back(AK4j2NHEFvsEtaplot);
  plots.push_back(AK4j2NHEFvsPtplot);

  plots.push_back(AK4j3ptvsEtaplot  );
  plots.push_back(AK4j3PhivsEtaplot );
  plots.push_back(AK4j3NEMFvsEtaplot);
  plots.push_back(AK4j3NEMFvsPtplot );
  plots.push_back(AK4j3NHEFvsEtaplot);
  plots.push_back(AK4j3NHEFvsPtplot);

  plots.push_back(AK4j4ptvsEtaplot  );
  plots.push_back(AK4j4PhivsEtaplot );
  plots.push_back(AK4j4NEMFvsEtaplot);
  plots.push_back(AK4j4NEMFvsPtplot );
  plots.push_back(AK4j4NHEFvsEtaplot);
  plots.push_back(AK4j4NHEFvsPtplot);
 
  plots.push_back(DeltaPhi1plot);
  plots.push_back(DeltaPhi2plot);
  plots.push_back(DeltaPhi3plot);
  plots.push_back(DeltaPhi4plot);
  plots.push_back(DeltaPhiAK8JMETplot);

  plots.push_back(J1pt_Massplot);
  plots.push_back(J1_SDMassplot);
  plots.push_back(J1pt_Mass1plot);
  plots.push_back(J1pt_Tau21plot);
  plots.push_back(DDT_Tau21plot);
  plots.push_back(Tau21vsJMassplot);

  plots.push_back(GMassvsZMTplot);  
  plots.push_back(GMassplot);
  plots.push_back(GMass1plot);
  plots.push_back(GMass2plot);
  plots.push_back(ZMTplot);
  plots.push_back(ZMT1plot);
  plots.push_back(ZMT2plot);
  plots.push_back(ZMT3plot);
  plots.push_back(ZMT4plot); 

  plots.push_back(J1pt_Ptplot);
  plots.push_back(J1pt_Pt1plot);
  plots.push_back(J1pt_Etaplot);
  plots.push_back(J1pt_Eta1plot);

  plots.push_back(VBFmjj_plot);
  plots.push_back(VBFptjj_plot);
  plots.push_back(VBFj1pt_plot);
  plots.push_back(VBFj2pt_plot);
  plots.push_back(VBFdEta_plot);
  plots.push_back(VBFdPhi_plot);
  plots.push_back(VBFj1Eta_plot);
  plots.push_back(VBFj2Eta_plot);
  plots.push_back(VBFj1Phi_plot);
  plots.push_back(VBFj2Phi_plot);
  plots.push_back(VBFj1j2Eta_plot);


  // background MC samples
  for( int iSample = 0 ; iSample < skims.ntuples.size() ; iSample++){
    RA2bTree* ntuple = skims.ntuples[iSample];
    TFile* outputFile = new TFile("plotObs_"+selection_label+"_baseline_"+skims.sampleName[iSample]+".root","RECREATE");
    
    for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
      plots[iPlot].addNtuple(ntuple,skims.sampleName[iSample]);
    }
    int numEvents = ntuple->fChain->GetEntries();
    ntupleBranchStatus<RA2bTree>(ntuple);
    TString filename;
    double weight = 0.;
    for( int iEvt = 0 ; iEvt < min(MAX_EVENTS,numEvents) ; iEvt++ ){
    //for( int iEvt = 0 ; iEvt < min(0,numEvents) ; iEvt++ ){
        ntuple->GetEntry(iEvt);
        if( iEvt % 100000 == 0 ) cout << skims.sampleName[iSample] << ": " << iEvt << "/" << numEvents << endl;
        filename = ntuple->fChain->GetFile()->GetName();
        if( ( filename.Contains("SingleLept") || filename.Contains("DiLept") ) && ntuple->madHT>600. )continue;
        if(! selectionFunc(ntuple) ) continue;

        weight = ntuple->Weight*lumi;
      // ------------ end weights -------------
      //cout << "event passed all selections" << endl;
        for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++ ){
	        plots[iPlot].fill(ntuple,weight);
        }
    }

    for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
        plots[iPlot].Write(ntuple);
    }
    outputFile->Close();
 }// end loop over samples
    
  // Signal samples
  vector<RA2bTree*> sigSamples;
  for( int iSample = 0 ; iSample < skims.signalNtuples.size() ; iSample++){
    RA2bTree* ntuple = skims.signalNtuples[iSample];
    TFile* outputFile = new TFile("plotObs_"+selection_label+"_baseline_"+skims.signalSampleName[iSample]+".root","RECREATE");

    sigSamples.push_back(ntuple);
    for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
      plots[iPlot].addSignalNtuple(ntuple,skims.signalSampleName[iSample]);
    }

    int numEvents = ntuple->fChain->GetEntries();
    ntupleBranchStatus<RA2bTree>(ntuple);
    for( int iEvt = 0 ; iEvt < min(MAX_EVENTS,numEvents) ; iEvt++ ){
    //for( int iEvt = 0 ; iEvt < min(0,numEvents) ; iEvt++ ){
      ntuple->GetEntry(iEvt);
      //cout<<"Run Num: "<<ntuple->RunNum<<endl;  
      if( iEvt % 100000 == 0 ) cout << skims.signalSampleName[iSample] << ": " << iEvt << "/" << numEvents << endl;
      if(! selectionFunc(ntuple) ) continue;
      for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
	    if (skims.signalSampleName[iSample]=="VBFG_1000") 
	    plots[iPlot].fillSignal(ntuple,ntuple->Weight*lumi);
        }
    }

    for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
        plots[iPlot].Write(ntuple);
    }
    
    outputFile->Close();
  }// end loop over samples


  // Data samples
  for( int iSample = 0 ; iSample < skims.dataNtuple.size() ; iSample++){
    RA2bTree* ntuple = skims.dataNtuple[iSample];
    TFile* outputFile = new TFile("plotObs_"+selection_label+"_baseline_"+skims.dataSampleName[iSample]+".root","RECREATE");
	  
    for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
        plots[iPlot].addDataNtuple(ntuple,skims.dataSampleName[iSample]);
    }
    
    int numEvents = ntuple->fChain->GetEntries();
    ntupleBranchStatus<RA2bTree>(ntuple);
    cout << "data MET: " << numEvents << endl;
    for( int iEvt = 0 ; iEvt < min(MAX_EVENTS,numEvents) ; iEvt++ ){
    //for( int iEvt = 0 ; iEvt < min(1000,numEvents) ; iEvt++ ){
        ntuple->GetEntry(iEvt);
        //cout<<"Run Num: "<<ntuple->RunNum<<endl;
        if( iEvt % 100000 == 0 ) cout << "data_MET: " << iEvt << "/" << min(MAX_EVENTS,numEvents) << endl;
        if(! selectionFunc(ntuple) ) continue;
        if( !signalTriggerCut(ntuple) ) continue;
      
        for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
	        plots[iPlot].fillData(ntuple);
        }
    }

    for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
        //if (plots[iPlot].is2Dhist) continue;
        plots[iPlot].Write();
    }// end loop over plots
    
    outputFile->Close();
  }// end loop over samples

}// end process


int main(int argc, char** argv){

  string signal_label,background_label,data_label;
  string selection_label;
  if( argc > 5 )
    MAX_EVENTS = atoi(argv[5]);
  else
    MAX_EVENTS = 99999999;
  if( argc > 4 )
    data_label = argv[4];
  else
    data_label="";
  if( argc > 3 )
    signal_label = argv[3];
  else
    signal_label = "";
  if( argc > 2 )
    background_label = argv[2];
  else
    background_label = "ZJets_400to600";
  if( argc > 1 )
    selection_label = argv[1];
  else
    selection_label = "ZSBNoVBF";

  process(selection_label,
	  background_label,
	  signal_label,
	  data_label);
  
}
