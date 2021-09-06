function TACombinations(FolderExpNameArray, PrescanExpNameArray, EgoNameArray, AutowareConfigArray, SimulinkConfigArray, TagsConfigArray, SHHConfig)
if not((length(FolderExpNameArray) == length(PrescanExpNameArray)) && (length(FolderExpNameArray) == length(EgoNameArray)))
    error('Error: FolderExpNameArray, PrescanExpNameArray and EgoNameArray must have the same length.')
end


numberOfColums = length(FolderExpNameArray)*length(AutowareConfigArray)*length(SimulinkConfigArray)*length(TagsConfigArray);

TAOrder = table('Size', [7 numberOfColums], 'VariableTypes', repelem("string", numberOfColums), 'RowNames', {'FolderExpName' 'PrescanExpName' 'EgoName' 'AutowareConfig' 'SimulinkConfig' 'TagsConfig' 'SHHConfig'});

c=1;
for C_Sce = 1:length(FolderExpNameArray)
    for C_Aut = 1:length(AutowareConfigArray)
        for C_Sim = 1:length(SimulinkConfigArray)
            for C_Tag = 1:length(TagsConfigArray)
                TAOrder{'folderExperiment',c} = FolderExpNameArray(C_Sce);
                TAOrder{'prescanExperiment',c} = PrescanExpNameArray(C_Sce);
                TAOrder{'EgoName',c} = EgoNameArray(C_Sce);
                TAOrder{'TARosParameters',c} = AutowareConfigArray(C_Aut);
                TAOrder{'TASimulinkParameters',c} = SimulinkConfigArray(C_Sim);
                TAOrder{'TagsConfig',c} = TagsConfigArray(C_Tag);
                TAOrder{'SHHConfig',c} = SHHConfig;

                c=c+1;
            end
        end
    end
end

cd('Configurations')

delete('TAOrder.xlsx') % to overwrite the preexisting file, without this line overlaps can occur if the previous table was bigger
writetable(TAOrder, 'TAOrder.xlsx', 'WriteRowNames', true, 'WriteVariableNames', false);
cd('..')

end


