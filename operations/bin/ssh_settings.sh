#!/bin/bash

cd ~


echo -ne '\n\n\n' | ssh-keygen


ssh-copy-id -i ~/.ssh/id_rsa.pub $USER@epics.radonc.washington.edu


#ssh $USER@epics.radonc.washington.edu

gnome-terminal -e "bash -c \"ssh $USER@epics.radonc.washington.edu; exec bash\""

