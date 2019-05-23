#include "TLorentzVector.h"
#include "TRandom3.h"
#include <iostream>

// constants
// ==============================================
double bbtagCut = 0.3;
//TFile* puWeightFile = new TFile("../data/PileupHistograms_0121_69p2mb_pm4p6.root");

//TFile* puWeightFile = new TFile("/uscms_data/d3/smuthumu/NonThermalDM/Sample_Production/Ntupple/Ntuple_New/CMSSW_10_2_11_patch1/src/TreeMaker/Production/test/data/PileupHistograms_0121_69p2mb_pm4p6.root");// Summer16

//TFile* puWeightFile = new TFile("/uscms_data/d3/smuthumu/NonThermalDM/Sample_Production/Ntupple/Ntuple_New/CMSSW_10_2_11_patch1/src/TreeMaker/Production/test/data/PileupHistograms_0328_63mb_pm5.root");// Fall17

TFile* puWeightFile = new TFile("/uscms_data/d3/smuthumu/NonThermalDM/Sample_Production/Ntupple/Ntuple_New/CMSSW_10_2_11_patch1/src/TreeMaker/Production/test/data/PileupHistograms_0118_63mb_pm5.root");// Autumn18

TH1F* puWeightHist = (TH1F*) puWeightFile->Get("pu_weights_down");
// - - - - - - weights for WJets, GJets, - - - - - - - - 
// - - - - - - and ZJets NLO Pt distribution - - - - - - 
TFile* NLOWeightFile = new TFile("../data/kfactors.root");
TH1F* GJets_NLO = (TH1F*) NLOWeightFile->Get("GJets_1j_NLO/nominal_G");
TH1F* GJets_LO = (TH1F*) NLOWeightFile->Get("GJets_LO/inv_pt_G");
TH1F* WJets_NLO = (TH1F*) NLOWeightFile->Get("WJets_012j_NLO/nominal");
TH1F* WJets_LO = (TH1F*) NLOWeightFile->Get("WJets_LO/inv_pt");
TH1F* ZJets_NLO = (TH1F*) NLOWeightFile->Get("ZJets_01j_NLO/nominal");
TH1F* ZJets_LO = (TH1F*) NLOWeightFile->Get("ZJets_LO/inv_pt");
// ==============================================

double CalcdPhi( double phi1 , double phi2 ){
  double dPhi = phi1-phi2;
  if( dPhi < -TMath::Pi() ) 
    dPhi += 2*TMath::Pi() ;
  if( dPhi > TMath::Pi() )
    dPhi -= 2*TMath::Pi() ;
  return fabs(dPhi);
  //return dPhi;

}


double CalcDeltaR( double eta1, double phi1 , double eta2, double phi2 ){
    float dEta = (eta1-eta2);
    float dPhi = CalcdPhi(phi1, phi2);
    return sqrt((dEta*dEta) + (dPhi * dPhi));
}

double ZMT(double pt1, double phi1, double pt2, double phi2){
    TLorentzVector v1, v2;
    v1.SetPtEtaPhiM(pt1,0,phi1,0);
    v2.SetPtEtaPhiM(pt2,0,phi2,0);
    return (v1+v2).M();
}

template<typename ntupleType>void ntupleBranchStatus(ntupleType* ntuple){
  ntuple->fChain->SetBranchStatus("*",0);
  ntuple->fChain->SetBranchStatus("Muons",1);
  ntuple->fChain->SetBranchStatus("NMuons",1);
  ntuple->fChain->SetBranchStatus("Electrons",1);
  ntuple->fChain->SetBranchStatus("NElectrons",1);
  ntuple->fChain->SetBranchStatus("iso*clean",1);
  //ntuple->fChain->SetBranchStatus("isoElectronTracksclean",1);
  //ntuple->fChain->SetBranchStatus("isoMuonTracksclean",1);
  //ntuple->fChain->SetBranchStatus("isoPionTracksclean",1);
  ntuple->fChain->SetBranchStatus("iso*Tracks",1);
  ntuple->fChain->SetBranchStatus("JetsAK8*",1);
  ntuple->fChain->SetBranchStatus("Jets*",1);
  ntuple->fChain->SetBranchStatus("Jets_chargedHadronEnergyFraction",1);
  ntuple->fChain->SetBranchStatus("Jets_neutralHadronEnergyFraction",1);
  ntuple->fChain->SetBranchStatus("DeltaPhi*",1);
  ntuple->fChain->SetBranchStatus("HT*",1);
  ntuple->fChain->SetBranchStatus("NJets",1);
  ntuple->fChain->SetBranchStatus("BTags*",1);
  ntuple->fChain->SetBranchStatus("MHT",1);
  ntuple->fChain->SetBranchStatus("Weight",1);
  ntuple->fChain->SetBranchStatus("pu*",1);
  ntuple->fChain->SetBranchStatus("puWeightNew",1); // new
  ntuple->fChain->SetBranchStatus("TriggerNames",1);
  ntuple->fChain->SetBranchStatus("TriggerPass",1);
  ntuple->fChain->SetBranchStatus("Photon*",1);
  ntuple->fChain->SetBranchStatus("madMinPhotonDeltaR",1);
  ntuple->fChain->SetBranchStatus("GenParticles*",1);
  ntuple->fChain->SetBranchStatus("madHT",1);
  ntuple->fChain->SetBranchStatus("*Filter",1);
  ntuple->fChain->SetBranchStatus("PFCaloMETRatio",1); // new
  ntuple->fChain->SetBranchStatus("TrueNumInteractions",1);
  ntuple->fChain->SetBranchStatus("NVtx",1);
  ntuple->fChain->SetBranchStatus("JetID*",1);
  ntuple->fChain->SetBranchStatus("ZCandidates",1); //new
  ntuple->fChain->SetBranchStatus("NonPrefiringProb",1);
  ntuple->fChain->SetBranchStatus("NonPrefiringProbUp",1);
  ntuple->fChain->SetBranchStatus("NonPrefiringProbDn",1);
  ntuple->fChain->SetBranchStatus("HTRatioDPhiFilter",1);
  //ntuple->fChain->SetBranchStatus("BTags",1);
  ntuple->fChain->SetBranchStatus("MET",1);
  ntuple->fChain->SetBranchStatus("METPhi",1);
  ntuple->fChain->SetBranchStatus("HTclean",1);
  ntuple->fChain->SetBranchStatus("NJetsclean",1);
  ntuple->fChain->SetBranchStatus("BTagsclean",1);
  ntuple->fChain->SetBranchStatus("METclean",1);
  ntuple->fChain->SetBranchStatus("METPhiclean",1);
  ntuple->fChain->SetBranchStatus("CaloMET",1);
  ntuple->fChain->SetBranchStatus("NumInteractions",1);
  ntuple->fChain->SetBranchStatus("nAllVertices",1);
  ntuple->fChain->SetBranchStatus("NJetsISR",1);
  ntuple->fChain->SetBranchStatus("madMinDeltaRStatus",1);


 // ntuple->fChain->SetBranchStatus("Photon*",1);
 // ntuple->fChain->SetBranchStatus("DeltaPhi*",1);
 // ntuple->fChain->SetBranchStatus("TriggerNames",1); 
 // ntuple->fChain->SetBranchStatus("TriggerPass",1);
 // ntuple->fChain->SetBranchStatus("MHT",1);
 // ntuple->fChain->SetBranchStatus("HT",1);
 // ntuple->fChain->SetBranchStatus("NJets",1);
 // ntuple->fChain->SetBranchStatus("BTags",1);
 // ntuple->fChain->SetBranchStatus("MET",1);
 // ntuple->fChain->SetBranchStatus("MHT",1);
 // ntuple->fChain->SetBranchStatus("METPhi",1);

 // ntuple->fChain->SetBranchStatus("HTclean",1);
 // ntuple->fChain->SetBranchStatus("NJetsclean",1);
 // ntuple->fChain->SetBranchStatus("BTagsclean",1);
 // ntuple->fChain->SetBranchStatus("METclean",1);
 // ntuple->fChain->SetBranchStatus("METPhiclean",1);

 // ntuple->fChain->SetBranchStatus("JetsAK8*",1);
 // ntuple->fChain->SetBranchStatus("Jets*",1);
 // ntuple->fChain->SetBranchStatus("Weight",1);  
 // ntuple->fChain->SetBranchStatus("puWeightNew",1);  
 // ntuple->fChain->SetBranchStatus("TrueNumInteractions",1);  
 // ntuple->fChain->SetBranchStatus("TriggerPass",1);  
 // ntuple->fChain->SetBranchStatus("HBHENoiseFilter",1);
 // ntuple->fChain->SetBranchStatus("HBHEIsoNoiseFilter",1);
 // ntuple->fChain->SetBranchStatus("eeBadScFilter",1);
 // ntuple->fChain->SetBranchStatus("EcalDeadCellTriggerPrimitiveFilter",1);
 // ntuple->fChain->SetBranchStatus("BadPFMuonFilter",1);
 // ntuple->fChain->SetBranchStatus("BadChargedCandidateFilter",1);
 // ntuple->fChain->SetBranchStatus("globalTightHalo2016Filter",1);
 // ntuple->fChain->SetBranchStatus("CaloMET",1);
 // ntuple->fChain->SetBranchStatus("NVtx",1);
 // ntuple->fChain->SetBranchStatus("NumInteractions",1);
 // ntuple->fChain->SetBranchStatus("nAllVertices",1);
 // ntuple->fChain->SetBranchStatus("JetID*",1);
 // ntuple->fChain->SetBranchStatus("madHT",1);
 // ntuple->fChain->SetBranchStatus("NJetsISR",1);
 // ntuple->fChain->SetBranchStatus("madMinDeltaRStatus",1);
 // ntuple->fChain->SetBranchStatus("madMinPhotonDeltaR",1);

 // ntuple->fChain->SetBranchStatus("GenParticles*",1);
}

/***************************************************************/
/* - - - - - - - - - - - - gen-level cuts - - - - - - - - - -  */
/***************************************************************/

template<typename ntupleType> double FillGenWPt(ntupleType* ntuple){
    //cout << "FillGenWPt:" << endl;
    if( ntuple->GenParticles == NULL ) return -999.;
    double pt = -999.;
    for( unsigned int p = 0 ; p < ntuple->GenParticles->size() ; p++ ){
        if( abs(ntuple->GenParticles_PdgId->at(p)) == 24 ){
            //std::cout << "pt: " << ntuple->GenParticles->at(p).Pt() << std::endl;
            pt = ntuple->GenParticles->at(p).Pt();
        }
    }
    return pt; 
}

template<typename ntupleType> double FillGenZPt(ntupleType* ntuple){
    //cout << "FillGenZPt:" << endl;
    if( ntuple->GenParticles == NULL ) return -999.;
    double pt = -999.;
    for( unsigned int p = 0 ; p < ntuple->GenParticles->size() ; p++ ){
        if( abs(ntuple->GenParticles_PdgId->at(p)) == 23 ){
            //std::cout << "pt: " << ntuple->GenParticles->at(p).Pt() << std::endl;
            pt = ntuple->GenParticles->at(p).Pt();
        }
    }
    return pt; 
}

template<typename ntupleType> bool genWmatched(ntupleType* ntuple){
    if( ntuple->JetsAK8->size() == 0 ) return false;
    
    for( int i=0 ; i < ntuple->GenParticles->size() ; i++ ){
        if( abs(ntuple->GenParticles_PdgId->at(i)) == 24 && ntuple->JetsAK8->at(0).DeltaR(ntuple->GenParticles->at(i))<0.4)
            return true;
    }
    return false;
}

template<typename ntupleType> bool genTmatched(ntupleType* ntuple){
    if( ntuple->JetsAK8->size() == 0 ) return false;
    
    for( int i=0 ; i < ntuple->GenParticles->size() ; i++ ){
        if( abs(ntuple->GenParticles_PdgId->at(i)) == 6 && ntuple->JetsAK8->at(0).DeltaR(ntuple->GenParticles->at(i))<0.4)
            return true;
    }
    return false;
}

template<typename ntupleType> int getNumGenHiggses(ntupleType* ntuple){
    int numHiggses=0;
    for( int i=0 ; i < ntuple->GenParticles->size() ; i++ ){
        if( ntuple->GenParticles_PdgId->at(i) == 25 && 
            ntuple->GenParticles_ParentId->at(i) == 1000023 && 
            ntuple->GenParticles_Status->at(i) == 22 )
            numHiggses++;
    }
    return numHiggses;
}

template<typename ntupleType> int getNumGenZs(ntupleType* ntuple){
    int numZs=0;
    for( int i=0 ; i < ntuple->GenParticles->size() ; i++ ){
        if( ntuple->GenParticles_PdgId->at(i) == 23 && 
            ntuple->GenParticles_ParentId->at(i) == 1000023 && 
            ntuple->GenParticles_Status->at(i) == 22 )
            numZs++;    
    }
    return numZs;
}

template<typename ntupleType> bool genLevelHHcut(ntupleType* ntuple){
    int numHiggses=getNumGenHiggses(ntuple),numZs=getNumGenZs(ntuple);
    if(numHiggses==2 && numZs==0) return true;
    else return false;
}

template<typename ntupleType> bool genLevelZHcut(ntupleType* ntuple){
    int numHiggses=getNumGenHiggses(ntuple),numZs=getNumGenZs(ntuple);
    if(numHiggses==1 && numZs==1) return true;
    else return false;
}

template<typename ntupleType> bool genLevelZZcut(ntupleType* ntuple){
    int numHiggses=getNumGenHiggses(ntuple),numZs=getNumGenZs(ntuple);
    if(numHiggses==0 && numZs==2) return true;
    else return false;
}

/***************************************************************/
/* - - - - - - - - - - - - custom weights - - - - - - - - - -  */
/***************************************************************/
template<typename ntupleType> double GJetsNLOWeights(ntupleType* ntuple){
    if( ntuple->Photons->size() == 0 ) return 0.;
    double photon_pt = -999.;//ntuple->Photons->at(0).Pt();
    int photonIndex=-1;
    for( unsigned int p = 0 ; p < ntuple->GenParticles->size() ; p++ ){
        if( abs(ntuple->GenParticles_PdgId->at(p)) == 22 ){
            if( photonIndex < 0 )
                photonIndex = p;
            else if( ntuple->GenParticles->at(p).Pt() > ntuple->GenParticles->at(photonIndex).Pt() )
                photonIndex = p;
        }
    }               
    photon_pt = ntuple->GenParticles->at(photonIndex).Pt();
    
    if( photon_pt>150. ){
        double LO = GJets_LO->GetBinContent( GJets_LO->FindBin(photon_pt) );
        double NLO = GJets_NLO->GetBinContent( GJets_NLO->FindBin(photon_pt) );
        return (LO==0?0.:NLO/LO);
    }else
        return GJets_NLO->GetBinContent(1)/GJets_LO->GetBinContent(1);
}

template<typename ntupleType> double WJetsNLOWeights(ntupleType* ntuple){
    double Wpt=-999.;
    for( unsigned int p = 0 ; p < ntuple->GenParticles->size() ; p++ ){
        if( abs(ntuple->GenParticles_PdgId->at(p)) == 24 )
            Wpt = ntuple->GenParticles->at(p).Pt();
    }
    if( Wpt>150. ){
        double LO = WJets_LO->GetBinContent( WJets_LO->FindBin(Wpt) );
        double NLO = WJets_NLO->GetBinContent( WJets_NLO->FindBin(Wpt) );
        return (LO==0?0.:NLO/LO/1.21);
    }else
        return WJets_NLO->GetBinContent(1)/WJets_LO->GetBinContent(1)/1.21;
}

template<typename ntupleType> double ZJetsNLOWeights(ntupleType* ntuple){
    double Zpt=-999.;
    for( unsigned int p = 0 ; p < ntuple->GenParticles->size() ; p++ ){
        if( abs(ntuple->GenParticles_PdgId->at(p)) == 23 )
            Zpt = ntuple->GenParticles->at(p).Pt();
    }
    if( Zpt>150. ){
        double LO = ZJets_LO->GetBinContent( ZJets_LO->FindBin(Zpt) );
        double NLO = ZJets_NLO->GetBinContent( ZJets_NLO->FindBin(Zpt) );
        return (LO==0?0.:NLO/LO/1.23);
    }else
        return ZJets_NLO->GetBinContent(1)/ZJets_LO->GetBinContent(1)/1.23;
}

template<typename ntupleType> double singleMuonTrigWeights(ntupleType* ntuple){
    if( ntuple->Muons->size() == 0 ) return 0.;
    else if( ntuple->HT > 300. ){
        if( ntuple->HT < 500.){
            if( ntuple->Muons->at(0).Pt() > 25. ){
                if( ntuple->Muons->at(0).Pt() < 30. ){
                    return .787;
                }else if( ntuple->Muons->at(0).Pt() < 50. ){
                    return .843;
                }else{
                    return .908;
                }
            }else{
                return 0.;
            }
        }else if( ntuple->HT > 500. ){
            return .949;
        }else{
            return 0.;
        }
    }
}

template<typename ntupleType> double singleElectronTrigWeights(ntupleType* ntuple){
    if( ntuple->Electrons->size() == 0 ) return 0.;
    else if( ntuple->HT > 450. ){
        
        //cout << "ntuple->HT: " << ntuple->HT << endl;
        //cout << "ntuple->Electrons->at(0).Pt(): " << ntuple->Electrons->at(0).Pt() << endl;

        if( ntuple->Electrons->at(0).Pt() > 25. ){
            if( ntuple->Electrons->at(0).Pt() < 30. ){
                return 0.794;
            }else if( ntuple->Electrons->at(0).Pt() < 40. ){
                return 0.826;
            }else if( ntuple->Electrons->at(0).Pt() < 50. ){
                return 0.872;
            }else if( ntuple->Electrons->at(0).Pt() < 75. ){
                return 0.884;
            }else if( ntuple->Electrons->at(0).Pt() < 100. ){
                return 0.913;
            }else{
                return 0.947;
            }
        }else{
            return 0.;
        }
    }else if( ntuple->HT > 300. ){

        //cout << "ntuple->HT: " << ntuple->HT << endl;
        //cout << "ntuple->Electrons->at(0).Pt(): " << ntuple->Electrons->at(0).Pt() << endl;

        if( ntuple->Electrons->at(0).Pt() > 25. ){
            if( ntuple->Electrons->at(0).Pt() < 30. ){
                return 0.572;
            }else if( ntuple->Electrons->at(0).Pt() < 40. ){
                return 0.775;
            }else if( ntuple->Electrons->at(0).Pt() < 50. ){
                return 0.858;
            }else if( ntuple->Electrons->at(0).Pt() < 75. ){
                return 0.861;
            }else if( ntuple->Electrons->at(0).Pt() < 100. ){
                return 0.932;
            }else{
                return 1.;
            }  
        }else{
            return 0.;
        }
    }else{
        return 0.;
    }
}

template<typename ntupleType> double lowDphiTrigWeights(ntupleType* ntuple){
    if( ntuple->MET>100. ){
        if( ntuple->MET<200. ){
            return 0.500;
        }else if( ntuple->MET<300. ){
            return 0.712;
        }else if( ntuple->MET<400. ){
            return 0.806;
        }else if( ntuple->MET<500. ){
            return 0.874;
        }else if( ntuple->MET<700. ){
            return 0.866;
        }else{
            return 0.766;
        }
    }else
        return 0.;
}

template<typename ntupleType> double customPUweights(ntupleType* ntuple){
    int nVtx = ntuple->TrueNumInteractions;
    return puWeightHist->GetBinContent(puWeightHist->GetXaxis()->FindBin(min(ntuple->TrueNumInteractions,puWeightHist->GetBinLowEdge(puWeightHist->GetNbinsX()+1))));
}

enum ISRweightType {kNom,kUp,kDn};
template<typename ntupleType> double ISRweights(ntupleType* ntuple, ISRweightType wType = kNom ){

    double wanted_w_isr=1.;
    double wanted_sys_isr[2]={1.,1.};

    TString sample = ntuple->fChain->GetFile()->GetName();

    // these are taken from here:
    // https://github.com/manuelfs/babymaker/blob/3a57e1bace6c52832fe40e401cf37bc6b50923c3/bmaker/genfiles/src/change_weights.cxx#L156-L175
    // via Manuel Franco Sevilla
    if(sample.Contains("TTJets_HT-600to800")) {
        wanted_w_isr = 0.7838;
        wanted_sys_isr[0] = 0.8965;
        wanted_sys_isr[1] = 0.6604;
    }else if(sample.Contains("TTJets_HT-800to1200")) {
        wanted_w_isr = 0.7600;
        wanted_sys_isr[0] = 0.8851;
        wanted_sys_isr[1] = 0.6230;
    }else if(sample.Contains("TTJets_HT-1200to2500")) {
        wanted_w_isr = 0.7365;
        wanted_sys_isr[0] = 0.8739;
        wanted_sys_isr[1] = 0.5861;
    }else if(sample.Contains("TTJets_HT-2500toInf")) {
        wanted_w_isr = 0.7254;
        wanted_sys_isr[0] = 0.8686;
        wanted_sys_isr[1] = 0.5687;
    }else{ //  if(sample.Contains("TTJets_SingleLept") or sample.Contains("TTJets_DiLept") ){
        // these numbers should really only be applied to the inclusive sample
        wanted_w_isr = 1.071;
        wanted_sys_isr[0] = 1.071;
        wanted_sys_isr[1] = 1.071;
    }
    
    double D;
    if( wType == kNom ) D = wanted_w_isr;
    else D = wanted_sys_isr[wType-1];

    double w[6]={0.920,0.821,0.715,0.662,0.561,0.511};
    if( ntuple->NJetsISR == 0 )
        return D;
    else if( ntuple->NJetsISR >= 6 )
        return w[5]*D;
    else 
        return w[ntuple->NJetsISR]*D;
}

//////////////////////
// Lepton functions //
//////////////////////


template<typename ntupleType> double computeRecoil(ntupleType* ntuple){ 
    if( ntuple->Muons->size() == 0 ) return -9999.;
    double lepPt = ntuple->Muons->at(0).Pt();
    double lepPhi = ntuple->Muons->at(0).Phi(); 
    double MET = ntuple->MET;
    double METPhi = ntuple->METPhi;
    double rx=MET*cos(METPhi);
    double ry=MET*sin(METPhi);
    for(int i=0; i<ntuple->Muons->size(); i++) {
       double lepPt = ntuple->Muons->at(i).Pt();
       double lepPhi = ntuple->Muons->at(i).Phi(); 
       rx=rx+lepPt*cos(lepPhi);
       ry=ry+lepPt*sin(lepPhi);
    }
    return sqrt(rx*rx+ry*ry);
}


template<typename ntupleType> double computeMuonMT(ntupleType* ntuple){ 
    if( ntuple->Muons->size() == 0 ) return -9999.;
    double lepPt = ntuple->Muons->at(0).Pt();
    double lepPhi = ntuple->Muons->at(0).Phi(); 
    double MET = ntuple->MET;
    double METPhi = ntuple->METPhi;
    return sqrt( 2*lepPt*MET * ( 1 - cos( METPhi-lepPhi ) ) );
}


template<typename ntupleType> double computeDimuonMass(ntupleType* ntuple){
    if( ntuple->Muons->size() != 2 ) return -9999.;
    double muPt1 = ntuple->Muons->at(0).Pt();
    double muPhi1 = ntuple->Muons->at(0).Phi();
    double muEta1 = ntuple->Muons->at(0).Eta();
    double muPt2 = ntuple->Muons->at(1).Pt();
    double muPhi2 = ntuple->Muons->at(1).Phi();
    double muEta2 = ntuple->Muons->at(1).Eta();
    double muMass = 0.106;
    TLorentzVector v1, v2;
    v1.SetPtEtaPhiM(muPt1,muEta1,muPhi1,muMass);
    v2.SetPtEtaPhiM(muPt2,muEta2,muPhi2,muMass);
    return (v1+v2).M();
    
}



////////////////////////////////////////////////////////////
// - - - - - - - - EVENT LEVEL VARIABLES - - - - - - - -  //
////////////////////////////////////////////////////////////

// AK4 Jets Pt

template<typename ntupleType> double fillJetPt1(ntupleType* ntuple){
    if( ntuple->Jets->size() >= 1) 
        return ntuple->Jets->at(0).Pt();
    else 
        return -999.;
}

template<typename ntupleType> double fillJetEta1(ntupleType* ntuple){
    if(ntuple->Jets->size() >= 1)
       return ntuple->Jets->at(0).Eta();
    else 
        return -999.;
}

template<typename ntupleType> double fillJet1CHF(ntupleType* ntuple){
    if( ntuple->Jets_chargedHadronEnergyFraction->size() >= 1)
        return ntuple->Jets_chargedHadronEnergyFraction->at(0);
    else
        return -999.;
}



template<typename ntupleType> double fillJet1NHF(ntupleType* ntuple){
    if( ntuple->Jets_neutralHadronEnergyFraction->size() >= 1)
        return ntuple->Jets_neutralHadronEnergyFraction->at(0);
    else
        return -999.;
}


template<typename ntupleType> double fillJet1CEMF(ntupleType* ntuple){
    if( ntuple->Jets_chargedEmEnergyFraction->size() >= 1)
        return ntuple->Jets_chargedEmEnergyFraction->at(0);
    else
        return -999.;
}

template<typename ntupleType> double fillJet1NEMF(ntupleType* ntuple){
    if( ntuple->Jets_neutralEmEnergyFraction->size() >= 1)
        return ntuple->Jets_neutralEmEnergyFraction->at(0);
    else
        return -999.;
}

template<typename ntupleType> double fillJetPt2(ntupleType* ntuple){
    if( ntuple->Jets->size() >= 2) 
        return ntuple->Jets->at(1).Pt();
    else 
        return -999.;
}

template<typename ntupleType> double fillJetPt3(ntupleType* ntuple){
    if( ntuple->Jets->size() >= 3) 
        return ntuple->Jets->at(2).Pt();
    else 
        return -999.;
}

template<typename ntupleType> double fillJetPt4(ntupleType* ntuple){
    if( ntuple->Jets->size() >= 4) 
        return ntuple->Jets->at(3).Pt();
    else 
        return -999.;
}

// End of 4 AK4 Jets Pt


// For Leptons

template<typename ntupleType> double fillDimuonMass(ntupleType* ntuple){
  return computeDimuonMass(ntuple);
}


//Muon Distributions

//mu1 pt

template<typename ntupleType> double fillMuonPt1(ntupleType* ntuple){
    if( ntuple->Muons->size() >= 1)
        return ntuple->Muons->at(0).Pt();
    else
        return -999.;
}

//mu1 eta

template<typename ntupleType> double fillMuonEta1(ntupleType* ntuple){
    if( ntuple->Muons->size() >= 1)
        return ntuple->Muons->at(0).Eta();
    else
        return -999.;
}

//mu1 phi

template<typename ntupleType> double fillMuonPhi1(ntupleType* ntuple){
    if( ntuple->Muons->size() >= 1)
        return ntuple->Muons->at(0).Phi();
    else
        return -999.;
}

//mu2 pt

template<typename ntupleType> double fillMuonPt2(ntupleType* ntuple){
    if( ntuple->Muons->size() >= 2)
        return ntuple->Muons->at(1).Pt();
    else
        return -999.;
}

//mu2 eta

template<typename ntupleType> double fillMuonEta2(ntupleType* ntuple){
    if( ntuple->Muons->size() >= 2)
        return ntuple->Muons->at(1).Eta();
    else
        return -999.;
}

//mu2 phi

template<typename ntupleType> double fillMuonPhi2(ntupleType* ntuple){
    if( ntuple->Muons->size() >= 2)
        return ntuple->Muons->at(1).Phi();
    else
        return -999.;
}


//Filling Electron

//elec1 pt

template<typename ntupleType> double fillElecPt1(ntupleType* ntuple){
    if( ntuple->Electrons->size() >= 1)
        return ntuple->Electrons->at(0).Pt();
    else
        return -999.;
}

//elec1 eta

template<typename ntupleType> double fillElecEta1(ntupleType* ntuple){
    if( ntuple->Electrons->size() >= 1)
        return ntuple->Electrons->at(0).Eta();
    else
        return -999.;
}

//elec1 phi

template<typename ntupleType> double fillElecPhi1(ntupleType* ntuple){
    if( ntuple->Electrons->size() >= 1)
        return ntuple->Electrons->at(0).Phi();
    else
        return -999.;
}

//elec2 pt

template<typename ntupleType> double fillElecPt2(ntupleType* ntuple){
    if( ntuple->Electrons->size() >= 2)
        return ntuple->Electrons->at(1).Pt();
    else
        return -999.;
}

//elec2 eta

template<typename ntupleType> double fillElecEta2(ntupleType* ntuple){
    if( ntuple->Electrons->size() >= 2)
        return ntuple->Electrons->at(1).Eta();
    else
        return -999.;
}

//elec2 phi

template<typename ntupleType> double fillElecPhi2(ntupleType* ntuple){
    if( ntuple->Electrons->size() >= 2)
        return ntuple->Electrons->at(1).Phi();
    else
        return -999.;
}

// End of Leptons


template<typename ntupleType> double fillNVtx(ntupleType* ntuple){
  return ntuple->NVtx;
}

template<typename ntupleType> double fillnAllVertices(ntupleType* ntuple){
  return ntuple->nAllVertices;
}

template<typename ntupleType> double fillNumInteractions(ntupleType* ntuple){
  return ntuple->NumInteractions;
}

template<typename ntupleType> double fillMadHT(ntupleType* ntuple){
  return ntuple->madHT;
}

template<typename ntupleType> double fillDeltaPhi1(ntupleType* ntuple){
  //return ntuple->DeltaPhi1;
  if( ntuple->Jets->size() == 0 ) return 0.;  
  double phi1 = ntuple->Jets->at(0).Phi();  
  double phi2 = ntuple->METPhi;  
  double Dphi1 = CalcdPhi(phi1, phi2);  
  return Dphi1;	
}

template<typename ntupleType> double fillDeltaPhi2(ntupleType* ntuple){
  //return ntuple->DeltaPhi2;
  if( ntuple->Jets->size() <2 ) return 0.;  
  double phi1 = ntuple->Jets->at(1).Phi();  
  double phi2 = ntuple->METPhi;  
  double Dphi2 = CalcdPhi(phi1, phi2);  
  return Dphi2;	
}

template<typename ntupleType> double fillDeltaPhi3(ntupleType* ntuple){
  //return ntuple->DeltaPhi3;
  if( ntuple->Jets->size() <3 ) return 0.;  
  double phi1 = ntuple->Jets->at(2).Phi();  
  double phi2 = ntuple->METPhi;  
  double Dphi3 = CalcdPhi(phi1, phi2);  
  return Dphi3;	
}

template<typename ntupleType> double fillDeltaPhi4(ntupleType* ntuple){
  //return ntuple->DeltaPhi4;
  if( ntuple->Jets->size() <4 ) return 0.;  
  double phi1 = ntuple->Jets->at(3).Phi();  
  double phi2 = ntuple->METPhi;  
  double Dphi4 = CalcdPhi(phi1, phi2);  
  return Dphi4;	
}

template<typename ntupleType> double fillDeltaPhi1clean(ntupleType* ntuple){
  return ntuple->DeltaPhi1clean;
}

template<typename ntupleType> double fillHT(ntupleType* ntuple){
  return ntuple->HT;
}

template<typename ntupleType> double fillHTclean(ntupleType* ntuple){
  return ntuple->HTclean;
}

template<typename ntupleType> double fillMHT(ntupleType* ntuple){
  return ntuple->MHT;
}

template<typename ntupleType> double fillMET(ntupleType* ntuple){
  return ntuple->MET;
}

template<typename ntupleType> double fillMETclean(ntupleType* ntuple){
  return ntuple->METclean;
}

template<typename ntupleType> double fillOne(ntupleType* ntuple){
  return 1.;
}

template<typename ntupleType> double fillNJets(ntupleType* ntuple){
  return ntuple->NJets;
}

template<typename ntupleType> double fillNJetsclean(ntupleType* ntuple){
  return ntuple->NJetsclean;
}

template<typename ntupleType> double fillBTags(ntupleType* ntuple){
  return ntuple->BTags;
}

////////////////////////////////
// HIGHEST PT JET PROPERTIES  //
////////////////////////////////
template<typename ntupleType> double fillLeadingJetMinDRB(ntupleType* ntuple){
    if( ntuple->JetsAK8->size() == 0 ) return -999.;
    else{
        double minDRB = 999.;
        double DRB = 999.;
        for( int i = 0 ; i < ntuple->Jets->size() ; i++ ){
            DRB = 999.;            
            if( abs(ntuple->Jets_partonFlavor->at(i)) == 5 ){
                DRB = ntuple->JetsAK8->at(0).DeltaR(ntuple->Jets->at(i));
            }
            if( DRB < minDRB ) 
                minDRB = DRB;
        }
        return minDRB;
    }
}


template<typename ntupleType> bool FiltersCut(ntupleType* ntuple){
    return (	ntuple->HBHENoiseFilter==1 && 
        	ntuple->HBHEIsoNoiseFilter==1 && 
        	ntuple->eeBadScFilter==1 && 
        	ntuple->EcalDeadCellTriggerPrimitiveFilter == 1 && 
        	ntuple->NVtx>0 && 
        	ntuple->MET/ntuple->CaloMET < 5. &&
        	//ntuple->PFCaloMETRatio < 5. &&
        	ntuple->BadPFMuonFilter == 1 &&
        	ntuple->BadChargedCandidateFilter == 1 &&
        	ntuple->globalSuperTightHalo2016Filter == 1);
        	//ntuple->globalTightHalo2016Filter == 1);
}

template<typename ntupleType> bool BTagsCut(ntupleType* ntuple){
  return ntuple->BTags>0 ; 
}

template<typename ntupleType> bool DeltaPhi1Cut(ntupleType* ntuple){
  return fillDeltaPhi1(ntuple)>0.5;
}

template<typename ntupleType> bool DeltaPhi2Cut(ntupleType* ntuple){
  return fillDeltaPhi2(ntuple)>0.5;
}

template<typename ntupleType> bool DeltaPhi3Cut(ntupleType* ntuple){
  return fillDeltaPhi3(ntuple)>0.5;
}

template<typename ntupleType> bool DeltaPhi4Cut(ntupleType* ntuple){
  return fillDeltaPhi4(ntuple)>0.5;
}

template<typename ntupleType> bool DeltaPhiCuts(ntupleType* ntuple){
    return ( DeltaPhi1Cut(ntuple) &&
             DeltaPhi2Cut(ntuple) &&
             DeltaPhi3Cut(ntuple) &&
             DeltaPhi4Cut(ntuple) ) ;
}             

template<typename ntupleType> bool lowDPhiCuts(ntupleType* ntuple){
    return !DeltaPhiCuts(ntuple);
}


template<typename ntupleType> bool AK4JetPtCut(ntupleType* ntuple){
  return ( ntuple->Jets->size() >= 1 &&
	   ntuple->Jets->at(0).Pt() > 100. &&
	   fabs(ntuple->Jets->at(0).Eta()) < 2.5 &&					
	   ntuple->Jets_chargedHadronEnergyFraction->at(0) >0.1 &&		
	   ntuple->Jets_neutralHadronEnergyFraction->at(0) <0.8 		
	);
}



template<typename ntupleType> bool AK4JetPtCutWithoutCHF(ntupleType* ntuple){
  return ( ntuple->Jets->size() >= 1 &&
           ntuple->Jets->at(0).Pt() > 100. &&
           fabs(ntuple->Jets->at(0).Eta()) < 2.5
        );
}

template<typename ntupleType> bool METCut(ntupleType* ntuple){
  return ( ntuple->MET > 250.);
}

template<typename ntupleType> bool RecoilCut(ntupleType* ntuple){
  return ( computeRecoil(ntuple) > 250.);
}

template<typename ntupleType> double fillZMT(ntupleType* ntuple){
     if( ntuple->Jets->size() == 0 ) return 0.;
     double AK4Pt = ntuple->Jets->at(0).Pt();
     double AK4Phi = ntuple->Jets->at(0).Phi();
     double MET = ntuple->MET;
     double METPhi = ntuple->METPhi;
     return ZMT(AK4Pt, AK4Phi, MET, METPhi);
     //return sqrt( 2*AK8Pt*MET * ( 1 - cos( DeltaPhiAK8JMETCut(ntuple)) ) );
}


// 1) Monojet cut
template<typename ntupleType> bool baselineCutMonojetZMuMu(ntupleType* ntuple){
  return ( //METCut(ntuple)  &&
          // RecoilCut(ntuple)  &&
           AK4JetPtCut(ntuple) && 
           DeltaPhiCuts(ntuple) &&
           ntuple->Photons->size()==0 &&  
          // ntuple->Muons->size()==0 &&
          // ntuple->Electrons->size()==0 &&
           ntuple->BTags == 0 && 
           ntuple->isoElectronTracks==0 && ntuple->isoPionTracks==0 &&
           FiltersCut(ntuple) &&
           ntuple->JetID == 1);
}
 
template<typename ntupleType> bool baselineCutMonojet(ntupleType* ntuple){
  return ( METCut(ntuple)  &&
           AK4JetPtCut(ntuple) &&
           DeltaPhiCuts(ntuple) &&
           ntuple->Photons->size()==0 &&
           ntuple->Muons->size()==0 &&
           ntuple->Electrons->size()==0 &&
           ntuple->BTags == 0 &&
           ntuple->isoElectronTracks==0 && ntuple->isoMuonTracks==0 && ntuple->isoPionTracks==0 &&
           FiltersCut(ntuple) &&
           ntuple->JetID == 1);
}

template<typename ntupleType> bool baselineCutMonojet_MinusCHF(ntupleType* ntuple){
  return ( METCut(ntuple)  &&
           AK4JetPtCutWithoutCHF(ntuple) &&
           DeltaPhiCuts(ntuple) &&
           ntuple->Photons->size()==0 &&
           ntuple->Muons->size()==0 &&
           ntuple->Electrons->size()==0 &&
           ntuple->BTags == 0 &&
           ntuple->isoElectronTracks==0 && ntuple->isoMuonTracks==0 && ntuple->isoPionTracks==0 &&
           FiltersCut(ntuple) &&
           ntuple->JetID == 1);
}
 
template<typename ntupleType> bool singleMuCut(ntupleType* ntuple){
    if( ntuple->Muons->size() != 1 || ntuple->Electrons->size() != 0 ) return false;
    double MT = computeMuonMT(ntuple);
    return ntuple->Muons->at(0).Pt()>25. &&
           MT < 100.;

}


template<typename ntupleType> bool doubleMuCut(ntupleType* ntuple){
    if( ntuple->Muons->size() != 2 || ntuple->Electrons->size() != 0 ) return false;
   // double MT = computeMuonMT(ntuple);
    return ntuple->Muons->at(0).Pt()>25. && ntuple->Muons->at(1).Pt()>10.;

}


template<typename ntupleType> bool singleMuBaselineCut(ntupleType* ntuple){

    return ( singleMuCut(ntuple) && 
             ntuple->MET > 100.             &&
             ntuple->HT > 600.                         &&
             ntuple->JetsAK8->size() >= 2 &&
             ntuple->JetsAK8->at(0).Pt() > 300. && 
             ntuple->JetsAK8_prunedMass->at(0) > 50. && 
             ntuple->JetsAK8_prunedMass->at(0) < 250. && 
             ntuple->JetsAK8->at(1).Pt() > 300. &&
             ntuple->JetsAK8_prunedMass->at(1) > 50. && 
             ntuple->JetsAK8_prunedMass->at(1) < 250.&&
             DeltaPhiCuts( ntuple ) && 
             FiltersCut(ntuple) &&
             ntuple->JetID == 1);
    
}

template<typename ntupleType> bool ZMuMuBaselineCut(ntupleType* ntuple){

   double ZMass=computeDimuonMass(ntuple); 
        //return ( baselineCutMonojetZMuMu(ntuple)&& doubleMuCut(ntuple));
        return ( baselineCutMonojetZMuMu(ntuple));
            // ZMass > 60. && ZMass < 110. ); 
}


template<typename ntupleType> bool singleEleCut(ntupleType* ntuple){
    if( ntuple->Muons->size() != 0 || ntuple->Electrons->size() != 1 ) return false;
    double MT = computeElectronMT(ntuple);
    return ( ntuple->Electrons->at(0).Pt()>25. && 
             MT < 100. ) ;
}
template<typename ntupleType> bool singleEleBaselineCut(ntupleType* ntuple){


    return ( singleEleCut(ntuple) && 
             ntuple->MET > 100.             &&
             ntuple->HT > 600.                         &&
             ntuple->JetsAK8->size() >= 2 &&
             ntuple->JetsAK8->at(0).Pt() > 300. && 
             ntuple->JetsAK8_prunedMass->at(0) > 50. && 
             ntuple->JetsAK8_prunedMass->at(0) < 250. && 
             ntuple->JetsAK8->at(1).Pt() > 300. &&
             ntuple->JetsAK8_prunedMass->at(1) > 50. && 
             ntuple->JetsAK8_prunedMass->at(1) < 250.&&
             DeltaPhiCuts( ntuple ) && 
             FiltersCut(ntuple) &&
             ntuple->JetID == 1);
    
}

template<typename ntupleType> bool lowDphiBaselineCut(ntupleType* ntuple){

    return ( ntuple->MET > 300.             &&
             ntuple->HT > 600.                         &&
             ntuple->JetsAK8->size() >= 2 &&
             ntuple->JetsAK8->at(0).Pt() > 300. && 
             ntuple->JetsAK8_prunedMass->at(0) > 50. && 
             ntuple->JetsAK8_prunedMass->at(0) < 250. && 
             ntuple->JetsAK8->at(1).Pt() > 300. &&
             ntuple->JetsAK8_prunedMass->at(1) > 50. && 
             ntuple->JetsAK8_prunedMass->at(1) < 250.&&
             ! DeltaPhiCuts( ntuple ) && 
             FiltersCut(ntuple) &&
             ntuple->JetID == 1);
}

template<typename ntupleType> bool photonBaselineCut(ntupleType* ntuple){
    return ( ntuple->Photons->size()==1 &&
             ntuple->Photons->at(0).Pt() > 100. && 
             ntuple->Photons_fullID->size() == 1 && 
             ntuple->Photons_fullID->at(0) == 1 &&
             ntuple->METclean > 100.             &&
             ntuple->HTclean > 400.                         &&
             ntuple->JetsAK8Clean->size()>=2 && 
             ntuple->JetsAK8Clean->at(0).Pt() > 300. && 
             ntuple->JetsAK8Clean_prunedMass->at(0) > 50. && 
             ntuple->JetsAK8Clean_prunedMass->at(0) < 250. && 
             ntuple->JetsAK8Clean->at(1).Pt() > 300. &&
             ntuple->JetsAK8Clean_prunedMass->at(1) > 50. && 
             ntuple->JetsAK8Clean_prunedMass->at(1) < 250.&&
             ntuple->DeltaPhi1clean>0.5 && 
             ntuple->DeltaPhi2clean>0.5 &&
             ntuple->DeltaPhi3clean>0.3 && 
             ntuple->DeltaPhi4clean>0.3 &&
             ntuple->isoElectronTracksclean==0 &&
             ntuple->isoMuonTracksclean == 0 && 
             ntuple->isoPionTracksclean == 0 &&
             ntuple->Electrons->size() == 0 &&
             ntuple->Muons->size() == 0 && 
             FiltersCut(ntuple) &&
             ntuple->JetIDclean == 1);
}

template<typename ntupleType> bool photonBaselineCut_loose(ntupleType* ntuple){
    return ( ntuple->Photons->size()==1 &&
             ntuple->Photons->at(0).Pt() > 100. && 
             ntuple->Photons_fullID->size() == 1 && 
             ntuple->Photons_fullID->at(0) == 1 &&
             ntuple->METclean > 100.             &&
             ntuple->HTclean > 400.                         &&
             ntuple->JetsAK8Clean->size()>=2 && 
             ntuple->DeltaPhi1clean>0.5 && 
             ntuple->DeltaPhi2clean>0.5 &&
             ntuple->DeltaPhi3clean>0.3 && 
             ntuple->DeltaPhi4clean>0.3 &&
             ntuple->isoElectronTracksclean==0 &&
             ntuple->isoMuonTracksclean == 0 && 
             ntuple->isoPionTracksclean == 0 &&
             ntuple->Electrons->size() == 0 &&
             ntuple->Muons->size() == 0 && 
             FiltersCut(ntuple) &&
             ntuple->JetIDclean == 1);
}

template<typename ntupleType> bool leadJetTighMassCut(ntupleType* ntuple ){ 
    return ntuple->JetsAK8_doubleBDiscriminator->size()>=1 && 
           (ntuple->JetsAK8_prunedMass->at(0) > 85. && 
            ntuple->JetsAK8_prunedMass->at(0) < 135.);    
}

template<typename ntupleType> bool subleadJetTighMassCut(ntupleType* ntuple ){ 
    return ntuple->JetsAK8_doubleBDiscriminator->size()>=2 && 
           (ntuple->JetsAK8_prunedMass->at(1) > 85. && 
            ntuple->JetsAK8_prunedMass->at(1) < 135.);
}

template<typename ntupleType> bool singleHiggsTagLooseCut(ntupleType* ntuple ){ 
    return ( ntuple->JetsAK8_doubleBDiscriminator->size()>=2 &&
             ( ( ntuple->JetsAK8_doubleBDiscriminator->at(0) > bbtagCut ) 
             && ( ntuple->JetsAK8_doubleBDiscriminator->at(1) < bbtagCut ) ) ||
        ( ( ntuple->JetsAK8_doubleBDiscriminator->at(0) < bbtagCut ) 
          && ( ntuple->JetsAK8_doubleBDiscriminator->at(1) > bbtagCut ) ) );
}

template<typename ntupleType> bool OneOrMoreHiggsTagLooseCut(ntupleType* ntuple ){ 
    return ( ntuple->JetsAK8_doubleBDiscriminator->size()>=2 &&
             ( ntuple->JetsAK8_doubleBDiscriminator->at(0) > bbtagCut ||
               ntuple->JetsAK8_doubleBDiscriminator->at(1) > bbtagCut ) );
}

template<typename ntupleType> bool antiTaggingLooseCut(ntupleType* ntuple ){
    return ( ntuple->JetsAK8_doubleBDiscriminator->size()>=2 &&
             ( ( ntuple->JetsAK8_doubleBDiscriminator->at(0) < bbtagCut
               ) &&
             ( ntuple->JetsAK8_doubleBDiscriminator->at(1) < bbtagCut 
               ) ) ) ;
}

template<typename ntupleType> bool doubleTaggingLooseCut(ntupleType* ntuple ){
    return ( ntuple->JetsAK8_doubleBDiscriminator->size()>=2 &&
             ntuple->JetsAK8_doubleBDiscriminator->at(0) > bbtagCut && 
             ntuple->JetsAK8_doubleBDiscriminator->at(1) > bbtagCut );
}

template<typename ntupleType> bool doubleMassCut(ntupleType* ntuple ){
    return ( ntuple->JetsAK8_doubleBDiscriminator->size()>=2 &&
             ntuple->JetsAK8_prunedMass->at(0) > 85. &&
             ntuple->JetsAK8_prunedMass->at(0) < 135. &&
             ntuple->JetsAK8_prunedMass->at(1) > 85. &&
             ntuple->JetsAK8_prunedMass->at(1) < 135. 
             );
}

template<typename ntupleType> bool singleHiggsTagCut(ntupleType* ntuple ){
    return ntuple->JetsAK8_doubleBDiscriminator->size()>=2 && 
        ( (ntuple->JetsAK8_prunedMass->at(0) > 85. && 
           ntuple->JetsAK8_prunedMass->at(0) < 135. && 
           ntuple->JetsAK8_doubleBDiscriminator->at(0) > bbtagCut ) ||
          (ntuple->JetsAK8_prunedMass->at(1) > 85. && 
           ntuple->JetsAK8_prunedMass->at(1) < 135. && 
           ntuple->JetsAK8_doubleBDiscriminator->at(1) > bbtagCut ) );
}

template<typename ntupleType> bool doubleHiggsTagCut(ntupleType* ntuple ){
    return ntuple->JetsAK8_doubleBDiscriminator->size()>=2 &&
        ( ntuple->JetsAK8_prunedMass->at(0) > 85. && 
          ntuple->JetsAK8_prunedMass->at(0) < 135. && 
          ntuple->JetsAK8_doubleBDiscriminator->at(0) > bbtagCut &&
          ntuple->JetsAK8_prunedMass->at(1) > 85. && 
          ntuple->JetsAK8_prunedMass->at(1) < 135. && 
          ntuple->JetsAK8_doubleBDiscriminator->at(1) > bbtagCut ) ;
}

template<typename ntupleType> bool tagSR(ntupleType* ntuple, int i){
    if( ntuple->JetsAK8_doubleBDiscriminator->size() <= i || 
        ntuple->JetsAK8_prunedMass->size() <= i ) return false;
    return ( ntuple->JetsAK8_doubleBDiscriminator->at(i) > bbtagCut &&
             ntuple->JetsAK8_prunedMass->at(i) > 85. && 
             ntuple->JetsAK8_prunedMass->at(i) < 135. );
}

template<typename ntupleType> bool tagSB(ntupleType* ntuple, int i ){
    if( ntuple->JetsAK8_doubleBDiscriminator->size() <= i || 
        ntuple->JetsAK8_prunedMass->size() <= i ) return false;
    return ( ntuple->JetsAK8_doubleBDiscriminator->at(i) > bbtagCut && 
             (
              ( ntuple->JetsAK8_prunedMass->at(i) < 85. &&
                ntuple->JetsAK8_prunedMass->at(i) > 50. ) ||
              ( ntuple->JetsAK8_prunedMass->at(i) > 135. &&
                ntuple->JetsAK8_prunedMass->at(i) < 250. ) 
              ) 
             );
}

template<typename ntupleType> bool antitagSR(ntupleType* ntuple, int i){
        if( ntuple->JetsAK8_doubleBDiscriminator->size() <= i || 
        ntuple->JetsAK8_prunedMass->size() <= i ) return false;
    return ( ntuple->JetsAK8_doubleBDiscriminator->at(i) < bbtagCut &&
             ( ntuple->JetsAK8_prunedMass->at(i) > 85. &&
               ntuple->JetsAK8_prunedMass->at(i) < 135. ) );
}
        
template<typename ntupleType> bool antitagSB(ntupleType* ntuple, int i){
    if( ntuple->JetsAK8_doubleBDiscriminator->size() <= i || 
        ntuple->JetsAK8_prunedMass->size() <= i ) return false;
    return ( ntuple->JetsAK8_doubleBDiscriminator->at(i) < bbtagCut &&
             (
              ( ntuple->JetsAK8_prunedMass->at(i) < 85. &&
                ntuple->JetsAK8_prunedMass->at(i) > 50. ) ||
              ( ntuple->JetsAK8_prunedMass->at(i) > 135. &&
                ntuple->JetsAK8_prunedMass->at(i) < 250. ) 
              )
             );
}

template<typename ntupleType> bool antitagSRCut(ntupleType* ntuple){
    return ( antitagSR(ntuple,0)&&antitagSR(ntuple,1) );
}

template<typename ntupleType> bool antitagSBCut(ntupleType* ntuple){
    return ( ( antitagSB(ntuple,0)&&antitagSB(ntuple,1) ) ||
             ( antitagSB(ntuple,0)&&antitagSR(ntuple,1) ) ||
             ( antitagSR(ntuple,0)&&antitagSB(ntuple,1) ) );
}

template<typename ntupleType> bool tagSRCut(ntupleType* ntuple){
    return ( ( tagSR(ntuple,0)&&antitagSR(ntuple,1) ) || 
             ( antitagSR(ntuple,0)&&tagSR(ntuple,1) ) ) ;
}

template<typename ntupleType> bool tagSBCut(ntupleType* ntuple){
    return ( ( tagSB(ntuple,0)&&antitagSB(ntuple,1) ) ||
             ( tagSR(ntuple,0)&&antitagSB(ntuple,1) ) ||
             ( tagSB(ntuple,0)&&antitagSR(ntuple,1) ) ||
             ( antitagSB(ntuple,0)&&tagSB(ntuple,1) ) ||
             ( antitagSR(ntuple,0)&&tagSB(ntuple,1) ) ||
             ( antitagSB(ntuple,0)&&tagSR(ntuple,1) ) );

}

template<typename ntupleType> bool doubletagSRCut(ntupleType* ntuple){
    return ( tagSR(ntuple,0)&&tagSR(ntuple,1) );
}

template<typename ntupleType> bool doubletagSBCut(ntupleType* ntuple){
    return ( ( tagSB(ntuple,0)&&tagSB(ntuple,1) ) ||
             ( tagSB(ntuple,0)&&tagSR(ntuple,1) ) ||
             ( tagSR(ntuple,0)&&tagSB(ntuple,1) ) );
}

////////////////////////////////////////////////////////////////////////
// - - - - - - - - - - photon specializations - - - - - - - - - - - - //
////////////////////////////////////////////////////////////////////////
template<typename ntupleType> double fillPhotonPt(ntupleType* ntuple ){ 
    if( ntuple->Photons->size() == 0 )
        return -999.;
    else
        return ntuple->Photons->at(0).Pt();
}

template<typename ntupleType> bool singleHiggsTagLooseCut_photon(ntupleType* ntuple ){ 
  return ( ( ntuple->JetsAK8Clean_doubleBDiscriminator->at(0) > bbtagCut ) 
           && ( ntuple->JetsAK8Clean_doubleBDiscriminator->at(1) < bbtagCut ) ) || 
      ( ( ntuple->JetsAK8Clean_doubleBDiscriminator->at(0) < bbtagCut ) 
        && ( ntuple->JetsAK8Clean_doubleBDiscriminator->at(1) > bbtagCut ) );
}

template<typename ntupleType> bool antiTaggingLooseCut_photon(ntupleType* ntuple ){
    return ( ( ( ntuple->JetsAK8Clean_doubleBDiscriminator->at(0) < bbtagCut
               ) &&
             ( ntuple->JetsAK8Clean_doubleBDiscriminator->at(1) < bbtagCut 
               ) ) ) ;
}

template<typename ntupleType> bool doubleTaggingLooseCut_photon(ntupleType* ntuple ){
    return ( ntuple->JetsAK8Clean_doubleBDiscriminator->at(0) > bbtagCut && 
             ntuple->JetsAK8Clean_doubleBDiscriminator->at(1) > bbtagCut );
}

template<typename ntupleType> bool doubleMassCut_photon(ntupleType* ntuple ){
    return ( ntuple->JetsAK8Clean_prunedMass->at(0) > 85. &&
             ntuple->JetsAK8Clean_prunedMass->at(0) < 135. &&
             ntuple->JetsAK8Clean_prunedMass->at(1) > 85. &&
             ntuple->JetsAK8Clean_prunedMass->at(1) < 135. );
}

template<typename ntupleType> bool singleHiggsTagCut_photon(ntupleType* ntuple ){
    return ( (ntuple->JetsAK8Clean_prunedMass->at(0) > 85. && 
              ntuple->JetsAK8Clean_prunedMass->at(0) < 135. && 
              ntuple->JetsAK8Clean_doubleBDiscriminator->at(0) > bbtagCut ) ||
             (ntuple->JetsAK8Clean_prunedMass->at(1) > 85. && 
              ntuple->JetsAK8Clean_prunedMass->at(1) < 135. && 
              ntuple->JetsAK8Clean_doubleBDiscriminator->at(1) > bbtagCut ) );
}

template<typename ntupleType> bool doubleHiggsTagCut_photon(ntupleType* ntuple ){
    return ( ntuple->JetsAK8Clean_prunedMass->at(0) > 85. && 
             ntuple->JetsAK8Clean_prunedMass->at(0) < 135. && 
             ntuple->JetsAK8Clean_doubleBDiscriminator->at(0) > bbtagCut &&
             ntuple->JetsAK8Clean_prunedMass->at(1) > 85. && 
             ntuple->JetsAK8Clean_prunedMass->at(1) < 135. && 
             ntuple->JetsAK8Clean_doubleBDiscriminator->at(1) > bbtagCut ) ;
}

template<typename ntupleType> bool tagSR_photon(ntupleType* ntuple, int i){
    if( ntuple->JetsAK8Clean_doubleBDiscriminator->size() <= i || 
        ntuple->JetsAK8_prunedMass->size() <= i ) return false;
    return ( ntuple->JetsAK8Clean_doubleBDiscriminator->at(i) > bbtagCut &&
             ntuple->JetsAK8Clean_prunedMass->at(i) > 85. && 
             ntuple->JetsAK8Clean_prunedMass->at(i) < 135. );
}

template<typename ntupleType> bool tagSB_photon(ntupleType* ntuple, int i ){
    if( ntuple->JetsAK8Clean_doubleBDiscriminator->size() <= i || 
        ntuple->JetsAK8Clean_prunedMass->size() <= i ) return false;
    return ( ntuple->JetsAK8Clean_doubleBDiscriminator->at(i) > bbtagCut && 
             (
              ( ntuple->JetsAK8Clean_prunedMass->at(i) < 85. &&
                ntuple->JetsAK8Clean_prunedMass->at(i) > 50. ) ||
              ( ntuple->JetsAK8Clean_prunedMass->at(i) > 135. &&
                ntuple->JetsAK8Clean_prunedMass->at(i) < 250. ) 
              ) 
             );
}

template<typename ntupleType> bool antitagSR_photon(ntupleType* ntuple, int i){
        if( ntuple->JetsAK8Clean_doubleBDiscriminator->size() <= i || 
        ntuple->JetsAK8Clean_prunedMass->size() <= i ) return false;
    return ( ntuple->JetsAK8Clean_doubleBDiscriminator->at(i) < bbtagCut &&
             ( ntuple->JetsAK8Clean_prunedMass->at(i) > 85. &&
               ntuple->JetsAK8Clean_prunedMass->at(i) < 135. ) );
}
        
template<typename ntupleType> bool antitagSB_photon(ntupleType* ntuple, int i){
    if( ntuple->JetsAK8Clean_doubleBDiscriminator->size() <= i || 
        ntuple->JetsAK8Clean_prunedMass->size() <= i ) return false;
    return ( ntuple->JetsAK8Clean_doubleBDiscriminator->at(i) < bbtagCut &&
             (
              ( ntuple->JetsAK8Clean_prunedMass->at(i) < 85. &&
                ntuple->JetsAK8Clean_prunedMass->at(i) > 50. ) ||
              ( ntuple->JetsAK8Clean_prunedMass->at(i) > 135. &&
                ntuple->JetsAK8Clean_prunedMass->at(i) < 250. ) 
              )
             );
}

template<typename ntupleType> bool antitagSRCut_photon(ntupleType* ntuple){
    return ( antitagSR_photon(ntuple,0)&&antitagSR_photon(ntuple,1) );
}

template<typename ntupleType> bool antitagSBCut_photon(ntupleType* ntuple){
    return ( ( antitagSB_photon(ntuple,0)&&antitagSB_photon(ntuple,1) ) ||
             ( antitagSB_photon(ntuple,0)&&antitagSR_photon(ntuple,1) ) ||
             ( antitagSR_photon(ntuple,0)&&antitagSB_photon(ntuple,1) ) );
}

template<typename ntupleType> bool tagSRCut_photon(ntupleType* ntuple){
    return ( ( tagSR_photon(ntuple,0)&&antitagSR_photon(ntuple,1) ) || 
             ( antitagSR_photon(ntuple,0)&&tagSR_photon(ntuple,1) ) ) ;
}

template<typename ntupleType> bool tagSBCut_photon(ntupleType* ntuple){
    return ( ( tagSB_photon(ntuple,0)&&antitagSB_photon(ntuple,1) ) ||
             ( tagSR_photon(ntuple,0)&&antitagSB_photon(ntuple,1) ) ||
             ( tagSB_photon(ntuple,0)&&antitagSR_photon(ntuple,1) ) ||
             ( antitagSB_photon(ntuple,0)&&tagSB_photon(ntuple,1) ) ||
             ( antitagSR_photon(ntuple,0)&&tagSB_photon(ntuple,1) ) ||
             ( antitagSB_photon(ntuple,0)&&tagSR_photon(ntuple,1) ) );

}

template<typename ntupleType> bool doubletagSRCut_photon(ntupleType* ntuple){
    return ( tagSR_photon(ntuple,0)&&tagSR_photon(ntuple,1) );
}

template<typename ntupleType> bool doubletagSBCut_photon(ntupleType* ntuple){
    return ( ( tagSB_photon(ntuple,0)&&tagSB_photon(ntuple,1) ) ||
             ( tagSB_photon(ntuple,0)&&tagSR_photon(ntuple,1) ) ||
             ( tagSR_photon(ntuple,0)&&tagSB_photon(ntuple,1) ) );
}

/////////////////////////////////////////////////
// - - - - - - - Trigger Cuts - - - - - - - -  //
/////////////////////////////////////////////////
template<typename ntupleType> bool signalTriggerCut(ntupleType* ntuple){
    //return ntuple->TriggerPass->at(42) == 1 || ntuple->TriggerPass->at(43) == 1 || ntuple->TriggerPass->at(44) == 1 || ntuple->TriggerPass->at(45) == 1 ; 

	return (ntuple->TriggerPass->at(110) == 1 || ntuple->TriggerPass->at(114) == 1 ||
           ntuple->TriggerPass->at(116) == 1 || ntuple->TriggerPass->at(118) == 1 ||
           ntuple->TriggerPass->at(122) == 1 || ntuple->TriggerPass->at(124) == 1 ||
           ntuple->TriggerPass->at(126) == 1 || ntuple->TriggerPass->at(129) == 1 ||
           ntuple->TriggerPass->at(131) == 1 || ntuple->TriggerPass->at(133) == 1 ||
           ntuple->TriggerPass->at(134) == 1 ) ;

}

template<typename ntupleType> bool singleMuTriggerCut(ntupleType* ntuple){
    return ( ntuple->TriggerPass->at(20)==1 || ntuple->TriggerPass->at(21)==1 || ntuple->TriggerPass->at(22)==1 || ntuple->TriggerPass->at(23)==1 || ntuple->TriggerPass->at(24)==1 || ntuple->TriggerPass->at(28)==1 || ntuple->TriggerPass->at(29)==1 );
}

template<typename ntupleType> bool singleEleTriggerCut(ntupleType* ntuple){
    return ntuple->TriggerPass->at(6) == 1 || ntuple->TriggerPass->at(7) == 1 || ntuple->TriggerPass->at(8) == 1 || ntuple->TriggerPass->at(9) == 1 || ntuple->TriggerPass->at(10) == 1 || ntuple->TriggerPass->at(11) == 1 || ntuple->TriggerPass->at(12) == 1 || ntuple->TriggerPass->at(13) == 1 || ntuple->TriggerPass->at(14) == 1 ;
}

template<typename ntupleType> bool lowDphiTriggerCut(ntupleType* ntuple){
    return ntuple->TriggerPass->at(42) == 1 || ntuple->TriggerPass->at(43) == 1 || ntuple->TriggerPass->at(44) == 1 || ntuple->TriggerPass->at(45) == 1 ; 
}

template<typename ntupleType> bool photonTriggerCut(ntupleType* ntuple){
    return ntuple->TriggerPass->at(53) == 1 || ntuple->TriggerPass->at(54) == 1 ; // || ntuple->TriggerPass->at(51) || ntuple->TriggerPass->at(52);
}

// print out trigger name
/*vector<string> TriggerNames;
    int n = ntuple->TriggerNames.size();
    for(int i=0; i<n; i++){
        string TName = TriggerNames[i];
        std::cout<<"Trigger Names: "<<TName<<std::endl;
    }
*/
// end of Trigger name printout

template<typename ntupleType> int getClosestGenHiggses(ntupleType* ntuple, double jeteta, double jetphi){
    float dRMin=999999.;
    for( int i=0 ; i < ntuple->GenParticles->size() ; i++ ){
        if( ntuple->GenParticles_PdgId->at(i) == 25 &&
            ntuple->GenParticles_ParentId->at(i) == 1000023 &&
            ntuple->GenParticles_Status->at(i) == 22 ){
                float dR=sqrt((jeteta-ntuple->GenParticles->at(i).Eta())*(jeteta-ntuple->GenParticles->at(i).Eta()) +(jetphi-ntuple->GenParticles->at(i).Phi())*(jetphi-ntuple->GenParticles->at(i).Phi()));
                if(dRMin>dR)dRMin=dR;
                }
    }
    return dRMin;
}
template<typename ntupleType> int getClosestGenZ(ntupleType* ntuple, double jeteta, double jetphi){
    float dRMin=999999.;
    for( int i=0 ; i < ntuple->GenParticles->size() ; i++ ){
        if( ntuple->GenParticles_PdgId->at(i) == 23 &&
            ntuple->GenParticles_ParentId->at(i) == 1000023 &&
            ntuple->GenParticles_Status->at(i) == 22 ){
                float dR=sqrt((jeteta-ntuple->GenParticles->at(i).Eta())*(jeteta-ntuple->GenParticles->at(i).Eta()) +(jetphi-ntuple->GenParticles->at(i).Phi())*(jetphi-ntuple->GenParticles->at(i).Phi()));
                if(dRMin>dR)dRMin=dR;
                }
    }
    return dRMin;
}
template<typename ntupleType>double ResolutionSmear(ntupleType* ntuple, int j,unsigned int seed, bool SFUp=false){
TRandom3 rand(seed);
double sigmaJMR=0;
if(ntuple->JetsAK8_NumBhadrons->at(j)!=2)return ntuple->JetsAK8_prunedMass->at(j);
if(ntuple->JetsAK8->at(j).Pt()>300. && ntuple->JetsAK8->at(j).Pt()<=600.)sigmaJMR=12.55;
if(ntuple->JetsAK8->at(j).Pt()>600. && ntuple->JetsAK8->at(j).Pt()<=800.)sigmaJMR=10.24;
if(ntuple->JetsAK8->at(j).Pt()>800. && ntuple->JetsAK8->at(j).Pt()<=1000.)sigmaJMR= 9.85;
if(ntuple->JetsAK8->at(j).Pt()>1000.)sigmaJMR=9.44;
sigmaJMR=sigmaJMR/110.;
double sigmaJMRSF=1.23;
if(SFUp)sigmaJMRSF=sigmaJMRSF-0.18;
double dRHiggs=getClosestGenHiggses(ntuple, ntuple->JetsAK8->at(j).Eta(), ntuple->JetsAK8->at(j).Phi());
double dRZ=getClosestGenZ(ntuple, ntuple->JetsAK8->at(j).Eta(), ntuple->JetsAK8->at(j).Phi());
if(dRHiggs>dRZ){
if(ntuple->JetsAK8->at(j).Pt()>300. && ntuple->JetsAK8->at(j).Pt()<=600.)sigmaJMR=8.27;
if(ntuple->JetsAK8->at(j).Pt()>600. && ntuple->JetsAK8->at(j).Pt()<=800.)sigmaJMR=7.13;
if(ntuple->JetsAK8->at(j).Pt()>800. && ntuple->JetsAK8->at(j).Pt()<=1000.)sigmaJMR=6.83;
if(ntuple->JetsAK8->at(j).Pt()>1000.)sigmaJMR=6.90;
sigmaJMR=sigmaJMR/83.;
}
double gausSmear=rand.Gaus(0, sigmaJMR)*sqrt((sigmaJMRSF*sigmaJMRSF -1));
double smearmass=(gausSmear+1.)*ntuple->JetsAK8_prunedMass->at(j);
return smearmass;
}
template<typename ntupleType>double SignalISRCorrection(ntupleType* ntuple){
float ISRWeights[7]={1.0, 0.920, 0.821, 0.715, 0.662, 0.561,0.511};
if(ntuple->NJetsISR==0) return ISRWeights[0];
if(ntuple->NJetsISR==1) return ISRWeights[1];
if(ntuple->NJetsISR==2) return ISRWeights[2];
if(ntuple->NJetsISR==3) return ISRWeights[3];
if(ntuple->NJetsISR==4) return ISRWeights[4];
if(ntuple->NJetsISR==5) return ISRWeights[5];
if(ntuple->NJetsISR>=6) return ISRWeights[6];
}
template<typename ntupleType> double doubleBSF(ntupleType* ntuple,int j){
double doubleBSF=1.0;
if(ntuple->JetsAK8->at(j).Pt()>300. && ntuple->JetsAK8->at(j).Pt()<=350)doubleBSF=0.96;
if(ntuple->JetsAK8->at(j).Pt()>350. && ntuple->JetsAK8->at(j).Pt()<=430)doubleBSF=1.00;
if(ntuple->JetsAK8->at(j).Pt()>430.)doubleBSF=1.01;
return doubleBSF;
}
template<typename ntupleType> double doubleBSFUp(ntupleType* ntuple,int j){
double doubleBSF=1.0;
if(ntuple->JetsAK8->at(j).Pt()>300. && ntuple->JetsAK8->at(j).Pt()<=350)doubleBSF=0.96+0.03;
if(ntuple->JetsAK8->at(j).Pt()>350. && ntuple->JetsAK8->at(j).Pt()<=430)doubleBSF=1.00+0.024;
if(ntuple->JetsAK8->at(j).Pt()>430. && ntuple->JetsAK8->at(j).Pt()<840)doubleBSF=1.01+0.02;
if(ntuple->JetsAK8->at(j).Pt()>840)doubleBSF=1.01+0.04;
return doubleBSF;
}
template<typename ntupleType> double doubleBSFDn(ntupleType* ntuple,int j){
double doubleBSF=1.0;
if(ntuple->JetsAK8->at(j).Pt()>300. && ntuple->JetsAK8->at(j).Pt()<=350)doubleBSF=0.96-0.02;
if(ntuple->JetsAK8->at(j).Pt()>350. && ntuple->JetsAK8->at(j).Pt()<=430)doubleBSF=1.00-0.043;
if(ntuple->JetsAK8->at(j).Pt()>430. && ntuple->JetsAK8->at(j).Pt()<840)doubleBSF=1.01-0.04;
if(ntuple->JetsAK8->at(j).Pt()>840)doubleBSF=1.01-0.08;
return doubleBSF;
}
