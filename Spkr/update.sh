#!/bin/bash
./pack.sh
scp spkr.zip pi@$1:~/
ssh pi@$1 << EOF
rm -rf spkr
unzip spkr.zip -d spkr
chmod +x ~/spkr/onboot.sh
sudo cp spkr/interfaces /etc/network/interfaces
cd ~/spkr
make
crontab ~/spkr/crontab
sudo reboot
EOF
