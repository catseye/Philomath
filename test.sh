#!/bin/sh -e

./build-proof.sh eg/demo-proof1 && eg/*.exe && rm eg/*.exe && echo "ok"
./build-proof.sh eg/demo-proof2 && eg/*.exe && rm eg/*.exe && echo "ok"
./build-proof.sh eg/demo-proof3 && eg/*.exe && rm eg/*.exe && echo "ok"
# ./build-proof.sh eg/demo-nonproof1 && eg/*.exe && rm eg/*.exe && echo "ok"
