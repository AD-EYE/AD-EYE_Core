scans= extract_scan;
save('C:\Users\adeye\AD-EYE_Core\AD-EYE\Experiments\Real_world\scans_data','scans');

function scan_data=extract_scan()
    scan=[];
    for i=[0:9]
        ptcloud=pcread(strcat('C:\Users\adeye\Desktop\real_world_data\data\AutoDrive\recording\2019_8_2\rec3\lidar_left\scan00000',num2str(i),'.pcd'));
        scan=[scan;ptcloud];
    end
    for i=[10:99]
        scan=[scan;pcread(strcat('C:\Users\adeye\Desktop\real_world_data\data\AutoDrive\recording\2019_8_2\rec3\lidar_left\scan0000',num2str(i),'.pcd'))];
    end
    for i=[100:944]
        scan=[scan;pcread(strcat('C:\Users\adeye\Desktop\real_world_data\data\AutoDrive\recording\2019_8_2\rec3\lidar_left\scan000',num2str(i),'.pcd'))];
    end
    scan_data=scan;
end
