#include <math.h>
void CapitalGamma(){
	TLatex latex;
	TFile *f = new TFile("13TeV_CR0_RHoff.root");
	char multiplicities[7][12] = { "pytree", "pytree020", "pytree2040", "pytree4060", "pytree6080", "pytree80100", "pytree100" };
	Double_t meanmpT[7] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
	Double_t intskewness[7] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    TCanvas *c1=new TCanvas("c1","Intensive Skewness");
    c1->SetGrid();
	TGraph *gpT = new TGraph();

	for (Int_t k = 1; k<7; k++){

		TTree *tree1 = (TTree*)f->Get(multiplicities[k]);
		Long64_t entries = (Long64_t)tree1->GetEntries();

		const Long64_t maxTrack = 10000000;

		Int_t ntrack=0;
		Double_t pT[maxTrack];
		Double_t mpT[maxTrack];
		Double_t numerator1 = 0.0;
		Double_t numerator2 = 0.0;
		Double_t numerator3 = 0.0;
		Double_t numerator = 0.0;
		Double_t denominator1 = 1.0;
		Double_t denominator2 = 1.0;
		Double_t denominator = 1.0;
		for (Int_t i; i<maxTrack; i++)
		{
			mpT[i] = 0.0;
		}

		tree1->SetBranchAddress("ntrack", &ntrack);
		tree1->SetBranchAddress("pT", &pT);

		for (Int_t i = 0; i<entries; i++){
            tree1->GetEntry(i);
			Double_t q1=0.0;
			Double_t q2=0.0;
			Double_t q3=0.0;
			for (Int_t j = 0; j<ntrack; j++){
				mpT[i] += pT[j];
				q1+= pT[j];
				q2+= pow(pT[j],2);
				q3+= pow(pT[j],3);
			}
			if (ntrack > 0){
				mpT[i] = mpT[i] / ntrack;
			}
			meanmpT[k] += mpT[i];
			if (ntrack > 0){
				numerator3 += q1/ntrack;
				if (ntrack > 1){
					numerator2 += (pow(q1, 2) - q2) / (ntrack*(ntrack - 1));
					if (ntrack > 2){
						numerator1 += (pow(q1, 3) - 3 * q2 * q1 + 2 * q3) / (ntrack*(ntrack - 1)*(ntrack - 2));
					}
				}
			}
		}

		meanmpT[k] = meanmpT[k] / entries;
		numerator1 = numerator1 / entries;
		numerator2 = numerator2 / entries;
		numerator3 = numerator3 / entries;
		denominator1 = numerator2;
		denominator2 = numerator3;
		numerator = (numerator1 - 3 * numerator2 * numerator3 + 2 * pow(numerator3, 3)) * meanmpT[k];
		denominator = pow(denominator1 - pow(denominator2, 2), 2);
		if (denominator != 0){
			intskewness[k] = numerator / denominator;
		}
		gpT->SetPoint(k -1, 20 * k - 10, intskewness[k]);
		gpT->SetMarkerStyle(21);
        gpT->SetMarkerSize(1.6);
        gpT->SetTitle("Intensive Skewness");
        gpT->GetXaxis()->SetTitle("Multiplicity");
        gpT->GetYaxis()->SetTitle("#Gamma_{pT}");

		delete tree1;

	}

	gpT->Draw("AP");

    auto legend = new TLegend(0.1,0.7,0.36,0.9);
    legend->SetHeader("Legend"); 
    legend->AddEntry("gpT","Intrinsic Skewness for corresponding multiplicity class","P");
    legend->Draw();

}