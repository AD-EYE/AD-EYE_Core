experiment = prescan.api.experiment.loadExperimentFromFile('W01_Base_MapUnrealPb.pb')
ego_vehicle = findobj(experiment.objects,'name','BMW_X5_SUV_1');

camera = findobj(ego_vehicle.sensors,'name','PhysicsBasedCameraUnreal_1');
camera.imager.resolutionX = 960
camera.imager.resolutionY = 720
camera = findobj(ego_vehicle.sensors,'name','PhysicsBasedCameraUnreal_2');
camera.imager.resolutionX = 960
camera.imager.resolutionY = 720
camera = findobj(ego_vehicle.sensors,'name','PhysicsBasedCameraUnreal_3');
camera.imager.resolutionX = 960
camera.imager.resolutionY = 720

prescan.api.simulink.run(experiment, 'Regenerate', 'off',  'StopTime', '100')