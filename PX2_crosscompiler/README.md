
To build docker image:

- Copy cuda 9.2, driveworks1.2 and nvidia folder into this directory (needs around 33GB) 
    folder location: https://kth-my.sharepoint.com/personal/naveenm_ug_kth_se/_layouts/15/onedrive.aspx?fromShare=true&ga=1&id=%2Fpersonal%2Fnaveenm%5Fug%5Fkth%5Fse%2FDocuments%2FADEYE%5FOD%2FWork%2FRevathy%5FSeptember%5F2023%2Fcross%5Fcompile%5Ffolders%2Etar%2Egz&parent=%2Fpersonal%2Fnaveenm%5Fug%5Fkth%5Fse%2FDocuments%2FADEYE%5FOD%2FWork%2FRevathy%5FSeptember%5F2023
- Open terminal in the folder containing dockerfile and execute:
    docker build -t ubuntu16_crosscompile:latest .
- To run generated image:
    docker run -v /path/to/driveworks_camera_gmslfolder/on/host:/home/ubuntu/driveworks_camera_gmsl -it ubuntu16_crosscompile:latest

Instructions to cross compile gmsl camera code provided in its readme file. Execute those instructions from inside the image

P.S:

While copying files to docker context- useful commands:
- To give right priviliage to all users for all files in a folder
    sudo chmod -R a+r foldername
- change owner of a folder
    sudo chown -R username foldername
(This helps in preveting `docker build Error checking context: 'can't stat'` error)

### If you need to install more arm libraries:
- Add arm64 architecture to sources following instructions from below link:
https://docs.nvidia.com/drive/active/5.0.10.3L/nvvib_docs/index.html#page/NVIDIA%2520DRIVE%2520Linux%2520SDK%2520Development%2520Guide%2FSystem%2520Programming%2FQSG_lnx_nfs_dpx.html%23wwpID0E0GD0HA

- Download arm packages of all dependencies of a package
create a folder to download the packages and execute the following command (replace packagename with required package)

    for i in $(apt-rdepends packagename:arm64  | grep -v "^ "); do sudo apt-get download $i":arm64" 2>>errors.txt; done

- Unpack the downloaded deb files to  nvidia/nvidia_sdk/DRIVE_OS_5.0.10.3_SDK_with_DriveWorks_Linux_OS_PX2_AUTOCHAUFFEUR/DriveSDK/drive-t186ref/targetfs directory. Go to downloaded folder and execute following commands ( replace /path/to/targetfs with correct path)
    ls -1 | grep [.]deb >> all_debs.txt
    cat all_debs.txt | while read fn; do dpkg-deb -x $fn /path/to/targetfs; done
    rm all_debs.txt