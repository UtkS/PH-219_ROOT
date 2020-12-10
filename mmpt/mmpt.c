void mmpt()
{
TFile *f=new TFile("13TeV_CR0_RHoff.root");
char multiplicities[7][12] = {"pytree","pytree020","pytree2040","pytree4060","pytree6080","pytree80100","pytree100"};
Double_t meanmpT[7] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0};
TCanvas *c1=new TCanvas("c1", "Mean mean pT", 200,10,700,50);
c1->SetGrid();
TGraph *gpT = new TGraph();

for(Int_t k=1;k<7;k++){
    
    TTree *tree1 = (TTree*)f->Get(multiplicities[k]);
    Long64_t entries = (Long64_t)tree1->GetEntries();
    //entries=entries/50;
    const Long64_t maxTrack=10000000;
    //const Long64_t maxpT=1000000;
    Int_t ntrack;
    Double_t pT[maxTrack];
    Double_t mpT[maxTrack];	   
    for(Int_t i; i<maxTrack;i++)
    {
    mpT[i]=0.0;
    } 
    
    tree1->SetBranchAddress("ntrack",&ntrack);
    tree1->SetBranchAddress("pT",&pT);

        //TGraph *hpT = new TGraph(no. of inputs, x_inputs, y_inputs);
        //TGraph *gpT = new TGraph(7, , );

        for(Int_t i=0;i<entries;i++){

            tree1->GetEntry(i);

            for(Int_t j=0;j<ntrack;j++){
                mpT[i] += pT[j];
            }
			if (ntrack > 0){
				mpT[i] = mpT[i] / ntrack;
			}
        meanmpT[k]+=mpT[i];
	}
        meanmpT[k]=meanmpT[k]/entries;
        //hpT->Fill(meanmpT);
        gpT->SetPoint(k-1,20*k-10,meanmpT[k]);
    gpT->SetMarkerStyle(21);

        delete tree1;
        //hpT->Fit("expo");

}
gpT->SetLineStyle(9);
gpT->SetTitle("<<pT>>");
//gpT->SetTitleFontSize(1.0);
gpT->GetXaxis()->SetTitle("Multiplicity Class");
gpT->GetYaxis()->SetTitle("<<pT>>");

gpT->Draw("ALP");
gpT->GetYaxis()->SetRangeUser(0.0,1.5);
	gpT->Draw("ALP");
	c1->Update();
auto legend = new TLegend(0.1,0.7,0.7,0.9);
   legend->SetHeader("Legend"); // option "C" allows to center the header
   legend->AddEntry("gpT","<<pT>> for corresponding multiplicity class","P");
   legend->SetTextSize(0.03);   
   legend->Draw();
}
