#!/bin/bash
# angelcad end user setup
# Run this script with sudo privilege

if [ "$EUID" -ne 0 ]
  then echo "Please run as root"
  exit
fi

#remove previous installation of these packages
apt -y remove angelcad
apt -y remove xcsg

# install the ones provided with this script
apt -y install ./xcsg*.deb
apt -y install ./angelcad*.deb

echo "Confirming installation, you should see paths to 'xcsg', 'as_csg', 'angelview' and 'angelcad' below"
echo "From package xcsg    : `which xcsg`" 
echo "From package angelcad: `which as_csg`"
echo "From package angelcad: `which angelview`"
echo "From package angelcad: `which angelcad`"
echo "AngelCAD installation complete"
