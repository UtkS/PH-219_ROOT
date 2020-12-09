void mptplot80100()
{
        TFile *f=new TFile("13TeV_CR0_RHoff.root");
        TTree *tree = (TTree*)f->Get("pytree80100");
        Long64_t entries = (Long64_t)tree->GetEntries();

        const Long64_t maxTrack=100000;
    Int_t ntrack;
    Double_t pT[maxTrack];
    Double_t mpT=0.0;	    

    tree->SetBranchAddress("ntrack",&ntrack);
    tree->SetBranchAddress("pT",&pT);

        TH1D *hpT = new TH1D("hpT","Average Transverse Momentum 80-100",100,0.0,5.0);
        TCanvas *c1=new TCanvas();
        c1->SetLogy();

        for(Int_t i=0;i<entries;i++){

            tree->GetEntry(i);
            Int_t ntrk = ntrack;

            for(Int_t j=0;j<ntrk;j++){

                mpT += pT[j];
                 }
	mpT=mpT/ntrack;
        hpT->Fill(mpT);
	}
    
	hpT->GetXaxis()->SetTitle("Average Transverse Momentum");
	hpT->GetYaxis()->SetTitle("Counts");

        hpT->Draw();
        hpT->Fit("gaus");
        auto legend = new TLegend(0.1,0.7,0.48,0.9);
        legend->SetHeader("Legend","C");
        legend->AddEntry(hpT,"Average Transverse Momentum","f");
        legend->AddEntry("gaus","Gaussian Fit","l");
        legend->Draw();

}