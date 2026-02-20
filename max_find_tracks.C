#include <TFile.h>
#include <TDirectory.h>
#include <TTree.h>
#include <iostream>
#include <vector>
#include <climits>

void max_find_tracks(const char* filename) {

  TFile* f = TFile::Open(filename, "READ");
  if (!f || f->IsZombie()) {
    std::cerr << "[ERROR] cannot open: " << filename << "\n";
    return;
  }

  TDirectory* d = (TDirectory*) f->Get("trackingNtuple");
  if (!d) {
    std::cerr << "[ERROR] missing trackingNtuple in: " << filename << "\n";
    f->Close();
    return;
  }

  TTree* t = (TTree*) d->Get("tree");
  if (!t) {
    std::cerr << "[ERROR] missing tree in: " << filename << "\n";
    f->Close();
    return;
  }

  Long64_t nEv = t->GetEntries();
  if (nEv == 0) {
    std::cout << filename << "   events=0\n";
    f->Close();
    return;
  }

  std::vector<float>* trk_pt = nullptr;
  t->SetBranchAddress("trk_pt", &trk_pt);

  double totalTracks = 0;
  Long64_t minN = LLONG_MAX, maxN = 0;

  for (Long64_t i = 0; i < nEv; ++i) {
    t->GetEntry(i);
    if (!trk_pt) continue;
    Long64_t N = (Long64_t)trk_pt->size();
    totalTracks += N;
    if (N < minN) minN = N;
    if (N > maxN) maxN = N;
  }

  double avg = totalTracks / (double)nEv;

  std::cout
    << filename
    << "   events=" << nEv
    << "   totalTracks=" << totalTracks
    << "   avgTracksPerEvent=" << avg
    << "   minTracksPerEvent=" << minN
    << "   maxTracksPerEvent=" << maxN
    << std::endl;

  f->Close();
}