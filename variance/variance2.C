void variance2()
{
TFile *f=new TFile("13TeV_CR0_RHoff.root");
char multiplicities[6][12] = {"pytree020","pytree2040","pytree4060","pytree6080","pytree80100","pytree100"};
Double_t meanmpT[6] = {0.0,0.0,0.0,0.0,0.0,0.0};
TCanvas *c1=new TCanvas("c1","Standardised Variance");
c1->SetGrid();
TGraph *gpT = new TGraph();

for(Int_t k=0;k<6;k++){
    
    TTree *tree1 = (TTree*)f->Get(multiplicities[k]);
    Long64_t entries = (Long64_t)tree1->GetEntries();
    const Long64_t maxTrack=1000;
    Int_t ntrack;
    Double_t pT[maxTrack];
   	   
    tree1->SetBranchAddress("ntrack",&ntrack);
    tree1->SetBranchAddress("pT",&pT);


        for(Int_t i=0;i<entries;i++){

	    Double_t mpT=0.0;
            tree1->GetEntry(i);

            for(Int_t j=0;j<ntrack;j++){

                mpT += pT[j];
            }
	if(ntrack!=0){
	mpT=mpT/ntrack;}
        meanmpT[k]+=mpT;
	}
        meanmpT[k]=meanmpT[k]/entries;
	Double_t temp1;
	for(Int_t i=0;i<entries;i++){

	 Double_t mpT=0.0;
	 tree1->GetEntry(i);

            for(Int_t j=0;j<ntrack;j++){

                mpT += pT[j];
	      }
	if(ntrack!=0){
	mpT=mpT/ntrack;}
	temp1 = temp1 + ((mpT - meanmpT[k])*(mpT - meanmpT[k]));
	}
	temp1 = temp1/entries;
	Double_t variance;
	variance = sqrt(temp1);
	variance = variance/meanmpT[k];
        gpT->SetPoint(k,20*k+10,variance);
        gpT->SetMarkerStyle(21);
        gpT->SetMarkerSize(1.6);

        delete tree1;
        

}
gpT->SetLineStyle(9);
gpT->SetTitle("Standardised Variance");
gpT->GetXaxis()->SetTitle("Multiplicity Classes");
gpT->GetYaxis()->SetTitle("Standardized Variance");
gpT->Draw("ALP");

auto legend = new TLegend(0.1,0.7,0.48,0.9);
   legend->SetHeader("Legend","C"); // option "C" allows to center the header
   legend->AddEntry("gpT","1 observation of standardized variance","P");
   legend->Draw();
}
