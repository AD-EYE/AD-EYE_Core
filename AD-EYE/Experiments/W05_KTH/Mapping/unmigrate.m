function unmigrate()
%UNMIGRATE restore original model from migration backup
backupfolder = '.\Migrated\version_201920_133005' ;
backupmodel  = 'W05_KTH_201920_133005_cs' ;
srcfolder    = '.' ;
srcmodel     = 'W05_KTH_cs' ;
mbxutils.backupModel(backupfolder,backupmodel,srcfolder,srcmodel); 
chdir('.');
open_system('W05_KTH_cs');
end
