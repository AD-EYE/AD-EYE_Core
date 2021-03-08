classdef PerlFile < builders.common.FileWriter
    %PERLFILE Create the perl_info.mk file
    
    properties
        endLine = [char(13) char(10)];
    end
    
    methods
        function self = PerlFile(name,installPath)
            self.openFile(name);
            if strcmpi(installPath,'host')
                perlExe = fullfile(matlabroot,'sys','perl','win32','bin','perl.exe');
                perlExe = RTW.transformPaths(perlExe);
            else
                perlExe = '<Perl executable undefined>';
            end
            self.writeLine('PERL = %s',perlExe);
            self.closeFile();
        end
    end
end
