function detection_templates
% From sign images inside folder TSR_detection_templates, the function
% creates detection_templates.mat file, which is used in detection process.

N = 6;	% No of signs to detect

DetectTemplates = struct([]);

DetectTemplates(1).name = 'z101';
DetectTemplates(1).ext  = 'png';
DetectTemplates(1).dir  = 'TSR_detection_templates';
DetectTemplates(1).detID   = 1;

DetectTemplates(2).name = 'z205';
DetectTemplates(2).ext  = 'png';
DetectTemplates(2).dir  = 'TSR_detection_templates';
DetectTemplates(2).detID   = 2;

DetectTemplates(3).name = 'z206';
DetectTemplates(3).ext  = 'png';
DetectTemplates(3).dir  = 'TSR_detection_templates';
DetectTemplates(3).detID   = 3;

DetectTemplates(4).name = 'z267';
DetectTemplates(4).ext  = 'png';
DetectTemplates(4).dir  = 'TSR_detection_templates';
DetectTemplates(4).detID   = 5;

DetectTemplates(5).name = 'z272';
DetectTemplates(5).ext  = 'png';
DetectTemplates(5).dir  = 'TSR_detection_templates';
DetectTemplates(5).detID   = 4;

DetectTemplates(6).name = 'z274-57';
DetectTemplates(6).ext  = 'png';
DetectTemplates(6).dir  = 'TSR_detection_templates';
DetectTemplates(6).detID   = 4;

%% Generate detection templates
for ii = 1 : N
    DetectTemplates(ii).img  = detection_template(DetectTemplates(ii).dir, DetectTemplates(ii).ext, DetectTemplates(ii).name);
end

save('..\includes_TSR\DetectTemplates.mat', 'DetectTemplates');     %#ok<*NASGU>

end

function im_out = detection_template(im_dir, im_ext, im_name)
% Prepares a template from a file

% Read the file
im_rgb = imread(strcat('../includes_TSR/',im_dir,'/',im_name,'.',im_ext),im_ext);

% Convert image
hcsc1 = video.ColorSpaceConverter;
hcsc1.Conversion = 'RGB to YCbCr';
im_ycbcr = step(hcsc1, im_rgb);
im_y  = im_ycbcr(:,:,1);
im_cr = im_ycbcr(:,:,3);

hcsc2 = video.ColorSpaceConverter;
hcsc2.Conversion = 'RGB to intensity';
im_int = step(hcsc2, im_rgb);

% Normalization
im_y   = (double(im_y  ) - 16) / 219;
im_cr  = (double(im_cr ) - 16) / 224;
im_int =  double(im_int)       / 255;

% Convert to binary
im_CrBin = im_cr > 0.55;

[nn, mm] = size(im_CrBin);
im_out = zeros(nn,mm);
for ii = 1 : nn
    for jj = 1 : mm
        if im_CrBin(ii,jj)
            im_out(ii,jj) = im_y(ii,jj);
        end
    end
end

% Resize image to accurate sign size
[ner, nec] = cutimage(im_out);
im_out = im_out(ner, nec);

% Resize (saves some simulation time)
im_out = imresize(im_out, [100 NaN]);

end