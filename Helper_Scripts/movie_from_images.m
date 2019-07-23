writerObj = VideoWriter('World_import.avi');
writerObj.FrameRate=20;
open(writerObj);
for K = 1 : 400
  filename = sprintf('PhysicsBasedCameraSensor_1_capture_opticsandsensor_%05d.png', K);
  png = imread(filename);
  raw = png(:,:,1);
  hdr = single(demosaic(raw, 'bggr'));
  sdr = tonemap(hdr);
  writeVideo(writerObj, sdr);
end
close(writerObj);