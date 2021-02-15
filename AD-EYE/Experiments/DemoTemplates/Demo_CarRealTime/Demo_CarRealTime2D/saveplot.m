function obrazek(indexTime)
%#codgen
eml.extrinsic('sprintf');
eml.extrinsic('clock');
eml.extrinsic('gcf');
eml.extrinsic('mkdir');
eml.extrinsic('getframe');
eml.extrinsic('imwrite');
eml.extrinsic('findobj');

% a=getVariable('h_Rdlg','workspace')
hh=evalin('base','h_Rdlg');
dirout = sprintf('Results/Result_GUI');

Outputfilename1 = 'GUI';
%Outputfilename2 = 'fig';

fileout1 = sprintf('%s/%s_%05.0f.png',dirout,Outputfilename1, indexTime);
%fileout2 = sprintf('%s/%s_%05.0f.png',dirout,Outputfilename2, indexTime);

%=== GUI ===============================
h=findobj(hh,'name','AEBS Radar');
% h=findobj('name','AEBS_radar_graph')
% h=findobj('name','radar_guide_graph')
% h = findobj('Tag','figure 1');
im=getframe(h);
imwrite(im.cdata,fileout1);

%=== plot ==============================
%h = findobj('Name','radar_guide_graph');
%im=getframe(h);
%imwrite(im.cdata,fileout2);

end
