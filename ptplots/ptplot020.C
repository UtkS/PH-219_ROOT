void ptplot020()
{
        TFile *f=new TFile("13TeV_CR0_RHoff.root");
        TTree *tree = (TTree*)f->Get("pytree020");
        Long64_t entries = (Long64_t)tree->GetEntries();

        const Long64_t maxTrack=10000000;

    Int_t ntrack;
    Double_t pT[maxTrack];

    tree->SetBranchAddress("ntrack",&ntrack);
    tree->SetBranchAddress("pT",&pT);

        TH1D *hpT = new TH1D("hpT","Transverse Momentum 0-20",100,0.0,5.0);
        TCanvas *c1=new TCanvas();
        c1->SetLogy();

        for(Int_t i=1;i<entries;i++){

            tree->GetEntry(i);
            Int_t ntrk = ntrack;

            for(Int_t j=0;j<ntrk;j++){

                Double_t pT1 = pT[j];
                hpT->Fill(pT1);
            }
        }
	hpT->GetXaxis()->SetTitle("pT (GeV/c)");
        hpT->GetYaxis()->SetTitle("Counts");
        hpT->Draw();
        hpT->Fit("expo");
        auto legend = new TLegend(0.1,0.7,0.36,0.9);
        legend->SetHeader("Legend");
        legend->AddEntry(hpT,"Transverse Momentum","f");
        legend->AddEntry(expo,"Exponential Fit","l");
	legend->SetTextSize(0.03);
	legend->Draw();
}
