#!/bin/bash
# packaging script using EPM for native package creation
# Run this script with sudo privilege

if [ "$EUID" -ne 0 ];
  then echo "Please run this script as root"
  exit
fi

check_distro2(){
    if [[ -e /etc/redhat-release ]]
    then
      DISTRO=$(cat /etc/redhat-release)
    elif [[ -e /usr/bin/lsb_release ]]
    then
      DISTRO=$(lsb_release -d | awk -F ':' '{print $2}')
    elif [[ -e /etc/issue ]]
    then
      DISTRO=$(cat /etc/issue)
    else
      DISTRO=$(cat /proc/version)
    fi
    #remove 1st character (tab character)
    DISTRO="${DISTRO:1:${#DISTRO}}"
    # replace all blanks characters with dash
    DISTRO=${DISTRO// /-}
    #make all characters lowercase
    DISTRO="${DISTRO,,}"
}
check_distro2
echo $DISTRO

PACKAGE_NAME="angelcad"
echo "$PACKAGE_NAME *.deb build started....please wait"

# CPDE_USR defines where to find the binaries to package. We don't have to check 
# that $CPDE_USR exists, because epm will do it and report any errors
if [ -z ${CPDE_USR+x} ]; then
   export CPDE_USR=~/cpde_usr
   echo "CPDE_USR is unset, defaults to '$CPDE_USR'"; 
else 
   echo "CPDE_USR is set to '$CPDE_USR'"; 
fi

# set paths to source binaries and assign version number
# use full path to executable so we don't accidentaly reference any other in $PATH
export PATH=$PATH:$CPDE_USR/bin
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PATH
export ANGELCAD_VERSION="`${CPDE_USR}/bin/as_csg --version`"

# Cleanup any existing deb file
find . -name '*.deb' | while read OLD_DEB_FILE; do
   echo "Removing old  : `ls -l $OLD_DEB_FILE`"
   rm "$OLD_DEB_FILE"
done

# Create new deb file.
epm -f deb "$PACKAGE_NAME" ./epm/"$PACKAGE_NAME"_epm.list

# Check that the package creation was OK and report
DEB_FILE=`find . -name '*.deb'`
if [ -f "$DEB_FILE" ]
then
   echo "New package   : `ls -l $DEB_FILE`  OK"
   
   #Folder of angelcad DEB file
   DEB_FOLDER="$(dirname $DEB_FILE)"
   #find the xcsg package and copy it in
   XCSG_PATH="../../../xcsg/"
   XCSG_DEB=`find $XCSG_PATH -name '*.deb'`
   
   #copy in xcsg deb file
   if [ ! -f "$XCSG_DEB" ]; then
      echo "ERROR: The XCSG *.deb file not found under $XCSG_PATH. Build it first...exiting build script."
      exit 1
   fi
   cp -f "$XCSG_DEB" "$DEB_FOLDER"
   XCSG_DEB=`find . -name 'xcsg*.deb'`
   
   #copy in the setup script
   cp -f ./angelcad_setup.sh "$DEB_FOLDER"
   SETUP_SH=`find $DEB_FOLDER -name '*_setup.sh'`

   ZIP_NAME="$PACKAGE_NAME"-"$ANGELCAD_VERSION"-"$DISTRO.zip"
   rm "$ZIP_NAME"
   zip -q -r "$ZIP_NAME" "$DEB_FILE"
   zip -q -r "$ZIP_NAME" "$XCSG_DEB"
   zip -q -r "$ZIP_NAME" "$SETUP_SH"
   rm "$SETUP_SH"

   if [ -f "$ZIP_NAME" ]
   then
      echo "Zipped package: `ls -l $ZIP_NAME`  OK"
      unzip -l "$ZIP_NAME"
   fi
else 
   echo "ERROR: no *.deb file created, please check and correct."
fi

exit
