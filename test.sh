#!/bin/sh

for PROOF in demo-proof1 demo-proof2 demo-proof3; do
    rm -f eg/*.exe
    ./build-proof.sh eg/$PROOF && eg/$PROOF.exe && echo "$PROOF ok"
done

for NONPROOF in demo-nonproof1 demo-nonproof2 demo-nonproof3; do
    rm -f eg/*.exe
    ./build-proof.sh eg/$NONPROOF
    if eg/$NONPROOF.exe; then
        echo "ERROR: nonproof $NONPROOF terminated with exit code 0"
        exit 1
    fi
    echo "nonproof $NONPROOF ok"
done
