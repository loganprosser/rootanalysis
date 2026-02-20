#!/usr/bin/env bash
set -euo pipefail

ROOT_BIN="/home/lap284/Documents/applications/root/bin/root"
MACRO="/home/lap284/.commands/rootC/paraRootC/max_find_tracks.C"
NPROCS="${NPROCS:-7}"
OUTDIR="/nfs/cms/tracktrigger/logan/root/eventNumAnalysis/track_counts_logs"

rm -rf "$OUTDIR"
mkdir -p "$OUTDIR"

echo "file    events    totalTracks    avgTracksPerEvent    minTracksPerEvent    maxTracksPerEvent"

find . -maxdepth 1 -type f -name "*.root" -print0 \
| xargs -0 -P "$NPROCS" -I{} bash -lc '
  set -euo pipefail
  file="{}"
  base=$(basename "$file")
  log="'"$OUTDIR"'/${base%.root}.out"

  "'"$ROOT_BIN"'" -l -b -q "'"$MACRO"'(\"$file\")" > "$log" 2>&1
'

for f in ./*.root; do
  [ -e "$f" ] || continue
  base=$(basename "$f")
  log="$OUTDIR/${base%.root}.out"
  awk -v file="$f" '$1==file {print}' "$log"
done