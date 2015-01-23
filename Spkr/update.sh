#!/bin/bash
./pack.sh
scp spkr.zip pi@$1:~/
ssh pi@$1 << EOF
rm -rf Spkr
unzip spkr.zip
chmod +x ~/Spkr/onboot.sh
sudo cp Spkr/interfaces /etc/network/interfaces
cd ~/Spkr
make
crontab ~/Spkr/crontab
EOF
