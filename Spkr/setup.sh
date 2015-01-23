#!/bin/bash
ssh pi@$1 << EOF
sudo apt-get install libvlc-dev
EOF
