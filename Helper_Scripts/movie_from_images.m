writerObj = VideoWriter('World_import.avi');
writerObj.FrameRate=20;
open(writerObj);
for K = 1 : 1500
  filename = sprintf('HumViewCamera_%05d.png', K);
  png = imread(filename);
  %raw = png(:,:,1);
  %hdr = single(demosaic(raw, 'bggr'));
  %sdr = tonemap(hdr);
  writeVideo(writerObj, png);
end
close(writerObj);